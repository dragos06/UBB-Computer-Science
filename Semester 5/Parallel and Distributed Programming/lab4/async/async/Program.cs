using System.Net.Sockets;
using System.Text;
using System.Diagnostics;

class Program
{
    static readonly (string host, string path)[] Targets = new[]
    {
        ("textfiles.com", "/stories/wlgirl.txt"),
        ("textfiles.com", "/stories/yukon.txt"),
        ("textfiles.com", "/stories/vainsong.txt"),
        ("textfiles.com", "/stories/silverb.txt"),
        ("textfiles.com", "/stories/frum"),
        ("textfiles.com", "/stories/mario.txt"),
        ("textfiles.com", "/stories/mindprob.txt"),
        ("textfiles.com", "/stories/vampword.txt"),
        ("textfiles.com", "/stories/pepsi.degenerat"),
        ("textfiles.com", "/stories/fred.txt")
    };

    static async Task Main()
    {
        Directory.CreateDirectory("downloads");
        Console.WriteLine("Starting async/await downloads...");

        Stopwatch sw = Stopwatch.StartNew();

        var tasks = new List<Task>();
        foreach (var t in Targets)
        {
            tasks.Add(AsyncDownloader.DownloadAsync(t.host, t.path));
        }

        await Task.WhenAll(tasks);

        sw.Stop();
        Console.WriteLine("All downloads complete (async/await).");
        Console.WriteLine($"Total time: {sw.ElapsedMilliseconds} ms");
    }
}

class AsyncDownloader
{
    const int BufferSize = 4096;

    public static async Task DownloadAsync(string host, string path)
    {
        var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        var buffer = new byte[BufferSize];
        var received = new List<byte>();

        int contentLength = -1;
        int bodyStartIndex = -1;
        bool headersParsed = false;

        try
        {
            await ConnectAsync(socket, host, 80);

            string request = $"GET {path} HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n";
            byte[] reqBytes = Encoding.ASCII.GetBytes(request);
            await SendAsync(socket, reqBytes);

            while (true)
            {
                int bytes = await ReceiveAsync(socket, buffer);
                if (bytes <= 0) break;

                for (int i = 0; i < bytes; i++) received.Add(buffer[i]);

                if (!headersParsed)
                {
                    string text = Encoding.ASCII.GetString(received.ToArray());
                    int idx = text.IndexOf("\r\n\r\n", StringComparison.Ordinal);
                    if (idx != -1)
                    {
                        headersParsed = true;
                        bodyStartIndex = idx + 4;
                        var headerLines = text.Substring(0, idx).Split(new[] { "\r\n" }, StringSplitOptions.None);
                        foreach (var line in headerLines)
                        {
                            int colon = line.IndexOf(':');
                            if (colon <= 0) continue;
                            string name = line.Substring(0, colon).Trim();
                            string value = line.Substring(colon + 1).Trim();
                            if (string.Equals(name, "Content-Length", StringComparison.OrdinalIgnoreCase))
                            {
                                int.TryParse(value, out contentLength);
                            }
                        }
                    }
                }

                if (headersParsed && contentLength >= 0)
                {
                    int bodyBytes = received.Count - bodyStartIndex;
                    if (bodyBytes >= contentLength) break;
                }
            }

            byte[] all = received.ToArray();
            int bodyIndex = bodyStartIndex >= 0 ? bodyStartIndex : 0;
            int bodyLength = headersParsed && contentLength >= 0 ? Math.Min(contentLength, all.Length - bodyIndex) : Math.Max(0, all.Length - bodyIndex);
            byte[] body = new byte[bodyLength];
            Array.Copy(all, bodyIndex, body, 0, bodyLength);

            string fileName = MakeSafeFileName(host, path);
            File.WriteAllBytes(fileName, body);
            Console.WriteLine($"[{host}{path}] Saved {bodyLength} bytes -> {fileName}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{host}{path}] Error: {ex.Message}");
        }
        finally
        {
            try { socket.Close(); } catch { }
        }
    }

    static Task ConnectAsync(Socket socket, string host, int port)
    {
        var tcs = new TaskCompletionSource<bool>();
        socket.BeginConnect(host, port, ar =>
        {
            try
            {
                socket.EndConnect(ar);
                tcs.SetResult(true);
            }
            catch (Exception ex) { tcs.SetException(ex); }
        }, null);
        return tcs.Task;
    }

    static Task SendAsync(Socket socket, byte[] data)
    {
        var tcs = new TaskCompletionSource<int>();
        socket.BeginSend(data, 0, data.Length, SocketFlags.None, ar =>
        {
            try
            {
                int sent = socket.EndSend(ar);
                tcs.SetResult(sent);
            }
            catch (Exception ex) { tcs.SetException(ex); }
        }, null);
        return tcs.Task;
    }

    static Task<int> ReceiveAsync(Socket socket, byte[] buffer)
    {
        var tcs = new TaskCompletionSource<int>();
        socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ar =>
        {
            try
            {
                int bytes = socket.EndReceive(ar);
                tcs.SetResult(bytes);
            }
            catch (Exception ex) { tcs.SetException(ex); }
        }, null);
        return tcs.Task;
    }

    static string MakeSafeFileName(string host, string path)
    {
        string p = path;
        if (p == "/") p = "root";
        p = p.TrimStart('/').Replace('/', '_');
        if (p == "") p = "root";
        string fileName = $"{host}_{p}.txt";
        foreach (char c in Path.GetInvalidFileNameChars())
            fileName = fileName.Replace(c, '_');
        return Path.Combine("downloads", fileName);
    }
}
