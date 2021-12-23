//
// Created by d3vyatk4 on 23.12.2021.
//

#ifndef MOD3_MATRIXGRAPH_H
#define MOD3_MATRIXGRAPH_H

#include "IGraph.h"
#include <vector>
#include <cassert>

class MatrixGraph :  public IGraph {
private:
    std::vector<std::vector<bool>> adjacencyMatrix;

public:

    MatrixGraph(size_t size);
    MatrixGraph(const IGraph &graph);

    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;
};


#endif //MOD3_MATRIXGRAPH_H
