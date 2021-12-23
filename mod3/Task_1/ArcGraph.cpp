//
// Created by d3vyatk4 on 23.12.2021.
//

#include "ArcGraph.h"
#include <cassert>


ArcGraph::ArcGraph(const IGraph &graph) {

    count_vertice = graph.VerticesCount();

    for (auto i = 0; i < count_vertice; ++i) {
        for (auto &to : graph.GetNextVertices(i)) {
            std::pair<int, int> pair(i, to);
            pair_edge.push_back(pair);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < count_vertice);
    assert(0 <= to && to < count_vertice);
    pair_edge.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {

    return static_cast<int>(count_vertice);
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {

    std::vector<int> next_vert;

    for (auto &edges : pair_edge) {
        if (edges.first == vertex) {
            next_vert.push_back(edges.second);
        }
    }
    return next_vert;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> prev_vert;

    for (auto &edges : pair_edge) {
        if (edges.second == vertex) {
            prev_vert.push_back(edges.first);
        }
    }
    return prev_vert;
}