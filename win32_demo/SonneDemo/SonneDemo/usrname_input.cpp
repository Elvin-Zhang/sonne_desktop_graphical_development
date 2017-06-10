#include "stdafx.h"
#include "SonneDemo.h"

#include "usrname_input.h"

HINSTANCE g_hInst;
HWND g_win_hwnd;


ATOM NewMyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= NewWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SONNEDEMO));
	wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDI_SONNEDEMO);
	wcex.lpszClassName	= L"usrname_inpt";
	wcex.hIconSm		= NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL NewInitInstance(HINSTANCE hInstance, HWND hWndPar, int nCmdShow)
{
	HWND hWnd;

	g_hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	NewMyRegisterClass(hInstance);

	hWnd = CreateWindow(L"usrname_inpt", L"77676",   
		WS_OVERLAPPEDWINDOW, 100, 80, 600, 400, hWndPar, NULL, hInstance, NULL); 
	g_win_hwnd = hWnd;
	// hWnd=CreateDialog(hInstance,MAKEINTRESOURCE(IDD_FORMVIEW1),NULL,0);  
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, 5);  
	UpdateWindow(hWnd);  
	// ��Ϣѭ��  
	MSG msg;  
	while(GetMessage(&msg,NULL,0,0))  {  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  

	return TRUE;
}


// ����Ի�����Ϣ  
INT_PTR CALLBACK NewDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)  
{ 
	int ret_num;
	HWND hwnd;
	WCHAR buff[32];
	switch (msg)  
	{  
	case WM_COMMAND:  
		{  
			switch(LOWORD(wParam))  { 
			case IDC_BUTTON3: 

				ret_num = GetDlgItemText(hdlg,IDC_EDIT1,buff,32);

				//ע�Ͳ�������һ�ֻ�ȡ�ı����ı���д��
				hwnd = GetDlgItem(hdlg,IDC_EDIT1); 
				ret_num = GetWindowText(hwnd, buff, 32 );

				MessageBox(hdlg, buff, L"��ʾ", MB_OK | MB_ICONINFORMATION); 

				SendMessage(g_win_hwnd, WM_CLOSE, 0, 0);
				break; 
			default:  
				break;  
			}  
		}  
		return 0;  
	}  
	return (INT_PTR)FALSE;  
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (message)
	{
	case WM_CREATE:  
		{  
			// �����Ի���  
			HWND hdlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_FORMVIEW1), hWnd, (DLGPROC)NewDlgProc);  
			// ��ʾ�Ի���  
			ShowWindow(hdlg, SW_SHOWNA);  
		}  
		return 0; 
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{

		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, NewAbout);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		//	case WM_PAINT:
		//		hdc = BeginPaint(hWnd, &ps);
		//		// TODO: �ڴ���������ͼ����...
		//		EndPaint(hWnd, &ps);
		//		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK NewAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}