#pragma once

#include <windows.h>
#include "my_duilib.h"
#include <iostream>
#include "VM661JTcpDLL.h"

class CUploadUserMenuWnd: public CXMLWnd {
public:
    explicit CUploadUserMenuWnd(LPCTSTR pszXMLPath,int tag);

protected:
	virtual ~CUploadUserMenuWnd();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������

public:
    void Init(HWND hWndParent, POINT ptPos);
    virtual void    OnFinalMessage(HWND hWnd);
    virtual LRESULT HandleMessage (UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT OnKillFocus   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify( TNotifyUI& msg );
private:
	int tag;
	int iNewWinNum;
};
