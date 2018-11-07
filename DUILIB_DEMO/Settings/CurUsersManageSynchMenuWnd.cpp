#include "CurUsersManageSynchMenuWnd.h"

extern c_page_info page_info;
extern user_sel_ret* user_cur_dev_arr;
extern CCurUsrManageSynchronizedWnd *g_uiUsrManageSynchronizedWnd;
extern char g_chLoginAdminName[255];

CCurUserManageSynchMenuWnd::CCurUserManageSynchMenuWnd(LPCTSTR pszXMLPath, int tag)
	: CXMLWnd(pszXMLPath) {
	this->tag = tag;
	this->iNewWinNum = 0;
}

CCurUserManageSynchMenuWnd::~CCurUserManageSynchMenuWnd() {
}

void CCurUserManageSynchMenuWnd::Init(HWND hWndParent, POINT ptPos) {
	Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	::ClientToScreen(hWndParent, &ptPos);
	::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CCurUserManageSynchMenuWnd::OnFinalMessage(HWND /*hWnd*/) {
	if (iNewWinNum >0)
		delete this;
}

LRESULT CCurUserManageSynchMenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		break;


	default:
		bHandled = FALSE;
	}

	if (bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}


//DWORD writeCertsUsers(LPVOID lpParameter) {
//	DWORD iWritingRet;
//	int ret
//		= MessageBoxA(NULL, "ȷ��д��֤����û���д�������Ҫ�����ӣ�д�����ǰ�벻Ҫ�رս��档", "д��", MB_OKCANCEL | MB_SYSTEMMODAL);
//	if (ret == IDOK) {
//		//btnClose->SetEnabled(false);
//		iWritingRet = CEncryptionUtils::write_user_certs();
//		//btnClose->SetEnabled(true);
//	}
//	if (iWritingRet == OK)
//		g_uiUserManageWin->InitWindow();
//	else
//		MessageBoxA(NULL, "д�����", "д��", MB_SYSTEMMODAL);
//	return iWritingRet;
//}

typedef struct {
	string userId;
	string userName;
} DELETE_THREAD_PARAMETER, *P_DELETE_THREAD_PARAMETER;

DELETE_THREAD_PARAMETER threadParameter;

DWORD deleteThread(LPVOID lpParameter) {
	P_DELETE_THREAD_PARAMETER temp = (P_DELETE_THREAD_PARAMETER)lpParameter;
	int ret = MessageBoxA(NULL, MAKE_SURE_DELETE_MSG, "ɾ���û�", MB_OKCANCEL | MB_SYSTEMMODAL);
	if (ret == IDOK) {
		if (!updateUserFingersDevIdNull(temp->userId)) {
			MessageBox(NULL, "ɾ��ʧ�ܣ�ɾ���û���ʧ��", "ɾ���û�", NULL);
			return -1;
		}
		//if (!deleteUserCertByUserId(user_id)) {
		//	MessageBox(NULL, "ɾ��ʧ�ܣ�ɾ���û�֤���ϵ��ʧ��", "ɾ���û�", NULL);
		//	return;
		//}
		delUserFingers((char*)temp->userId.c_str());
		Sleep(100);
		//CEncryptionUtils::write_user_certs();
		char str_log[300] = "delete user";
		strcat(str_log, temp->userName.c_str());
		MYLOG::write_log(str_log, DEL_USER_LOG, g_chLoginAdminName);
		g_uiUsrManageSynchronizedWnd->InitWindow();
	}
	return 0;
}


void CCurUserManageSynchMenuWnd::Notify(TNotifyUI& msg) {
	DWORD(*pDeleteThread)(LPVOID lpParam);
	int num;
	//string user_id;
	//string username;

	if (msg.sType == _T("itemclick")) {
		num = page_info.get_begin_index() + this->tag;
		//user_id = user_cur_dev_arr[num].id;
		//username = user_cur_dev_arr[num].name;
		threadParameter.userId = user_cur_dev_arr[num].id;
		threadParameter.userName = user_cur_dev_arr[num].name;

		//if (!MYSQL_INTERFACES::ifUserOfDevExits(user_id)) {
		//	if (iNewWinNum == 0) {
		//		MessageBox(NULL, "�ǵ�ǰ�豸�û����޷�����", NULL, NULL);
		//		iNewWinNum++;
		//		return;
		//	}
		//}
		string click_menu_option = msg.pSender->GetName().ToString();
		//if (!click_menu_option.compare(_T("check_certs"))) {
		//	if (iNewWinNum == 0) {
		//		PostMessage(WM_KILLFOCUS);
		//		//num = page_info.get_begin_index() + this->tag;
		//		createCurDevUserCertsWin(user_id);
		//	}
		//	iNewWinNum++;
		//}
#if 0
		if (!click_menu_option.compare(_T("check_devs"))) {
			if (iNewWinNum == 0) {
				PostMessage(WM_KILLFOCUS);
				num = page_info.get_begin_index() + this->tag;
				user_id = user_arr[num].id;
				devs = MYSQL_INTERFACES::select_devs_of_user("", &dev_num, user_id);
				// ��ʾ���û��豸�б�
				create_usr_dev_lst_win(dev_num, devs);
			}
			iNewWinNum++;
		}
#endif
		//if (!click_menu_option.compare(_T("check_fingers"))) {
		//	if (iNewWinNum == 0) {
		//		PostMessage(WM_KILLFOCUS);
		//		//num = page_info.get_begin_index() + this->tag;

		//		create_finger_manage_win(user_id, username);
		//	}
		//	iNewWinNum++;
		//}
		//if( !click_menu_option.compare(_T("edit")) ) {
		//	cout << "hh";//MessageBox(NULL, msg.pSender->GetName(), NULL, NULL);
		//}

		/*
		*  ɾ�����ݿ��и��û����ݣ�����ָ��������֤���ϵ
		*/
		if (!click_menu_option.compare(_T("delete"))) {
			pDeleteThread = deleteThread;
			if (iNewWinNum == 0) {
				CreateThread(NULL, NULL, pDeleteThread, (void *)&threadParameter,NULL, NULL);
			}
			iNewWinNum++;
		}
	}
	__super::Notify(msg);
}

LRESULT CCurUserManageSynchMenuWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	Close();

	bHandled = FALSE;
	return __super::OnKillFocus(uMsg, wParam, lParam, bHandled);
}
