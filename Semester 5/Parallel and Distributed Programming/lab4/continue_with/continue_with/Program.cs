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

    static void Main()
    {
        Directory.CreateDirectory("downloads");
        Console.WriteLine("Starting Task-based downloads...");

        Stopwatch sw = Stopwatch.StartNew();

        List<Task> allTasks = new List<Task>();

        foreach (var t in Targets)
        {
            allTasks.Add(TaskDownloader.DownloadAsync(t.host, t.path));
        }

        Task.WaitAll(allTasks.ToArray());

        sw.Stop();
        Console.WriteLine("All downloads complete (Tasks + ContinueWith).");
        Console.WriteLine($"Total time: {sw.ElapsedMilliseconds} ms");
    }
}

class TaskDownloader
{
    const int BufferSize = 4096;

    public static Task DownloadAsync(string host, string path)
    {
        var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        var buffer = new byte[BufferSize];
        var received = new List<byte>();

        int contentLength = -1;
        int bodyStartIndex = -1;
        bool headersParsed = false;

        var tcsConnect = new TaskCompletionSource<bool>();

        socket.BeginConnect(host, 80, ar =>
        {
            try
            {
                socket.EndConnect(ar);
                tcsConnect.SetResult(true);
            }
            catch (Exception ex)
            {
                tcsConnect.SetException(ex);
            }
        }, null);

        return tcsConnect.Task.ContinueWith(_ =>
        {
            string request = $"GET {path} HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n";
            byte[] reqBytes = Encoding.ASCII.GetBytes(request);
            var tcsSend = new TaskCompletionSource<int>();
            socket.BeginSend(reqBytes, 0, reqBytes.Length, SocketFlags.None, ar =>
            {
                try
                {
                    int sent = socket.EndSend(ar);
                    tcsSend.SetResult(sent);
                }
                catch (Exception ex)
                {
                    tcsSend.SetException(ex);
                }
            }, null);
            return tcsSend.Task;
        }).Unwrap().ContinueWith(_ =>
        {
            var tcsReceive = new TaskCompletionSource<bool>();

            void ReceiveLoop()
            {
                socket.BeginReceive(buffer, 0, buffer.Length, SocketFlags.None, ar =>
                {
                    int bytes;
                    try
                    {
                        bytes = socket.EndReceive(ar);
                    }
                    catch (Exception ex)
                    {
                        tcsReceive.SetException(ex);
                        return;
                    }

                    if (bytes <= 0)
                    {
                        tcsReceive.SetResult(true);
                        return;
                    }

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
                        if (bodyBytes >= contentLength)
                        {
                            tcsReceive.SetResult(true);
                            return;
                        }
                    }

                    ReceiveLoop();

                }, null);
            }

            ReceiveLoop();
            return tcsReceive.Task;
        }).Unwrap().ContinueWith(_ =>
        {
            byte[] all = received.ToArray();
            int bodyIndex = bodyStartIndex >= 0 ? bodyStartIndex : 0;
            int bodyLength = headersParsed && contentLength >= 0 ? Math.Min(contentLength, all.Length - bodyIndex) : Math.Max(0, all.Length - bodyIndex);
            byte[] body = new byte[bodyLength];
            Array.Copy(all, bodyIndex, body, 0, bodyLength);

            string fileName = MakeSafeFileName(host, path);
            try
            {
                File.WriteAllBytes(fileName, body);
                Console.WriteLine($"[{host}{path}] Saved {bodyLength} bytes -> {fileName}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[{host}{path}] Save failed: {ex.Message}");
            }
            try { socket.Close(); } catch { }
        });
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
