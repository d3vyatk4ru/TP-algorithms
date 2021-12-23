//
// Created by d3vyatk4 on 21.12.2021.
//

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "IGraph.h"
#include <functional>
#include <queue>
#include <iostream>

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex: graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex: graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

int main() {

    std::cout << "#1\tListGraph realization\n";

    ListGraph listGraph(7);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);

    mainBFS(listGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    mainDFS(listGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    std::cout << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "#2\t MatrixGraph realization\n";
    MatrixGraph matrixGraph(7);
    matrixGraph.AddEdge(0, 1);
    matrixGraph.AddEdge(0, 5);
    matrixGraph.AddEdge(1, 2);
    matrixGraph.AddEdge(1, 3);
    matrixGraph.AddEdge(1, 5);
    matrixGraph.AddEdge(1, 6);
    matrixGraph.AddEdge(3, 2);
    matrixGraph.AddEdge(3, 4);
    matrixGraph.AddEdge(3, 6);
    matrixGraph.AddEdge(5, 4);
    matrixGraph.AddEdge(5, 6);
    matrixGraph.AddEdge(6, 4);

    mainBFS(matrixGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;

    MatrixGraph matrixGraph2(matrixGraph);
    mainBFS(matrixGraph2, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    mainDFS(matrixGraph2, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    std::cout << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "#3\tSetGraph realization\n";
    SetGraph setGraph(7);
    setGraph.AddEdge(0, 1);
    setGraph.AddEdge(0, 5);
    setGraph.AddEdge(1, 2);
    setGraph.AddEdge(1, 3);
    setGraph.AddEdge(1, 5);
    setGraph.AddEdge(1, 6);
    setGraph.AddEdge(3, 2);
    setGraph.AddEdge(3, 4);
    setGraph.AddEdge(3, 6);
    setGraph.AddEdge(5, 4);
    setGraph.AddEdge(5, 6);
    setGraph.AddEdge(6, 4);

    mainBFS(setGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    SetGraph setGraph2(setGraph);
    mainBFS(setGraph2, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    mainDFS(setGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    
    std::cout << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "#4\tArcGraph realization\n";
    ArcGraph arcGraph(7);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 5);
    arcGraph.AddEdge(1, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 5);
    arcGraph.AddEdge(1, 6);
    arcGraph.AddEdge(3, 2);
    arcGraph.AddEdge(3, 4);
    arcGraph.AddEdge(3, 6);
    arcGraph.AddEdge(5, 4);
    arcGraph.AddEdge(5, 6);
    arcGraph.AddEdge(6, 4);

    mainBFS(arcGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;

    ArcGraph ArcGraph2(arcGraph);
    mainDFS(arcGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;
    mainBFS(arcGraph, [](int vertex){ std::cout << vertex << " ";});
    std::cout << std::endl;

    return 0;
}
