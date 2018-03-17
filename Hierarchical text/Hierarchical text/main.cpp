#include "TText.h"
#include <Windows.h>

void clrscr(void);
void clreol(void);
void gotoxy(int x, int y);

int main() {
	char fileName[] = "C:\\Users\\User\\Documents\\GitHub projects\\Lab6-Text\\Source.txt";

	TText text, copytext;
	char s;

	cout << "i - info\n";

	while(true){
		cout << "->";
		cin >> s;
		
		switch (s) {
		case 'i': cout << "r - read\np - print\ns - save\nc - copy\nq - quit\n"; break;
		case 'r': text.Read(fileName); break;
		case 'p': text.Print(); break;
		case 's': text.Save("C:\\Users\\User\\Documents\\GitHub projects\\Lab6-Text\\SavedText.txt"); break;
		//case 'c': TText tmp(text.Copy()); tmp.Save("C:\\Users\\User\\Documents\\GitHub projects\\Lab6-Text\\Copy.txt"); break;
		case 'z': clrscr(); break;
		case 'x': gotoxy(5, 5); break;
		case 'q': exit(0);
		default: cout << "Inpput error\n";
		}
	}

	return 0;
}




void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
