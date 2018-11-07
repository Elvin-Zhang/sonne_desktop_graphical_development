#pragma once

#include <windows.h>
#include "sqlite_utils.h"
#include "sel_user_impt.h"
#include "add_user1.h"
#include "page_utils.h"
#include "CurUsersManageSynchMenuWnd.h"


/**
*  sonne
*  2018-9
*  �鿴��ǰ�豸�û��б�ͬ������
*/
class CCurUsrManageSynchronizedWnd : public CXMLWnd {
private:
	HINSTANCE hinstance;
	void init_data();
public:
	explicit CCurUsrManageSynchronizedWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance);

	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
};

/**
*  sonne
*  2018-9
*  �鿴��ǰ�豸�û��б�ͬ������
*/
void  createCurUsrManageSynchronized(HINSTANCE hInstance, HWND par_hwnd);