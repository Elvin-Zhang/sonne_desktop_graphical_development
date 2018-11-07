#include "EditFingerName.h"

extern HINSTANCE g_hInst;
string g_strInptEditFingerName;
CEditFingerNameWnd *p_cEditFingerNameWin;


CEditFingerNameWnd::CEditFingerNameWnd(LPCTSTR pszXMLPath, string id, string name)
	: CXMLWnd(pszXMLPath) {
	this->id = id;
	this->name = name;
}


void CEditFingerNameWnd::InitWindow() {
	CenterWindow();
	CEditUI* inpt_name
		= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
	inpt_name->SetText(this->name.c_str());
}


void CEditFingerNameWnd::OnFinalMessage(HWND hWnd) {
	__super::OnFinalMessage(hWnd);
}


void CEditFingerNameWnd::Notify(TNotifyUI& msg) {
	if (msg.sType == _T("click")) {
		if (msg.pSender->GetName() == _T("EDIT")) {
			// ��ȡ�����֤����
			CEditUI* inpt_name
				= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
			g_strInptEditFingerName = inpt_name->GetText().ToString();
			int iInptStrLen = g_strInptEditFingerName.length();

			if (iInptStrLen == 0) {
				MessageBox(NULL, "������ָ������", NULL, MB_SYSTEMMODAL);
				return;
			}

			//if (STROPERATION::isStrIllegal2(g_strInptEditName.c_str())) {
			//	MessageBox(NULL, "������û����к��зǷ��ַ�", NULL, MB_SYSTEMMODAL);
			//	return;
			//}

			if (iInptStrLen > MAX_USERNAME_LEN) {
				MessageBox(NULL, "�������ָ������������������", NULL, MB_SYSTEMMODAL);
				return;
			}

			//if (checkIfAdminOfNameExists((char*)g_strInptEditName.c_str())) {
			//	MessageBox(NULL, "��������û����Ѵ���", NULL, MB_SYSTEMMODAL);
			//	return;
			//}
			editFingerName(this->id, STROPERATION::ASCII2UTF_8(g_strInptEditFingerName));
			this->Close();
		}
	}
	__super::Notify(msg);
}


CControlUI* CEditFingerNameWnd::CreateControl(LPCTSTR pstrClassName) {
	return NULL;
}


void  createEditFingerNameWin(string id, string name) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
	p_cEditFingerNameWin = new CEditFingerNameWnd(_T("edit_finger_name.xml"), id, name);
	p_cEditFingerNameWin->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	p_cEditFingerNameWin->ShowModal();
	delete p_cEditFingerNameWin;
	p_cEditFingerNameWin = NULL;
	::CoUninitialize();
}