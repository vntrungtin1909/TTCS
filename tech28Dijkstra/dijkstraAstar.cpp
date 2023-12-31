#include<bits/stdc++.h>
using namespace std;

const int maxn = 100001;
using ll = long long;
const int INF = 100001;

class Graph {
private:
    vector<pair<int, double>> adj[maxn];
    int pre[maxn];

public:
    void addEdge(int u, int v, double weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // Uncomment this line for undirected graph
    }

    vector<int> dijkstra(int start, int goal) {
        pre[0] = 0;
        vector<int> path;
        vector<ll> d(maxn, INF);
        d[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({0, start});

        while (!Q.empty()) {
            pair<int, int> top = Q.top();
            Q.pop();
            int u = top.second;
            int kc = top.first;
            if (kc > d[u]) continue;
            for (auto it : adj[u]) {
                int v = it.first;
                int w = it.second;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    Q.push({d[v], v});
                }
            }
        }

        if (d[goal] == INF) return path;

        while (1) {
            path.push_back(goal);
            if (goal == start) break;
            goal = pre[goal];
        }
        reverse(begin(path), end(path));
        return path;
    }

    vector<int> AStar(int start, int goal) {
        vector<int> path;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        vector<double> g_score(maxn, INFINITY);
        vector<double> f_score(maxn, INFINITY);
        vector<int> came_from(maxn, -1);

        g_score[start] = 0.0;
        f_score[start] = heuristic(start, goal);

        pq.push(make_pair(f_score[start], start));

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            if (current == goal) {
                path = reconstructPath(came_from, goal);
                break;
            }

            for (auto const& neighbor : adj[current]) {
                int neighbor_node = neighbor.first;
                double tentative_g_score = g_score[current] + neighbor.second;
                if (tentative_g_score < g_score[neighbor_node]) {
                    came_from[neighbor_node] = current;
                    g_score[neighbor_node] = tentative_g_score;
                    f_score[neighbor_node] = g_score[neighbor_node] + heuristic(neighbor_node, goal);
                    pq.push(make_pair(f_score[neighbor_node], neighbor_node));
                }
            }
        }

        return path;
    }

private:
    double heuristic(int from, int to) {
        return sqrt(pow((from - to), 2)); // Đây chỉ là heuristic đơn giản
    }

    vector<int> reconstructPath(vector<int>& came_from, int current) {
        vector<int> path;
        while (came_from[current] != -1) {
            path.insert(path.begin(), current);
            current = came_from[current];
        }
        path.insert(path.begin(), current);
        return path;
    }
};

int main() {
    Graph graph;

    // Đọc đầu vào từ người dùng và tạo đồ thị
    int num_dinh, num_canh, start, des;
    cin >> num_dinh >> num_canh >> start >> des;

    for (int i = 0; i < num_canh; ++i) {
        int x, y;
        double w;
        cin >> x >> y >> w;
        graph.addEdge(x, y, w);
    }

    // Sử dụng thuật toán Dijkstra để tìm đường đi từ 'start' đến 'des'
    vector<int> dijkstra_path = graph.dijkstra(start, des);

    // Sử dụng thuật toán A* để tìm đường đi từ 'start' đến 'des'
    vector<int> astar_path = graph.AStar(start, des);

    // Hiển thị đường đi tìm được từ cả hai thuật toán
    cout << "Đường đi từ " << start << " đến " << des << " (Dijkstra): ";
    if (dijkstra_path.empty()) {
        cout << "Không có đường đi" << endl;
    } else {
        for (int node : dijkstra_path) {
            cout << node << " ";
        }
        cout << endl;
    }

    cout << "Đường đi từ " << start << " đến " << des << " (A*): ";
    if (astar_path.empty()) {
        cout << "Không có đường đi" << endl;
    } else {
        for (int node : astar_path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
