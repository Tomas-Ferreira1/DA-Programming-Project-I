#include "Graph.h"

// Adicionar uma aresta no Max-Flow exige sempre adicionar uma aresta "inversa" ou "residual"
void Graph::addEdge(int from, int to, int capacity) {
    Edge a{to, capacity, 0, (int)adj[to].size()};
    Edge b{from, 0, 0, (int)adj[from].size()}; // Aresta inversa nasce com capacidade 0
    adj[from].push_back(a);
    adj[to].push_back(b);
}

int Graph::edmondsKarp(int source, int sink) {
    int max_flow = 0;

    while (true) {
        // Vetores para rastrear o caminho da água
        std::vector<int> parent(numNodes, -1);
        std::vector<int> parentEdge(numNodes, -1);
        std::queue<int> q;

        q.push(source);
        parent[source] = source; // Marca a origem como visitada

        // Tentar encontrar um caminho da Fonte até ao Sumidouro onde ainda caiba água
        while (!q.empty() && parent[sink] == -1) {
            int curr = q.front();
            q.pop();

            for (std::size_t i = 0; i < adj[curr].size(); ++i) {
                Edge& edge = adj[curr][i];
                int next = edge.to;

                // Se ainda não visitámos o nó 'next' E ainda há espaço neste cano
                if (parent[next] == -1 && edge.capacity - edge.flow > 0) {
                    parent[next] = curr;
                    parentEdge[next] = i;
                    q.push(next);
                }
            }
        }

        // Se não conseguimos chegar ao sumidouro, o Max-Flow terminou
        if (parent[sink] == -1) {
            break;
        }

        // Se chegámos, vamos ver qual foi o "cano mais estreito" nesse caminho (gargalo)
        int push_flow = std::numeric_limits<int>::max();
        int curr = sink;
        while (curr != source) {
            int prev = parent[curr];
            int edgeIdx = parentEdge[curr];
            push_flow = std::min(push_flow, adj[prev][edgeIdx].capacity - adj[prev][edgeIdx].flow);
            curr = prev;
        }

        max_flow += push_flow;

        // Agora atualizamos os fluxos das arestas por onde a água passou
        curr = sink;
        while (curr != source) {
            int prev = parent[curr];
            int edgeIdx = parentEdge[curr];
            int revIdx = adj[prev][edgeIdx].revIndex;

            adj[prev][edgeIdx].flow += push_flow; // Adiciona fluxo na direção normal
            adj[curr][revIdx].flow -= push_flow;  // Subtrai na direção inversa (residual)
            curr = prev;
        }
    }

    return max_flow;
}