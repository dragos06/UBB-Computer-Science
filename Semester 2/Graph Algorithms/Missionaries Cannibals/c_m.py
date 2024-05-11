class Vertex:
    def __init__(self, d):
        self.__dict = dict(d)
        self.__items = ["c1", "c2", "c3", "m1", "m2", "m3", "boat"]

    def __repr__(self):
        return f"{self.__dict}"

    def __str__(self):
        return f"{self.__dict}"

    def return_dictionary(self):
        """
        Returns the dictionary of the vertex
        :return: The dictionary of the vertex
        """
        return self.__dict.items()

    def parse_neighbors(self):
        """
        Generates the neighbors of the vertex
        :return: The neighbors of the vertex
        """
        for item in self.__items:
            d = dict(self.__dict)
            if item != "boat":
                if d[item] != d["boat"]:
                    continue
                d[item] = not d[item]
            d["boat"] = not d["boat"]
            v = Vertex(d)

            if v.is_valid():
                yield v

    def is_valid(self):
        """
        Checks if the vertex is valid or not (if the cannibals are more than the missionaries)
        :return: True if the vertex is valid, False otherwise
        """

        # MISSIONARIES LEFT, MISSIONARIES RIGHT
        m_l_nr = 0
        m_r_nr = 0
        for i in range(1, 4):
            if int(self.__dict[f"m{i}"]):
                m_r_nr += 1
            if not int(self.__dict[f"m{i}"]):
                m_l_nr += 1
        if m_l_nr < 0 or m_r_nr < 0:
            return False

        # CANNIBALS LEFT, CANNIBALS RIGHT
        c_l_nr = 0
        c_r_nr = 0
        for i in range(1, 4):
            if int(self.__dict[f"c{i}"]):
                c_r_nr += 1
            if not int(self.__dict[f"c{i}"]):
                c_l_nr += 1
        if c_l_nr < 0 or c_r_nr < 0:
            return False

        # CANNIBALS LEFT, MISSIONARIES LEFT
        c_l_nr = 0
        m_l_nr = 0
        for i in range(1, 4):
            if not int(self.__dict[f"m{i}"]):
                m_l_nr += 1
            if not int(self.__dict[f"c{i}"]):
                c_l_nr += 1
        if c_l_nr > m_l_nr:
            return False

        # CANNIBALS RIGHT, MISSIONARIES RIGHT
        c_r_nr = 0
        m_r_nr = 0
        for i in range(1, 4):
            if not int(self.__dict[f"m{i}"]):
                m_r_nr += 1
            if not int(self.__dict[f"c{i}"]):
                c_r_nr += 1
        if c_r_nr > m_r_nr:
            return False

        return True

    def __eq__(self, other):
        if not isinstance(other, Vertex):
            return False
        return self.__dict == other.__dict

    def __hash__(self):
        val = 0
        for key in self.__items:
            val = val * 2 + (1 if self.__dict[key] else 0)
        return val


class CannibalsAndMissionariesGraph:
    def parse_neighbors(self, x):
        """
        Parses the neighbors
        :param x: The vertex
        :return: The neighbors of the vertex
        """
        return x.parse_neighbors()

    def init_state(self):
        """
        Returns the initial state of the graph (the state where all the missionaries and cannibals are on the left side)
        :return: The initial state of the graph
        """
        return Vertex({"c1": False, "c2": False, "c3": False, "m1": False, "m2": False, "m3": False, "boat": False})

    def final_state(self):
        """
        Returns the final state of the graph (the state where all the missionaries and cannibals are on the right side)
        :return: The final state of the graph
        """
        return Vertex({"c1": True, "c2": True, "c3": True, "m1": True, "m2": True, "m3": True, "boat": True})
