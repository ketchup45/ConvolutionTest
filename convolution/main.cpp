#include <conio.h>
#include <iostream>
#include "main.h"
#include <windows.h>
using namespace std;

//已使用一维数组表示矩阵,请检验

int main()
{
    // 定义相关变量
    char choice;
    char ch;

    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数
        menu(); // 调用菜单显示函数

        // 按要求输入菜单选择项choice
         choice = _getch();

        if (choice == '0') {// 选择退出
            cout << "\n 确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            case '1':
                matriplus();
                break;
            case '2':
                nummulti();
                break;
            case '3':
                matritrans();
                break;
            case '4':
                matrimulti();
                break;
            case '5':
                hadamulti();
                break;
            case '6':
                conv();
                break;
            case '7':
                basicconv();
                break;
            case '8':
                basicOTSU();
                break;
            case '9':
                moreOSTU();
                break;
            default:
                cout << "\n 输入错误，请重新输入" << endl;
                wait_for_enter();
        }
    }
    return 0;
}

