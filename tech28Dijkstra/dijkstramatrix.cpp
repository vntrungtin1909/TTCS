#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <tuple>
#include <stack>

using namespace std;

class ShortestPath {
    int rows, cols;
    vector<vector<int>> grid;
    vector<vector<int>> distances;
    vector<vector<pair<int, int>>> previous; // Lưu trữ thông tin đỉnh trước của mỗi đỉnh

public:
    ShortestPath(const vector<vector<int>>& matrix) {
        rows = matrix.size();
        cols = matrix[0].size();
        grid = matrix;
    }

    int dijkstra(pair<int, int> start, pair<int, int> end) {
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        distances.assign(rows, vector<int>(cols, INT_MAX));
        previous.assign(rows, vector<pair<int, int>>(cols, {-1, -1}));

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        distances[start.first][start.second] = grid[start.first][start.second];
        pq.push(make_tuple(distances[start.first][start.second], start.first, start.second));

        while (!pq.empty()) {
            int distance, x, y;
            tie(distance, x, y) = pq.top();
            pq.pop();

            if (x == end.first && y == end.second) {
                return distances[x][y];
            }

            for (auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    int newDistance = distance + grid[newX][newY];

                    if (newDistance < distances[newX][newY]) {
                        distances[newX][newY] = newDistance;
                        previous[newX][newY] = {x, y}; // Lưu thông tin đỉnh trước
                        pq.push(make_tuple(newDistance, newX, newY));
                    }
                }
            }
        }

        return INT_MAX;
    }

    // Truy vết đường đi từ đỉnh bắt đầu đến đỉnh kết thúc
    stack<pair<int, int>> tracePath(pair<int, int> start, pair<int, int> end) {
        stack<pair<int, int>> path;
        pair<int, int> current = end;

        while (current != start) {
            path.push(current);
            current = previous[current.first][current.second];
        }

        path.push(start); // Thêm đỉnh bắt đầu vào đường đi

        return path;
    }

    void show(pair<int, int> start, pair<int, int> end) {
        int shortestDistance = dijkstra(start, end);
        if (shortestDistance!= INT_MAX) {
        cout << "Khoang cach ngan nhat tu " << start.first << "," << start.second << " den " << end.first << "," << end.second << " la: " << shortestDistance << endl;

        stack<pair<int, int>> path = tracePath(start, end);

        cout << "Duong di: ";
        while (!path.empty()) {
            pair<int, int> vertex = path.top();
            path.pop();
            cout << "(" << vertex.first << "," << vertex.second << ") ";
        }
        cout << endl;
        } else {
        cout << "Khong co duong di tu " << start.first << "," << start.second << " den " << end.first << "," << end.second << endl;
        }

    }
};

int main() {
    vector<vector<int>> matrix = {
        {1, 1, 1},
        {15, 12, 1},
        {16, 1, 1}
    };

    ShortestPath sp(matrix);
    pair<int, int> start = {0, 0};
    pair<int, int> end = {2, 1};
    sp.show(start, end);

    // int shortestDistance = sp.dijkstra(start, end);

    // if (shortestDistance != INT_MAX) {
    //     cout << "Khoang cach ngan nhat tu " << start.first << "," << start.second << " den " << end.first << "," << end.second << " la: " << shortestDistance << endl;

    //     stack<pair<int, int>> path = sp.tracePath(start, end);

    //     cout << "Duong di: ";
    //     while (!path.empty()) {
    //         pair<int, int> vertex = path.top();
    //         path.pop();
    //         cout << "(" << vertex.first << "," << vertex.second << ") ";
    //     }
    //     cout << endl;
    // } else {
    //     cout << "Khong co duong di tu " << start.first << "," << start.second << " den " << end.first << "," << end.second << endl;
    // }

    return 0;
}
