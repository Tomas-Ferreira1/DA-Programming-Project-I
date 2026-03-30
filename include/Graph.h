#pragma once
#include <vector>
#include <queue>
#include <limits>

/**
 * @brief Estrutura que representa uma aresta (ligacao) no grafo de fluxo.
 */
struct Edge {
    int to;         // Para que nó vai
    int capacity;
    int flow;       // Quanta "água" está a passar lá agora
    int revIndex;   // Índice da aresta inversa
};


/**
 * @brief Classe que representa uma Rede de Fluxo (Max-Flow).
 * * Utiliza o algoritmo de Edmonds-Karp para calcular a atribuicao
 * maxima entre Submissoes e Revisores.
 */
class Graph {
private:
    int numNodes;
    // Lista de Adjacências: Cada nó tem uma lista dos seus canos de saída
    std::vector<std::vector<Edge>> adj;

public:
    /**
     * @brief Construtor da classe Graph.
     * @param n Numero total de nos a criar no grafo (incluindo Source e Sink).
     */
    // Construtor: cria o grafo com um número 'n' de nós
    Graph(int n) : numNodes(n), adj(n) {}

    /**
     * @brief Adiciona uma aresta direcionada ao grafo (e a sua correspondente aresta residual).
     * @param from Indice do no de origem.
     * @param to Indice do no de destino.
     * @param capacity A capacidade maxima de fluxo desta aresta.
     */
    // Função para adicionar um cano entre dois nós
    void addEdge(int from, int to, int capacity);

    /**
     * @brief Executa o algoritmo de Edmonds-Karp para encontrar o fluxo maximo.
     * @param source Indice do no Fonte (Source).
     * @param sink Indice do no Sumidouro (Sink).
     * @return O valor inteiro do fluxo maximo encontrado na rede.
     */
    // Algoritmo de Edmonds-Karp para descobrir o fluxo máximo
    int edmondsKarp(int source, int sink);

    /**
     * @brief Getter para obter a lista de adjacencias do grafo.
     * @return Referencia constante para a matriz de adjacencias.
     */
    const std::vector<std::vector<Edge>>& getAdj() const { return adj; }
};