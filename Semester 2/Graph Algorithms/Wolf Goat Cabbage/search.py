import w_g_c


class TreeNode:
    def __str__(self):
        return f"parent: {self.parent}, level: {self.level}, children: {self.children}"

    def __repr__(self):
        return f"parent: {self.parent}, level: {self.level}, children: {self.children}"


def bfs(g, s):
    """
    Breadth-first search
    :param g: The graph
    :param s: The starting vertex
    :return: The tree of the shortest path
    """
    tree = {}
    q = [s]
    tree[s] = TreeNode()
    tree[s].parent = None
    tree[s].level = 0
    tree[s].children = []
    head = 0
    while head < len(q):
        x = q[head]
        head += 1
        for y in g.parse_neighbors(x):
            if y not in tree.keys():
                q.append(y)
                tree[y] = TreeNode()
                tree[y].parent = x
                tree[y].level = tree[x].level + 1
                tree[y].children = []
                tree[x].children.append(y)
    return tree


def shortest_path(g, s, t):
    """
    Find the shortest path from s to t
    :param g: The graph
    :param s: The starting vertex
    :param t: The target vertex
    :return: The shortest path
    """
    tree = bfs(g, s)
    start = s
    target = t
    if target not in tree.keys():
        return None
    path_rev = list()
    while target != start:
        path_rev.append(target)
        target = tree[target].parent
    path_rev.append(start)
    path_rev.reverse()
    return path_rev


if __name__ == "__main__":
    g = w_g_c.WolfGoatCabbageGraph()
    s = g.init_state()
    t = g.final_state()
    path = shortest_path(g, s, t)
    print("\n" * 3)
    for dictionary in path:
        for key, value in dictionary.return_dictionary():
            if not value:
                print(f"{key.upper()}", end=" ")
        print()
        print("_" * 25)
        print()
        print("_" * 25)
        for key, value in dictionary.return_dictionary():
            if value:
                print(f"{key.upper()}", end=" ")
        print("\n" * 3)
