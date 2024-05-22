#include "main.h"
#include<iostream>
using namespace std;

//����ӷ�
void matriplus()
{
	system("cls"); // ��������
	cout << "���ڽ��о���ӷ�" << endl << endl;

	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊ��һ������ֵ" << endl;
	GetMatrix(mat1, row1, coL1);
	
	int* mat2 = NULL;//����2
	int row2;//����
	int coL2;//����
	cout << "��Ϊ�ڶ�������ֵ" << endl;
	GetMatrix(mat2, row2, coL2);

	if (row1 != row2)
		cout << "�����������ȣ��޷���ӣ�" << endl;
	else if (coL1 != coL2)
		cout << "�����������ȣ��޷���ӣ�" << endl;
	else { //�Ϸ�
		int* mat3 = NULL;//����3
		GetMatrix(mat3, row1, coL1, 1);
		//���
		for (int i = 0; i < row1; i++) 
			for (int j = 0; j < coL1; j++) 
				mat3[i * coL1 + j] = mat1[i * coL1 + j] + mat2[i * coL1 + j];

		cout << "����1Ϊ" << endl;
		PrintMat(mat1, row1, coL1);//��������ֵ
		cout << "����2Ϊ" << endl;
		PrintMat(mat2, row2, coL2);//��������ֵ
		cout << "������͵Ľ��Ϊ" << endl;
		PrintMat(mat3, row1, coL1);//��������ֵ

		//DeleteMat(mat3, row1, coL1);//�ͷ�
		delete[]mat3;
	}	
	//DeleteMat(mat1, row1, coL1);//�ͷ�
	//DeleteMat(mat2, row2, coL2);//�ͷ�
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//��������
void nummulti()
{
	system("cls"); // ��������
	cout << "���ڽ��о�������" << endl << endl;

	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊ����ֵ" << endl;
	GetMatrix(mat1, row1, coL1);

	int n;
	cout << "���������˵����֣�" ;
	cin >> n;
	cout << endl;

	cout << "ԭ����Ϊ" << endl;
	PrintMat(mat1, row1, coL1);//��������ֵ

	//����
	for (int i = 0; i < row1; i++)
		for (int j = 0; j < coL1; j++)
			mat1[i * coL1 + j] *= n;

	cout << "��������" << n << "�Ľ��Ϊ" << endl;
	PrintMat(mat1, row1, coL1);//��������ֵ

	//DeleteMat(mat1, row1, coL1);//�ͷ�
	delete[]mat1;
	wait_for_enter();
}

//����ת��
void matritrans()
{
	system("cls"); // ��������
	cout << "���ڽ��о���ת��" << endl << endl;

	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊ����ֵ" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//����2
	GetMatrix(mat2, coL1, row1, 1);

	//ת��
	for (int i = 0; i < coL1; i++)
		for (int j = 0; j < row1; j++)
			mat2[i * row1 + j] = mat1[j * coL1 + i];

	cout << "ԭ����Ϊ" << endl;
	PrintMat(mat1, row1, coL1);//��������ֵ
	cout << "����ת�õĽ��Ϊ" << endl;
	PrintMat(mat2, coL1, row1);//��������ֵ
		
	//DeleteMat(mat1, row1, coL1);//�ͷ�
	//DeleteMat(mat2, coL1, row1);//�ͷ�
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//����˷�
void matrimulti()
{
	system("cls"); // ��������
	cout << "���ڽ��о���˷�" << endl << endl;

	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊ��һ������ֵ" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//����2
	int row2;//����
	int coL2;//����
	cout << "��Ϊ�ڶ�������ֵ" << endl;
	GetMatrix(mat2, row2, coL2);

	if (coL1 != row2)
		cout << "����1�������;���2����������ȣ��޷���ˣ�" << endl;
	else { //�Ϸ�
		int* mat3 = NULL;//����3
		GetMatrix(mat3, row1, coL2, 1);
		//����˷�
		for (int i = 0; i < row1; i++)
			for (int j = 0; j < coL2; j++) {
				mat3[i * coL2 + j] = 0;
				for (int k = 0; k < coL1; k++) //�ۼ����
					mat3[i * coL2 + j] += (mat1[i * coL1 + k] * mat2[k * coL2 + j]);
			}		

		cout << "����1Ϊ" << endl;
		PrintMat(mat1, row1, coL1);//��������ֵ
		cout << "����2Ϊ" << endl;
		PrintMat(mat2, row2, coL2);//��������ֵ
		cout << "����˷��Ľ��Ϊ" << endl;
		PrintMat(mat3, row1, coL2);//��������ֵ

		//DeleteMat(mat3, row1, coL2);//�ͷ�
		delete[]mat3;
	}
	//DeleteMat(mat1, row1, coL1);//�ͷ�
	//DeleteMat(mat2, row2, coL2);//�ͷ�
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//hardmard�˷�
void hadamulti()
{
	system("cls"); // ��������
	cout << "���ڽ���hardmard�˷�" << endl << endl;

	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊ��һ������ֵ" << endl;
	GetMatrix(mat1, row1, coL1);

	int* mat2 = NULL;//����2
	int row2;//����
	int coL2;//����
	cout << "��Ϊ�ڶ�������ֵ" << endl;
	GetMatrix(mat2, row2, coL2);

	if (row1 != row2)
		cout << "�����������ȣ��޷�hardmard�˷���" << endl;
	else if (coL1 != coL2)
		cout << "�����������ȣ��޷�hardmard�˷���" << endl;
	else { //�Ϸ�
		int* mat3 = NULL;//����3
		GetMatrix(mat3, row1, coL1, 1);
		//hardmard�˷�
		for (int i = 0; i < row1; i++)
			for (int j = 0; j < coL1; j++)
				mat3[i * coL1 + j] = mat1[i * coL1 + j] * mat2[i * coL1 + j];

		cout << "����1Ϊ" << endl;
		PrintMat(mat1, row1, coL1);//��������ֵ
		cout << "����2Ϊ" << endl;
		PrintMat(mat2, row2, coL2);//��������ֵ
		cout << "hardmard�˷��Ľ��Ϊ" << endl;
		PrintMat(mat3, row1, coL1);//��������ֵ

		//DeleteMat(mat3, row1, coL1);//�ͷ�
		delete[]mat3;
	}
	//DeleteMat(mat1, row1, coL1);//�ͷ�
	//DeleteMat(mat2, row2, coL2);//�ͷ�
	delete[]mat1;
	delete[]mat2;
	wait_for_enter();
}

//����ԭ����
void MatPad(int*& mat1, const int& row1, const int& coL1, int*& mat2, int& row2, int& coL2, const int& padding);
//������
void conv()
{
	system("cls"); // ��������
	cout << "���ڽ��о�����" << endl << endl;
	
	int* mat1 = NULL;//����1
	int row1;//����
	int coL1;//����
	cout << "��Ϊԭ����ֵ" << endl;
	GetMatrix(mat1, row1, coL1);

	//���Ԥ��ֵ
	int kersiz = 3; //����˱߳�
	int padding = 1; //���0
	int stride = 1; //�ƶ��Ĳ���
	int dilation = 1; //��չ��

	//��ԭ��������
	int* mat2 = NULL;//����2
	int row2;//����
	int coL2;//����
	MatPad(mat1, row1, coL1, mat2, row2, coL2, padding);

	int* ker = NULL;//�����
	cout << "��Ϊ����˸�ֵ" << endl;
	GetMatrix(ker, kersiz, kersiz, 2);

	//�������
	int* mat3 = NULL;//����3
	GetMatrix(mat3, row1, coL1, 1);

	cout << "ԭ���������Ϊ��" << endl;
	PrintMat(mat2, row2, coL2);
	cout << "�����Ϊ��" << endl;
	PrintMat(ker, kersiz, kersiz);

	//�������о������
	for (int i1 = 0; i1 < row1; i1++)
		for (int j1 = 0; j1 < coL1; j1++) {
			int t = 0;
			//���� kersiz*kersiz
			for (int i2 = 0; i2 < kersiz; i2++)
				for (int j2 = 0; j2 < kersiz; j2++) 
					t += mat2[(i1 + i2) * coL2 + (j1 + j2)] * ker[i2 * kersiz + j2];
			mat3[i1 * coL1 + j1] = t; //���Ӧ���ĺ�
		}

	cout << "���������Ϊ��" << endl;
	PrintMat(mat3, row1, coL1);
	//�ͷſռ�
	delete[]mat1;
	delete[]mat2;
	delete[]mat3;
	delete[]ker;
	wait_for_enter();
}