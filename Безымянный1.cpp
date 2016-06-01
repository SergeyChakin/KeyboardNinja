#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "fstream"
#include <string>
#include <math.h>
#include <algorithm>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <locale.h>
using namespace std;



string a, *b, *ans, input = "", output = "",name1;//��������� ���� ������; b,ans ��� ������� �����, � ������� �� ���������� �������� �� ������
//������� � �������� ������������������; input, output ��� ������ ������, � ������� �������� �����, ����� ��� ������ ������;
//name1 ��� ��� �����, ������� �� ��������� ��� ����������
COORD point, point1, point2;//����������, ������ ��� �������� � ������������ ������ � ������� �������
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//���������� ���������� ��������� ������ ������(����� ��� ���������� ������ SetConsoleCursorPosition!!)

void ramka(){//������� �������� �����
	setlocale(0,"");
	point2.X = 0;//���������� ���������� x � � ���� ��������� ������ � �������
	point2.Y = 9;
	SetConsoleCursorPosition(hout, point2);//��������� ������
	for (int i = 1; i <= 80; ++i){//������ ������� �����
		printf("%c", '_');
	}
	point2.Y = 20;
	SetConsoleCursorPosition(hout, point2);//��������� ������
	for (int i = 1; i <= 80; ++i){//������ ������ �����
		printf("%c", '_');
	}
}

int modul(int x){//������� ������
	if (x < 0)
		return -x;
	return x;
}
void result(int anserr){//��������� ���������
	if (anserr>17) cout << "Train more!";
	else if (anserr > 12) cout << "You can do batter!";
	else if (anserr >= 5) cout << "Not bad!";
	else if (anserr == 4) cout << "Wooden medal!";
	else if (anserr == 3) cout << "Bronze medal!";
	else if (anserr == 2) cout << "Silver medal!";
	else if (anserr == 1) cout << "Gold medal!";
	else if (anserr == 0) cout << "Brilliant!";
}
int main()
{
	SetConsoleCP (1251);
	SetConsoleOutputCP (1251);
	time_t start1, end1, forstart, forend;//����� ��� ��������
	int counts = 0, countans = 0, i = 0, anserr = 0, lvl;
	char c;
	point.X = 0;
	point.Y = 0;
	point1.X = 0;
	point1.Y = 10;
	ifstream cin1("easy.in");
	ifstream cin2("norm.in");
	ifstream cin3("hard.in");
	cout << "Select the level of difficulty:" << endl << "1)Easy" << endl << "2)Normal" << endl << "3)Hard" << endl;//�������� ������� ���������
	cin >> lvl;
	b = new string[200];
	ans = new string[200];
	switch (lvl){
	case 1:
	while (cin1 >> a){//��������� � ����� �����
		a += ' ';
		b[counts] = a;
		input += a;
		counts++;
		}
		break;
	case 2:
	while (cin2 >> a){//��������� � ����� �����
		a += ' ';
		b[counts] = a;
		input += a;
		counts++;
	}
	break;
	case 3:
	while (cin3 >> a){//��������� � ����� �����
		a += ' ';
		b[counts] = a;
		input += a;
		counts++;
	}
		break;
	default:
		break;
	}
	
	system("CLS");

	time(&forstart);
	int k = 1;
	while (k < 7){//���� ������� �������(5,4,3,2,1)
		time(&forend);
		if (forend - forstart >= k){
			system("CLS");
			cout << 6 - k;
			k++;
		}
	}
	time(&start1);//�������� �����
	for (i = 0; i < counts; ++i){//���� �� ���� ������, ������� �� �������
		SetConsoleCursorPosition(hout, point);//������������� ������ � ������
		for (int j = 0; j < i + 1; ++j){//������� �����, ������� ������������ ���� �������
			cout << b[j];
		}
		if (i != 0){//����� �� ��������� �� ������� ���� �������� ������
			point1.X += ans[i - 1].size();//� �������� ��� ���� �� ������ ����������� �����
			if (point1.X >= 80)
				point1.X -= 80, point1.Y++;
		}

		ramka();//������ �����
		SetConsoleCursorPosition(hout, point1);//������������� ������ �� ����� ��� �����

		while (1){//����������� ������ ��, ��� ������ ������������
			c = getch();//���������� ������ ����� getch()
			cout << c;//������� ��, ��� �� �������
			if (c == '\b'){//����� ���� ��������� ������� ���������(�������� �������)
				cout << " \b";//�������� � ���, ��� �������� �� �� ������ ��������� � ���� �����, � ��� ��� �������, �� ������ ������� ��������� ��������� ������
			}
			if (c == '\b'){
				if (ans[i].size()){//��������, ���� �� �� ������� �� ������ ������
					ans[i].erase(ans[i].size() - 1, 1);//��� ��� �� ������� ������
				}
			}
			else{
				ans[i] += c;//����� �� ���������� �������� ������ � �����
			}
			if (c == ' ' || c == 13){//���� ����� ������ ��� enter �� ���� ����� ��������
				break;
			}
		}
		output += ans[i];//��������� ����� � �������� ������
	}
	time(&end1);
	end1 -= start1;//������� ������� ������� ������
	system("CLS");
	for (int i = 0; i < min(input.size(), output.size()); ++i){//� ���� ����� �� ���� �� ������� ����������� �� �����
		if (input[i] != output[i]){//���������, ������
			anserr++;//������� �� ����������
		}
	}
	anserr += modul(input.size() - output.size());//��� ���� � ������ �������� ������� �������� ������� � �������� ������
	cout << "Your speed: " << float(output.size()) / ((float(end1) / 60)) << " Chars per minute!" << endl;//������� �������� �����

	cout << "Errors: " << anserr << endl;//���������� ������
	result(anserr);//� ���������
	getch();
	return 0;
}
