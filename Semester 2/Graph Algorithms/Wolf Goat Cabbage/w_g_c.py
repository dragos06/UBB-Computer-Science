class Vertex:
    def __init__(self, d):
        self.__dict = dict(d)
        self.__items = ["wolf", "goat", "cabbage", "boat"]

    def __repr__(self):
        return f"{self.__dict}"

    def __str__(self):
        return f"{self.__dict}"

    def return_dictionary(self):
        """
        Return the dictionary of the vertex
        :return: The dictionary of the vertex
        """
        return self.__dict.items()

    def parse_neighbors(self):
        """
        Parse the neighbors of the vertex
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
        Check if the vertex is valid
        :return: True if the vertex is valid, False otherwise
        """
        if self.__dict["goat"] == self.__dict["boat"]:
            return True
        if self.__dict["goat"] == self.__dict["wolf"]:
            return False
        if self.__dict["goat"] == self.__dict["cabbage"]:
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


class WolfGoatCabbageGraph:
    def parse_neighbors(self, x):
        """
        Parse the neighbors
        :param x: The vertex
        :return: The neighbors of the vertex
        """
        return x.parse_neighbors()

    def init_state(self):
        return Vertex({"wolf": False, "goat": False, "cabbage": False, "boat": False, })

    def final_state(self):
        return Vertex({"wolf": True, "goat": True, "cabbage": True, "boat": True, })