Mutex globalMutex = new Mutex();
List<int> bankAccounts = new List<int>();
List<Thread> threads = new List<Thread>();
Random random = new Random();
int numberThreads = 0;
int numberAccounts = 0;
int globalTotal = 0;
Timer timer;

void SetUp()
{
    numberThreads = 20000;
    numberAccounts = 2000;
    for (int i = 0; i < numberAccounts; i++)
    {
        bankAccounts.Add(random.Next(1000, 10000));
        globalTotal += bankAccounts[i];
    }
}

void Transfer()
{
    int source = -1;
    int destination = -1;
    while (source == destination)
    {
        source = random.Next(numberAccounts);
        destination = random.Next(numberAccounts);
    }

    int amount = random.Next(500, 1500);

    globalMutex.WaitOne();
    if (bankAccounts[source] >= amount)
    {
        bankAccounts[source] -= amount;
        bankAccounts[destination] += amount;
        Console.WriteLine("Moved " + amount + " money from " + source + " to " + destination);
    }
    else
    {
        Console.WriteLine("Couldn't move " + amount + " money from " + source + " to " + destination);
    }
    globalMutex.ReleaseMutex();
}

void ConsistencyCheck(object? sender)
{
    int currentTotal = 0;
    globalMutex.WaitOne();
    for (int i = 0; i < numberAccounts; i++)
    {
        currentTotal += bankAccounts[i];
    }
    globalMutex.ReleaseMutex();

    if (currentTotal == globalTotal)
    {
        Console.WriteLine("Balance is the same");
    }
    else
    {
        Console.WriteLine("Balance is not the same");
    }
}

void Start()
{

    DateTime start = DateTime.Now;
    SetUp();
    timer = new Timer(ConsistencyCheck, null, 0, 50);
    for (int i = 0; i < numberThreads; i++)
    {
        threads.Add(new Thread(Transfer));
        threads[i].Start();
    }

    for (int i = 0; i < numberThreads; i++)
    {
        threads[i].Join();
    }
    timer.Dispose();
    ConsistencyCheck(null);
    globalMutex.Dispose();
    DateTime finish = DateTime.Now;
    Console.WriteLine("Final time: " + (finish - start));
}

Start();