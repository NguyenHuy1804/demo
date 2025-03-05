#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // Giá trị vô cực

int dx[4] = { -1, 1, 0, 0 }; // Lên, xuống
int dy[4] = { 0, 0, -1, 1 }; // Trái, phải

vector<vector<int>> memo;
vector<vector<bool>> visited; // Mảng đánh dấu ô đã đi qua
int N;

// Kiểm tra ô hợp lệ
bool isValid(int x, int y, vector<vector<int>>& maze) {
    return x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0 && !visited[x][y];
}

// Hàm đệ quy tìm đường đi ngắn nhất
int findShortestPath(vector<vector<int>>& maze, int x, int y, int steps) {
    if (!isValid(x, y, maze)) return INF; // Nếu đi vào ô không hợp lệ

    if (x == N - 1 && y == N - 1) return steps; // Nếu đến đích

    if (memo[x][y] != INF && memo[x][y] <= steps) return memo[x][y]; // Nếu đã có kết quả tốt hơn

    visited[x][y] = true; // Đánh dấu đã đi qua

    int minPath = INF;
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        minPath = min(minPath, findShortestPath(maze, newX, newY, steps + 1));
    }

    visited[x][y] = false; // Bỏ đánh dấu để thử nhánh khác

    memo[x][y] = minPath; // Lưu kết quả tối ưu
    return minPath;
}

int main() {
    cout << "Nhap kich thuoc me cung N: ";
    cin >> N;

    vector<vector<int>> maze(N, vector<int>(N));
    cout << "Nhap me cung (0: trong, 1: chuong ngai vat):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> maze[i][j];

    memo.assign(N, vector<int>(N, INF)); // Khởi tạo memo
    visited.assign(N, vector<bool>(N, false)); // Khởi tạo mảng visited

    int result = findShortestPath(maze, 0, 0, 0);

    if (result == INF)
        cout << "Khong co duong di!" << endl;
    else
        cout << "Do dai duong di ngan nhat: " << result << endl;

    return 0;
}
