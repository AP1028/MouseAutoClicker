#include <iostream>
#include <conio.h>
#include <windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
POINT pt;
POINT _pt;
POINT current;
HDC hDC = GetDC(NULL);
COLORREF color;
COLORREF _color;
bool status = false;
bool _status = true;
bool activate = false;
using namespace std;
int main()
{
	_pt.x = 10;
	_pt.y = 10;
	while (true)
	{
		if (!status)
		{
			GetCursorPos(&pt);
			if (status != _status || color != _color || pt.x != _pt.x || pt.y != _pt.y)
			{
				system("cls");
				color = GetPixel(hDC, pt.x, pt.y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "The program is off! Press down on spacebar to start the program." << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "The position of mouse: " << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "The color of the pixel at the position of the mouse: " << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "Press down on the space bar to start the program. \nHow to use: When the window pops out, move the mouse to the 'Yes' or 'Continue' button and press down on the space bar.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			_pt = pt;
			_color = color;
			_status = status;
			activate = false;
		}
		else if (GetPixel(hDC, pt.x, pt.y) != color)
		{
			if (status != _status || activate)
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				cout << "The program is on!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "The position of mouse: " << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "The color of the pixel at the position of the mouse: " << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "Press down on the space bar to stop the program.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			_status = status;
			activate = false;
		}
		else
		{
			GetCursorPos(&current);
			SetCursorPos(pt.x, pt.y);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(10);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(10);
			SetCursorPos(current.x, current.y);
			if (status != _status)
			{
				system("cls");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cout << "Popout detected!" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "The position of mouse: " << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "The color of the pixel at the position of the mouse: " << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "If you get into a dead loop, press down on the space bar to stop the program.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			_status = status;
			activate = true;
		}
		if (KEY_DOWN(VK_SPACE))
		{
			while (true)
			{
				if (!KEY_DOWN(VK_SPACE))
				{
					status = !status;
					break;
				}
			}
		}
	}
	return 0;
}