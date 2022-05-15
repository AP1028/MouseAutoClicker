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
				cout << "程序未启动！按下空格启动程序。" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "当前光标坐标：" << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "当前像素颜色：" << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "按下空格来启动程序。\n使用方法：弹窗跳出后鼠标放到确定键上方，然后按下空格键，开始等待\n";
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
				cout << "程序已启动！" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "目标像素位置：" << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "目标像素颜色：" << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "按下空格来关闭程序。\n";
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
				cout << "弹窗已弹出！" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "目标像素位置：" << "X:" << pt.x << " Y:" << pt.y << endl;
				cout << "目标像素颜色：" << color << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "若陷入死循环，按下空格来关闭程序。\n";
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