#include <conio.h>
#include <iostream>
#include <windows.h>
#include "main.h"
using namespace std;

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

void menu()
{
    cout << "**************************************************************" << endl;
    cout << "*      1、矩阵加法      2、矩阵数乘       3、矩阵转置        *" << endl;
    cout << "*      4、矩阵乘法      5、hardmard乘法   6、矩阵卷积        *" << endl;
    cout << "*      7、卷积应用      8、OSTU算法       0、退出系统        *" << endl;
    cout << "*      9、背景黑化（半成品）                                 *" << endl;
    cout << "**************************************************************" << endl;
    cout << "选择菜单项<0-9>：" ;
}


//获取矩阵
void GetMatrix(int* &mat, int &row, int &col, int set)
{
    if (set == 0) { //是否已经设置好值
        cout << "请输入矩阵行数：";
        cin >> row;
        cout << "请输入矩阵列数：";
        cin >> col;
    }

    //动态内存申请
    mat = new(nothrow) int [row * col];
    if (mat == NULL)
        return;

    //输入，给矩阵赋值
    if (set != 1) { //是否已经设置好值
        for (int i = 0; i < row; i++) {
            cout << "请输入矩阵第" << i + 1 << "行的共" << col << "个数的值" ;
            cout << "（数字之间以空格隔开）" << endl;
            for (int j = 0; j < col; j++)
                cin >> mat[i * col + j];
        }
        cout << endl;
    }
}

//释放矩阵空间(改为一维数组后，本函数无用)
void DeleteMat(int** &mat, const int &row, const int& col)
{
    for (int i = 0; i < row; i++)
        delete[] mat[i];//先释放指针数组中的一级指针
    delete[] mat;//再释放二级指针
}

//输出矩阵的值
void PrintMat(int*& mat, const int& row, const int& col)
{
    for (int i = 0; i < row; i++) {
        cout << "{" ;
        for (int j = 0; j < col; j++)
            cout << mat[i * col + j] << "   ";
        cout << "}" << endl;
    }
}

//在卷积运算中对原矩阵扩充
void MatPad(int*& mat1, const int& row1, const int& coL1, int*& mat2, int& row2, int& coL2, const int& padding)
{
    row2 = row1 + 2 * padding;
    coL2 = coL1 + 2 * padding;
    //动态内存申请
    mat2 = new(nothrow) int[row2 * coL2];
    if (mat2 == NULL)
        return;
    //遍历赋值
    for (int i = 0; i < row2; i++) 
        for (int j = 0; j < coL2; j++) {
            if (i == 0 || j == 0 || i == row2 - 1 || j == coL2 - 1)
                mat2[i * coL2 + j] = 0;//扩充部分，在边缘
            else
                mat2[i * coL2 + j] = mat1[(i - 1) * coL1 + (j - 1)];//其余部分
        }
}

