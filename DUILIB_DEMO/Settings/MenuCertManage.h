#pragma once

#include <windows.h>
#include "my_duilib.h"
#include "VM661JTcpDLL.h"
#include "certs.h"
#include "EditCert.h"

class CMenuCertManageWnd : public CXMLWnd
{
public:
	explicit CMenuCertManageWnd(LPCTSTR pszXMLPath, string id, string name, string content, string date, string type);

protected:
	virtual ~CMenuCertManageWnd();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������

public:
	void Init(HWND hWndParent, POINT ptPos);
	virtual void    OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify(TNotifyUI& msg);
private:
	int iNewWinNum;
	string id;
	string name;
	string content;
	string type;
	string date;
};
