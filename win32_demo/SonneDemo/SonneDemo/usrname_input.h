#pragma once

#include "resource.h"


// �˴���ģ���а����ĺ�����ǰ������:
ATOM				NewMyRegisterClass(HINSTANCE hInstance);
BOOL				NewInitInstance(HINSTANCE, int);
LRESULT CALLBACK	NewWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	NewAbout(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK NewDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL NewInitInstance(HINSTANCE hInstance, HWND hWndPar, int nCmdShow);