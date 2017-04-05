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
	HWND hwnd;

	// �˴���ģ���а����ĺ�����ǰ������:
	ATOM				MyRegisterClass(HINSTANCE hInstance);
	BOOL				InitInstance(HINSTANCE, int);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


		//************************************
	// ��      ��:	sonne
	// ��  ��  ��:  InitList
	// ��      ��:  ���ڳ�ʼ������
	// ��  ��  ��:  MANAGE::InitList
	// ��  ��  Ȩ:  public 
	// ����ֵ����:  VOID
	// �����޶���: 	
	//************************************
	VOID InitList(HWND hwnd)
	{
		htmlayout::dom::element root;
		htmlayout::dom::element	name;
		root = htmlayout::dom::element::root_element(hwnd); 
		name = root.get_element_by_id("NAME");
		name.clear();
		name.insert(htmlayout::dom::element::create("option", L"Bob"), 0);
		name.insert(htmlayout::dom::element::create("option", L"Alice"), 1);
		name.insert(htmlayout::dom::element::create("option", L"Peter"), 2);
		SetWindowText(hwnd,"NAME LIST");
	}

	void OnButtonClick(HELEMENT button);

	struct DOMEventsHandlerType: htmlayout::event_handler
	{
		DOMEventsHandlerType(): event_handler(0xFFFFFFFF) {}
		virtual BOOL handle_event (HELEMENT he, BEHAVIOR_EVENT_PARAMS& params ) 
		{ 
			switch( params.cmd )
			{
			case BUTTON_CLICK:              NEW::OnButtonClick(params.heTarget); break;// click on button
		    case BUTTON_PRESS:              break;// mouse down or key down in button
		    case BUTTON_STATE_CHANGED:      break;
			case EDIT_VALUE_CHANGING:       break;// before text change
		    case EDIT_VALUE_CHANGED:        break;//after text change
		    case SELECT_SELECTION_CHANGED:  break;// selection in <select> changed
		    case SELECT_STATE_CHANGED:      break;// node in select expanded/collapsed, heTarget is the node
            case POPUP_REQUEST: 
                                        break;// request to show popup just received, 
                                              //     here DOM of popup element can be modifed.
		    case POPUP_READY:               break;// popup element has been measured and ready to be shown on screen,
                                              //     here you can use functions like ScrollToView.
            case POPUP_DISMISSED:           break;// popup element is closed,
                                              //     here DOM of popup element can be modifed again - e.g. some items can be removed
                                              //     to free memory.
            case MENU_ITEM_ACTIVE:                // menu item activated by mouse hover or by keyboard
				 break;
            case MENU_ITEM_CLICK:                 // menu item click 
				 break;


				// "grey" event codes  - notfications from behaviors from this SDK 
			case HYPERLINK_CLICK:           break;// hyperlink click
			case TABLE_HEADER_CLICK:        break;// click on some cell in table header, 
                                              //     target = the cell, 
                                              //     reason = index of the cell (column number, 0..n)
		    case TABLE_ROW_CLICK:           break;// click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)
		    case TABLE_ROW_DBL_CLICK:       break;// mouse dbl click on data row in the table, target is the row
                                              //     target = the row, 
                                              //     reason = index of the row (fixed_rows..n)

            case ELEMENT_COLLAPSED:         break;// element was collapsed, so far only behavior:tabs is sending these two to the panels
            case ELEMENT_EXPANDED:          break;// element was expanded,
			}
			return FALSE; 
		}
	} DOMEventsHandler;

	LRESULT CALLBACK HTMLayoutNotifyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LPVOID vParam)
	{
		// all HTMLayout notification are comming here.
		NMHDR*  phdr = (NMHDR*)lParam;

		switch(phdr->code)
		{
		case HLN_CREATE_CONTROL:    break; //return OnCreateControl((LPNMHL_CREATE_CONTROL) lParam);
		case HLN_CONTROL_CREATED:   break; //return OnControlCreated((LPNMHL_CREATE_CONTROL) lParam);
		case HLN_DESTROY_CONTROL:   break; //return OnDestroyControl((LPNMHL_DESTROY_CONTROL) lParam);
		case HLN_LOAD_DATA:         break;
		case HLN_DATA_LOADED:       break; //return OnDataLoaded((LPNMHL_DATA_LOADED)lParam);
		case HLN_DOCUMENT_COMPLETE: break; //return OnDocumentComplete();
		case HLN_ATTACH_BEHAVIOR:   break;
		}
		return 0;
	}

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
			// Normally HTMLayout sends its notifications
            // to its parent. 
            // In this particular case we are using callback function to receive and
            // and handle notification. Don't bother the desktop window (parent of this window)
            // by our notfications.
            HTMLayoutSetCallback(hWnd,&HTMLayoutNotifyHandler,0);

            // attach DOM events handler so we will be able to receive DOM events like BUTTON_CLICK, HYPERLINK_CLICK, etc.
			htmlayout::attach_event_handler(hWnd, &DOMEventsHandler);
			memset(wsz,0,sizeof(wsz));
			MultiByteToWideChar(CP_ACP, 0, path, strlen(path)+1, wsz, sizeof(wsz)/sizeof(wsz[0]));
            HTMLayoutLoadFile(hWnd,wsz); //Hello.htm��Ҫ���ں�exeͬһĿ¼,�ǵð�dllҲcopy��ȥ  
			InitList(hWnd);
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
		hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
		htmlayout::dom::element root;
		char szCurrPath[MAX_PATH];
	    GetCurrentDirectory(MAX_PATH,szCurrPath);

		NewRegisterClass(hInst);

		hwnd = CreateWindow("hh", NULL, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWndPar, NULL, hInst, NULL);

		EnableWindow(hWndPar,FALSE);

	    if (!hwnd)
	    {
			return FALSE;
		}

	    ShowWindow(hwnd, 5);
        UpdateWindow(hwnd);

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

	
	//************************************
	// ��      ��:	sonne
	// ��  ��  ��:  OnButtonClick
	// ��      ��:  ��ť��Ӧ�¼�
	// ��  ��  ��:  OnButtonClick
	// ��  ��  Ȩ:  public 
	// ����ֵ����:  VOID
	// �����޶���: 	
	//************************************
	void OnButtonClick(HELEMENT button)
	{
		htmlayout::dom::element cBut = button;
		if (!wcscmp(cBut.get_attribute("id"),L"ACT"))
		{
			htmlayout::dom::element root;
			htmlayout::dom::element	name;
			root = htmlayout::dom::element::root_element(hwnd); 
			name = root.get_element_by_id("NAME");
			name.insert(htmlayout::dom::element::create("option", L"Whoami"), 0);
		}
		if (!wcscmp(cBut.get_attribute("id"),L"DEL"))
		{
			htmlayout::dom::element root;
			htmlayout::dom::element	nameList;
			root = htmlayout::dom::element::root_element(hwnd); 
			nameList = root.get_element_by_id("NAME");
			htmlayout::dom::element selName;
			selName = nameList.find_first("option:checked");
			selName.destroy();
			SetWindowText(hwnd,"NAME LIST");
		}
		if (!wcscmp(cBut.get_attribute("id"),L"EDI"))
		{
			htmlayout::dom::element root;
			htmlayout::dom::element	nameList;
			root = htmlayout::dom::element::root_element(hwnd); 
			nameList = root.get_element_by_id("NAME");
			htmlayout::dom::element selName;
			selName = nameList.find_first("option:checked");
			selName.set_value("Iamwho");
			SetWindowText(hwnd,"NAME LIST");
		}
	}

}

