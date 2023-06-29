rem 测试生成终局
.\shudu.exe -c 3

rem 测试求解1
.\shudu.exe -s .\testfile\empty.txt
rem 测试求解2
.\shudu.exe -s .\testfile\full.txt 
rem 测试求解3
.\shudu.exe -s .\testfile\game_easy.txt
rem 测试求解4
.\shudu.exe -s .\testfile\game_middle.txt
rem 测试求解5
.\shudu.exe -s .\testfile\game_hard.txt  
rem 测试求解6
.\shudu.exe -s .\testfile\noresult.txt   
rem 测试求解7
.\shudu.exe -s .\testfile\wrong.txt  

rem 测试生成游戏1
.\shudu.exe -n 5
rem 测试生成游戏2
.\shudu.exe -n 3 -m 2
rem 测试生成游戏3
.\shudu.exe -n 3 -m 3
rem 测试生成游戏4
.\shudu.exe -n 4 -m 1
rem 测试生成游戏5
.\shudu.exe -n 3 -f 25   
rem 测试生成游戏6
.\shudu.exe -n 3 -f 19            
rem 测试生成游戏7
.\shudu.exe -n 3 -u        

rem 测试命令行参数兼容1
.\shudu.exe -m 3
rem 测试命令行参数兼容2
.\shudu.exe -f 30
rem 测试命令行参数兼容3
.\shudu.exe -m 3  -u        
rem 测试命令行参数兼容4
.\shudu.exe -m 3  -f 30 
