#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>


struct Edge{
    int to;             // destination node index
    int capacity;       // max flow allowed
    int flow;           // current flow
    int reverseEdge;    // index of the reverse edge
};

class Graph{
private:
    int numNodes;
    std::vector<std::vector<Edge>> adj;     // list of edges for every node

public:
    Graph(int n) : numNodes(n), adj(n) {}

    void addEdge(int from, int to, int cap){
        Edge forward = {to, cap, 0, (int)adj[to].size()};
        Edge backward = {from, 0, 0, (int)adj[from].size()};

        adj[from].push_back(forward);
        adj[to].push_back(backward);
    }

    int getNumNodes() const { return numNodes; }
    std::vector<std::vector<Edge>>& getAdj() { return adj; }

    bool bfs(int s, int t,  std::vector<int>& parent, std::vector<int>& edgeIdx){
        std::fill(parent.begin(), parent.end(), -1);
        parent[s] = s;
        std::queue<int> q;
        q.push(s);

        while (!q.empty()){
            int u = q.front();
            q.pop();

            for (int i = 0; i < (int)adj[u].size(); ++i) {
                Edge &e = adj[u][i];
                if (parent[e.to] == -1 && (e.capacity - e.flow) > 0){
                    parent[e.to] = u;
                    edgeIdx[e.to] = i;

                    if (e.to == t) return true;
                    q.push(e.to);
                }
            }
        }
        return false;
    }

    int maxFlow(int s, int t){
        int totalFlow  = 0;
        std::vector<int> parent(numNodes);
        std::vector<int> edgeIdx(numNodes);

        while (bfs(s, t, parent, edgeIdx)){
            int pathFlow = std::numeric_limits<int>::max();

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                int idx = edgeIdx[v];
                pathFlow = std::min(pathFlow, adj[u][idx].capacity - adj[u][idx].flow);
            }

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                int idx = edgeIdx[v];
                adj[u][idx].flow += pathFlow;

                int revIdx = adj[u][idx].reverseEdge;
                adj[v][revIdx].flow -= pathFlow;
            }
            totalFlow += pathFlow;
        }
        return totalFlow;
    }
};

//
// Created by danie on 28/03/2026.
//

#ifndef DA_PROGRAMMING_PROJECT_I_MAIN_GRAPH_H
#define DA_PROGRAMMING_PROJECT_I_MAIN_GRAPH_H

#endif //DA_PROGRAMMING_PROJECT_I_MAIN_GRAPH_H
