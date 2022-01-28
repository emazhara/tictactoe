#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

#define MAINMENU 1
#define NEWGAME 2
#define INGAME 3
#define X 1
#define O 0

class Menu {
public:
	int points;
	string* text;
	Menu(int points) {
		this->points = points;
		text = new string[points];
	}
	void print() {
		cout << "�������� ����� ����:" << endl;
		for (int i = 0; i < this->points; i++) {
			cout << i + 1 << ". " << text[i] << endl;
		}
	}
};

class Field {
public:
	static const int width = 3;
	static const int height = 3;
	int** matrix;
	Field() {
		matrix = new int* [height];
		for (int i = 0; i < height; i++) {
			matrix[i] = new int[width];
			for (int j = 0; j < width; j++)
				matrix[i][j] = 2;
		}
	}
	~Field() {
		for (int i = 0; i < height; i++)
			delete [] matrix[i];
		delete [] matrix;
	}
	void printField() {
		cout << "_ _ _ _ _ _ _ _ _ _" << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << "|  ";
				if (matrix[i][j] == X)
					cout << "X  ";
				else if (matrix[i][j] == O)
					cout << "O  ";
				else
					cout << "   ";
			}
			cout << "|";
			cout << endl;
			cout << "_ _ _ _ _ _ _ _ _ _" << endl;
		}
	}
	int whoIsWinning() {
		for (int i = 0; i < height; i++) {  // �������� 3 ���������� �������� � ������
			int result1 = 1, result2 = 0;
			for (int j = 0; j < width; j++) {
				result1 *= matrix[i][j];
				result2 += matrix[i][j];
			}
			if (result1 == 1)
				return X;
			else if (result2 == 0)
				return O;
		}
		for (int j = 0; j < width; j++) {  // �������� 3 ���������� �������� � �������
			int result1 = 1, result2 = 0;
			for (int i = 0; i < height; i++) {
				result1 *= matrix[i][j];
				result2 += matrix[i][j];
			}
			if (result1 == 1)
				return X;
			else if (result2 == 0)
				return O;
		}
		{  // �������� 3 ���������� �������� �� ����������
			int result1 = 1, result2 = 0;
			for (int i = 0; i < height; i++) {
				result1 *= matrix[i][i];
				result2 += matrix[i][i];
			}
			if (result1 == 1)
				return X;
			else if (result2 == 0)
				return O;
			for (int i = 0; i < height; i++) {
				result1 *= matrix[i][width - i - 1];
				result2 += matrix[i][width - i - 1];
			}
			if (result1 == 1)
				return X;
			else if (result2 == 0)
				return O;
		}
		return -1;
	}
	void clearField() {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				this->matrix[i][j] = 2;
	}
	bool isFieldFull() {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (this->matrix[i][j] == 2)
					return false;
		return true;
	}
};

class Game {
public:
	Field* f;
	int currentPlayer;

	Game() {
		this->f = new Field();
		this->f->clearField();
		this->currentPlayer = 1;
	}
	~Game() {
		delete f;
	}
	int gameStep() {  // ��������������, ��� ����������� �� ������ ���� ���, �������� � main
		system("cls");
		cout << "������� ������� \"P\" ����� ���������� ����" << endl << endl;
		cout << "��� ������ " << this->currentPlayer << endl << endl;
		this->f->printField();
		cout << endl << "�������� ����� ������, � ������� ��������� ������ ������" << endl;
		char input;
		cin >> input;
		int selectedCellH = 0, selectedCellW = 0;
		switch (input) {
		case '1':
			selectedCellH = 1;
			break;
		case '2':
			selectedCellH = 2;
			break;
		case '3':
			selectedCellH = 3;
			break;
		case 'P':
			return 1;  // ��������� ���������� �����
		case 'p':
			return 1;
		default:
			system("cls");
			cout << "�������������� ����� ����. �� ������� ����. ����������� � ����� �����������!" << endl;
			system("pause");
			return -1;  // ��������� ���������� ����
		}

		if (selectedCellH) {
			cout << endl << "�������� ����� �������, � ������� ��������� ������ ������" << endl;
			char input2;
			cin >> input2;
			switch (input2) {
			case '1':
				selectedCellW = 1;
				break;
			case '2':
				selectedCellW = 2;
				break;
			case '3':
				selectedCellW = 3;
				break;
			case 'P':
				return 1;  // ��������� ���������� �����
			case 'p':
				return 1;
			default:
				system("cls");
				cout << "�������������� ����� ����. �� ������� ����. ����������� � ����� �����������!" << endl;
				system("pause");
				return -1;  // ��������� ���������� ����
			}
		}

		if (this->currentPlayer == 1) {
			if(this->f->matrix[selectedCellH - 1][selectedCellW - 1] == 2)
			    this->f->matrix[selectedCellH - 1][selectedCellW - 1] = X;
			else {
				cout << "��� ������ ��� ���������. �������� ������ ������!" << endl;
				system("pause");
				return 0;
			}
			this->currentPlayer = 2;
			return 0;  // ��������� ������� ������������ ����
		}
		else {
			if (this->f->matrix[selectedCellH - 1][selectedCellW - 1] == 2)
			    this->f->matrix[selectedCellH - 1][selectedCellW - 1] = O;
			else {
				cout << "��� ������ ��� ���������. �������� ������ ������!" << endl;
				system("pause");
				return 0;
			}
			this->currentPlayer = 1;
			return 0;
		}
	}
};


int main(void) {
	system("chcp 1251>nul");

	Menu* mainMenu = new Menu(2);
	mainMenu->text[0] = "������ ����� ����";
	mainMenu->text[1] = "�����";

	Menu* pauseMenu = new Menu(3);
	pauseMenu->text[0] = "���������� ����";
	pauseMenu->text[1] = "������ ����� ����";
	pauseMenu->text[2] = "����� � ������� ����";

	int status = MAINMENU;
	int currentPlayer = 1;
	Game* g = NULL;

	while (status) {
		switch(status) {
		case MAINMENU:
			system("cls");
			mainMenu->print();
			int menuSelection;
			cin >> menuSelection;
			switch (menuSelection) {
			case 1:
				status = NEWGAME;
				break;
			case 2:
				system("cls");
				cout << "������� �� ����!" << endl;
				system("pause");
				return 0;
			default:
				system("cls");
				cout << "�������������� ����� ����. �� ������� ����. ����������� � ����� �����������!" << endl;
				system("pause");
				return -1;
			}
			break;
		case NEWGAME:
			delete g;
            g = new Game();
			status = INGAME;
			break;
		case INGAME:
			if (g->f->whoIsWinning() == -1) {
				if (g->f->isFieldFull()) {
					system("cls");
					g->f->printField();
					cout << "�����!" << endl;
					system("pause");
					status = MAINMENU;
					g = NULL;
					break;
				}

				int callBack = g->gameStep();
				if (callBack == -1)
					return -1;
				else if (callBack == 1) {
					system("cls");
					cout << "�����" << endl << endl;
					pauseMenu->print();
					int menuChoise;
					cin >> menuChoise;
					switch (menuChoise) {
					case 1:
						break;
					case 2:
						status = NEWGAME;
						g = NULL;
						break;
					case 3:
						status = MAINMENU;
						g = NULL;
						break;
					default:
						system("cls");
						cout << "�������������� ����� ����. �� ������� ����. ����������� � ����� �����������!" << endl;
						system("pause");
						return -1;
					}
				}
			}
			else if (g->f->whoIsWinning() == O) {
				system("cls");
				g->f->printField();
				cout << "������� ����� 2. ����������� � �������!" << endl;
				system("pause");
				status = MAINMENU;
				g = NULL;
			}
			else {
				system("cls");
				g->f->printField();
				cout << "������� ����� 1. ����������� � �������!" << endl;
				system("pause");
				status = MAINMENU;
				g = NULL;
			}
			break;
		}
	}
	delete g;
	delete mainMenu;
	delete pauseMenu;
	system("pause>nul");
	return 0;
}