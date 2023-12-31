#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Graph
{
private:
    vector<vector<pair<int, double>>> adjacency_list;

public:
    Graph(int n) : adjacency_list(n) {}

    vector<pair<int, double>> wGraph(int n)
    {
        return adjacency_list[n];
    }

    void addEdge(int u, int v, double weight)
    {
        adjacency_list[u].push_back(make_pair(v, weight));
        adjacency_list[v].push_back(make_pair(u, weight)); 
    }

    vector<int> AStar(int start, int goal)
    {
        vector<int> path;
        int num_vertices = adjacency_list.size();
        if (start < 0 || start >= num_vertices || goal < 0 || goal >= num_vertices)
            return path; // Nếu không có đỉnh start hoặc goal trong đồ thị, trả về đường đi trống

        vector<double> g_score(num_vertices, INFINITY);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        vector<double> f_score(num_vertices, INFINITY);
        vector<int> came_from(num_vertices, -1);

        g_score[start] = 0.0;
        f_score[start] = heuristic(start, goal);

        pq.push(make_pair(heuristic(start, goal), start));

        while (!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();

            if (current == goal)
            {
                path = reconstructPath(came_from, goal);
                break;
            }

            for (auto const &neighbor : adjacency_list[current])
            {
                int neighbor_node = neighbor.first;
                double tentative_g_score = g_score[current] + neighbor.second;
                if (tentative_g_score < g_score[neighbor_node])
                {
                    came_from[neighbor_node] = current;
                    g_score[neighbor_node] = tentative_g_score;
                    f_score[neighbor_node] = g_score[neighbor_node] + heuristic(neighbor_node, goal);
                    pq.push(make_pair(g_score[neighbor_node] + heuristic(neighbor_node, goal), neighbor_node));
                }
            }
        }

        return path;
    }

private:
    double heuristic(int from, int to)
    {
        // Hàm heuristic ở đây có thể được thay đổi tùy thuộc vào vấn đề cụ thể
        // Trong trường hợp đơn giản, chúng ta có thể sử dụng khoảng cách Euclid
        return sqrt(pow((from - to), 2)); // Đây chỉ là heuristic đơn giản
    }

    vector<int> reconstructPath(vector<int> &came_from, int current)
    {
        vector<int> path;
        while (came_from[current] != -1)
        {
            path.insert(path.begin(), current);
            current = came_from[current];
        }
        path.insert(path.begin(), current);
        return path;
    }
};

int main()
{
    int num_vertices = 6; // Số lượng đỉnh trong đồ thị

    Graph graph(num_vertices);
    // Thêm các cạnh vào đồ thị
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 6);
    graph.addEdge(4, 5, 1);

    // Sử dụng thuật toán A* để tìm đường đi từ đỉnh 0 đến đỉnh 5
    vector<int> path = graph.AStar(1, 4);
    double sum = 0;
    // Hiển thị đường đi tìm được
    cout << "Đường đi từ đỉnh 0 đến đỉnh 5: ";
    for (int i = 0; i < path.size(); ++i)
    {
        int currentNode = path[i];
        int nextNode = (i + 1 < path.size()) ? path[i + 1] : -1;

        // Thực hiện các thao tác với currentNode và nextNode ở đây
        cout << currentNode << " ";

        // Nếu không phải là đỉnh cuối cùng, tính tổng trọng số
        if (nextNode != -1)
        {
            vector<pair<int, double>> q = graph.wGraph(currentNode);
            for (auto const &neighbor : q)
            {
                if (neighbor.first == nextNode)
                {
                    sum += neighbor.second;
                    break;
                }
            }
        }
    }
    cout << endl;
    cout << "Tổng trọng số của đường đi: " << sum << endl;


    return 0;
}
