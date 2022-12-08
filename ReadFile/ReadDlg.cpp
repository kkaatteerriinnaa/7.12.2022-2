#include "Header.h"

ReadThreadDlg* ReadThreadDlg::ptr = NULL;

ReadThreadDlg::ReadThreadDlg(void)
{
	ptr = this;
}

ReadThreadDlg::~ReadThreadDlg(void)
{

}

void ReadThreadDlg::Close(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Read_Thread(LPVOID lp)
{
	ReadThreadDlg* ptr = (ReadThreadDlg*)lp;
	char buf[4096];

	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ifstream in(TEXT("file.txt"));

			if (!in.is_open())
			{
				MessageBox(0, TEXT("Error"), TEXT("Error"), MB_OK);
				return 1;
			}
			int B[100];
			int sum = 0;
			for (int i = 0; i < 100; i++)
			{
				in >> B[i];
				sum += B[i];
			}
			TCHAR str[30];
			wsprintf(str, TEXT("Сумма чисел равна %d"), sum);
			MessageBox(0, str, TEXT("Мьютекс"), MB_OK);

		in.close();
		
		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Чтение данных из файла file.txt завершено!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL ReadThreadDlg::InitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Read_Thread, this, 0, NULL);
	return TRUE;
}

BOOL CALLBACK ReadThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Close);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->InitDialog);
	}
	return FALSE;
}