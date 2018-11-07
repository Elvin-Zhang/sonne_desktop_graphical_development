#include <windows.h>


#ifdef _WIN64
	#pragma comment(lib,"VM661JTcpDLL.lib")
	#pragma comment(lib,"sqlite3.lib")
#else
	#pragma comment(lib,"VM661JTcpDLL_32.lib")
#endif


#include "my_including.h"

char g_cers_path[256] = {0};
char g_manager_cers_path[256] = {0};

#include "str_utils.h"
#include "file_utils.h"
#include "my_log.h"

HINSTANCE g_hInst = NULL;						// ��ǰʵ��
HANDLE g_get_dev_status_thread;                 // ��ȡ�豸״̬�߳�
//CWINDOWS g_MainWindow;							// ��������
wchar_t * input_usrname;
int is_delete = NO_DELETE;
char g_sn[32] = "000000000000";
//string g_dev_name;
bool g_is_conn = false;
bool g_bIs1stAdmin= false;
char  g_chLoginAdminName[255];

#include "VM661JTcpDLL.h"
//#include "Login.h"
#include "Crc.h"
#include "dev_manage.h"
#include "user_manage.h"
#include "logs.h"
#include "admins.h"
#include "certs.h"
#include "main_win.h"
#include "admin_login.h"
#include "sqlite_utils.h"

//DWORD WINAPI close_dev_thread(LPVOID lpParameter) {
//	TGCloseDev();
//	return TRUE;
//}

/**
 *    ���ߣ�sonne
 *    ���ڣ�2018-02-02
 *    ��ע���̣߳�ʵʱ�ж��豸����״̬
 */
//DWORD get_dev_status(LPVOID lpParameter) {
//	do {
//		if (TGGetStatus() >= 0)  
//			g_is_conn = true;
//		else
//			g_is_conn = false;
//		Sleep(1000);
//	} while(1);
//}





int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd ){
	// �������ݿ�
	//if (RET_ERROR == MYSQL_INTERFACES::ConnMySQL()) {
	if (RET_ERROR == sqliteConn()) {
		MessageBoxA(NULL, "�������ݿ�ʧ�ܣ������˳����������ݿ�����������", "���д���", MB_SYSTEMMODAL);
		return RET_ERROR;
	}
	createTables();
	g_hInst = hInstance;

#ifdef _TEST_TEST
	int ret, mode = 0;
#ifdef _TEST_WITH_DEV_CONN
	// hid����
	//ret = TGOpenDev(&mode);
	//if (ret >= OK) {
		//g_is_conn = true;
		//TGDevGetSN(g_sn);
		//if (MYSQL_INTERFACES::if_dev_of_sn_exit("", g_sn)) {
		//if (!checkIfDevExists("", g_sn)) {
		//	char chDevDate[30];
		//	STROPERATION::getDateString(chDevDate);
			//MYSQL_INTERFACES::insert_dev("", g_sn, chDevDate, "1");
		//	addDevSqlite("", g_sn, chDevDate, "1");
		//}
	//}
	//else {
	//	MessageBoxA(NULL, "�B���O��ʧ��", "���д���", MB_SYSTEMMODAL);
	//	return RET_ERROR;
	//}
	// �̣߳���ȡ�豸״̬
	//g_get_dev_status_thread = CreateThread(NULL, NULL, get_dev_status, NULL, NULL, NULL);
	g_is_conn = true;
#else
	strcpy(g_sn, "0000000000000000");
	//g_dev_name = "dev1";
#endif
	//TGDevGetSN(g_sn);

#ifdef _TEST_WITH_LOGIN
	//�ж��ǲ����״�ʹ��
	//if (MYSQL_INTERFACES::is_manager_exit()) {
	if (checkIfAdminExists()) {
		//if (LOGIN::login(hInstance)) {
		if (adminLogin()) {
			//is_new_dev();
			// ��¼��־
			MYLOG::write_log("logined the management system", 1, g_chLoginAdminName);
			create_main_win();
			//g_MainWindow.Create(hInstance, &HTMLayoutNotifyHandler, &DOMEventsHandler, L"MainDlg.html", InitWindows, NULL);
		}
	}
	else {
		g_bIs1stAdmin = true;
		// ע��
		createAddAdminWin();
	}
#else
	//g_MainWindow.Create(hInstance, &HTMLayoutNotifyHandler, &DOMEventsHandler, L"MainDlg.html", InitWindows, NULL);
	create_main_win();
#endif
#else
	g_MainWindow.Create(hInstance, &HTMLayoutNotifyHandler, &DOMEventsHandler, L"MainDlg.html", InitWindows, NULL);
#endif


	//MYSQL_INTERFACES::CloseMySQLConn();
	sqliteClose();

	return 0;
}
