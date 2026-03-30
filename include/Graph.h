#pragma once
#include <vector>
#include <queue>
#include <limits>

// Estrutura para os "Canos" (Arestas)
struct Edge {
    int to;         // Para que nó vai
    int capacity;
    int flow;       // Quanta "água" está a passar lá agora
    int revIndex;   // Índice da aresta inversa
};

class Graph {
private:
    int numNodes;
    // Lista de Adjacências: Cada nó tem uma lista dos seus canos de saída
    std::vector<std::vector<Edge>> adj;

public:
    // Construtor: cria o grafo com um número 'n' de nós
    Graph(int n) : numNodes(n), adj(n) {}

    // Função para adicionar um cano entre dois nós
    void addEdge(int from, int to, int capacity);

    // Algoritmo de Edmonds-Karp para descobrir o fluxo máximo
    int edmondsKarp(int source, int sink);

    const std::vector<std::vector<Edge>>& getAdj() const { return adj; }
};