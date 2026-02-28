import java.util.*;
import java.util.concurrent.*;

class DirectedGraph {
    private final int numVertices;
    private final List<List<Integer>> adjList;

    public DirectedGraph(int numVertices) {
        this.numVertices = numVertices;
        this.adjList = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; i++) {
            this.adjList.add(new ArrayList<>());
        }
    }

    public void addEdge(int src, int dest) {
        adjList.get(src).add(dest);
    }

    public List<Integer> getNeighbors(int v) {
        return adjList.get(v);
    }

    public int getNumVertices() {
        return numVertices;
    }
}
