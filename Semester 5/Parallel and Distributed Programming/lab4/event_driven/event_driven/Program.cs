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
        Console.WriteLine("Starting callback-based downloads...");

        var countdown = new CountdownEvent(Targets.Length);

        Stopwatch sw = Stopwatch.StartNew();

        foreach (var t in Targets)
        {
            var d = new CallbackDownloader(t.host, t.path, countdown);
            d.Start();
        }

        countdown.Wait();
        sw.Stop();

        Console.WriteLine("All downloads complete (callbacks).");
        Console.WriteLine($"Total time: {sw.ElapsedMilliseconds} ms");
    }
}

class CallbackDownloader
{
    const int BufferSize = 4096;

    public readonly string Host;
    public readonly string Path;
    readonly Socket _socket;
    readonly byte[] _buffer = new byte[BufferSize];
    readonly List<byte> _received = new List<byte>();
    readonly CountdownEvent _countdown;

    bool _headersParsed = false;
    int _contentLength = -1;
    int _bodyStartIndex = -1;

    public CallbackDownloader(string host, string path, CountdownEvent countdown)
    {
        Host = host;
        Path = path;
        _countdown = countdown;
        _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    }

    public void Start()
    {
        try
        {
            _socket.BeginConnect(Host, 80, OnConnected, null);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] BeginConnect threw: {ex.Message}");
            Finish();
        }
    }

    void OnConnected(IAsyncResult ar)
    {
        try
        {
            _socket.EndConnect(ar);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] Connect failed: {ex.Message}");
            Finish();
            return;
        }

        string request = $"GET {Path} HTTP/1.1\r\nHost: {Host}\r\nConnection: close\r\n\r\n";
        byte[] reqBytes = Encoding.ASCII.GetBytes(request);
        try
        {
            _socket.BeginSend(reqBytes, 0, reqBytes.Length, SocketFlags.None, OnSent, null);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] BeginSend threw: {ex.Message}");
            Finish();
        }
    }

    void OnSent(IAsyncResult ar)
    {
        try
        {
            int sent = _socket.EndSend(ar);
            _socket.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnReceive, null);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] Send failed: {ex.Message}");
            Finish();
        }
    }

    void OnReceive(IAsyncResult ar)
    {
        int bytes;
        try
        {
            bytes = _socket.EndReceive(ar);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] Receive error: {ex.Message}");
            Finish();
            return;
        }

        if (bytes <= 0)
        {
            TryFinalizeAndSave();
            Finish();
            return;
        }

        for (int i = 0; i < bytes; i++) _received.Add(_buffer[i]);

        if (!_headersParsed)
        {
            TryParseHeaders();
        }

        if (_headersParsed && _contentLength >= 0)
        {
            int bodyBytesAvailable = _received.Count - _bodyStartIndex;
            if (bodyBytesAvailable >= _contentLength)
            {
                TryFinalizeAndSave();
                Finish();
                return;
            }
        }

        try
        {
            _socket.BeginReceive(_buffer, 0, _buffer.Length, SocketFlags.None, OnReceive, null);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] BeginReceive threw: {ex.Message}");
            Finish();
        }
    }

    void TryParseHeaders()
    {
        string receivedText;
        try
        {
            receivedText = Encoding.ASCII.GetString(_received.ToArray());
        }
        catch
        {
            return;
        }

        int idx = receivedText.IndexOf("\r\n\r\n", StringComparison.Ordinal);
        if (idx == -1) return;

        _headersParsed = true;
        _bodyStartIndex = idx + 4;

        string headers = receivedText.Substring(0, idx);
        var lines = headers.Split(new[] { "\r\n" }, StringSplitOptions.None);
        foreach (var line in lines)
        {
            int colon = line.IndexOf(':');
            if (colon <= 0) continue;
            string name = line.Substring(0, colon).Trim();
            string value = line.Substring(colon + 1).Trim();
            if (string.Equals(name, "Content-Length", StringComparison.OrdinalIgnoreCase))
            {
                if (int.TryParse(value, out int cl))
                {
                    _contentLength = cl;
                }
            }
        }
    }

    void TryFinalizeAndSave()
    {
        byte[] all = _received.ToArray();
        int bodyIndex = _bodyStartIndex >= 0 ? _bodyStartIndex : 0;
        int bodyLength;

        if (_headersParsed && _contentLength >= 0)
        {
            bodyLength = Math.Min(_contentLength, all.Length - bodyIndex);
        }
        else
        {
            bodyLength = Math.Max(0, all.Length - bodyIndex);
        }

        byte[] body = new byte[bodyLength];
        Array.Copy(all, bodyIndex, body, 0, bodyLength);

        string fileName = MakeSafeFileName(Host, Path);
        try
        {
            File.WriteAllBytes(fileName, body);
            Console.WriteLine($"[{Host}{Path}] Saved {bodyLength} bytes -> {fileName}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[{Host}{Path}] Save failed: {ex.Message}");
        }
    }

    void Finish()
    {
        try { _socket.Close(); } catch { }
        _countdown.Signal();
    }

    static string MakeSafeFileName(string host, string path)
    {
        string p = path;
        if (p == "/") p = "root";
        p = p.TrimStart('/').Replace('/', '_');

        if (p == "") p = "root";

        string fileName = $"{host}_{p}.txt";

        foreach (char c in System.IO.Path.GetInvalidFileNameChars())
            fileName = fileName.Replace(c, '_');

        return System.IO.Path.Combine("downloads", fileName);
    }
}
