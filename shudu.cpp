#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

const int N = 9;
const int EMPTY_CELL = 0;
const int NUM_EMPTY_CELLS = 40;  // 填入的空缺位置数量

// 检查在(row, col)位置上填入数字num是否合法
bool isValid(int grid[N][N], int row, int col, int num) {
    // 检查行和列
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // 检查小九宫格
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// 递归求解数独
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // 找到一个未填数字的位置
    bool isFilled = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == EMPTY_CELL) {
                isFilled = true;
                break;
            }
        }
        if (isFilled) {
            break;
        }
    }

    // 如果所有位置都已填满，则数独已解决
    if (!isFilled) {
        return true;
    }

    // 生成随机数字的顺序
    vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_device rd;
    mt19937 g(rd());
    shuffle(nums.begin(), nums.end(), g);

    // 尝试填入随机顺序的数字
    for (int num : nums) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            // 递归求解剩余的空格
            if (solveSudoku(grid)) {
                return true;
            }

            // 回溯
            grid[row][col] = EMPTY_CELL;
        }
    }

    return false;
}

// 生成数独
void generateSudoku(int grid[N][N]) {
    // 初始化为全0
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            grid[row][col] = EMPTY_CELL;
        }
    }

    // 随机选择要填入空缺位置的行和列
    vector<int> positions(N * N);
    for (int i = 0; i < N * N; i++) {
        positions[i] = i;
    }
    random_shuffle(positions.begin(), positions.end());

    // 填入空缺位置
    for (int i = 0; i < NUM_EMPTY_CELLS; i++) {
        int pos = positions[i];
        int row = pos / N;
        int col = pos % N;
        grid[row][col] = EMPTY_CELL;
    }

    solveSudoku(grid);
}

// 打印数独
void printSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    int grid[N][N];

    generateSudoku(grid);
    cout << "Generated Sudoku:" << endl;
    printSudoku(grid);

    return 0;
}
