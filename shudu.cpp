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
bool nmfu[4];
bool checkflags(bool nmfu[4]){
    if(nmfu[1]&&!nmfu[0]){
        cout << "Error: Both -m and -n parameters must be used together." << endl;
        return false;
    }
    if(nmfu[2]&&!nmfu[0]){
        cout << "Error: Both -f and -n parameters must be used together." << endl;
        return false;
    }
    if(nmfu[3]&&!nmfu[0]){
        cout << "Error: Both -u and -n parameters must be used together." << endl;
        return false;
    }
    if(nmfu[1]&&nmfu[2]){
        cout << "Error: Both -m and -f parameters can't be used together." << endl;
    }
    return true;
}
class shudu {
public:
    int grid[N][N];
    int NUM_EMPTY_CELLS;    // 填入的空缺位置数量
	shudu() {
        NUM_EMPTY_CELLS = 20;
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
                if(grid[row][col]==EMPTY_CELL)
                    cout << "$";
                else
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
    bool readSudokuFromFile(string filename);
    void setNumEmptyCells(int num){
        NUM_EMPTY_CELLS = num;
    }
    bool hasempty();
    bool checkonly();
    void generateOnlySudoku();
    void copysudu(shudu t){
        for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				t.grid[i][j] = this->grid[i][j];
    }
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
    // printSudoku();
    // 填入空缺位置
    for (int i = 0; i < NUM_EMPTY_CELLS; i++) {
        int pos = positions[i];
        int row = pos / N;
        int col = pos % N;
        grid[row][col] = EMPTY_CELL;
    }
}

void shudu::clean() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;
}

// 将数独写入文件
void shudu::writeSudokuToFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if(grid[row][col]==EMPTY_CELL)
                    file << "$" << " ";
                else
                    file << grid[row][col] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Sudoku written to file: " << filename << endl;
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

// 从文件中读取数独
bool shudu::readSudokuFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                string cell;
                if (!(file >> cell)) {
                    cout << "Invalid Sudoku data in file: " << filename << endl;
                    return false;
                }

                if (cell == "$") {
                    grid[row][col] = EMPTY_CELL;
                } else {
                    grid[row][col] = stoi(cell);
                }
            }
        }
        file.close();
        return true;
    } else {
        cout << "Unable to open file: " << filename << endl;
        return false;
    }
}

bool shudu::hasempty(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]==EMPTY_CELL)
                return true;
        }
    }
    return false;
}
bool shudu::checkonly(){
    int resultnum=0;
    int nownum=0;
    shudu fuben;
    copysudu(fuben);
    while(fuben.hasempty()){
        int row, col;

        // 找到一个未填数字的位置(row, col)
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
                if (fuben.grid[row][col] == EMPTY_CELL) {
                    break;
                }
            }
        }

        for(int trynum=0;trynum<N;trynum++){
            if (fuben.isValid(row, col, trynum)) {
                shudu temp;
                fuben.copysudu(temp);
                temp.grid[row][col]=trynum;
                // 递归求解剩余的空格
                if (temp.solveSudoku()) {
                    resultnum++;
                    nownum=trynum;            
                }
            }
        }
        if(resultnum>1)
            return false;
        else{
            fuben.grid[row][col]=nownum;
        }

    }
    return true;
}

void shudu::generateOnlySudoku() {
    // 初始化为全0
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            grid[row][col] = EMPTY_CELL;
        }
    }

    // 生成完整的数独
    solveSudoku();
    int count=0;
    // 移除数字直到解不再唯一,并且最多移除30个
    while (count<70) {
        // 随机选择要移除的位置
        int row = rand() % N;
        int col = rand() % N;

        // 保存要移除的数字
        int removedNum = grid[row][col];

        // 暂时移除数字
        grid[row][col] = EMPTY_CELL;
        
        if (!checkonly()) {
            // 如果解不唯一，则恢复移除的数字
            grid[row][col] = removedNum;
            break;
        }
        count++;
    }

    // printSudoku();
}

int main(int argc, char* argv[]) {
    shudu a;
    const char* optstring = "c:s:n:m:f:u:";  
    for(int i=0;i<4;i++)nmfu[i]=false;
    int o;
    string filepath;
    int mode=1;//1生成终盘 2求解 3生成游戏
    int num=1;//生成的数量
    int difficulty = 1;  // 游戏难度级别，默认为1
    int EmptyCells=20;
    bool only=false; //生成的解是否唯一
    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 'c':
                num = atoi(optarg);
                break;
            case 's':
                mode=2;
                filepath = optarg;
                cout<<filepath<<endl;
                break;
            case 'n':
                nmfu[0]=true;
                mode = 3;
                num = atoi(optarg);
                break;
            case 'm':
                nmfu[1]=true;
                difficulty = atoi(optarg);
                break;
            case 'f':
                nmfu[2]=true;
                EmptyCells = atoi(optarg);
                break;
            case 'u':
                nmfu[3]=true;
                only=true;
                break;
            default:break;
        }
    }
    if(!checkflags(nmfu))
        return 0;
    switch (difficulty)
    {
    case 1:break;
    case 2:
        EmptyCells=38;
        a.setNumEmptyCells(EmptyCells);
        break;
    case 3:
        EmptyCells=55;
        a.setNumEmptyCells(EmptyCells);
        break;
    default:
        cout<<"ERROR: difficulty should be in [1,2,3]"<<endl;
        return 0;
    }
    if(EmptyCells>=20&&EmptyCells<=55)
        a.setNumEmptyCells(EmptyCells);
    else{
        cout<<"ERROR: EmptyCells should be in [20-55]"<<endl;
        return 0;
    }
    if(mode==1){
        int count=0;
        while(count<num){
            string strcount=to_string(count+1);
            filepath=".\\EndGameFile\\"+strcount+".txt";
            srand( (unsigned)time( 0 )+count );
            a.generateSudoku();
            a.solveSudoku();
            a.writeSudokuToFile(filepath);
            a.printSudoku();
            a.clean();
            count++;
        }
    }
    else if(mode==2){
        a.readSudokuFromFile(filepath);
        a.printSudoku();
        cout<<"solved shudu"<<endl;
        a.solveSudoku();
        a.printSudoku();
    }
    else if(mode==3){
        if(!only){
            int count=0;
            while(count<num){
                string strcount=to_string(count+1);
                filepath=".\\GameFile\\"+strcount+".txt";
                srand( (unsigned)time( 0 )+count );
                a.generateSudoku();
                a.writeSudokuToFile(filepath);
                a.printSudoku();
                a.clean();
                count++;
            }
        }
        else{
            int count=0;
            while(count<num){
                string strcount=to_string(count+1);
                filepath=".\\GameFile\\"+strcount+".txt";
                srand( (unsigned)time( 0 )+count );
                a.generateOnlySudoku();
                a.writeSudokuToFile(filepath);
                a.printSudoku();
                a.clean();
                count++;
            }
        }
    }
    return 0;
}