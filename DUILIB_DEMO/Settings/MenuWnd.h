#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "page_info.h"
#include "dev_manage.h"

class CMenuWnd: public CXMLWnd
{
public:
    explicit CMenuWnd(LPCTSTR pszXMLPath, int tag);

protected:
    virtual ~CMenuWnd();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������

public:
    void Init(HWND hWndParent, POINT ptPos);
    virtual void    OnFinalMessage(HWND hWnd);
    virtual LRESULT HandleMessage (UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT OnKillFocus   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify( TNotifyUI& msg );
private:
	int iNewWinNum;
	int tag;
};
