import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

class ForkJoinSolver implements HamiltonianSolver {
    private final DirectedGraph graph;
    private final ForkJoinPool pool;

    public ForkJoinSolver(DirectedGraph graph) {
        this.graph = graph;
        this.pool = new ForkJoinPool(); 
    }

    @Override
    public List<Integer> solve(int startVertex) {
        boolean[] visited = new boolean[graph.getNumVertices()];
        visited[startVertex] = true;
        List<Integer> path = new ArrayList<>();
        path.add(startVertex);

        HamiltonianTask rootTask = new HamiltonianTask(startVertex, visited, path);
        return pool.invoke(rootTask);
    }

    private class HamiltonianTask extends RecursiveTask<List<Integer>> {
        private final int current;
        private final boolean[] visited;
        private final List<Integer> path;

        public HamiltonianTask(int current, boolean[] visited, List<Integer> path) {
            this.current = current;
            this.visited = visited;
            this.path = path;
        }

        @Override
        protected List<Integer> compute() {
            
            if (path.size() == graph.getNumVertices()) {
                if (graph.getNeighbors(current).contains(path.get(0))) {
                    List<Integer> fullPath = new ArrayList<>(path);
                    fullPath.add(path.get(0));
                    return fullPath;
                }
                return null;
            }

            List<Integer> validNeighbors = new ArrayList<>();
            for (int n : graph.getNeighbors(current)) {
                if (!visited[n]) validNeighbors.add(n);
            }

            List<HamiltonianTask> subTasks = new ArrayList<>();

            for (int neighbor : validNeighbors) {
                
                boolean[] newVisited = visited.clone();
                newVisited[neighbor] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(neighbor);

                HamiltonianTask task = new HamiltonianTask(neighbor, newVisited, newPath);
                subTasks.add(task);
                task.fork();
            }

            for (HamiltonianTask task : subTasks) {
                List<Integer> result = task.join();
                if (result != null) {
                    return result;
                }
            }

            return null;
        }
    }
}