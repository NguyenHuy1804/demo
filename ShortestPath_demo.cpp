#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // Giá trị vô cực để đại diện cho không thể đi đến

// Mảng hướng đi: Lên, Xuống, Trái, Phải
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

vector<vector<int>> memo;       // Bảng nhớ lưu khoảng cách ngắn nhất đến mỗi ô
vector<vector<bool>> visited;   // Đánh dấu các ô đã đi qua
int N;                          // Kích thước mê cung

// Kiểm tra xem ô (x, y) có hợp lệ để đi vào không
bool isValid(int x, int y, vector<vector<int>>& maze) {
    return (x >= 0 && x < N && y >= 0 && y < N) // Không vượt biên
        && (maze[x][y] == 0)                    // Không phải chướng ngại vật
        && (!visited[x][y]);                    // Chưa được đi qua
}

// Đệ quy tìm đường đi ngắn nhất từ (x, y) đến (N-1, N-1)
int findShortestPath(vector<vector<int>>& maze, int x, int y, int steps) {
    // Nếu đi vào ô không hợp lệ, trả về INF
    if (!isValid(x, y, maze)) return INF;

    // Nếu đã đến đích, trả về số bước hiện tại
    if (x == N - 1 && y == N - 1) return steps;

    // Nếu đã có kết quả tối ưu hơn, không cần tiếp tục
    if (memo[x][y] <= steps) return memo[x][y];

    // Đánh dấu đã đi qua ô này
    visited[x][y] = true;
    memo[x][y] = steps; // Lưu số bước tại ô này

    int minPath = INF; // Biến lưu giá trị nhỏ nhất tìm được

    // Thử đi 4 hướng: Lên, Xuống, Trái, Phải
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        minPath = min(minPath, findShortestPath(maze, newX, newY, steps + 1));
    }

    // Bỏ đánh dấu để cho phép thử các đường đi khác
    visited[x][y] = false;

    return minPath;
}

int main() {
    // Nhập kích thước mê cung
    cout << "Nhap kich thuoc me cung N: ";
    cin >> N;

    // Khởi tạo mê cung
    vector<vector<int>> maze(N, vector<int>(N));
    cout << "Nhap me cung (0: trong, 1: chuong ngai vat):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> maze[i][j];

    // Khởi tạo bảng nhớ và mảng đánh dấu
    memo.assign(N, vector<int>(N, INF));
    visited.assign(N, vector<bool>(N, false));

    // Tìm đường đi ngắn nhất
    int result = findShortestPath(maze, 0, 0, 0);

    // Xuất kết quả
    if (result == INF)
        cout << "Khong co duong di" << endl;
    else
        cout << "Do dai duong di ngan nhat: " << result << endl;

    return 0;
}
