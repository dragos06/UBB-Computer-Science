import math


class Graph:
    def __init__(self, vertices=0):
        self.__vertices = vertices
        self.__dict_in = {}
        self.__dict_out = {}
        self.__dict_cost = {}
        for i in range(0, self.__vertices):
            self.__dict_in[i] = []
            self.__dict_out[i] = []

    @property
    def vertices(self):
        """
        Getter for the number of vertices
        :return: The number of vertices
        """
        return self.__vertices

    @vertices.setter
    def vertices(self, value):
        """
        Setter for the number of vertices
        :param value: The new number of vertices
        :return: The new number of vertices
        """
        self.__vertices = value

    def is_vertex(self, vertex):
        """
        Checks if a vertex exists
        :param vertex: The vertex to be checked
        :return: True if the vertex exists, False otherwise
        """
        return vertex in self.__dict_in.keys() and vertex in self.__dict_out.keys()

    def is_edge(self, vertex_x, vertex_y):
        """
        Checks if an edge exists
        :param vertex_x: The first vertex
        :param vertex_y: The second vertex
        :raises: ValueError: If the first vertex does not exist
        :raises: ValueError: If the second vertex does not exist
        :return: True if the edge exists, False otherwise
        """
        if not self.is_vertex(vertex_x):
            raise ValueError(f"Vertex {vertex_x} does not exist")
        if not self.is_vertex(vertex_y):
            raise ValueError(f"Vertex {vertex_y} does not exist")
        return vertex_x in self.__dict_in[vertex_y] and vertex_y in self.__dict_out[vertex_x]

    def add_vertex(self, vertex):
        """
        Adds a vertex to the graph
        :param vertex: The vertex to be added
        :raises ValueError: If the vertex already exists
        """
        if self.is_vertex(vertex):
            raise ValueError("Vertex already exists")
        self.__dict_in[vertex] = []
        self.__dict_out[vertex] = []
        self.__vertices += 1

    def add_edge(self, vertex_x, vertex_y, cost):
        """
        Adds an edge to the graph
        :param vertex_x: The first vertex
        :param vertex_y: The second vertex
        :param cost: The cost of the edge
        :raises ValueError: If the first vertex does not exist
        """
        if not self.is_vertex(vertex_x):
            raise ValueError("First vertex does not exist")
        if not self.is_vertex(vertex_y):
            raise ValueError("Second vertex does not exist")
        if self.is_edge(vertex_x, vertex_y):
            raise ValueError("Edge already exists")
        self.__dict_in[vertex_x].append(vertex_y)
        self.__dict_in[vertex_y].append(vertex_x)
        self.__dict_out[vertex_x].append(vertex_y)
        self.__dict_out[vertex_y].append(vertex_x)
        self.__dict_cost[(vertex_x, vertex_y)] = cost
        self.__dict_cost[(vertex_y, vertex_x)] = cost

    def return_dict_cost(self):
        """
        Returns the dictionary of costs
        :return: The dictionary of costs
        """
        return self.__dict_cost.items()

    def parse_vertices_out(self, vertex):
        """
        Parses the outbound vertices of a vertex
        :param vertex: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The list of outbound vertices
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist")
        return list(self.__dict_out[vertex])

    def parse_vertices_in(self, vertex):
        """
        Parses the inbound vertices of a vertex
        :param vertex: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The list of inbound vertices
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist")
        return list(self.__dict_in[vertex])

    def parse_vertices(self):
        """
        Parses the vertices of the graph
        :return: The list of vertices
        """
        return list(self.__dict_in.keys())

    def in_degree(self, vertex):
        """
        Returns the in degree of a vertex
        :param vertex: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The in degree of the vertex
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist")
        return len(self.__dict_in[vertex])

    def out_degree(self, vertex):
        """
        Returns the out degree of a vertex
        :param vertex: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The out degree of the vertex
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist")
        return len(self.__dict_out[vertex])

    def parse_outbound_edges(self, vertex_x):
        """
        Parses the outbound edges of a vertex
        :param vertex_x: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The list of outbound edges
        """
        if not self.is_vertex(vertex_x):
            raise ValueError("Vertex does not exist")
        outbound_edges = []
        for vertex_y in self.parse_vertices_out(vertex_x):
            outbound_edges.append((vertex_x, vertex_y))
        return list(outbound_edges)

    def parse_inbound_edges(self, vertex_y):
        """
        Parses the inbound edges of a vertex
        :param vertex_y: The vertex
        :raises ValueError: If the vertex does not exist
        :return: The list of inbound edges
        """
        if not self.is_vertex(vertex_y):
            raise ValueError("Vertex does not exist")
        inbound_edges = []
        for vertex_x in self.parse_vertices_in(vertex_y):
            inbound_edges.append((vertex_x, vertex_y))
        return list(inbound_edges)

    def get_edge_cost(self, vertex_x, vertex_y):
        """
        Returns the cost of an edge
        :param vertex_x: The first vertex
        :param vertex_y: The second vertex
        :raises ValueError: If the first vertex does not exist
        :raises ValueError: If the second vertex does not exist
        :raises ValueError: If the edge does not exist
        :return: The cost of the edge
        """
        if not self.is_vertex(vertex_x):
            raise ValueError("First vertex does not exist")
        if not self.is_vertex(vertex_y):
            raise ValueError("Second vertex does not exist")
        if not self.is_edge(vertex_x, vertex_y):
            raise ValueError("Edge does not exist")
        return self.__dict_cost[(vertex_x, vertex_y)]

    def modify_edge_cost(self, vertex_x, vertex_y, value):
        """
        Returns the cost of an edge
        :param vertex_x: The first vertex
        :param vertex_y: The second vertex
        :param value: The new value of the edge
        :raises ValueError: If the first vertex does not exist
        :raises ValueError: If the second vertex does not exist
        :raises ValueError: If the edge does not exist
        :return: The cost of the edge
        """
        if not self.is_vertex(vertex_x):
            raise ValueError("First vertex does not exist")
        if not self.is_vertex(vertex_y):
            raise ValueError("Second vertex does not exist")
        if not self.is_edge(vertex_x, vertex_y):
            raise ValueError("Edge does not exist")
        self.__dict_cost[(vertex_x, vertex_y)] = value

    def remove_vertex(self, vertex):
        """
        Removes a vertex from the graph
        :param vertex: The vertex to be removed
        :raises ValueError: If the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist")
        for vertex_y in self.parse_vertices_out(vertex):
            self.__dict_in[vertex_y].remove(vertex)
            self.__dict_cost.pop((vertex, vertex_y))
        for vertex_x in self.parse_vertices_in(vertex):
            self.__dict_out[vertex_x].remove(vertex)
            self.__dict_cost.pop((vertex_x, vertex))
        self.__dict_in.pop(vertex)
        self.__dict_out.pop(vertex)
        self.__vertices -= 1

    def remove_edge(self, vertex_x, vertex_y):
        """
        Removes an edge from the graph
        :param vertex_x: The first vertex
        :param vertex_y: The second vertex
        :raises ValueError: If the first vertex does not exist
        :raises ValueError: If the second vertex does not exist
        :raises ValueError: If the edge does not exist
        """
        if not self.is_vertex(vertex_x):
            raise ValueError("First vertex does not exist")
        if not self.is_vertex(vertex_y):
            raise ValueError("Second vertex does not exist")
        if not self.is_edge(vertex_x, vertex_y):
            raise ValueError("Edge does not exist")
        self.__dict_out[vertex_x].remove(vertex_y)
        self.__dict_in[vertex_y].remove(vertex_x)
        self.__dict_cost.pop((vertex_x, vertex_y))

    def nr_vertices(self):
        """
        Returns the number of vertices
        :return: The number of vertices
        """
        return self.vertices

    def nr_edges(self):
        """
        Returns the number of edges
        :return: The number of edges
        """
        return len(self.__dict_cost)

    def read_graph_from_file(self, read_file_name):
        """
        Reads a graph from a file
        :param read_file_name: the name of the file
        """
        with open(read_file_name, 'r') as file:
            first_line = file.readline().split()
            # First case, when the graph is not modified
            if len(first_line) == 2:
                vertices, edges = first_line
                lines = file.readlines()
                for line in lines:
                    vertex_x, vertex_y, cost = line.strip().split()
                    vertex_x = int(vertex_x)
                    vertex_y = int(vertex_y)
                    cost = int(cost)
                    if not self.is_vertex(vertex_x):
                        self.add_vertex(vertex_x)
                    if not self.is_vertex(vertex_y):
                        self.add_vertex(vertex_y)
                    self.add_edge(vertex_x, vertex_y, cost)
                for i in range(0, int(vertices)):
                    if not self.is_vertex(i):
                        self.add_vertex(i)
            # Second case, when the graph is modified and we need to use the second format
            elif len(first_line) == 3:
                vertex_x, vertex_y, cost = first_line
                vertex_x = int(vertex_x)
                vertex_y = int(vertex_y)
                cost = int(cost)
                # Vertex is isolated
                if vertex_y == -1:
                    self.add_vertex(vertex_x)
                # Vertex is not isolated, and we need to add the edge as well and the other vertices
                else:
                    if not self.is_vertex(vertex_x):
                        self.add_vertex(vertex_x)
                    if not self.is_vertex(vertex_y):
                        self.add_vertex(vertex_y)
                    self.add_edge(vertex_x, vertex_y, cost)
                lines = file.readlines()
                for line in lines:
                    vertex_x, vertex_y, cost = line.strip().split()
                    vertex_x = int(vertex_x)
                    vertex_y = int(vertex_y)
                    cost = int(cost)
                    # Vertex is isolated
                    if vertex_y == -1:
                        self.add_vertex(vertex_x)
                    # Vertex is not isolated, and we need to add the edge as well and the other vertices
                    else:
                        if not self.is_vertex(vertex_x):
                            self.add_vertex(vertex_x)
                        if not self.is_vertex(vertex_y):
                            self.add_vertex(vertex_y)
                        self.add_edge(vertex_x, vertex_y, cost)

    def write_graph_to_file(self, write_file_name):
        """
        Writes a graph to a file
        :param write_file_name: The name of the file
        """
        file = open(write_file_name, 'w')
        isolated = False
        for vertex in self.__dict_in.keys():
            if len(self.__dict_out[vertex]) == 0 and len(self.__dict_in[vertex]) == 0:
                isolated = True
        if isolated:
            for vertex_x in self.__dict_out.keys():
                # First case, we need to write -1 -1 to know that the vertex is isolated when reading the graph
                if len(self.__dict_out[vertex_x]) == 0 and len(self.__dict_in[vertex_x]) == 0:
                    file.write(f"{vertex_x} {-1} {-1}\n")
                # Second case, we need to write the edge
                else:
                    for vertex_y in self.__dict_out[vertex_x]:
                        cost = self.__dict_cost[(vertex_x, vertex_y)]
                        file.write(f"{vertex_x} {vertex_y} {cost}\n")
        else:
            file.write(f"{self.vertices} {self.nr_edges()}\n")
            for edge, cost in self.return_dict_cost():
                vertex_x, vertex_y = edge
                file.write(f"{vertex_x} {vertex_y} {cost}\n")
        file.close()

    def rev_bfs(self, t):
        """
        Reverse BFS algorithm
        :param t: the target vertex
        :return: a dictionary with the next vertex and a dictionary with the distance
        """
        if not self.is_vertex(t):
            raise ValueError("Target is not a vertex")
        queue = [t]
        next_v = dict()
        dist = dict()
        visited = set()

        # Initialize the dictionaries
        visited.add(t)
        dist[t] = 0
        # While the queue is not empty
        while len(queue) > 0:
            # Get the first element
            y = queue[0]
            queue.pop(0)
            # For each vertex connected to y
            for x in self.__dict_in[y]:
                # If the vertex is not visited
                if x not in visited:
                    # Add it to the queue, mark it as visited, set the distance and the next vertex
                    queue.append(x)
                    visited.add(x)
                    dist[x] = dist[y] + 1
                    next_v[x] = y
        return next_v, dist

    def matrix_multiplication(self):
        # Variable to store the number of vertices
        n = len(list(self.parse_vertices()))
        # Weight matrix
        w = {}
        # Previous matrix
        prev = {}
        # Initialize the matrices
        for vertex_x in sorted(self.parse_vertices()):
            for vertex_y in sorted(self.parse_vertices()):
                # If the vertices are the same, the cost is 0 and the previous vertex is None
                if vertex_x == vertex_y:
                    w[vertex_x, vertex_y] = 0
                    prev[vertex_x, vertex_y] = None
                # If the edge exists, the cost is the cost of the edge and the previous vertex is the first vertex
                elif self.is_edge(vertex_x, vertex_y):
                    w[vertex_x, vertex_y] = self.get_edge_cost(vertex_x, vertex_y)
                    prev[vertex_x, vertex_y] = vertex_x
                # If the edge does not exist, the cost is infinity
                else:
                    w[vertex_x, vertex_y] = math.inf
        # Exponentiation by squaring
        k = 1
        # Initialize the intermediate matrices
        inter_w = [w]
        while k < n:
            next_w = {}
            next_p = {}
            for vertex_x in sorted(self.parse_vertices()):
                for vertex_y in sorted(self.parse_vertices()):
                    next_w[vertex_x, vertex_y] = math.inf
                    for z in self.parse_vertices():
                        # If the cost is smaller, update the cost and the previous vertex
                        if next_w[vertex_x, vertex_y] > w[vertex_x, z] + w[z, vertex_y]:
                            next_w[vertex_x, vertex_y] = w[vertex_x, z] + w[z, vertex_y]
                            # If both weights are different, the previous vertex is the previous vertex of z,y
                            if next_w[vertex_x, vertex_y] != w[vertex_x, vertex_y]:
                                next_p[vertex_x, vertex_y] = prev[z, vertex_y]
                            # If both weights are the same, the previous vertex is the previous vertex of x,y
                            else:
                                next_p[vertex_x, vertex_y] = prev[vertex_x, vertex_y]
                    # If the cost is infinity and the vertices are the same, we have negative cost cycle, return None
                    if next_w[vertex_x, vertex_y] < 0 and vertex_x == vertex_y:
                        return None
            # Append the intermediate matrix
            inter_w.append(next_w)
            # Squaring the exponent
            k = k * 2
            # Update the matrices
            w = next_w
            prev = next_p
        # Return the weight matrix, the previous matrix and the intermediate matrix
        return w, prev, inter_w

    def kruskal_alg(self):
        """
        Kruskal algorithm
        :return: a list of edges
        """
        # Initialize the list of edges
        edges = []
        # Initialize the list of sets
        sets = []
        # Initialize the list of edges
        for vertex in self.parse_vertices():
            sets.append({vertex})
            for vertex_y in self.parse_vertices_out(vertex):
                if vertex < vertex_y:
                    edges.append((vertex, vertex_y, self.get_edge_cost(vertex, vertex_y)))
        # Sort the edges by cost
        edges = sorted(edges, key=lambda x: (x[2], x[0], x[1]))
        # Initialize the list of spanning tree
        spanning_tree = []
        # For each edge
        for edge in edges:
            vertex_x, vertex_y, cost = edge
            set_x = -1
            set_y = -1
            # Find the set of the first vertex
            for i in range(len(sets)):
                if vertex_x in sets[i]:
                    set_x = i
                    break
            # Find the set of the second vertex
            for i in range(len(sets)):
                if vertex_y in sets[i]:
                    set_y = i
                    break
            # If the sets are different, add the edge to the spanning tree
            if set_x != set_y:
                spanning_tree.append((vertex_x, vertex_y, cost))
                # Merge the sets
                sets[set_x] = sets[set_x].union(sets[set_y])
                sets.pop(set_y)
        if len(spanning_tree) == len(self.parse_vertices()) - 1:
            return spanning_tree
        return None

    def dfs(self, vertex, visited, path):

        visited.add(vertex)
        path.append(vertex)
        for neighbor in self.__dict_out[vertex]:
            if neighbor not in visited:
                self.dfs(neighbor, visited, path)

    # def find_hamiltonian_cycle(self):
    #     mst = self.kruskal_alg()
    #     mst_graph = Graph(len(self.__dict_out))
    #     for u, v, cost in mst:
    #         mst_graph.add_edge(u, v, cost)
    #
    #     start_vertex = next(iter(self.__dict_out))
    #     visited = set()
    #     path = []
    #     mst_graph.dfs(start_vertex, visited, path)
    #     path.append(start_vertex)
    #
    #     # Shortcutting repeated vertices
    #     hamiltonian_cycle = []
    #     visited = set()
    #     for vertex in path:
    #         if vertex not in visited:
    #             visited.add(vertex)
    #             hamiltonian_cycle.append(vertex)
    #     hamiltonian_cycle.append(hamiltonian_cycle[0])  # to form a cycle
    #
    #     return hamiltonian_cycle

    # def choose(self, last, visited):
    #     """
    #     Function that chooses which point will be visited next
    #     :param last: The last visited vertex
    #     :param visited: List of visited vertices
    #     :return: The next vertex to be visited and the minimum cost to that vertex
    #     """
    #     # Initialize the minimum cost and the next vertex
    #     min_cost = float('inf')
    #     j_min = -1
    #     # For each vertex
    #     for j in self.parse_vertices():
    #         # If the vertex is not visited and there is an edge between the last vertex and the current vertex
    #         if not visited[j] and self.is_edge(last, j):
    #             # If the cost is smaller, update the minimum cost and the next vertex
    #             cost = self.get_edge_cost(last, j)
    #             if cost < min_cost:
    #                 min_cost = cost
    #                 j_min = j
    #     return j_min, min_cost
    #
    # def find_shortest_path(self):
    #     """
    #     Finds the shortest path using a heuristic approach
    #     :return: The shortest path and its cost
    #     """
    #
    #     save_cost = float('inf')
    #     save_path = []
    #
    #     for start in self.parse_vertices():
    #         # Initialize the variables
    #         visited = {v: False for v in self.parse_vertices()}
    #         path = [start]
    #         visited[start] = True
    #         count = 1
    #         cost = 0
    #
    #         # Choose the next vertex to visit
    #         for _ in range(self.nr_vertices() - 1):
    #             last = path[-1]
    #             next_vertex, min_cost = self.choose(last, visited)
    #             if next_vertex == -1:
    #                 break
    #             path.append(next_vertex)
    #             visited[next_vertex] = True
    #             cost += min_cost
    #
    #         # Add the cost to return to the start point
    #         if self.is_edge(path[-1], start):
    #             cost += self.get_edge_cost(path[-1], start)
    #             path.append(start)
    #
    #         # If the path is a Hamiltonian cycle
    #         if cost < save_cost:
    #             # Update the minimum cost and the path
    #             save_cost = cost
    #             save_path = path
    #
    #     return save_path, save_cost

    # def find_hamiltonian_cycle_double_tree(self):
    #     """
    #     Finds a Hamiltonian cycle with a cost of at most twice the minimum cost using the Double Tree algorithm
    #     :return: The Hamiltonian cycle and its cost
    #     """
    #     # Find the minimum spanning tree
    #     mst_edges = self.kruskal_alg()
    #     # If the graph is not connected
    #     if mst_edges is None:
    #         return None, None
    #     # Create a graph with the minimum spanning tree
    #     mst_graph = Graph(len(self.parse_vertices()))
    #     for u, v, cost in mst_edges:
    #         mst_graph.add_edge(u, v, cost)
    #
    #     # Find the Eulerian circuit/ Preorder traversal
    #     start_vertex = next(iter(self.parse_vertices()))
    #     visited = set()
    #     eulerian_circuit = []
    #     mst_graph.dfs(start_vertex, visited, eulerian_circuit)
    #     eulerian_circuit.append(start_vertex)
    #
    #     # Shortcutting repeated vertices
    #     hamiltonian_cycle = []
    #     visited = set()
    #     for vertex in eulerian_circuit:
    #         if vertex not in visited:
    #             visited.add(vertex)
    #             hamiltonian_cycle.append(vertex)
    #     hamiltonian_cycle.append(hamiltonian_cycle[0])  # to form a cycle
    #
    #     # Calculate the cost of the Hamiltonian cycle
    #     hamiltonian_cost = 0
    #     for i in range(len(hamiltonian_cycle) - 1):
    #         hamiltonian_cost += self.get_edge_cost(hamiltonian_cycle[i], hamiltonian_cycle[i + 1])
    #
    #     # Return the Hamiltonian cycle and its cost
    #     return hamiltonian_cycle, hamiltonian_cost

    def find_hamiltonian_cycle_double_tree(self):
        # Find the minimum spanning tree
        parent = [-1] * self.nr_vertices()
        min_cost = 0
        edges = [(cost, vertex_x, vertex_y) for (vertex_x, vertex_y), cost in self.__dict_cost.items()]
        edges.sort()

        # Kruskal's algorithm
        def find(vertex):
            if parent[vertex] == -1:
                return vertex
            return find(parent[vertex])

        def union(vertex_x, vertex_y):
            root_x = find(vertex_x)
            root_y = find(vertex_y)
            if root_x != root_y:
                parent[root_x] = root_y

        mst_edges = []
        for cost, vertex_x, vertex_y in edges:
            if find(vertex_x) != find(vertex_y):
                union(vertex_x, vertex_y)
                min_cost += cost
                mst_edges.append((vertex_x, vertex_y))

        mst_graph = Graph(self.nr_vertices())
        for vertex_x, vertex_y in mst_edges:
            mst_graph.add_edge(vertex_x, vertex_y, self.get_edge_cost(vertex_x, vertex_y))

        # Find the Eulerian circuit
        def dfs(v, visited, eulerian_circuit):
            visited[v] = True
            for neighbor in mst_graph.parse_vertices_out(v):
                if not visited[neighbor]:
                    dfs(neighbor, visited, eulerian_circuit)
            eulerian_circuit.append(v)

        eulerian_circuit = []
        visited = [False] * self.nr_vertices()
        dfs(0, visited, eulerian_circuit)
        eulerian_circuit = eulerian_circuit[::-1]

        # Shortcutting repeated vertices
        hamiltonian_cycle = []
        visited = [False] * self.nr_vertices()
        total_cost = 0
        for vertex in eulerian_circuit:
            if not visited[vertex]:
                if hamiltonian_cycle:
                    total_cost += self.get_edge_cost(hamiltonian_cycle[-1], vertex)
                hamiltonian_cycle.append(vertex)
                visited[vertex] = True
        total_cost += self.get_edge_cost(hamiltonian_cycle[-1], hamiltonian_cycle[0])
        hamiltonian_cycle.append(hamiltonian_cycle[0])

        return hamiltonian_cycle, total_cost

    def cond(self, sol):
        # Check if the current solution forms a valid cycle
        return len(sol) == self.vertices and sol[0] in self.parse_vertices_out(sol[-1])

    def back(self, sol, best_sol):
        # Perform backtracking to find the Hamiltonian cycle
        if self.cond(sol):
            return sol[:], min(best_sol, sol, key=lambda s: sum(self.get_edge_cost(s[i], s[i + 1]) for i in range(len(s) - 1) + [self.get_edge_cost(s[-1], s[0])]))

        # Add the neighbors of the last vertex in the solution
        for neighbor in self.parse_vertices_out(sol[-1]):
            if neighbor not in sol:
                sol.append(neighbor)
                best_sol = self.back(sol, best_sol)
                sol.pop()
        return best_sol

    def find_hamiltonian_cycle(self):
        # Find the Hamiltonian cycle using backtracking
        best_sol = None
        for vertex in self.parse_vertices():
            sol = [vertex]
            best_sol = self.back(sol, best_sol)
        return best_sol


def print_graph(graph):
    """
    Prints the whole graph
    :param graph: to be printed
    """
    print("Outbound:")
    for vertex_x in graph.parse_vertices():
        print(f"{vertex_x}: ", end='')
        for vertex_y in graph.parse_vertices_out(vertex_x):
            print(f" {vertex_y}", end='')
        print()

    print("Inbound:")
    for vertex_x in graph.parse_vertices():
        print(f"{vertex_x}: ", end='')
        for vertex_y in graph.parse_vertices_in(vertex_x):
            print(f" {vertex_y}", end='')
        print()
