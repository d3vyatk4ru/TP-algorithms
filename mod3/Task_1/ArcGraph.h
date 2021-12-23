//
// Created by d3vyatk4 on 23.12.2021.
//

#ifndef MOD3_ARCGRAPH_H
#define MOD3_ARCGRAPH_H

#include "IGraph.h"
#include <vector>
#include <algorithm>


class ArcGraph: public IGraph {
private:
    std::vector<std::pair<int, int>> pair_edge;
    size_t count_vertice;

public:

    ArcGraph(size_t size) : count_vertice(size) {};

    ArcGraph(const IGraph &graph);

    ~ArcGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
};


#endif //MOD3_ARCGRAPH_H
