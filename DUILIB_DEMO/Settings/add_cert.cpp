#include "add_cert.h"

extern CCertsWnd *g_uiCertsWnd;
extern HINSTANCE g_hInst;
extern CListUI* g_all_certs_lst;
extern int g_selected_certs_num2;
extern char g_chLoginAdminName[255];

CAddCertWnd::CAddCertWnd( LPCTSTR pszXMLPath, string user_id)
: CXMLWnd(pszXMLPath) {
	this->user_id = user_id;
}


void CAddCertWnd::InitWindow() {
	CenterWindow();
	inptDateUI
		= static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("date_inpt")));
	inptContentUI = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("content")));
	inptNameUI
		= static_cast<CEditUI*>(m_PaintManager.FindControl(_T("name")));
	inptDateUI->SetText("2030-01-01");
}


void CAddCertWnd::OnFinalMessage(HWND hWnd) {
     __super::OnFinalMessage(hWnd);
}


bool CAddCertWnd::is_ch_hex(const char ch) {
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4'
		|| ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' ||
		ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' ||
		ch == 'f' || ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' ||
		ch == 'E' || ch == 'F')
		return true;
	return false;
}


int CAddCertWnd::check_input(const char *input) {
	const char *p = input;
	int count_len = 0;
	while (*p != '\0') {
		if (!is_ch_hex(*p))
			return INPUTED_CH_NOT_HEX;
		count_len++;
		p++;
	}
	if (count_len != 64)
		return LEN_OF_CODE_WRONG;
	return INPUT_RIGHT;
}



void CAddCertWnd::Notify( TNotifyUI& msg ) {
    if( msg.sType == _T("click") ) {
        if( msg.pSender->GetName() == _T("add") ) {
			int iCurDevCertNum = 0;
#ifdef _TEST_OUTO_CREATE_CERT
			char* content = new char[40];
			// ���豸���� ��ȡ ֤����Կ���������
			char* str_content = new char[100];
			if (RET_ERROR == get_cert_content_func(content)) {
				MessageBox(NULL, "�豸�����豸ʧ��", NULL, MB_TOPMOST);
				return;
			}
			STROPERATION::HexToStr((unsigned char*)str_content, (unsigned char*)content, 32);
#else
			string strInptContent = inptContentUI->GetText().ToString();
			int ret_check = check_input(strInptContent.c_str());
			if (ret_check == LEN_OF_CODE_WRONG) {
				MessageBox(NULL, "������64��16�����ַ�", NULL, MB_TOPMOST);
				return;
			}
			if (ret_check == INPUTED_CH_NOT_HEX) {
				MessageBox(NULL, "������ַ������ַ���16������", NULL, MB_TOPMOST);
				return;
			}
#endif
			iCurDevCertNum  =  getNumOfCurDevCerts();
			if (iCurDevCertNum > 64) {
				MessageBox(NULL,"���豸֤�����Ѵ����ֵ", NULL, MB_TOPMOST);
				return;
			}
			// ��ȡ�����֤����
			string strInptName = inptNameUI->GetText().ToString();
			// sqliteʹ��utf-8���룬������Ҫת
			string strUtf8Name = STROPERATION::ASCII2UTF_8(strInptName);

			string strInptDate = inptDateUI->GetText().ToString();

			char today[40];
			STROPERATION::getDateString(today);

			// �û���������ڣ��������ڵ���
			int iDateCompareRet = STROPERATION::dateComparing(today, strInptDate.c_str());
			if (iDateCompareRet != LATER_THAN_TODAY) {
				MessageBox(NULL, "��������ʵ�֤����Ч��", NULL, MB_TOPMOST);
				return;
			}

			// ��ȡ֤������
		    CComboUI* pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo1")));
            int nsel = pCombox->GetCurSel();
			string type;
			if (nsel == 0)
				type = DYNAMIC_KEYT;
			else
				type = PACK_KEYT;
#ifdef _TEST_OUTO_CREATE_CERT
			if (FALSE == addCert(strInptDate, str_content, this->user_id, type, strUtf8Name)) {
#else
			// ����֤�鵽���ݿ�
			if (FALSE == addCert(strInptDate, strInptContent, this->user_id, type, strInptName)) {
#endif
				MessageBox(NULL, "֤�����ݿ�洢ʧ��", NULL, MB_TOPMOST);
				return;
			}

			// �����־
			char str_log[100] = "add cert";
			MYLOG::write_log(str_log, 6, g_chLoginAdminName);

			// ���֤���Ժ� ѡ����û��б����
			//sel_users_list.clear(); 
			g_uiCertsWnd->InitWindow();
#if 0
			//����û��������֤����ʾ��֤���б�
			CListTextElementUI* p_lst_element = new CListTextElementUI;
			p_lst_element->SetTag(g_selected_certs_num2);
			g_all_certs_lst->Add(p_lst_element);
			p_lst_element->SetText(0, strInptName.c_str());
			if (nsel == 0)
				p_lst_element->SetText(1,"��̬������Կ");
			else
				p_lst_element->SetText(1,"���������Կ");
#ifdef _TEST_OUTO_CREATE_CERT
			p_lst_element->SetText(2, str_content);
#else
			p_lst_element->SetText(2, strInptContent.c_str());
#endif
#endif

			//MYLOG::write_log("add a cert", ADD_CERT_LOG, g_chLoginAdminName);
#ifdef _TEST_OUTO_CREATE_CERT
			delete []content;
			delete []str_content;
			content = NULL;
			str_content = NULL;
#endif

			Close(IDOK);
		}
    }
	__super::Notify(msg);
}


CControlUI* CAddCertWnd::CreateControl( LPCTSTR pstrClassName ) {
    return NULL;
}


void  create_add_cert_win(string user_id,HWND par_hwnd) {
	::CoInitialize(NULL);
	CPaintManagerUI::SetInstance(g_hInst);
#ifdef _TEST_OUTO_CREATE_CERT
	CAddCertWnd *win = new CAddCertWnd(_T("add_cert2.xml"), user_id);
#else
	CAddCertWnd *win = new CAddCertWnd(_T("add_cert.xml"),user_id);
#endif
	HWND hwnd =  win->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST);
	win->ShowModal(); 
	delete win;
	win = NULL;
	::CoUninitialize();
}