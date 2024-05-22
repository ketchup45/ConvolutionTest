#include <conio.h>
#include <iostream>
#include <windows.h>
#include "main.h"
using namespace std;

void wait_for_enter()
{
    cout << endl
        << "���س�������";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

void menu()
{
    cout << "**************************************************************" << endl;
    cout << "*      1������ӷ�      2����������       3������ת��        *" << endl;
    cout << "*      4������˷�      5��hardmard�˷�   6��������        *" << endl;
    cout << "*      7�����Ӧ��      8��OSTU�㷨       0���˳�ϵͳ        *" << endl;
    cout << "*      9�������ڻ������Ʒ��                                 *" << endl;
    cout << "**************************************************************" << endl;
    cout << "ѡ��˵���<0-9>��" ;
}


//��ȡ����
void GetMatrix(int* &mat, int &row, int &col, int set)
{
    if (set == 0) { //�Ƿ��Ѿ����ú�ֵ
        cout << "���������������";
        cin >> row;
        cout << "���������������";
        cin >> col;
    }

    //��̬�ڴ�����
    mat = new(nothrow) int [row * col];
    if (mat == NULL)
        return;

    //���룬������ֵ
    if (set != 1) { //�Ƿ��Ѿ����ú�ֵ
        for (int i = 0; i < row; i++) {
            cout << "����������" << i + 1 << "�еĹ�" << col << "������ֵ" ;
            cout << "������֮���Կո������" << endl;
            for (int j = 0; j < col; j++)
                cin >> mat[i * col + j];
        }
        cout << endl;
    }
}

//�ͷž���ռ�(��Ϊһά����󣬱���������)
void DeleteMat(int** &mat, const int &row, const int& col)
{
    for (int i = 0; i < row; i++)
        delete[] mat[i];//���ͷ�ָ�������е�һ��ָ��
    delete[] mat;//���ͷŶ���ָ��
}

//��������ֵ
void PrintMat(int*& mat, const int& row, const int& col)
{
    for (int i = 0; i < row; i++) {
        cout << "{" ;
        for (int j = 0; j < col; j++)
            cout << mat[i * col + j] << "   ";
        cout << "}" << endl;
    }
}

//�ھ�������ж�ԭ��������
void MatPad(int*& mat1, const int& row1, const int& coL1, int*& mat2, int& row2, int& coL2, const int& padding)
{
    row2 = row1 + 2 * padding;
    coL2 = coL1 + 2 * padding;
    //��̬�ڴ�����
    mat2 = new(nothrow) int[row2 * coL2];
    if (mat2 == NULL)
        return;
    //������ֵ
    for (int i = 0; i < row2; i++) 
        for (int j = 0; j < coL2; j++) {
            if (i == 0 || j == 0 || i == row2 - 1 || j == coL2 - 1)
                mat2[i * coL2 + j] = 0;//���䲿�֣��ڱ�Ե
            else
                mat2[i * coL2 + j] = mat1[(i - 1) * coL1 + (j - 1)];//���ಿ��
        }
}

