#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <algorithm> // std::max kullanımı için

using namespace std;

// Komşuluk için yön vektörleri
const vector<int> dx = {-1, 1, 0, 0};
const vector<int> dy = {0, 0, -1, 1};

// Matris boyutlarını kontrol etmek için yardımcı fonksiyon
bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// DFS fonksiyonu
int dfs(vector<vector<int>> &grid, int x, int y) {
    int rows = grid.size();
    int cols = grid[0].size();

            // Mevcut hücreyi ziyaret edilmiş olarak işaretleyin
    grid[x][y] = 0;

    int size = 1; // Ada büyüklüğü

            // 4 yönde ilerle
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isValid(newX, newY, rows, cols) && grid[newX][newY] == 1) {
            size += dfs(grid, newX, newY);
        }
    }

    return size;
}

int findLargestIsland(vector<vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int maxIslandSize = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                maxIslandSize = max(maxIslandSize, dfs(grid, i, j));
            }
        }
    }

    return maxIslandSize;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}
    };

    cout << "En büyük ada büyüklüğü: " << findLargestIsland(grid) << endl;

    return a.exec();
}
