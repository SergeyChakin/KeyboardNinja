#include "head.h"

using namespace std;



string a, *b, *ans, input = "", output = "", name1;//Объявляем наши строки; b,ans это массивы строк, в которые мы записываем разбирую по словам
												   //входную и выходную последовательности; input, output это просто строки, в которой хранится текст, нужны для поиска ошибок;
												   //name1 это имя файла, который мы открываем для считывания
COORD point, point1, point2;//координаты, нужные для перехода к определенной строки и столбцу консоли
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//Определяем дискриптор выходного потока данных



int modul(int x) {//функция модуля
	if (x < 0)
		return -x;
	return x;
}

void ramka() {
	setlocale(0, "");
	point2.X = 0;
	point2.Y = 9;
	SetConsoleCursorPosition(hout, point2);//переносим курсор
	for (int i = 1; i <= 80; ++i) {//рисуем верхнюю линию
		printf("%c", '_');
	}
	point2.Y = 20;
	SetConsoleCursorPosition(hout, point2);
	for (int i = 1; i <= 80; ++i) {//рисуем нижнюю линию
		printf("%c", '_');
	}
}

void result(int anserr) {
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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	time_t start1, end1, forstart, forend;//время для таймеров
	int counts = 0, countans = 0, i = 0, anserr = 0, lvl;
	char c;
	point.X = 0;
	point.Y = 0;
	point1.X = 0;
	point1.Y = 10;
	ifstream cin1("easy.h");
	ifstream cin2("norm.h");
	ifstream cin3("hard.h");
	cout << "Select the level of difficulty:" << endl << "1)Easy" << endl << "2)Normal" << endl << "3)Hard" << endl;
	cin >> lvl;
	b = new string[200];
	ans = new string[200];
	switch (lvl) {
	case 1:
		while (cin1 >> a) {//считываем с файла текст
			a += ' ';
			b[counts] = a;
			input += a;
			counts++;
		}
		break;
	case 2:
		while (cin2 >> a) {
			a += ' ';
			b[counts] = a;
			input += a;
			counts++;
		}
		break;
	case 3:
		while (cin3 >> a) {
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
	while (k < 7) {//цикл отсчета времени(5,4,3,2,1)
		time(&forend);
		if (forend - forstart >= k) {
			system("CLS");
			cout << 6 - k;
			k++;
		}  
	}
	time(&start1);
	for (i = 0; i < counts; ++i) {//Идем по всем словам, которые мы считали
		SetConsoleCursorPosition(hout, point);
		for (int j = 0; j < i + 1; ++j) {//Выводим слова, которые пользователю надо вводить
			cout << b[j];
		}
		if (i != 0) {//Вычисляем на сколько надо сдвигать курсор
			point1.X += ans[i - 1].size();
			if (point1.X >= 80)
				point1.X -= 80, point1.Y++;
		}

		ramka();
		SetConsoleCursorPosition(hout, point1);

		while (1) {//посимвольно читаем то, что вводит пользователь
			c = getch();//собственно читаем через getch()
			cout << c;
			if (c == '\b') {//здесь идет обработка нажатия бэкспейса(удаления символа)
				cout << " \b";//проблема в том, что бэкспейс мы не должны добавлять в наше слово, а при его нажатии, мы должны удалить последний введенный символ
			}
			if (c == '\b') {
				if (ans[i].size()) {//проверка, чтоб мы не удаляли из пустой строки
					ans[i].erase(ans[i].size() - 1, 1);//вот тут мы удаляем символ
				}
			}
			else {
				ans[i] += c;//здесь мы прибовляем введеный символ к слову
			}
			if (c == ' ' || c == 13) {//если нажат пробел или enter то ввод слова закончен
				break;
			}
		}
		output += ans[i];//Добавляем слово к выходной строке
	}
	time(&end1);
	end1 -= start1;//смотрим сколько времени прошло
	system("CLS");
	for (int i = 0; i < min(input.size(), output.size()); ++i) {//в этом цикле мы идем до размера минимальной из строк
		if (input[i] != output[i]) {//проверяем, ошибки
			anserr++;
		}
	}
	anserr += modul(input.size() - output.size());//нам надо к ошибка добавить разницу размеров входной и выходной строки
	cout << "Your speed: " << float(output.size()) / ((float(end1) / 60)) << " Chars per minute!" << endl;

	cout << "Errors: " << anserr << endl;
	result(anserr);
	getch();
	return 0;
}
