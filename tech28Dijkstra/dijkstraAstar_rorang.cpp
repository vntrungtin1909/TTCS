#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Vertex {
public:
    int id;
    vector<pair<int, int>> neighbors;

    Vertex(int id) : id(id) {}
    void addNeighbor(int neighborId, int weight) {
        neighbors.push_back(make_pair(neighborId, weight));
    }
};

class Graph {
public:
    vector<Vertex> vertices;

    void addVertex(const Vertex& vertex) {
        vertices.push_back(vertex);
    }
};

class RoutingTable {
public:
    int destination;
    int previousVertex;
    int distance;

    RoutingTable(int destination) : destination(destination), previousVertex(-1), distance(numeric_limits<int>::max()) {}
};

class DijkstraAlgorithm {
public:
    Graph graph;

    DijkstraAlgorithm(const Graph& graph) : graph(graph) {}

    void dijkstra(int startVertexId) {
        int numVertices = graph.vertices.size();
        vector<RoutingTable> routingTables(numVertices, RoutingTable(startVertexId));
        routingTables[startVertexId].distance = 0;

        auto compare = [](const RoutingTable& a, const RoutingTable& b) {
            return a.distance > b.distance;
        };
        priority_queue<RoutingTable, vector<RoutingTable>, decltype(compare)> pq(compare);
        pq.push(routingTables[startVertexId]);

        while (!pq.empty()) {
            RoutingTable currentRoutingTable = pq.top();
            pq.pop();

            if (currentRoutingTable.distance > routingTables[currentRoutingTable.destination].distance) {
                continue;
            }

            const Vertex& currentVertex = graph.vertices[currentRoutingTable.destination];

            for (auto neighbor : currentVertex.neighbors) {
                int neighborId = neighbor.first;
                int weight = neighbor.second;
                int distance = currentRoutingTable.distance + weight;

                if (distance < routingTables[neighborId].distance) {
                    routingTables[neighborId].distance = distance;
                    routingTables[neighborId].previousVertex = currentRoutingTable.destination;
                    pq.push(routingTables[neighborId]);
                }
            }
        }

        // Print shortest paths
        for (int i = 0; i < numVertices; i++) {
            cout << "Shortest path to vertex " << i << ":\n";
            int currentVertexId = i;
            while (currentVertexId != startVertexId) {
                cout << currentVertexId << " ";
                currentVertexId = routingTables[currentVertexId].previousVertex;
            }
            cout << startVertexId << "\n";
        }
    }
};

class AStarAlgorithm {
public:
    Graph graph;
    int (*heuristic)(int, int);

    AStarAlgorithm(const Graph& graph, int (*heuristic)(int, int)) : graph(graph), heuristic(heuristic) {}

    void astar(int startVertexId, int goalVertexId) {
        int numVertices = graph.vertices.size();
        vector<RoutingTable> routingTables(numVertices, RoutingTable(goalVertexId));
        routingTables[startVertexId].distance = 0;

        auto compare = [this, goalVertexId](const RoutingTable& a, const RoutingTable& b) {
            return a.distance > b.distance;
        };
        priority_queue<RoutingTable, vector<RoutingTable>, decltype(compare)> pq(compare);
        pq.push(routingTables[startVertexId]);

        while (!pq.empty()) {
            RoutingTable currentRoutingTable = pq.top();
            pq.pop();

            int currentVertexId = currentRoutingTable.destination;

            if (currentVertexId == goalVertexId) {
                break;
            }

            const Vertex& currentVertex = graph.vertices[currentVertexId];

            for (auto neighbor : currentVertex.neighbors) {
                int neighborId = neighbor.first;
                int weight = neighbor.second;
                int distance = currentRoutingTable.distance + weight + heuristic(neighborId, goalVertexId);

                if (distance < routingTables[neighborId].distance) {
                    routingTables[neighborId].distance = distance;
                    routingTables[neighborId].previousVertex = currentVertexId;
                    pq.push(RoutingTable(neighborId));
                }
            }
        }

        // Print shortest path
        cout << "Shortest path from " << startVertexId << " to " << goalVertexId << ":\n";
        int currentVertexId = goalVertexId;
        while (currentVertexId != startVertexId) {
            cout << currentVertexId << " ";
            currentVertexId = routingTables[currentVertexId].previousVertex;
        }
        cout << startVertexId << "\n";
    }
};


// Example usage:
int heuristic(int source, int destination) {
    // Example heuristic function (Euclidean distance between vertices)
    // Not an actual implementation, just for demonstration purposes
    return abs(source - destination);
}

int main() {
    // Create vertices
    Vertex a(0);
    Vertex b(1);
    Vertex c(2);
    Vertex d(3);
    Vertex e(4);

    // Add edges
    a.addNeighbor(1, 4);
    a.addNeighbor(2, 2);
    b.addNeighbor(3, 5);
    c.addNeighbor(1, 1);
    c.addNeighbor(3, 8);
    c.addNeighbor(4, 10);
    d.addNeighbor(2, 2);

    // Create graph
    Graph graph;
    graph.addVertex(a);
    graph.addVertex(b);
    graph.addVertex(c);
    graph.addVertex(d);
    graph.addVertex(e);

    // Create Dijkstra algorithm instance
    DijkstraAlgorithm dijkstra(graph);

    // Run Dijkstra algorithm
    dijkstra.dijkstra(0);

    // Create A* algorithm instance
    AStarAlgorithm astar(graph, heuristic);

    // Run A* algorithm
    astar.astar(0, 3);

    return 0;
}