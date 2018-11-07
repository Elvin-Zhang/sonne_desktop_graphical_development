#pragma once
#include <windows.h>  
#include <iostream>
#include <string>  
#include <vector>

extern char g_cers_path[256];
extern char g_manager_cers_path[256];

#ifndef MY_HEADERS_H 
#define MY_HEADERS_H 

#define TG_DEBUG
//#define REG_DEBUG

//CMD1;no date package
#define DEV_KEY 0x0001				           //�豸��Կ�� 		PC->ARM
#define DEV_KEY_SET_SUCCESS 0x0002			   //�豸��Կ���óɹ���  ARM->PC
#define DEV_KEY_SET_FAILED 0x0003		       //�豸��Կ����ʧ�ܣ�  ARM->PC


#define	RAN_NUM_REQ			0x0006		       //���������	PC->ARM
#define	RAN_NUM				0x0007	           //�������	ARM->PC

#define	RESEND_CERT_REQ		0x0008	           //�������´���֤�飬ע����ĳ��ܻ����Ա֤�飻	PC->ARM
#define	CERT_INFO_REQ		0x0020	           //������h3�ϴ洢�ĸ���֤�����,��Ϣ����Ӧ CERT_NUM��	PC->ARM
#define	CERT_DATA_REQ		0x0021	           //������h3�ϴ洢�ĸ���֤�飻	PC->ARM



#define	UPPER_CERT_CONFIRM			0x0022	   //��λ���յ�֤����CRC��ȷ��ɾ��ԭ����֤�飻	PC->ARM
#define	UPPER_CERT_NO_CONFIRM		0x0023	   //��λ��û�յ�֤�����CRC�������´�����һ��֤�飻	PC->ARM

#define INFO_DATA_CRC_ERR		0x0025	       //��λ���յ��� ֤����Կ+��Ա��Ϣ ��CRC����	ARM->PC
#define CERT_DATA_B_CRC_RIGHT	0x0027	       //��λ�����뵽H3�е�֤��CRC��ȷ��ARM->PC
#define CERT_DATA_B_CRC_ERR		0x0028	       //��λ�����뵽H3�е�֤��CRC����ARM->PC

#define	CERT_NUM			0x0030	           //h3�ϴ洢�ĸ���֤�����,��Ӧ CERT_INFO_REQ��	ARM->PC

#define ENROLL_REQ 			0x0100		       //ע������		PC->ARM
#define	ENROLL_SUCCESS		0x0101		       //ע��ɹ���		ARM->PC
#define ENROLL_FAILED		0x0102		       //ע��ʧ�ܣ�		ARM->PC	

#define VALIDATE_LOCAL_REQ 		0x0110		   //����֤����֤����		PC->ARM
#define	VALIDATE_LOCAL_SUCCESS	0x0111		   //����֤����֤�ɹ���		ARM->PC
#define VALIDATE_LOCAL_FAILED		0x0112	   //����֤����֤ʧ�ܣ�		ARM->PC	

#define	VALIDATE_UPPER_SUCCESS	0x0114		   //��λ��֤����֤�ɹ���		ARM->PC
#define VALIDATE_UPPER_FAILED		0x0115	   //��λ��֤����֤ʧ�ܣ�		ARM->PC	

#define VALIDATE_UPPER_CERT_START 	0x0116	   //��λ��֤����֤,��λ����ʼ����֤��		PC->ARM
#define VALIDATE_UPPER_CERT_END 	0x0117	   //��λ��֤����֤,��λ����������֤�� (��������Զ���ʼ��֤)		PC->ARM
#define VALIDATE_UPPER_CERT_DATA 	0x0118	   //��λ��֤����֤,��λ������֤��(����֤�鴫��)		PC->ARM

#define DELETE_REQ 		0x0120		           //ɾ������		PC->ARM
#define	DELETE_SUCCESS	0x0121		           //ɾ���ɹ���		ARM->PC
#define DELETE_FAILED		0x0122		       //ɾ��ʧ�ܣ�		ARM->PC	

#define HEART_BEAT 0x6666			           //��������ARM->PC

//CMD1;date package
#define	INFO_DATA	0x1000				       //֤����Կ+��Ա��Ϣ+CRC��PC->ARM
#define CERT_DATA_A	0x1001				       //����Աע�����֤��+�������ARM->PC
#define CERT_DATA_A_FAIL 0x1004
#define CERT_DATA_B	0x1002				       //ע�����֤��(���뵽H3��)��PC->ARM
#define CERT_DATA_C	0x1003				       //����H3�ϵ�֤��(���뵽PC��)��ARM->PC

//CERT_TYPE
#define SUPER_MGR	0x00	                   //��������Ա
#define MGR		0x01		                   //����Ա
#define USR		0x02		                   //�û�

#define DEV_KEY_LENGTH 32
#define RAN_NUM_LENGTH 32

#define CERT_LENGTH 6112
#define CERT_WHOLE_LENGTH 6116


#define DEV_NAME "UD55"	
#define SERIAL_NUM "04005035c2185831020e"

#define CERT_SIZE 6148                         //֤���С
#define CMD_SIZE 1024                          //ָ�����С

#define CONTINUE_IMPT 1                        //��������
#define STOP_IMPT 2                            //�˳�
#define NONE_STATUS_OF_IMPT 0     

#define VALIDATE_REQ 		0x0110		       //��֤����		PC->ARM
#define	VALIDATE_SUCCESS	0x0111		       //��֤�ɹ���		ARM->PC
#define VALIDATE_FAILED		0x0112		       //��֤ʧ�ܣ�		ARM->PC	
#define REGISTER_SUCCESS    0x1001             //ע��ɹ�

#define DEV_VALIDATE_SUCCESS 1
#define DEV_VALIDATE_FAIL 2
#define DEV_VALIDATE_NOT_SUCCESS_NOT_FAIL 666

#define LOGIN_BY_PASSWORD 0
#define LOGIN_BY_FINGER 1
#define LOGIN_BY_FINGER_AND_PASSWD 2

#define VALIDATE_UPPER_END	0x0119		       //��λ��֤����֤������		PC->ARM

#define USER_TYPE_OF_USER 2
#define USER_TYPE_OF_MANAGE 1

#define YES_DELETE 111111
#define NO_DELETE  111112

#define ENCRYPT_SUCCESS 111113
#define ENCRYPT_FAIL 111114
#define ENCRYPT_NONE 111115

#define MAX_USERNAME_LEN 20

#define FINGER_PIC_SIZE 17328
#define FINGER_SAVE_SIZE 138625

#define USERLIST_BUF_SIZE 20000

#define DELETE_ADMIN_LOG  "4"
#define ADD_ADMIN_LOG "2"
#define ADMIN_LOGIN "1"
#define ADD_USER "3"
#define ADD_USER_FINGER "5"
#define ADD_CERT "6"
#define ADD_DEV_LOG "7"
#define LATER_THAN_TODAY 0
#define DYNAMIC_KEYT "0"
#define PACK_KEYT "1"
#define ADD_CERT_LOG_STR "8"
#define ADD_CERT_LOG 8
#define ADD_USER_FINGER_LOG 9
#define ADD_USER_FINGER_LOG_STR "9"
#define DEL_CERT_LOG 10
#define DEL_CERT_LOG_STR "10"
#define DEL_FINGER_LOG 11
#define DEL_FINGER_LOG_STR "11"
#define ADD_USER_LOG 3
#define CONFIGURE_CERTS_LOG 12
#define CONFIGURE_CERTS_LOG_STR "12"
#define CLEAR_DEV_LOG_STR "13"
#define CLEAR_DEV_LOG 13
#define DEL_USER_LOG 14
#define DEL_USER_LOG_STR "14"

#define MAKE_SURE_DELETE_MSG "ȷ��ɾ����"


typedef struct {
	std::vector<std::string> usrnames;
	int num;
	bool error_flag;
}   selectUsrnamesResult;

typedef struct {
	std::vector<std::string> manager_names;
	std::vector<std::string> contents;
	std::vector<std::string> times;
	std::vector<std::string> types;
	bool error_flag;
	int num;
}   log_select_ret;

typedef struct {
	char id[17];
	char name[200];
	char date[20];
	char status[10];
}	dev_sel_ret;

typedef struct {
	char id[17];
	char content[255];
	char manager_name[80];
	char str_time[60];
	char type[2];
	char date[20];
}	log_sel_ret;

typedef struct {
	char id[10];
	char user_id[128];
	char dev_id[16];
}	user_dev_sel_ret;

typedef struct {
	char id[128];
	char user_id[128];
	char content[255];
	char type[5];
	char date[30];
	char name[32];
}	cert_sel_ret;

typedef struct {
	char id[128];
	char name[200];
	char date[20];
	char dev_name[200];
}	user_sel_ret;


typedef struct {
	char id[128];
	char name[200];
	char date[20];
	char dev_name[200];
	int fingerNum;
	int certNum;
}	USER_INFO_SEL, *P_USER_INFO_SEL;


typedef struct {
	char name[225];
	char finger[FINGER_PIC_SIZE];
	int id;
}	sel_admin_ret;

typedef struct {
	char name[225];
	char finger[FINGER_SAVE_SIZE];
	int id;
}	sel_admin_ret2;


typedef struct {
	char id[12];
	char finger[FINGER_SAVE_SIZE];
	char name[100];
	char user_id[128];
	char username[255];
	char date[20];
}	sel_finger_ret3;

typedef struct {
	char name[100];
	char date[20];
	std::string id;
}   sel_finger_ret;

typedef struct {
	char name[100];
	char date[20];
	char finger[FINGER_PIC_SIZE];
	int id;
	char user_id[128];
	char username[100];
}   sel_finger_ret2;

typedef struct{
	char byKey[65];
	char wszName[32];
	int dwFlags;
	int dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
}SW_CERT,*PSW_CERT;

typedef struct {
	BYTE byKey[32];
	WCHAR wszName[32];
	DWORD dwFlags;
	DWORD dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
}FINAL_SW_CERT, *FINAL_PSW_CERT, **FINAL_PPSW_CERT;

typedef struct {
	char byKey[65];
	char wszName[32];
	int dwFlags;
	int dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
	char id[128];
}SW_CERT2, *PSW_CERT2;

typedef struct {
	std::vector<std::string> usrnames;
	std::vector<std::string> dates;
	int num;
	bool error_flag;
}   sel_admin_ret3;


typedef struct
{
	GUID UserID;				// �û���ʶGUID
	DWORD dwCertMap[2];		    // ֤��ӳ���
							    // Ŀǰ���֧��64��֤�飬ÿλ��Ӧһ��֤������ 
							    // ��Ӧ��λΪ1��ʾ���û�ӵ�д�֤��
	DWORD dwReserved[2];		// �����ռ�
} SW_USER, *PSW_USER, **PPSW_USER;

typedef struct
{
	DWORD dwSize;					// �˽ṹ���ܳ���
	DWORD dwUserTableOffset;		// �û���ƫ����������ڽṹͷ��
	DWORD dwUserTableLength;		// �û�����bleLength/ dwUserUnitSize,
									// ���ǵ��Ժ����չ������ֱ��ʹ
	DWORD dwUserUnitSize;			// ����Ϊsizeof(SW_USER)
									// UserTable���û�����ΪdwUserTa�õ�ǰ��SW_USER�ṹ�峤��
	DWORD dwCertTableOffset;		// ֤���ƫ����
	DWORD dwCertTableLength;		// ֤�����
									// ֤�����ΪdwCertTableLength/sizeof(SW_CERT)
} SW_USERCERTTABLE, *PSW_USERCERTTABLE;


typedef struct {
	char finger_name[32];
	unsigned char fdata[FINGER_PIC_SIZE];
} FINGER_DATA, *P_FINGER_DATA;


typedef struct {
	char user_name[128];
	char user_id[64];
	int fnum;            //ָ��������(�����û�ָ��������������6��)
	FINGER_DATA fingers[6];
	char	crc[2];						//crc
	char	reserve_2[2];
} USER_DATA, *P_USER_DATA;



typedef struct {
	char     finger_name[32];
}FINGER_INFO, *P_FINGER_INFO;

typedef struct {
	char     user_id[64];
	int             fnum;
	FINGER_INFO fdata[6];
	char	reserve_2[4];
	char       user_name[200];
}USER_INFO, *P_USER_INFO;



typedef struct
{
	DWORD dwSize;			// ���ṹ��С�������Ժ�İ汾����
	HANDLE hevtNotify;		// ָ���û�״̬�л�֪ͨ
} SDD_INIT_DATA, *PSDD_INIT_DATA;


typedef struct {
	char user_id[64];
	char finger_name[32];
	unsigned char fdata[FINGER_PIC_SIZE];
	int sync_flag;        //ͬ����־λ
	char	crc[2];
	char       user_name[200];
	char	reserve_2[2];
} SYNC_DATA, *P_SYNC_DATA;



typedef BOOL(WINAPI *SDFP_INIT_FUNC)(IN LPCSTR lpszSDFPLibFile);
typedef DWORD(WINAPI *SDFPDEV_INIT_FUNC)(IN PSDD_INIT_DATA psid);
typedef DWORD(WINAPI * SDFPDEV_CLOSE_FUNC)();
typedef BOOL(WINAPI *SDFP_CLOSE_FUNC)();
typedef DWORD(WINAPI *READ_USERCERT_TABLE_FUNC)(IN OUT DWORD*, OUT PSW_USERCERTTABLE);
typedef DWORD(WINAPI *WRITE_USERCERT_TABLE_FUNC)(IN PSW_USERCERTTABLE);
//typedef DWORD(WINAPI *TG_DEV_GET_SN)(char *sn);
//typedef DWORD(WINAPI *SD_DEV_INIT)(IN PSDD_INIT_DATA psid);
//typedef DWORD(WINAPI *TG_GET_RANDOM)(unsigned char *randombuf, int randomlength);



// �Ƿ�����豸�������ݣ����ע�͵����ɵ������Խ���
#define _TEST_TEST
//#define _TEST_WITH_LOGIN
#define _TEST_WITH_DEV_CONN
//#define _TEST_WH_LIB
#define _TEST_OUTO_CREATE_CERT


#define RET_ERROR -1
#define OK 0
#define CLOSE_DEV_FAIL "�Ͽ��豸ʧ��"
#define OPEN_DEV_FAIL "���豸ʧ��"
#define CLEAR_DEV_SUCCESS_STR "����豸�ɹ�"
#define CLEAR_DEV_FAIL_STR "����豸ʧ��"
#define SHOW_AFTER_CONN_DEV_STR "�����豸����ʾ"
#define RESULT_TITLE_WIN_STR "���"
#define RECONN_DEV_PLEASE_STR "�����������豸"


#define LEN_OF_CODE_WRONG 0
#define INPUTED_CH_NOT_HEX 1
#define INPUT_RIGHT 2

#define MAX_DEV_USER_CERT_SPACE  8072



#endif  
