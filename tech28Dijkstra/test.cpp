#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

class Node {
public:
    int id;
    vector<pair<int, int>> neighbors;

    Node(int _id) : id(_id) {}
};

class Graph {
public:
    vector<Node> nodes;

    void addNode(int id) {
        nodes.emplace_back(id);
    }

    void addEdge(int src, int dest, int weight) {
        nodes[src].neighbors.emplace_back(dest, weight);
        nodes[dest].neighbors.emplace_back(src, weight);
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(nodes.size(), numeric_limits<int>::max());
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& neighbor : nodes[u].neighbors) {
                int v = neighbor.first;
                int w = neighbor.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }

    vector<int> aStar(int start, int goal) {
        vector<int> dist(nodes.size(), numeric_limits<int>::max());
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (u == goal) break;

            if (d > dist[u]) continue;

            for (const auto& neighbor : nodes[u].neighbors) {
                int v = neighbor.first;
                int w = neighbor.second;
                int h = heuristic(v, goal, dist[u]);

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v] + h, v});
                }
            }
        }

        return dist;
    }

private:
    int heuristic(int u, int goal, int dist_u) {
        // Using Manhattan distance (sum of edge weights)
        return dist_u; // Assuming the heuristic for A* is the distance traveled so far
    }
};

int main() {
    Graph graph;

    for (int i = 0; i < 6; ++i) {
        graph.addNode(i);
    }

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 5);

    vector<int> dijkstraDist = graph.dijkstra(0);

    cout << "Khoảng cách từ đỉnh 0 đến các đỉnh khác (Dijkstra):" << endl;
    for (int i = 0; i < dijkstraDist.size(); ++i) {
        cout << "Đỉnh " << i << ": " << dijkstraDist[i] << endl;
    }

    vector<int> aStarDist = graph.aStar(0, 5);

    cout << "\nKhoảng cách từ đỉnh 0 đến các đỉnh khác (A*):" << endl;
    for (int i = 0; i < aStarDist.size(); ++i) {
        if (aStarDist[i] == numeric_limits<int>::max()) {
            cout << "Đỉnh " << i << ": Không đến được" << endl;
        } else {
            cout << "Đỉnh " << i << ": " << aStarDist[i] << endl;
        }
    }

    return 0;
}
