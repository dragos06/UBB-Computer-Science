void main() {
    int V = 20;
    DirectedGraph graph = generateRandomHamiltonianGraph(V, 0.5);

    IO.println("Graph generated with " + V + " vertices.");

    long start = System.currentTimeMillis();
    HamiltonianSolver threadedSolver = new ThreadedSolver(graph, 8); 
    List<Integer> path1 = threadedSolver.solve(0);
    long end = System.currentTimeMillis();
    IO.println("Threaded Solver Time: " + (end - start) + "ms");
    IO.println("Result: " + (path1 != null ? "Found" : "Not Found"));
    if (path1 != null) IO.println(path1);

    start = System.currentTimeMillis();
    HamiltonianSolver fjSolver = new ForkJoinSolver(graph);
    List<Integer> path2 = fjSolver.solve(0);
    end = System.currentTimeMillis();

    IO.println("ForkJoin Solver Time: " + (end - start) + "ms");
    IO.println("Result: " + (path2 != null ? "Found" : "Not Found"));
    if (path2 != null) IO.println(path2);
}

private static DirectedGraph generateRandomHamiltonianGraph(int V, double density) {
    DirectedGraph g = new DirectedGraph(V);

    Random rand = new Random();
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j && rand.nextDouble() < density) {
                g.addEdge(i, j);
            }
        }
    }
    return g;
}