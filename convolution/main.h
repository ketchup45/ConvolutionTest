#pragma once
#include<iostream>
using namespace std;

//showtools��ʾ����
void wait_for_enter();
void menu();//��ʾ�˵�
void GetMatrix(int* &mat, int& row, int& col, int set = 0);//�����ȡ����
void PrintMat(int*& mat, const int& row, const int& col);//��������ֵ

//BasicOperation��������
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv();

//ͼƬ����
struct ImageData {//������
	int row;//����
	int col;//����
	unsigned char* value;//�����ֵ
	ImageData(int Row, int Col) {
		//����ԭͼƬ�ĳߴ紴������
		row = Row;
		col = Col;
		value = new(nothrow) unsigned char[Row * Col];
		if (value == NULL)
			cout << "error";
	}
	~ImageData() {
		delete[]value;//�ͷ��ڴ�ռ�
	}
};

//���Ӧ��
void basicconv();
void basicOTSU();//��ֵ��
void moreOSTU();//�����ڻ�

