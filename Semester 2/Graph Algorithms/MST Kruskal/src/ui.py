import src.graph
from src.graph import Graph
import random


class UI:
    def __init__(self):
        self.__graph = Graph()
        self.__copy_graph = Graph()

    @staticmethod
    def print_menu():
        print("\n     GRAPH APPLICATION")
        print("[1] Add vertex to graph")
        print("[2] Add edge to graph")
        print("[3] Remove vertex from graph")
        print("[4] Remove edge from graph")
        print("[5] Get the number of vertices")
        print("[6] Parse the set of vertices")
        print("[7] Check if there is an edge between 2 vertices")
        print("[8] Get the in degree of a vertex")
        print("[9] Get the out degree of a vertex")
        print("[10] Parse the set of outbound edges of a vertex")
        print("[11] Parse the set of inbound edges of a vertex")
        print("[12] Get the cost of an edge")
        print("[13] Modify the cost of an edge")
        print("[14] Copy graph")
        print("[15] Read the graph from a text file")
        print("[16] Write the modified graph to a text file")
        print("[17] Create a random graph")
        print("[18] Print graph")
        print("[19] Print copied graph")
        print("[20] Find the lowest length path between two vertices using a backward BFS")
        print("[21] Find the lowest cost walk between two given vertices")
        print("[22] Construct a minimal spanning tree using the Kruskal's algorithm")
        print("[0] Exit\n")

    def start_ui(self):
        while True:
            try:
                self.print_menu()
                user_option = input("Please choose an option: ")
                if user_option == '1':
                    self.add_vertex_ui()
                elif user_option == '2':
                    self.add_edge_ui()
                elif user_option == '3':
                    self.remove_vertex_ui()
                elif user_option == '4':
                    self.remove_edge_ui()
                elif user_option == '5':
                    self.number_vertices_ui()
                elif user_option == '6':
                    self.print_vertices_ui()
                elif user_option == '7':
                    self.is_edge_ui()
                elif user_option == '8':
                    self.in_degree_ui()
                elif user_option == '9':
                    self.out_degree_ui()
                elif user_option == '10':
                    self.parse_outbound_edges_ui()
                elif user_option == '11':
                    self.parse_inbound_edges_ui()
                elif user_option == '12':
                    self.get_edge_cost_ui()
                elif user_option == '13':
                    self.modify_edge_cost_ui()
                elif user_option == '14':
                    self.copy_graph_ui()
                elif user_option == '15':
                    self.read_from_file()
                elif user_option == '16':
                    self.write_to_file()
                elif user_option == '17':
                    self.create_random_graph()
                elif user_option == '18':
                    src.graph.print_graph(self.__graph)
                elif user_option == '19':
                    src.graph.print_graph(self.__copy_graph)
                elif user_option == '20':
                    self.rev_bfs_ui()
                elif user_option == '21':
                    self.min_cost_path_matrix_multiplication()
                elif user_option == '22':
                    self.spanning_tree_kruskal()
                elif user_option == '0':
                    print("Exiting...")
                    break
                else:
                    print("Invalid user option!")
            except ValueError as ve:
                print("Error occurred: ", ve)

    def add_vertex_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        self.__graph.add_vertex(vertex)

    def add_edge_ui(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isdecimal():
            raise ValueError("First vertex is not an integer")
        vertex_x = int(vertex_x)
        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isdecimal():
            raise ValueError("Second vertex is not an integer")
        vertex_y = int(vertex_y)
        cost = input("Please enter the cost of the edge: ")
        cost = int(cost)
        self.__graph.add_edge(vertex_x, vertex_y, cost)

    def remove_vertex_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        self.__graph.remove_vertex(vertex)

    def remove_edge_ui(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isdecimal():
            raise ValueError("First vertex is not an integer")
        vertex_x = int(vertex_x)
        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isdecimal():
            raise ValueError("Second vertex is not an integer")
        vertex_y = int(vertex_y)
        self.__graph.remove_edge(vertex_x, vertex_y)

    def number_vertices_ui(self):
        print("Number of vertices is: ", end='')
        print(self.__graph.nr_vertices())

    def print_vertices_ui(self):
        print("The vertices are: ", end='')
        for vertex in sorted(self.__graph.parse_vertices()):
            print(vertex, end=' ')

    def in_degree_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        print(self.__graph.in_degree(vertex))

    def out_degree_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        print(self.__graph.out_degree(vertex))

    def parse_outbound_edges_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        for edge in self.__graph.parse_outbound_edges(vertex):
            print(edge)

    def parse_inbound_edges_ui(self):
        vertex = input("Please enter the vertex: ")
        if not vertex.isdecimal():
            raise ValueError("Vertex is not an integer")
        vertex = int(vertex)
        for edge in self.__graph.parse_inbound_edges(vertex):
            print(edge)

    def get_edge_cost_ui(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isdecimal():
            raise ValueError("First vertex is not an integer")
        vertex_x = int(vertex_x)
        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isdecimal():
            raise ValueError("Second vertex is not an integer")
        vertex_y = int(vertex_y)
        print(self.__graph.get_edge_cost(vertex_x, vertex_y))

    def modify_edge_cost_ui(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isnumeric():
            raise ValueError("First vertex is not an integer")
        vertex_x = int(vertex_x)

        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isnumeric():
            raise ValueError("Second vertex is not an integer")
        vertex_y = int(vertex_y)

        value = input("Please enter the new value of the edge: ")
        if not value.isnumeric():
            raise ValueError("Value is not an integer")
        value = int(value)

        self.__graph.modify_edge_cost(vertex_x, vertex_y, value)

    def create_random_graph(self):
        vertices = input("Please enter the number of vertices: ")

        if not vertices.isnumeric():
            raise ValueError("Number of vertices must be an integer")
        vertices = int(vertices)

        edges = input("Please enter the number of edges: ")

        if not edges.isnumeric():
            raise ValueError("Number of edges must be an integer")
        edges = int(edges)

        if edges > vertices * (vertices - 1) + vertices:
            print("Cannot create graph with that many vertices"
                  f"Maximum number of vertices is {vertices * (vertices - 1) + vertices}")
            edges = vertices * (vertices - 1) + vertices

        graph = Graph(vertices)
        while edges:
            vertex_x = random.randint(0, vertices - 1)
            vertex_y = random.randint(0, vertices - 1)
            vertex_cost = random.randint(1, 100)
            if not graph.is_edge(vertex_x, vertex_y):
                graph.add_edge(vertex_x, vertex_y, vertex_cost)
                edges -= 1
        self.__graph = graph

    def read_from_file(self):
        self.__graph = Graph()
        file_name = input("Please give the file name: ")
        self.__graph.read_graph_from_file(file_name)

    def write_to_file(self):
        file_name = input("Please give the file name: ")
        self.__graph.write_graph_to_file(file_name)

    def is_edge_ui(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isnumeric():
            raise ValueError(f"First vertex must be an integer")
        vertex_x = int(vertex_x)

        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isnumeric():
            raise ValueError(f"Second vertex must be an integer")
        vertex_y = int(vertex_y)

        if self.__graph.is_edge(vertex_x, vertex_y):
            print("Edge exists")
        else:
            print("Edge does not exist")

    def copy_graph_ui(self):
        for vertex in self.__graph.parse_vertices():
            self.__copy_graph.add_vertex(vertex)
        for edge, cost in self.__graph.return_dict_cost():
            vertex_x, vertex_y = edge
            self.__copy_graph.add_edge(vertex_x, vertex_y, cost)

    def rev_bfs_ui(self):
        start = input("Please enter the starting vertex: ")
        if not start.isnumeric():
            raise ValueError(f"Starting vertex must be an integer")
        start = int(start)
        if not self.__graph.is_vertex(start):
            raise ValueError("Starting vertex is not a vertex")
        target = input("Please enter the target vertex: ")
        if not target.isnumeric():
            raise ValueError(f"Target vertex must be an integer")
        target = int(target)

        try:
            next_v, dist = self.__graph.rev_bfs(target)
            print(f"The lowest length path has distance = {dist[start]}")
            while start != target:
                print(start, end=" -> ")
                start = next_v[start]
            print(start)
        except KeyError:
            print("Cannot find lowest length path")

    def min_cost_path_matrix_multiplication(self):
        vertex_x = input("Please enter the first vertex: ")
        if not vertex_x.isnumeric():
            raise ValueError(f"First vertex must be an integer")
        vertex_x = int(vertex_x)

        vertex_y = input("Please enter the second vertex: ")
        if not vertex_y.isnumeric():
            raise ValueError(f"Second vertex must be an integer")
        vertex_y = int(vertex_y)

        source = vertex_x
        target = vertex_y

        result = self.__graph.matrix_multiplication()

        # If there is a negative cost cycle
        if result is None:
            print("There exist negative cost cycles")
        # If there is no negative cost cycle
        else:
            # Extract the result
            w, prev, inter = result
            # Reconstruction of the path
            path = []
            while target != source:
                path.append(target)
                target = prev[source, target]
            path.append(source)
            path.reverse()
            print("The minimum cost path is: ", path)
            print("The cost of the minimum cost path is: ", w[vertex_x, vertex_y])
            print("\nThe intermediate matrices:")
            # Print the intermediate matrices
            for inter_w in inter:
                for vertex_x in sorted(self.__graph.parse_vertices()):
                    for vertex_y in sorted(self.__graph.parse_vertices()):
                        print(inter_w[vertex_x, vertex_y], end=" ")
                    print()
                print()

    def spanning_tree_kruskal(self):
        spanning_tree = self.__graph.kruskal_alg()
        print("The minimal spanning tree is:")
        tree_cost = 0
        for edge in spanning_tree:
            vertex_x, vertex_y, cost = edge
            tree_cost += cost
            print(f"({vertex_x}, {vertex_y}) with cost {cost}")
        print(f"The cost of the minimal spanning tree is {tree_cost}")