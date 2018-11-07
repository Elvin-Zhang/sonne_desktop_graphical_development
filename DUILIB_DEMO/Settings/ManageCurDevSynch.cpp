#include "my_duilib.h"
#include "ManageCurDevSynch.h"
//#include "MenuWnd2.h"


HWND g_cur_usr_manage_synchronized_win_hwnd;
CListUI* pUsrManageSynchronizedList;
user_sel_ret* user_cur_dev_arr;
CCurUsrManageSynchronizedWnd *g_uiUsrManageSynchronizedWnd;

bool bIsClearDev = false;
bool bIsImpting = false;

extern CControlUI * btnManageUser;
extern CControlUI* btnManageDev;
extern CControlUI* btnManageCert;
extern CControlUI* btnManageManager;
extern CControlUI*	uiInptDevId;
//extern CControlUI* btnClearDev;
extern CControlUI* btnManageCurDev;


/**
*  sonne
*  2018-9
*  �鿴��ǰ�豸�û��б�ͬ������
*/
CCurUsrManageSynchronizedWnd::CCurUsrManageSynchronizedWnd(LPCTSTR pszXMLPath, HINSTANCE hInstance)
	: CXMLWnd(pszXMLPath) {
	this->hinstance = hInstance;
}


void CCurUsrManageSynchronizedWnd::init_data() {
	//int how_many_users = getNumOfCurDevUsers();
	// ��ʼ��CListUI�ؼ�
	int how_many_users;
	CDuiString str;
	pUsrManageSynchronizedList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
	pUsrManageSynchronizedList->RemoveAll();
	selUsersOfCurDev(&user_cur_dev_arr,&how_many_users);
	for (int i = 0; i < how_many_users; i++) {
		CListTextElementUI* ele = new CListTextElementUI;
		ele->SetTag(i);
		pUsrManageSynchronizedList->Add(ele);

		str.Format(_T("%d"), i);
		ele->SetText(0, user_cur_dev_arr[i].id);
		ele->SetText(1, user_cur_dev_arr[i].name);
	}
}


void CCurUsrManageSynchronizedWnd::InitWindow() {
	CenterWindow();
	this->init_data();
}


void CCurUsrManageSynchronizedWnd::Notify(TNotifyUI& msg) {
#if 0
	// ˫���¼�
	if (msg.sType == _T("itemactivate")) {
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
		//sMessage += domain[iIndex].c_str();  

		::MessageBox(NULL, sMessage.GetData(), _T("��ʾ(by tojen)"), MB_OK);
	}
#endif
	if (msg.sType == _T("itemclick")) {
		UINT_PTR i_index = msg.pSender->GetTag();

		// ����ǵ�ǰ�豸���û��������в���
		//if (!strcmp(user_arr[clicked_user_num].dev_name, g_dev_name.c_str())) {
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		CCurUserManageSynchMenuWnd *p_menu = new CCurUserManageSynchMenuWnd(_T("Menu/CurUsersManageMenu.xml"), i_index);
		p_menu->Init(g_cur_usr_manage_synchronized_win_hwnd, pt);
		p_menu->ShowWindow(TRUE);
		//}
		//else {
		//	MessageBox(NULL, "�ǵ�ǰ�豸�û����޷�����", NULL, NULL);
		//}
	}
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("impt_btn")) {
			if (bIsImpting)
				return;
			bIsImpting = true;
			//createAddUserWin();
			createSelUsersImptWin();
			bIsImpting = false;
			this->init_data();
		}
		if (msg.pSender->GetName() == _T("CLEAR")) {
			if (bIsClearDev)
				return;
			bIsClearDev = true;
			int iClearRet
				= MessageBoxA(NULL, "ȷ�������豸��", "����", MB_OKCANCEL | MB_SYSTEMMODAL);
			if (iClearRet == IDOK) {
				if (TGGetStatus() < OK) {
					btnManageUser->SetEnabled(false);
					btnManageDev->SetEnabled(false);
					btnManageCert->SetEnabled(false);
					btnManageManager->SetEnabled(false);
					//btnClearDev->SetEnabled(false);
					btnManageCurDev->SetEnabled(false);
					uiInptDevId->SetText(SHOW_AFTER_CONN_DEV_STR);
					MessageBox(NULL, RECONN_DEV_PLEASE_STR, RESULT_TITLE_WIN_STR, MB_SYSTEMMODAL);
					return;
				}
				clearDb();
				int iCloseDevRet = clearDev();
				if (iCloseDevRet != OK) {
					MessageBox(NULL, CLEAR_DEV_FAIL_STR, RESULT_TITLE_WIN_STR, MB_SYSTEMMODAL);
					return;
				}
				//CreateThread(NULL, NULL, clearWriteCertsUsers, NULL, NULL, NULL);
				char str_log[100] = "clear device";
				MYLOG::write_log(str_log, CLEAR_DEV_LOG, g_chLoginAdminName);
			}
			bIsClearDev = false;
			this->init_data();
		}
	}
	__super::Notify(msg);
}


CControlUI* CCurUsrManageSynchronizedWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}

/**
*  sonne
*  2018-9
*  �鿴��ǰ�豸�û��б�ͬ������
*/
void  createCurUsrManageSynchronized(HINSTANCE hInstance, HWND par_hwnd) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(hInstance);

	g_uiUsrManageSynchronizedWnd = new CCurUsrManageSynchronizedWnd(_T("cur_user_manage.xml"), hInstance);
	g_cur_usr_manage_synchronized_win_hwnd = g_uiUsrManageSynchronizedWnd->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
	g_uiUsrManageSynchronizedWnd->ShowModal();
	//delete g_uiUsrManageSynchronizedWnd;
	::CoUninitialize();
}