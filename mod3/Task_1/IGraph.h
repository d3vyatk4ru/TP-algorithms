//
// Created by d3vyatk4 on 23.12.2021.
//

#ifndef MOD3_IGRAPH_H
#define MOD3_IGRAPH_H
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //MOD3_IGRAPH_H
