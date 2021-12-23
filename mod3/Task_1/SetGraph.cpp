//
// Created by d3vyatk4 on 23.12.2021.
//

#include "SetGraph.h"

SetGraph::SetGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {

    for (size_t i = 0; i < graph.VerticesCount(); ++i) {
        for (auto &next_vert : graph.GetNextVertices(i)) {
            adjacencyLists[i].insert(next_vert);
        }
    }
}

void SetGraph::AddEdge(int from, int to)  {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return static_cast<int>(adjacencyLists.size());;
}


std::vector<int> SetGraph::GetNextVertices(int vertex) const {

    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> next_vertices(adjacencyLists.size());

    for (auto value: adjacencyLists[vertex]) {
        next_vertices.push_back(value);
    }

    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {

    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prev_vertices;

    for (size_t i = 0; i < adjacencyLists.size(); ++i) {
        if (adjacencyLists[i].count(vertex)) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}