//
// Created by d3vyatk4 on 23.12.2021.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(size_t size) {
    adjacencyMatrix.resize(size, std::vector<bool>(size, 0));
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    adjacencyMatrix.resize(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), 0));
    std::vector<int> vertice;

    for (size_t i = 0; i < graph.VerticesCount(); ++i) {
        vertice = graph.GetNextVertices(i);
        for (auto &vert : vertice) {
            adjacencyMatrix[i][vert] = 1;
        }
    }
}
void MatrixGraph::AddEdge(int from, int to) {
    // проверка как на семинаре
    assert(0 <= from && from < adjacencyMatrix.size());
    assert(0 <= to && to < adjacencyMatrix.size());
    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(adjacencyMatrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const{

    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> next_vert = {};

    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[vertex][i]) {
            next_vert.push_back(i);
        }
    }

    return next_vert;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const{

    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> prevVertices = {};

    for (int j = 0; j < adjacencyMatrix.size(); j++) {
        if (adjacencyMatrix[j][vertex]) {
            prevVertices.push_back(j);
        }
    }

    return prevVertices;
}