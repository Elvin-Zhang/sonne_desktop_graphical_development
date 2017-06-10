// SonneDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SonneDemo.h"
#include "usrname_input.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HWND g_hwnd;
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
WCHAR pic_path[32];                             // ͼƬ·��

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


/**
*   ���ߣ�sonne
*   ���ڣ�2017-06-09 2017-06-08
*   ��ע��win32����demo  �ı����ȡ��ͼƬ��ʾ������
**/
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//Ĭ��ͼƬ·��
	WCHAR *pic_tmp_path = L"E:\\Bmp\\Bmp\\2.bmp";
	memcpy(pic_path, pic_tmp_path, 32);

	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SONNEDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SONNEDEMO));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SONNEDEMO));
	wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDI_SONNEDEMO);
	wcex.lpszClassName	= szWindowClass;
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	// hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	hWnd = CreateWindow(szWindowClass, L"�޵з����",   
		WS_OVERLAPPEDWINDOW, 100, 80, 600, 400, NULL, NULL, hInstance, NULL); 
	g_hwnd = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

 
// ����Ի�����Ϣ  
INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)  
{   
	HDC hdc;  
	PAINTSTRUCT ps;  
	HDC hdcMem;  
	HBITMAP hbmp;   //һ��λͼ�ľ��  
	BITMAP bmp; 

	WCHAR txt[32];

	//Ҫ�滻��ͼƬ·��
	WCHAR *tmp_path = L"E:\\Bmp\\Bmp\\3.bmp";

	switch (msg)  
	{  
	case WM_INITDIALOG:
		break;
	case WM_PAINT:   
		hdc = BeginPaint(hdlg,&ps); 
		hdcMem  = CreateCompatibleDC(hdc); 

		hbmp = (HBITMAP)LoadImage(NULL, pic_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
		GetObject(hbmp, sizeof(BITMAP), &bmp);  //�õ�һ��λͼ����  

		SelectObject(hdcMem, hbmp);  
		BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);        //��ʾλͼ  

		DeleteDC(hdcMem);  
		DeleteObject(hbmp);  
		EndPaint(hdlg,&ps); 
		break;
	case WM_COMMAND:  
		{  
			switch(LOWORD(wParam))  {  
			case IDC_BUTTON1:  
				//�´��ڣ���ʾ�ı���
				NewInitInstance( hInst,g_hwnd, 5);
				break;  
			case IDC_BUTTON2:  
				//����ͼƬ��·����
				memcpy(pic_path, tmp_path, 32);

				//�ֲ���ͼƬ����ˢ���ػ�
				RECT        rect;   
				SetRect(&rect, 0, 0, 500, 300); 
				InvalidateRect(hdlg,&rect,true);
				UpdateWindow(hdlg);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_CREATE:  
		{  
			// �����Ի���  
			HWND hdlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)DlgProc);  
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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
