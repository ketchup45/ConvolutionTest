#pragma once
#include<iostream>
using namespace std;

//showtools显示界面
void wait_for_enter();
void menu();//显示菜单
void GetMatrix(int* &mat, int& row, int& col, int set = 0);//输入获取矩阵
void PrintMat(int*& mat, const int& row, const int& col);//输出矩阵的值

//BasicOperation基本运算
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv();

//图片运算
struct ImageData {//矩阵类
	int row;//行数
	int col;//列数
	unsigned char* value;//矩阵的值
	ImageData(int Row, int Col) {
		//根据原图片的尺寸创建数组
		row = Row;
		col = Col;
		value = new(nothrow) unsigned char[Row * Col];
		if (value == NULL)
			cout << "error";
	}
	~ImageData() {
		delete[]value;//释放内存空间
	}
};

//卷积应用
void basicconv();
void basicOTSU();//二值化
void moreOSTU();//背景黑化

