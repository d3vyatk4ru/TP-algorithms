//
// Created by d3vyatk4 on 26.12.2021.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <set>

struct IGraph {
        virtual ~IGraph() {}

        // Добавление ребра от from к to.
        virtual void AddEdge(int from, int to, int cost) = 0;

        virtual int VerticesCount() const  = 0;

        virtual std::vector<std::pair<int, int>>  GetNextVertices(int vertex) const = 0;
        virtual std::vector<std::pair<int, int>>  GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
public:
    ListGraph(int size)
            : adjacencyLists(size)
    {
    }

    ListGraph(const IGraph &graph)
            : adjacencyLists(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++)
        {
            adjacencyLists[i] = graph.GetNextVertices(i);
        }
    }

    ~ListGraph()
    {
    }

    void AddEdge(int from, int to, int cost) override
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].emplace_back(to, cost);
    }

    int VerticesCount() const
    {
        return (int)adjacencyLists.size();
    }

    std::vector<std::pair<int, int>>  GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<std::pair<int, int>>  GetPrevVertices(int vertex) const
    {
        return adjacencyLists[vertex];
    }

private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

void search_distance(const IGraph &graph, int from, int to, const std::function<void(int)> &func) {

    std::vector<int> distance(graph.VerticesCount(), INT32_MAX);
    distance[from] = 0;

    std::set<std::pair<int, int>> priority_qu;
    priority_qu.emplace(0, from);

    while (!priority_qu.empty()) {

        auto current_vertex = priority_qu.begin();

        for (auto vertex : graph.GetNextVertices((int)((*current_vertex).second))) {

            if (distance[vertex.first] > distance[(int)((*current_vertex).second)] + vertex.second) {

                std::pair<int, int> temp(distance[vertex.first], vertex.second);

                if (priority_qu.find(temp) != priority_qu.end()) {
                    priority_qu.erase(priority_qu.find(temp));
                }

                distance[vertex.first] = distance[(int)(*current_vertex).second] + vertex.second;
                priority_qu.insert(std::pair<int, int>(distance[vertex.first], vertex.first));
            }
        }

        priority_qu.erase(priority_qu.find(*current_vertex));
    }

    func(distance[to]);
}

int main() {

    int n_vertices = 0;
    std::cin >> n_vertices;

    int n_edges = 0;
    std::cin >> n_edges;

    ListGraph graph(n_vertices);
    int from = 0, to = 0, cost = 0;

    for (size_t i = 0; i < n_edges; ++i) {
        std::cin >> from >> to >> cost;
        graph.AddEdge(from, to, cost);
        graph.AddEdge(to, from, cost);
    }

    int start = 0, stop = 0;
    std::cin >> start >> stop;

    search_distance(graph, start, stop, [](int distance){ std::cout << distance << std::endl;});

    return 0;
}