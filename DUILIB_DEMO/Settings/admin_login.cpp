#include "admin_login.h"

extern HINSTANCE g_hInst;
extern char g_chLoginAdminName[255];
CAdminLoginWnd *p_cAdminLoginWin;
BOOL g_bSucceed = TRUE;


/**
*    ���ߣ�sonne
*    ���ܣ��豸����֤�����̣�1PC���ͱ���֤�鵽�豸 2�豸��֤
*    ���ڣ�2017-06-22
*/
void validate_by_dev() {
	int num;
	// ��֤����
	sel_admin_ret *sel_admins;// = MYSQL_INTERFACES::select_all_admins("", &num);
	selAllAdmins(&num, &sel_admins);
	admin_login(sel_admins, num, g_chLoginAdminName);
	delete[] sel_admins;
	sel_admins = NULL;
}


DWORD WINAPI ValidateFinger(LPVOID lpParameter) {
	validate_by_dev();
	//TerminateThread(g_get_conn_state_thread,0);
	//SendMessage(g_cWindow.GetHandle(), WM_DESTROY, NULL, NULL);
	p_cAdminLoginWin->Close(IDOK);
	g_bSucceed = true;
	return 0;
}


CAdminLoginWnd::CAdminLoginWnd(LPCTSTR pszXMLPath)
	: CXMLWnd(pszXMLPath) {
}


void CAdminLoginWnd::InitWindow() {
	CreateThread(NULL, NULL, ValidateFinger, NULL, NULL, NULL);
	CenterWindow();
}


void CAdminLoginWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CAdminLoginWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == TEXT("click")) {
		if (msg.pSender->GetName() == TEXT("closebtn")) {
			Close(IDCLOSE);
			g_bSucceed = false;
		}
	}
	__super::Notify(msg);
}


CControlUI* CAdminLoginWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


bool  adminLogin() {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	p_cAdminLoginWin = new CAdminLoginWnd(_T("admin_login.xml"));
	HWND hwnd = p_cAdminLoginWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cAdminLoginWin->ShowModal();
	delete p_cAdminLoginWin;
	p_cAdminLoginWin = NULL;
	::CoUninitialize();
	return g_bSucceed;
}