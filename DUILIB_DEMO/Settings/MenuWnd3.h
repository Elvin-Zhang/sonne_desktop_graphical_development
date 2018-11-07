#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "page_info.h"
#include "admins.h"
#include "my_log.h"
#include "sqlite_utils.h"

class CMenuWnd4: public CXMLWnd {
public:
    explicit CMenuWnd4(LPCTSTR pszXMLPath, int tag);

protected:
    virtual ~CMenuWnd4();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������

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
