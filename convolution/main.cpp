#include <conio.h>
#include <iostream>
#include "main.h"
#include <windows.h>
using namespace std;

//��ʹ��һά�����ʾ����,�����

int main()
{
    // ������ر���
    char choice;
    char ch;

    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������
        menu(); // ���ò˵���ʾ����

        // ��Ҫ������˵�ѡ����choice
         choice = _getch();

        if (choice == '0') {// ѡ���˳�
            cout << "\n ȷ���˳���?" << endl;
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
                cout << "\n �����������������" << endl;
                wait_for_enter();
        }
    }
    return 0;
}

