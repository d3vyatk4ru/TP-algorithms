//
// Created by d3vyatk4 on 23.12.2021.
//

#ifndef MOD3_SETGRAPH_H
#define MOD3_SETGRAPH_H

#include "IGraph.h"
#include <vector>
#include <cassert>
#include <set>

class SetGraph : public IGraph {
private:
    std::vector<std::set<int>> adjacencyLists;

public:

    SetGraph(size_t size) : adjacencyLists(size) {}

    SetGraph(const IGraph &graph);

    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
};


#endif //MOD3_SETGRAPH_H
