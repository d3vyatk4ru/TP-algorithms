//
// Created by d3vyatk4 on 24.12.2021.
//


#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
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

    void AddEdge(int from, int to)
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
    }

    int VerticesCount() const
    {
        return (int)adjacencyLists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<int> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++)
        {
            for (int to: adjacencyLists[from])
            {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }

        return prevVertices;
    }

private:
    std::vector<std::vector<int>> adjacencyLists;
};

void BFS(const IGraph &graph, int from, int to, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(from);

    std::vector<int> n_ways(graph.VerticesCount(), 0);
    std::vector<int> distance(graph.VerticesCount(), INT32_MAX);

    distance[from] = 0;
    n_ways[from] = 1;

    while (!qu.empty()) {

        auto current_vertex = qu.front();
        qu.pop();

        for (auto vertex : graph.GetNextVertices(current_vertex)) {

            if (distance[vertex] > distance[current_vertex] + 1) {
                distance[vertex] = distance[current_vertex] + 1;
                qu.push(vertex);
            }

            if (distance[vertex] == distance[current_vertex] + 1) {
                n_ways[vertex] += n_ways[current_vertex];
            }
        }
    }
    func(n_ways[to]);
}

int main () {
    int n_vertices = 0;
    std::cin >> n_vertices;

    int n_edges = 0;
    std::cin >> n_edges;

    ListGraph graph(n_vertices);
    int from, to;

    for (size_t i = 0; i < n_edges; ++i) {
        std::cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int start = 0, stop = 0;

    std::cin >> start >> stop;
    BFS(graph, start, stop, [](int n_ways){ std::cout << n_ways<< std::endl;});

    return 0;
}