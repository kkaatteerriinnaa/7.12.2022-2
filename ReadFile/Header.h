#pragma once
#include<windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <fstream>
#include"resource.h"

using namespace std;

class ReadThreadDlg
{
public:
	ReadThreadDlg(void);
public:
	~ReadThreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ReadThreadDlg* ptr;
	void Close(HWND hwnd);
	BOOL InitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};
