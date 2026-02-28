import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

class ThreadedSolver implements HamiltonianSolver {
    private final DirectedGraph graph;
    private final int initialThreads;
    private final AtomicBoolean solutionFound = new AtomicBoolean(false);
    private volatile List<Integer> resultPath = null;

    public ThreadedSolver(DirectedGraph graph, int threadCount) {
        this.graph = graph;
        this.initialThreads = threadCount;
    }

    @Override
    public List<Integer> solve(int startVertex) {
        solutionFound.set(false);
        resultPath = null;

        List<Integer> path = new ArrayList<>();
        path.add(startVertex);
        boolean[] visited = new boolean[graph.getNumVertices()];
        visited[startVertex] = true;

        try {
            search(startVertex, visited, path, initialThreads);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        return resultPath;
    }

    private void search(int current, boolean[] visited, List<Integer> path, int threadsAvailable) throws InterruptedException {
        if (solutionFound.get()) return;

        if (path.size() == graph.getNumVertices()) {
            if (graph.getNeighbors(current).contains(path.get(0))) {
                
                if (solutionFound.compareAndSet(false, true)) {
                    List<Integer> finalPath = new ArrayList<>(path);
                    finalPath.add(path.get(0)); 
                    resultPath = finalPath;
                }
            }
            return;
        }

        List<Integer> neighbors = graph.getNeighbors(current);
        List<Integer> validNeighbors = new ArrayList<>();
        for (int n : neighbors) {
            if (!visited[n]) validNeighbors.add(n);
        }

        if (validNeighbors.isEmpty()) return;

        if (threadsAvailable <= 1 || validNeighbors.size() == 1) {
            
            for (int neighbor : validNeighbors) {
                if (solutionFound.get()) return;
                visited[neighbor] = true;
                path.add(neighbor);
                search(neighbor, visited, path, 1); 
                path.remove(path.size() - 1);
                visited[neighbor] = false;
            }
        } else {
            
            List<Thread> childThreads = new ArrayList<>();
            int k = validNeighbors.size();

            int q = threadsAvailable / k;
            int r = threadsAvailable % k;

            for (int i = 0; i < k; i++) {
                int neighbor = validNeighbors.get(i);
                
                int threadsForBranch = q + (i < r ? 1 : 0);

                boolean[] newVisited = visited.clone();
                newVisited[neighbor] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(neighbor);

                if (threadsForBranch > 0) {
                    Thread t = new Thread(() -> {
                        try {
                            search(neighbor, newVisited, newPath, threadsForBranch);
                        } catch (InterruptedException e) {
                            
                        }
                    });
                    childThreads.add(t);
                    t.start();
                }
                else {
                    search(neighbor, newVisited, newPath, 1);
                }
            }

            for (Thread t : childThreads) {
                t.join();
            }
        }
    }
}