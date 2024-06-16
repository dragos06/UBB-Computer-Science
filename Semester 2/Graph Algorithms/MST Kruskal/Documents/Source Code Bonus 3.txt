from collections import defaultdict


class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = defaultdict(list)

    def add_edge(self, u, v, cost):
        # (v, cost) is a tuple representing the edge from u to v with cost
        self.graph[u].append((v, cost))

    def sort_topological_utility(self, v, visited, stack):
        # Mark the current node as visited
        visited[v] = True
        # Recur for all the vertices adjacent to this vertex
        for neighbor, _ in self.graph[v]:
            if not visited[neighbor]:
                self.sort_topological_utility(neighbor, visited, stack)
        # Push current vertex to stack which stores the result
        stack.append(v)

    def sort_topological(self):
        # Mark all the vertices as not visited
        visited = [False] * self.vertices
        # Initialize an empty stack
        stack = []
        # Call the recursive helper function to store Topological Sort starting from all vertices one by one
        for i in range(self.vertices):
            if not visited[i]:
                self.sort_topological_utility(i, visited, stack)
        return stack[::-1]

    def paths_nr(self, s, t):
        # Initialize the distance array with infinity and the number of paths array with 0
        dist = [float('inf')] * self.vertices
        paths = [0] * self.vertices
        dist[s] = 0
        paths[s] = 1

        # Get the topological order of the vertices
        top_order = self.sort_topological()

        # Update the distance and number of paths arrays
        for u in top_order:
            for v, cost in self.graph[u]:
                # Relax the edge
                if dist[u] + cost < dist[v]:
                    dist[v] = dist[u] + cost
                    paths[v] = paths[u]
                # If there is more than one shortest path
                elif dist[u] + cost == dist[v]:
                    paths[v] += paths[u]

        return paths[t]


def load_from_file(filename):
    # Read the graph from the file
    with open(filename, 'r') as file:
        lines = file.readlines()
        vertices = int(lines[0])
        graph = Graph(vertices)
        for line in lines[1:]:
            u, v, cost = map(int, line.split())
            graph.add_edge(u, v, cost)
    return graph


def main():
    # Load the graph from the file
    filename = input("Please enter the filename: ")
    graph = load_from_file(filename)

    # Check if the graph is a Directed Acyclic Graph
    topological = graph.sort_topological()
    if len(topological) == graph.vertices:
        print("Topological Sorting:")
        print(topological)
        s = int(input("Enter source vertex: "))
        t = int(input("Enter target vertex: "))
        distinct_paths = graph.paths_nr(s, t)
        print(f"Number of distinct lowest cost paths between {s} and {t}: {distinct_paths}")
    else:
        print("The graph is not a Directed Acyclic Graph.")


if __name__ == "__main__":
    main()
