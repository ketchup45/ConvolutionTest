#include "main.h"
#include<iostream>
using namespace std;

//矩阵加法
void matriplus()
{
	system("cls"); // 清屏函数
	cout << "正在进行矩阵加法" << endl << endl;

	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为第一个矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);
	
	int* mat2 = NULL;//矩阵2
	int row2;//行数
	int coL2;//列数
	cout << "请为第二个矩阵赋值" << endl;
	GetMatrix(mat2, row2, coL2);

	if (row1 != row2)
		cout << "矩阵行数不等，无法相加！" << endl;
	else if (coL1 != coL2)
		cout << "矩阵列数不等，无法相加！" << endl;
	else { //合法
		int* mat3 = NULL;//矩阵3
		GetMatrix(mat3, row1, coL1, 1);
		//求和
		for (int i = 0; i < row1; i++) 
			for (int j = 0; j < coL1; j++) 
				mat3[i * coL1 + j] = mat1[i * coL1 + j] + mat2[i * coL1 + j];

		cout << "矩阵1为" << endl;
		PrintMat(mat1, row1, coL1);//输出矩阵的值
		cout << "矩阵2为" << endl;
		PrintMat(mat2, row2, coL2);//输出矩阵的值
		cout << "矩阵求和的结果为" << endl;
		PrintMat(mat3, row1, coL1);//输出矩阵的值

		//DeleteMat(mat3, row1, coL1);//释放
		delete[]mat3;
	}	
	//DeleteMat(mat1, row1, coL1);//释放
	//DeleteMat(mat2, row2, coL2);//释放
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//矩阵数乘
void nummulti()
{
	system("cls"); // 清屏函数
	cout << "正在进行矩阵数乘" << endl << endl;

	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);

	int n;
	cout << "请输入数乘的数字：" ;
	cin >> n;
	cout << endl;

	cout << "原矩阵为" << endl;
	PrintMat(mat1, row1, coL1);//输出矩阵的值

	//数乘
	for (int i = 0; i < row1; i++)
		for (int j = 0; j < coL1; j++)
			mat1[i * coL1 + j] *= n;

	cout << "矩阵数乘" << n << "的结果为" << endl;
	PrintMat(mat1, row1, coL1);//输出矩阵的值

	//DeleteMat(mat1, row1, coL1);//释放
	delete[]mat1;
	wait_for_enter();
}

//矩阵转置
void matritrans()
{
	system("cls"); // 清屏函数
	cout << "正在进行矩阵转置" << endl << endl;

	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//矩阵2
	GetMatrix(mat2, coL1, row1, 1);

	//转置
	for (int i = 0; i < coL1; i++)
		for (int j = 0; j < row1; j++)
			mat2[i * row1 + j] = mat1[j * coL1 + i];

	cout << "原矩阵为" << endl;
	PrintMat(mat1, row1, coL1);//输出矩阵的值
	cout << "矩阵转置的结果为" << endl;
	PrintMat(mat2, coL1, row1);//输出矩阵的值
		
	//DeleteMat(mat1, row1, coL1);//释放
	//DeleteMat(mat2, coL1, row1);//释放
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//矩阵乘法
void matrimulti()
{
	system("cls"); // 清屏函数
	cout << "正在进行矩阵乘法" << endl << endl;

	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为第一个矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//矩阵2
	int row2;//行数
	int coL2;//列数
	cout << "请为第二个矩阵赋值" << endl;
	GetMatrix(mat2, row2, coL2);

	if (coL1 != row2)
		cout << "矩阵1的列数和矩阵2的行数不相等，无法相乘！" << endl;
	else { //合法
		int* mat3 = NULL;//矩阵3
		GetMatrix(mat3, row1, coL2, 1);
		//矩阵乘法
		for (int i = 0; i < row1; i++)
			for (int j = 0; j < coL2; j++) {
				mat3[i * coL2 + j] = 0;
				for (int k = 0; k < coL1; k++) //累加求和
					mat3[i * coL2 + j] += (mat1[i * coL1 + k] * mat2[k * coL2 + j]);
			}		

		cout << "矩阵1为" << endl;
		PrintMat(mat1, row1, coL1);//输出矩阵的值
		cout << "矩阵2为" << endl;
		PrintMat(mat2, row2, coL2);//输出矩阵的值
		cout << "矩阵乘法的结果为" << endl;
		PrintMat(mat3, row1, coL2);//输出矩阵的值

		//DeleteMat(mat3, row1, coL2);//释放
		delete[]mat3;
	}
	//DeleteMat(mat1, row1, coL1);//释放
	//DeleteMat(mat2, row2, coL2);//释放
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//hardmard乘法
void hadamulti()
{
	system("cls"); // 清屏函数
	cout << "正在进行hardmard乘法" << endl << endl;

	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为第一个矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//矩阵2
	int row2;//行数
	int coL2;//列数
	cout << "请为第二个矩阵赋值" << endl;
	GetMatrix(mat2, row2, coL2);

	if (row1 != row2)
		cout << "矩阵行数不等，无法hardmard乘法！" << endl;
	else if (coL1 != coL2)
		cout << "矩阵列数不等，无法hardmard乘法！" << endl;
	else { //合法
		int* mat3 = NULL;//矩阵3
		GetMatrix(mat3, row1, coL1, 1);
		//hardmard乘法
		for (int i = 0; i < row1; i++)
			for (int j = 0; j < coL1; j++)
				mat3[i * coL1 + j] = mat1[i * coL1 + j] * mat2[i * coL1 + j];

		cout << "矩阵1为" << endl;
		PrintMat(mat1, row1, coL1);//输出矩阵的值
		cout << "矩阵2为" << endl;
		PrintMat(mat2, row2, coL2);//输出矩阵的值
		cout << "hardmard乘法的结果为" << endl;
		PrintMat(mat3, row1, coL1);//输出矩阵的值

		//DeleteMat(mat3, row1, coL1);//释放
		delete[]mat3;
	}
	//DeleteMat(mat1, row1, coL1);//释放
	//DeleteMat(mat2, row2, coL2);//释放
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//扩充原矩阵
void MatPad(int*& mat1, const int& row1, const int& coL1, int*& mat2, int& row2, int& coL2, const int& padding);
//矩阵卷积
void conv()
{
	system("cls"); // 清屏函数
	cout << "正在进行矩阵卷积" << endl << endl;
	
	int* mat1 = NULL;//矩阵1
	int row1;//行数
	int coL1;//列数
	cout << "请为原矩阵赋值" << endl;
	GetMatrix(mat1, row1, coL1);

	//卷积预设值
	int kersiz = 3; //卷积核边长
	int padding = 1; //填充0
	int stride = 1; //移动的步长
	int dilation = 1; //扩展率

	//对原矩阵扩充
	int* mat2 = NULL;//矩阵2
	int row2;//行数
	int coL2;//列数
	MatPad(mat1, row1, coL1, mat2, row2, coL2, padding);

	int* ker = NULL;//卷积核
	cout << "请为卷积核赋值" << endl;
	GetMatrix(ker, kersiz, kersiz, 2);

	//结果矩阵
	int* mat3 = NULL;//矩阵3
	GetMatrix(mat3, row1, coL1, 1);

	cout << "原矩阵扩充后为：" << endl;
	PrintMat(mat2, row2, coL2);
	cout << "卷积核为：" << endl;
	PrintMat(ker, kersiz, kersiz);

	//遍历进行卷积运算
	for (int i1 = 0; i1 < row1; i1++)
		for (int j1 = 0; j1 < coL1; j1++) {
			int t = 0;
			//遍历 kersiz*kersiz
			for (int i2 = 0; i2 < kersiz; i2++)
				for (int j2 = 0; j2 < kersiz; j2++) 
					t += mat2[(i1 + i2) * coL2 + (j1 + j2)] * ker[i2 * kersiz + j2];
			mat3[i1 * coL1 + j1] = t; //求对应积的和
		}

	cout << "矩阵卷积结果为：" << endl;
	PrintMat(mat3, row1, coL1);
	//释放空间
	delete[]mat1;
	delete[]mat2;
	delete[]mat3;
	delete[]ker;
	wait_for_enter();
}