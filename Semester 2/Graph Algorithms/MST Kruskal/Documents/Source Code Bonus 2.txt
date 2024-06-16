from collections import deque, defaultdict


def is_dag_and_topological_sort(graph, nr_vert):
    # Calculate in-degree of each vertex
    in_d = [0] * nr_vert
    for u in graph:
        for v in graph[u]:
            in_d[v] += 1

    # Initialize queue with vertices having in-degree 0
    queue = deque([u for u in range(nr_vert) if in_d[u] == 0])
    topological = []

    # Perform topological sort
    while queue:
        u = queue.popleft()
        topological.append(u)

        # Reduce in-degree of adjacent vertices
        for v in graph[u]:
            in_d[v] -= 1
            if in_d[v] == 0:
                queue.append(v)

    # Check if graph is a DAG
    if len(topological) == nr_vert:
        return True, topological
    else:
        return False, []


def count_paths_dag(graph, topological, start, target):
    # Initialize dp array
    num_vertices = len(topological)
    dp = [0] * num_vertices
    dp[start] = 1

    # Calculate number of paths for each vertex
    for u in topological:
        if dp[u] != 0:
            for v in graph[u]:
                dp[v] += dp[u]

    # Return number of paths from start to end
    return dp[target]


def main():
    # Read input from file
    input_file = input("Please enter the file name: ")

    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Parse input
    nr_vertices, nr_edges = map(int, lines[0].strip().split())

    # Create graph
    graph = defaultdict(list)
    edge_lines = lines[1:nr_edges + 1]

    # Add edges to graph
    for line in edge_lines:
        u, v = map(int, line.strip().split())
        graph[u].append(v)

    # Parse start and end vertices
    start_vertex, target_vertex = map(int, lines[nr_edges].strip().split())

    # Check if graph is a DAG and perform topological sort
    is_dag, topological = is_dag_and_topological_sort(graph, nr_vertices)

    # Count number of paths from start to end vertex
    if is_dag:
        print("The graph is a DAG.")
        print("Topological Sorting Order:", topological)
        num_paths = count_paths_dag(graph, topological, start_vertex, target_vertex)
        print(f"Number of distinct paths from {start_vertex} to {target_vertex}: {num_paths}")
    else:
        print("The graph is not a DAG.")


if __name__ == "__main__":
    main()
