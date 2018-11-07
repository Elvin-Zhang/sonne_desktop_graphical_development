#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "finger_manage.h"
#include "EditFingerName.h"

class CMenuFingerManageWnd : public CXMLWnd
{
public:
	explicit CMenuFingerManageWnd(LPCTSTR pszXMLPath, string id, string name, string userId);

protected:
	virtual ~CMenuFingerManageWnd();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������

public:
	void Init(HWND hWndParent, POINT ptPos);
	virtual void    OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify(TNotifyUI& msg);
private:
	int iNewWinNum;
	string id;
	string userId;
	string name;
};
