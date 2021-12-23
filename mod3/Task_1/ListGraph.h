//
// Created by d3vyatk4 on 22.12.2021.
//

#ifndef MOD3_LISTGRAPH_H
#define MOD3_LISTGRAPH_H

#include "IGraph.h"
#include <cassert>

struct ListGraph: public IGraph
{
public:
    ListGraph(int size);

    ListGraph(const IGraph &graph);

    ~ListGraph();

    void AddEdge(int from, int to);

    int VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;

    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::vector<int>> adjacencyLists;
};

#endif //MOD3_LISTGRAPH_H
