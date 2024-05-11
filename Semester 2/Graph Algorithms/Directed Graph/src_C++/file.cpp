#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

class Graph {
private:
    int vertices;
    map<int, vector<int>> dict_in;
    map<int, vector<int>> dict_out;
    map<pair<int, int>, int> dict_cost;

public:
    Graph(int n = 0) : vertices(n) {
        for (int i = 0; i < vertices; ++i) {
            dict_in[i] = {};
            dict_out[i] = {};
        }
    }

    void add_vertex(int vertex) {
        if (is_vertex(vertex)) {
            throw invalid_argument("Vertex already exists");
        }
        dict_in[vertex] = {};
        dict_out[vertex] = {};
        ++vertices;
    }

    bool is_vertex(int vertex) {
        return (dict_in.find(vertex) != dict_in.end()) && (dict_out.find(vertex) != dict_out.end());
    }

    void add_edge(int vertex_x, int vertex_y, int cost) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("First vertex does not exist!");
        }
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Second vertex does not exist!");
        }
        if (is_edge(vertex_x, vertex_y)) {
            throw invalid_argument("Edge already exists!");
        }
        dict_in[vertex_y].push_back(vertex_x);
        dict_out[vertex_x].push_back(vertex_y);
        dict_cost[make_pair(vertex_x, vertex_y)] = cost;
    }

    bool is_edge(int vertex_x, int vertex_y) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("First vertex does not exist!");
        }
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Second vertex does not exist!");
        }
        for (int v : dict_out[vertex_x]) {
            if (v == vertex_y) {
                return true;
            }
        }
        return false;
    }

    void remove_vertex(int vertex) {
        if (!is_vertex(vertex)) {
            throw invalid_argument("Vertex does not exist!");
        }
        for (int vertex_y : parse_vertex_out(vertex)) {
            auto it = dict_cost.find(make_pair(vertex, vertex_y));
            if (it != dict_cost.end()) {
                dict_cost.erase(it);
            }
            dict_in[vertex_y].erase(remove(dict_in[vertex_y].begin(), dict_in[vertex_y].end(), vertex), dict_in[vertex_y].end());
        }
        for (int vertex_x : parse_vertex_in(vertex)) {
            auto it = dict_cost.find(make_pair(vertex_x, vertex));
            if (it != dict_cost.end()) {
                dict_cost.erase(it);
            }
            dict_out[vertex_x].erase(remove(dict_out[vertex_x].begin(), dict_out[vertex_x].end(), vertex), dict_out[vertex_x].end());
        }
        dict_in.erase(vertex);
        dict_out.erase(vertex);
        vertices--;
    }

    void remove_edge(int vertex_x, int vertex_y) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("First vertex does not exist!");
        }
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Second vertex does not exist!");
        }
        if (!is_edge(vertex_x, vertex_y)) {
            throw invalid_argument("Edge does not exist!");
        }
        dict_out[vertex_x].erase(remove(dict_out[vertex_x].begin(), dict_out[vertex_x].end(), vertex_y), dict_out[vertex_x].end());
        dict_in[vertex_y].erase(remove(dict_in[vertex_y].begin(), dict_in[vertex_y].end(), vertex_x), dict_in[vertex_y].end());
        dict_cost.erase(make_pair(vertex_x, vertex_y));
    }

    int get_number_vertices() {
        return vertices;
    }

    int get_number_edges() {
        return dict_cost.size();
    }

    int get_cost(int vertex_x, int vertex_y) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("First vertex does not exist!");
        }
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Second vertex does not exist!");
        }
        if (!is_edge(vertex_x, vertex_y)) {
            throw invalid_argument("Edge does not exist!");
        }
        return dict_cost[make_pair(vertex_x, vertex_y)];
    }

    void modify_cost(int vertex_x, int vertex_y, int new_cost) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("First vertex does not exist!");
        }
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Second vertex does not exist!");
        }
        if (!is_edge(vertex_x, vertex_y)) {
            throw invalid_argument("Edge does not exist!");
        }
        dict_cost[make_pair(vertex_x, vertex_y)] = new_cost;
    }

    void load_graph_from_file(const string& file_name) {
        ifstream file(file_name);
        if (!file.is_open()) {
            throw runtime_error("File not found!");
        }

        string line;
        getline(file, line);
        istringstream iss(line);
        int vertex1, vertex2, cost;
        int n, m;
        if (!(iss >> vertex1 >> vertex2 >> cost)) { // Two vertices on the first line
            iss >> n >> m;
            while (getline(file, line)) {
                istringstream iss(line);
                iss >> vertex1 >> vertex2 >> cost;
                if (!is_vertex(vertex1))
                    add_vertex(vertex1);
                if (!is_vertex(vertex2))
                    add_vertex(vertex2);
                add_edge(vertex1, vertex2, cost);
            }
            for (int i = 0; i < this->vertices; i++)
                if (this->is_vertex(i) == false)
                    this->add_vertex(i);
        }
        else { // Three values on the first line
            iss >> vertex1 >> vertex2 >> cost;
            cout << vertex1 << " " << vertex2 << " " << cost;
            if (vertex2 == -1) {
                add_vertex(vertex1);
            }
            else {
                if (!is_vertex(vertex1))
                    add_vertex(vertex1);
                if (!is_vertex(vertex2))
                    add_vertex(vertex2);
                add_edge(vertex1, vertex2, cost);
            }
            while (getline(file, line)) {
                istringstream iss(line);
                iss >> vertex1 >> vertex2 >> cost;
                cout << vertex1 << " " << vertex2 << " " << cost;
                if (vertex2 == -1) {
                    add_vertex(vertex1);
                }
                else {
                    if (!is_vertex(vertex1))
                        add_vertex(vertex1);
                    if (!is_vertex(vertex2))
                        add_vertex(vertex2);
                    add_edge(vertex1, vertex2, cost);
                }
            }
        }
        file.close();
    }

    void save_graph_to_file(const string& file_name) {
        ofstream file(file_name);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing!");
        }

        bool found = false;
        for (auto& i : dict_out)
            if (i.second.empty() && dict_in[i.first].empty())
                found = true;

        if (!found) {
            file << vertices << " " << get_number_edges() << "\n";
            for (auto& i : dict_cost) {
                int vertex1 = i.first.first;
                int vertex2 = i.first.second;
                file << vertex1 << " " << vertex2 << " " << i.second << "\n";
            }
        }
        else {
            for (auto& i : dict_out) {
                if (i.second.empty() && dict_in[i.first].empty()) {
                    found = true;
                    file << i.first << " -1 -1\n";
                }
                else {
                    for (int vertex2 : i.second) {
                        int cost = dict_cost[{i.first, vertex2}];
                        file << i.first << " " << vertex2 << " " << cost << "\n";
                    }
                }
            }
        }
        file.close();
    }

    vector<int> parse_vertices() {
        vector<int> vertices;
        for (auto& entry : dict_in) {
            vertices.push_back(entry.first);
        }
        return vertices;
    }

    vector<int> parse_vertex_in(int vertex) {
        if (!is_vertex(vertex)) {
            throw invalid_argument("Vertex does not exist!");
        }
        return dict_in[vertex];
    }

    vector<int> parse_vertex_out(int vertex) {
        if (!is_vertex(vertex)) {
            throw invalid_argument("Vertex does not exist!");
        }
        return dict_out[vertex];
    }

    int in_degree(int vertex) {
        if (!is_vertex(vertex)) {
            throw invalid_argument("Vertex does not exist!");
        }
        return dict_in[vertex].size();
    }

    int out_degree(int vertex) {
        if (!is_vertex(vertex)) {
            throw invalid_argument("Vertex does not exist!");
        }
        return dict_out[vertex].size();
    }

    vector<pair<int, int>> parse_outbound_edges(int vertex_x) {
        if (!is_vertex(vertex_x)) {
            throw invalid_argument("Vertex does not exist!");
        }
        vector<pair<int, int>> edges;
        for (int vertex_y : parse_vertex_out(vertex_x)) {
            edges.push_back(make_pair(vertex_x, vertex_y));
        }
        return edges;
    }

    vector<pair<int, int>> parse_inbound_edges(int vertex_y) {
        if (!is_vertex(vertex_y)) {
            throw invalid_argument("Vertex does not exist!");
        }
        vector<pair<int, int>> edges;
        for (int vertex_x : parse_vertex_in(vertex_y)) {
            edges.push_back(make_pair(vertex_x, vertex_y));
        }
        return edges;
    }

    vector<pair<pair<int, int>, int>> parse_edges() {
        vector<pair<pair<int, int>, int>> edges;
        for (auto& entry : dict_cost) {
            edges.push_back(make_pair(entry.first, entry.second));
        }
        return edges;
    }
};

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <string>

using namespace std;

class UI {
private:
    Graph graph;
    Graph copy_graph;

public:
    void print_menu() {
        cout << "\n      GRAPH APPLICATION\n"
            << "\n[1] Add vertex to graph.\n"
            << "[2] Add edge to graph.\n"
            << "[3] Remove vertex from graph.\n"
            << "[4] Remove edge from graph.\n"
            << "[5] Get the number of vertices.\n"
            << "[6] Parse the set of vertices.\n"
            << "[7] Check if there is an edge between 2 vertices.\n"
            << "[8] Get the in degree of a vertex.\n"
            << "[9] Get the out degree of a vertex.\n"
            << "[10] Parse the set of outbound edges of a vertex.\n"
            << "[11] Parse the set of inbound edges of a vertex.\n"
            << "[12] Get the cost of an edge.\n"
            << "[13] Modify the cost of an edge.\n"
            << "[14] Copy graph.\n"
            << "[15] Read the graph from a text file.\n"
            << "[16] Write the modified graph to a text file.\n"
            << "[17] Create a random graph.\n"
            << "[18] Print graph.\n"
            << "[19] Print copied graph.\n"
            << "[20] Exit.\n";
    }

    void start() {
        while (true) {
            try {
                print_menu();
                int option;
                cout << "Please choose an option: ";
                cin >> option;
                switch (option) {
                case 1:
                    add_vertex();
                    break;
                case 2:
                    add_edge();
                    break;
                case 3:
                    remove_vertex();
                    break;
                case 4:
                    remove_edge();
                    break;
                case 5:
                    cout << "Number of vertices: " << graph.get_number_vertices() << endl;
                    break;
                case 6:
                    cout << "Vertices: ";
                    for (int v : graph.parse_vertices()) {
                        cout << v << " ";
                    }
                    cout << endl;
                    break;
                case 7:
                    find_if_edge();
                    break;
                case 8:
                    in_degree();
                    break;
                case 9:
                    out_degree();
                    break;
                case 10:
                    print_outbounds();
                    break;
                case 11:
                    print_inbounds();
                    break;
                case 12:
                    give_cost();
                    break;
                case 13:
                    modify_cost();
                    break;
                case 14:
                    copy_the_graph();
                    break;
                case 15:
                    read_from_file();
                    break;
                case 16:
                    save_to_file();
                    break;
                case 17:
                    random_graph();
                    break;
                case 18:
                    print_graph(graph);
                    break;
                case 19:
                    print_graph(copy_graph);
                    break;
                case 20:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid input!" << endl;
                    break;
                }
            }
            catch (const exception& error) {
                cerr << error.what() << endl;
            }
        }
    }

    void print_graph(Graph& graph) {
        cout << "Outbound: " << endl;
        for (int vertex_x : graph.parse_vertices()) {
            cout << vertex_x << ": ";
            for (int vertex_y : graph.parse_vertex_out(vertex_x)) {
                cout << vertex_y << " ";
            }
            cout << endl;
        }
        cout << "Inbound: " << endl;
        for (int vertex_x : graph.parse_vertices()) {
            cout << vertex_x << ": ";
            for (int vertex_y : graph.parse_vertex_in(vertex_x)) {
                cout << vertex_y << " ";
            }
            cout << endl;
        }
    }

    void add_vertex() {
        int vertex;
        cout << "Give a vertex: ";
        cin >> vertex;
        graph.add_vertex(vertex);
    }

    void add_edge() {
        int vertex_x, vertex_y, cost;
        cout << "Give the first vertex: ";
        cin >> vertex_x;
        cout << "Give the second vertex: ";
        cin >> vertex_y;
        cout << "Give the cost: ";
        cin >> cost;
        graph.add_edge(vertex_x, vertex_y, cost);
    }

    void remove_vertex() {
        int vertex;
        cout << "Give the vertex: ";
        cin >> vertex;
        graph.remove_vertex(vertex);
    }

    void remove_edge() {
        int vertex_x, vertex_y;
        cout << "Give the first vertex: ";
        cin >> vertex_x;
        cout << "Give the second vertex: ";
        cin >> vertex_y;
        graph.remove_edge(vertex_x, vertex_y);
    }

    void num_of_vertices() {
        cout << "Number of vertices is: " << graph.get_number_vertices() << endl;
    }

    void out_degree() {
        int vertex;
        cout << "Please give the vertex: ";
        cin >> vertex;
        cout << "The out degree of " << vertex << " is: " << graph.out_degree(vertex) << endl;
    }

    void modify_cost() {
        int vertex_x, vertex_y, new_cost;
        cout << "Please give the first vertex: ";
        cin >> vertex_x;
        cout << "Please give the second vertex: ";
        cin >> vertex_y;
        cout << "Please give the cost: ";
        cin >> new_cost;
        graph.modify_cost(vertex_x, vertex_y, new_cost);
    }

    void find_if_edge() {
        int vertex_x, vertex_y;
        cout << "Please give the first vertex: ";
        cin >> vertex_x;
        cout << "Please give the second vertex: ";
        cin >> vertex_y;
        if (graph.is_edge(vertex_x, vertex_y)) {
            cout << "There exists an edge from " << vertex_x << " to " << vertex_y << endl;
        }
        else {
            cout << "There is no an edge from " << vertex_x << " to " << vertex_y << endl;
        }
    }

    void in_degree() {
        int vertex;
        cout << "Please give the vertex: ";
        cin >> vertex;
        cout << "The in degree of " << vertex << " is: " << graph.in_degree(vertex) << endl;
    }

    void give_cost() {
        int vertex_x, vertex_y;
        cout << "Please give the first vertex: ";
        cin >> vertex_x;
        cout << "Please give the second vertex: ";
        cin >> vertex_y;
        cout << "The cost of the edge (" << vertex_x << ", " << vertex_y << ") is " << graph.get_cost(vertex_x, vertex_y) << endl;
    }

    void print_edges() {
        for (auto& edge : graph.parse_edges()) {
            cout << "(" << edge.first.first << ", " << edge.first.second << ") : " << edge.second << endl;
        }
    }

    void print_outbounds() {
        int vertex;
        cout << "Please give the vertex: ";
        cin >> vertex;
        cout << "Outbounds: ";
        for (auto& edge : graph.parse_outbound_edges(vertex)) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    void print_inbounds() {
        int vertex;
        cout << "Please give the vertex: ";
        cin >> vertex;
        cout << "Inbounds: ";
        for (auto& edge : graph.parse_inbound_edges(vertex)) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    void random_graph() {
        int n, m;
        cout << "Please give the number of vertices: ";
        cin >> n;
        cout << "Please give the number of edges: ";
        cin >> m;
        graph = Graph(n);
        if (m > n * (n - 1) + n) {
            m = n * (n - 1) + n;
            cout << "Cannot create a graph like this. Number of vertices is: " << m << endl;
        }
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, n - 1);
        while (m) {
            int vertex_x = dis(gen);
            int vertex_y = dis(gen);
            int vertex_cost = uniform_int_distribution<>(1, 200)(gen);
            if (!graph.is_edge(vertex_x, vertex_y)) {
                graph.add_edge(vertex_x, vertex_y, vertex_cost);
                m--;
            }
        }
    }

    void read_from_file() {
        graph = Graph();
        string file_name;
        cout << "Give the file name: ";
        cin >> file_name;
        graph.load_graph_from_file(file_name);
    }

    void save_to_file() {
        string file_name;
        cout << "Give the file name: ";
        cin >> file_name;
        graph.save_graph_to_file(file_name);
    }

    void copy_the_graph() {
        copy_graph = Graph();
        for (int vertex : graph.parse_vertices()) {
            copy_graph.add_vertex(vertex);
        }
        for (auto& edge : graph.parse_edges()) {
            copy_graph.add_edge(edge.first.first, edge.first.second, edge.second);
        }
        cout << "Graph was copied!" << endl;
    }
};


int main() {
    UI console;
    console.start();
}

