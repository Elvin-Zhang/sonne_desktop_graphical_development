#pragma once

#include <htmlayout.h>
#include "behaviors/notifications.h"
#include <htmlayout_behavior.hpp>

namespace NEW
{
	#define MAX_LOADSTRING 100
	// ȫ�ֱ���:
	HINSTANCE hInst;								// ��ǰʵ��
	TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
	TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

	// �˴���ģ���а����ĺ�����ǰ������:
	ATOM				MyRegisterClass(HINSTANCE hInstance);
	BOOL				InitInstance(HINSTANCE, int);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

    //
	//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
	//
	//  Ŀ��: ���������ڵ���Ϣ��
	//  ����: sonne
	//  ����: 2017-03-27
	//
	//  WM_COMMAND    - ����Ӧ�ó���˵�
	//  WM_PAINT    - ����������
	//  WM_DESTROY    - �����˳���Ϣ������
	//
	//
	LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		int wmId, wmEvent;
	    PAINTSTRUCT ps;
		HDC hdc;
	    LRESULT lResult;
        BOOL    bHandled;
		lResult = HTMLayoutProcND(hWnd,message,wParam,lParam, &bHandled);
        if(bHandled)
             return lResult;
  
	    char* path = "newPage.htm";
	    WCHAR wsz[256]; 

        switch (message)  
        { 
		case WM_CREATE: 
			memset(wsz,0,sizeof(wsz));
			MultiByteToWideChar(CP_ACP, 0, path, strlen(path)+1, wsz, sizeof(wsz)/sizeof(wsz[0]));
            HTMLayoutLoadFile(hWnd,wsz); //Hello.htm��Ҫ���ں�exeͬһĿ¼,�ǵð�dllҲcopy��ȥ  
			break;  
   
        case WM_COMMAND:  
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
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
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
       return 0;
	}

	//
	//  ����: MyRegisterClass()
	//
	//  Ŀ��: ע�ᴰ���ࡣ
	//  ����: sonne
	//  ����: 2017-03-27
	//
	ATOM NewRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)NewWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32HTML));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32HTML);
		wcex.lpszClassName	= "hh";
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	//   ����: sonne
	//   ����: 2017-03-27
	//
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND hWndPar, TCHAR szWindowClass[])
	{
		HWND newHWnd;
		hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
		htmlayout::dom::element root;
		char szCurrPath[MAX_PATH];
	    GetCurrentDirectory(MAX_PATH,szCurrPath);

		NewRegisterClass(hInst);

		newHWnd = CreateWindow("hh", NULL, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWndPar, NULL, hInst, NULL);

		EnableWindow(hWndPar,FALSE);

	    if (!newHWnd)
	    {
			return FALSE;
		}

	    ShowWindow(newHWnd, 5);
        UpdateWindow(newHWnd);

		MSG msg;
	    HACCEL hAccelTable;
		hAccelTable = LoadAccelerators(hInst, (LPCTSTR)IDR_ACCELERATOR);
	    while (GetMessage(&msg, NULL, 0, 0)) 
	    {
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		    {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		Sleep(100);
		EnableWindow(hWndPar,TRUE);
		SetForegroundWindow( hWndPar );
		BringWindowToTop(hWndPar);
		root = htmlayout::dom::element::root_element(hWndPar);
		if (root)
		{
			root.refresh();
		}
		SetCurrentDirectory(szCurrPath);
	    return TRUE;
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

}