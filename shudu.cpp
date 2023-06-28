#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define N 9
#define EMPTY_CELL 0

int NUM_EMPTY_CELLS = 40;  // 填入的空缺位置数量

class shudu {
private:
	int grid[N][N];
public:
	shudu() {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				grid[i][j] = 0;
	}
    void printSudoku() {
        for (int row = 0; row < N; row++) {
            if (row % 3 == 0)
                cout << "--------------------" << endl;
            for (int col = 0; col < N; col++) {
                if (col % 3 == 0)
                    cout << "|";
                cout << grid[row][col];
                if (col != 8)cout << " ";
                else cout << "|";
            }
            cout << endl;
        }
    }
    bool isValid(int row, int col, int num);// 检查在(row, col)位置上填入数字num是否合法
    bool solveSudoku();// 递归求解数独
    void generateSudoku();//生成数独
    void clean();
    void writeSudokuToFile(const string filename);
};
bool shudu::isValid(int row, int col, int num) {
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
bool shudu::solveSudoku() {
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
    vector<int> nums{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_device rd;
    mt19937 g(rd());
    shuffle(nums.begin(), nums.end(), g);

    // 尝试填入随机顺序的数字
    for (int num : nums) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;

            // 递归求解剩余的空格
            if (solveSudoku()) {
                return true;
            }

            // 回溯
            grid[row][col] = EMPTY_CELL;
        }
    }

    return false;
}

void shudu::generateSudoku() {
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
    solveSudoku();
    printSudoku();
    // 填入空缺位置
    for (int i = 0; i < NUM_EMPTY_CELLS; i++) {
        int pos = positions[i];
        int row = pos / N;
        int col = pos % N;
        grid[row][col] = EMPTY_CELL;
    }
}

int main(){
    shudu a;
    a.generateSudoku();
    cout<<"generated sudu"<<endl;
    a.printSudoku();
    cout<<"solved sudu"<<endl;
    a.solveSudoku();
}