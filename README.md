# 结对编程作业
生成、求解数独程序，windows10系统运行，使用g++编译，生成应用程序为shudu.exe。

------
<p align="left">
钱沛森 2012804<br>
张子昂 2012673<br>
专业：计算机科学与技术<br>
</p> 

------
## 功能
![这是图片](/pic/function.png "function")
## 关于代码
使用回溯算法编写，使用g++编译。
```
编译: g++ shudu.cpp -o shudu
```
## 代码测试
测试使用gcov+gcovr，gcov是g++配套的，gcovr需要pip下载。
测试样例在test.bat文件中，测试结果为两个html文件。
```
编译(代码测试用)：g++ -fprofile-arcs -ftest-coverage -fPIC -O0 shudu.cpp -o shudu
测试：./test.bat
可视化：gcovr -r . --html --html-details -o shudu-html-details.html
```