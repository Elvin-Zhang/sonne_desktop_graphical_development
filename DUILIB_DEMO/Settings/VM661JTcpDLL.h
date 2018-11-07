#ifndef _VM661JTCPDLL_H_
#define _VM661JTCPDLL_H_
#ifdef VM661JTCPDLL_EXPORTS
#define VM661JTCPDLL_API _declspec(dllexport)
#else
#define VM661JTCPDLL_API _declspec(dllimport)
#endif 
/******************************************************************************
*����Ϊ�豸����ֵ
******************************************************************************/
#define TG_OK                0x00
#define TG_COMM_ERR          0x01
#define TG_NO_FINGER         0x02

/******************************************************************************
*����Ϊ�豸������������
******************************************************************************/
#define BI					0x00	//Bi
#define BIBI				0x01	//BiBi	
#define REG_SUCCESS			0x02	//�Ǽǳɹ�
#define REG_FAIL 			0x03	//�Ǽ�ʧ��
#define PLS_REPUT			0x04	//���ٷ�һ��
#define PLS_PUT_CRUCLY     	0x05	//����ȷ������ָ
#define PLS_PUT_SOFTLY		0x06	//����Ȼ�����ָ
#define IDENT_SUCCESS		0x07	//��֤�ɹ�
#define IDENT_FAIL			0x08	//��֤ʧ��
#define PLS_REDO			0x09	//������
#define DEL_SUCCESS			0x0A	//ɾ���ɹ�
#define DEL_FAIL			0x0B	//ɾ��ʧ��
#define VEIN_FULL			0x0C	//ָ��������
#define VOLUME0				0xE0	//��С��������0
#define VOLUME1				0xE1	//�м���������1
#define VOLUME2				0xE2	//�м���������2
#define VOLUME3				0xE3	//�м���������3
#define VOLUME4				0xE4	//�м���������4
#define VOLUME5				0xE5	//�м���������5
#define VOLUME6				0xE6	//�м���������6
#define VOLUME7				0xE7	//�����������7

#include "my_including.h"
/******************************************************************************
*����ΪPC�����豸�ӿں���
******************************************************************************/
#define WINAPI __stdcall

#ifdef __cplusplus 
extern "C" {
#endif	
	/******************************************************************************
	Function:
	���豸������豸����״̬
	Output��
	Return��
	>0��������
	-1���Ͽ�����
	Others��
	�豸�Ĳ������ָ�����������ӿڵ���
	*****************************************************************************/
	VM661JTCPDLL_API	int TGGetStatus();
	/******************************************************************************
	Function:
	���豸��PC�˴���λ���豸
	Output��
	mode:ͨѶģʽ��1ΪHIDͨѶ��
	Return��
	>0���豸�򿪳ɹ�
	-1���豸��ʧ��
	Others��
	�豸�Ĳ������ָ�����������ӿڵ���
	*****************************************************************************/
	VM661JTCPDLL_API	int TGOpenDev(int* mode);
	/******************************************************************************
	Function:
	�ر��豸��PC�˹ر���λ���豸
	Return��
	0���豸�رճɹ�
	-1���豸�ѹر�
	Others��
	*****************************************************************************/
	VM661JTCPDLL_API int TGCloseDev();
	/******************************************************************************
	Function:
	�豸��ȡͼ���豸�Ĵ�������ȡָ����ͼ��
	Input��
	unsigned char* pImageData��ͼ������(500*200)
	int timeout:��ȡͼ��ȴ���ʱ�䣨�����������ʱ��û�м�⵽touch�ͷ���-1��
	timeout<=50,��λs;
	timeout>50����λms;
	Output��
	��
	Return��
	0���豸��ȡͼ��ɹ�
	-1���豸��ȡͼ��ʧ��
	Others��
	�豸��ȡͼ����ָPC�����������豸�����ȡ��绷��ͼ��
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetImage(unsigned char* pImageData, int timeout);
	/******************************************************************************
	Function:
	�豸�����������豸������ʾ����
	Input��
	int iVoiceValue����������
	Output��
	��
	Return��
	0���豸���������ɹ�
	-1���豸��������ʧ��
	Others��
	�����������ں��ж��壬�豸��һ���ϵ�ʱ����λ��Ҫ���豸����һ������������
	�����豸�������������������
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevPlayVoice(int VoiceValue);
	/******************************************************************************
	Function:
	��ȡ�豸�̼��ţ���firmware
	Input��
	��
	Output��
	char *fw����ȡ���Ĺ̼��ţ�16λ��
	Return��
	0����ȡ�豸�̼��ųɹ�
	-1����ȡ�豸�̼���ʧ��
	Others��
	�̼���Ϊ�ַ���
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetFW(char *fw);
	/******************************************************************************
	Function:
	��ȡ�豸���кţ���sn
	Input��
	��
	Output��
	char *sn����ȡ�������кţ�16λ��
	Return��
	0����ȡ�豸���кųɹ�
	-1����ȡ�豸���к�ʧ��
	Others��
	���к�Ϊ�ַ���
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetSN(char *sn);

	/******************************************************************************
	Function:
	�����豸��ģʽ��ǰ��/��� ����������ʱ��Ч��
	Input��
	int mode��1�����  ��  2��ǰ��
	Output��
	��
	Return��
	1�����óɹ�
	-1������ʧ��
	Others��
	�´��ϵ����Ч
	*****************************************************************************/
	VM661JTCPDLL_API int TGSetMode(int mode);
	/******************************************************************************
	Function:
	���ò���ȡͼ���ȡ��ʼ�м���ʼ��
	Input��
	��
	Output��
	char *rowcol��ͼ���ȡ�Ŀ�ʼ�м���ʼ�У�rowcolΪ�գ�ֻ��ȡ��rowcol��Ϊ�գ��������ٻ�ȡ��
	Return��
	0����ȡͼ���ȡ�Ŀ�ʼ�м���ʼ�гɹ�
	-1����ȡͼ���ȡ�Ŀ�ʼ�м���ʼ��ʧ��
	Others��
	��ʼ�м���ʼ��Ϊ�ַ���
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetGetRC(char *rowcol);
	/******************************************************************************
	Function:
	��ȡ����TF��״̬
	Input��
	��
	Output��
	char *tf����ȡ����TF��״̬����0�����쳣����1����������
	Return��
	0����ȡ����TF��״̬�ɹ�
	-1����ȡ����TF��״̬ʧ��
	Others��
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetTF(char *tf);
	/******************************************************************************
	Function:
	���û�ȡ�豸���кţ���sn
	Input��
	��
	Output��
	char *sn����ȡ�������кţ�16λ�������snΪ�գ���ֻ��ȡ����������sn����ȡ��
	Return��
	0�����û�ȡ�豸���кųɹ�
	-1�����û�ȡ�豸���к�ʧ��
	Others��
	���к�Ϊ�ַ���
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetGetSN(char *sn);
	VM661JTCPDLL_API int TGDevSetGetClientSN(char *sn);
	/******************************************************************************
	Function:
	����led��
	Input��
	int led_blue�����ƿ��ƣ�0����1������
	int led_green���̵ƿ��ƣ�0����1������
	int led_red����ƿ��ƣ�0����1������
	Output��
	��
	Return��
	0������led�Ƴɹ�
	-1������led��ʧ��
	Others��
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetLed(int led_blue, int led_green, int led_red);
	/*****************************************************************************
	*ע�⣺���½ӿڿ��Ը��������ң����ǲ��ܸ��ͻ�
	*1��VM661JTCPDLL_API int TGDevSetGetSN(char *sn);
	*******************************************************************************/
#if 0
	struct Package{
		char	device_name[32];	//�豸��
		int 	id;					//ID
		int		cmd1;				//ָ��1
		int		cmd2;				//ָ��2
		int 	length;				//���ݳ���
		int		cert_type;			//֤������
		int		sup_mgr_num;		//���س���֤�����
		int		mgr_num;			//���ع���Ա֤�����
		int		usr_num;			//�����û�֤�����
		char	serial_num[32];		//���к�
		char	random_num[32];		//�����
		char	cert_name[32];		//֤������
		char 	reserve_char[96];	//Ԥ������
	};//ָ���  1024B
#endif

	//VM661JTCPDLL_API int tg_net_send_cmd_package(Package send_pack);
	//VM661JTCPDLL_API int tg_net_send_data_package(char * data, int length);

	VM661JTCPDLL_API int admin_start_register(char *buff, char* username);

	VM661JTCPDLL_API int admin_login(sel_admin_ret* sel_admins, int num, char* admin_name); 

	VM661JTCPDLL_API int registerUserFingerOnlyDB(char *buff);

	VM661JTCPDLL_API int registerUserFinger(char *buff, const char* chUserIdAndFingerName);

	VM661JTCPDLL_API int get_user_lst(char* buf,int *num,int *len);

	//VM661JTCPDLL_API int load_user(SW_CERT* certs,sel_finger_ret2* fingers,char* username, char* user_id, int cert_num, int f_num);

	VM661JTCPDLL_API int get_cert_content_func(char *content);

	VM661JTCPDLL_API int set_dev_ciphercode(char *content, int length);

	VM661JTCPDLL_API int clearDev();

	VM661JTCPDLL_API int del_single_finger(const char* userAndFingerId);

	VM661JTCPDLL_API int delUserFingers(char* userId);

	VM661JTCPDLL_API int decryptTest();


	VM661JTCPDLL_API int imptUserFingersBegin(int num);
	/**
	*    sonne
	*    2018-09
	*    �����û�ָ����
	*/
	VM661JTCPDLL_API int imptUsersFingers(P_USER_DATA  user);


	VM661JTCPDLL_API int imptUserFingersEnd(int num);


	/**
	*    sonne
	*    2018-09
	*    ��ȡ�豸ָ������Ϣ
	*/
	VM661JTCPDLL_API int getFingerInfo(P_USER_INFO* pUserFingerInfo, int * num);


	/**
	*    sonne
	*    2018-09
	*    ����ͬ��ָ��������
	*/
	VM661JTCPDLL_API int sendSyncFingers(P_SYNC_DATA arr, int num);

	VM661JTCPDLL_API void fastDelete(void* pvAddr);
	VM661JTCPDLL_API void  fastDeleteArrs(void* pvAddr);
}
#endif

#if 0

#include "my_including.h"



#ifndef _TGVM661JCOMAPI_H_
#define _TGVM661JCOMAPI_H_

#ifdef TGVM661JCOMAPI_EXPORTS
#define TGVM661JCOMAPI_API _declspec(dllexport) __stdcall
#else
#define TGVM661JCOMAPI_API _declspec(dllimport) __stdcall
#endif 

#define FRONT
#define FACTORY

/******************************************************************************
*����Ϊ�豸������������
******************************************************************************/
#define VOICE_BI					0x00	//Bi
#define VOICE_BIBI					0x01	//BiBi	
#define VOICE_REG_SUCCESS			0x02	//�Ǽǳɹ�
#define VOICE_REG_FAIL 				0x03	//�Ǽ�ʧ��
#define VOICE_PLS_REPUT				0x04	//���ٷ�һ��
#define VOICE_PLS_PUT_CRUCLY     	0x05	//����ȷ������ָ
#define VOICE_PLS_PUT_SOFTLY		0x06	//����Ȼ�����ָ
#define VOICE_IDENT_SUCCESS			0x07	//��֤�ɹ�
#define VOICE_IDENT_FAIL			0x08	//��֤ʧ��
#define VOICE_PLS_REDO				0x09	//������
#define VOICE_DEL_SUCCESS			0x0A	//ɾ���ɹ�
#define VOICE_DEL_FAIL				0x0B	//ɾ��ʧ��
#define VOICE_VEIN_FULL				0x0C	//ָ��������
#define VOICE_REREG					0x0D	//�Ǽ��ظ� 
#define VOICE_VOLUME0				0xF0	//����
#define VOICE_VOLUME1				0xF2	//��������1
#define VOICE_VOLUME2				0xF4	//��������2
#define VOICE_VOLUME3				0xF6	//��������3
#define VOICE_VOLUME4				0xF8	//��������4
#define VOICE_VOLUME5				0xFA	//��������5
#define VOICE_VOLUME6				0xFA	//��������6
#define VOICE_VOLUME7				0xFA	//��������7

/****************+**************************************************************
*����ΪPC�����豸�ӿں���
******************************************************************************/

#ifdef __cplusplus 
extern "C" {
#endif	

	//2018-05-19
	int TGVM661JCOMAPI_API TGGetStatus();
	/******************************************************************************
	Function:
	���豸��PC�˴���λ���豸
	Input��
	��
	Output��
	mode:ͨѶģʽ��1ΪHIDͨѶ��
	Return��
	0���豸�򿪳ɹ�
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGOpenDev(int* mode);

	/******************************************************************************
	Function:
	�ر��豸��PC�˹ر���λ���豸
	Return��
	0���豸�رճɹ�
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGCloseDev();

	/******************************************************************************
	Function:
	��ȡ�豸״̬
	Input��
	��
	Output��
	��
	Return��
	>=0���豸������
	<0���豸δ����
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevStatus();

	/******************************************************************************
	Function:
	��ȡ�豸�̼��ţ���firmware
	Input��
	��
	Output��
	char* fw����ȡ���Ĺ̼��ţ�16 Bytes��
	Return��
	0����ȡ�豸�̼��ųɹ�
	-1����ʱ
	Others��
	�̼���Ϊ�ַ���
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevFW(char* fw);

	/******************************************************************************
	Function:
	��ȡ�豸���кţ���sn
	Input��
	��
	Output��
	char* sn����ȡ�������кţ�16 Bytes��
	Return��
	0����ȡ�豸���кųɹ�
	-1����ʱ
	Others��
	���к�Ϊ�ַ���
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevSN(char* sn);

	/******************************************************************************
	Function:
	��ȡ�豸�Ĺ���ģʽ��ǰ��/���
	Input��
	��
	Output��
	int* mode�� 0��ǰ�� ; 1�����
	Return��
	0����ȡ�ɹ�
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevMode(int* mode);

	/******************************************************************************
	Function:
	�����豸�ıȶ�ģʽ��ǰ��/���
	Input��
	int mode�� 0��ǰ�� ; 1�����
	Output��
	��
	Return��
	0�����óɹ�
	-1������ʧ��
	Others��
	������Ч
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetDevMode(int mode);

	/******************************************************************************
	Function:
	��ȡ�豸ͼ��
	Input��
	int timeout:��ȡͼ��ȴ���ʱ�䣨�����������ʱ��û�м�⵽touch�ͷ���-1��
	timeout<=50,��λs;
	timeout>50����λms;
	Output��
	unsigned char* imageData��ͼ������(208+500*200 Bytes)
	Return��
	0���豸��ȡͼ��ɹ�
	-1��ץͼ��ʱ
	-2:�豸�Ͽ�
	-3:����ȡ��
	Others��
	��
	*****************************************************************************/
	//int TGVM661JCOMAPI_API TGGetDevImage(unsigned char* imageData, int timeout);

	/******************************************************************************
	Function:
	ȡ����ȡ�豸ͼ��
	Input��
	��
	Output��
	��
	Return��
	0��ȡ���ɹ�
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGCancelGetImage();

	/******************************************************************************
	Function:
	�����豸�������豸������ʾ����
	Input��
	int voiceValue���������ݻ���������
	Output��
	��
	Return��
	0���豸���������ɹ�
	-1���豸��������ʧ��
	Others��
	�����������ں��ж��壬�豸��һ���ϵ�ʱ����λ��Ҫ���豸����һ������������
	Ĭ������ΪVOICE_VOLUME4��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGPlayDevVoice(int voiceValue);

	/******************************************************************************
	Function:
	����led��
	Input��
	int ledBlue�����ƿ��ƣ�0����1������
	int ledGreen���̵ƿ��ƣ�0����1������
	int ledRed����ƿ��ƣ�0����1������
	Output��
	��
	Return��
	0������led�Ƴɹ�
	-1������led��ʧ��
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetDevLed(int ledBlue, int ledGreen, int ledRed);

	/******************************************************************************
	Function:
	д�豸��Ϣ
	Input��
	char* devInfo;��д���豸����Ϣ
	int writeLen:��д�����Ϣ���ȡ�0<writeLen<=1024 Bytes��
	Output��
	��;
	Return��
	>0���ɹ�,ʵ��д�볤��
	-1����ʱ
	-2����δ���
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGWriteDevInfo(char* devInfo, int writeLen);

	/******************************************************************************
	Function:
	���豸��Ϣ
	Input��
	char* devInfo;����������Ϣ
	int readLen:����������Ϣ���ȡ�0<readLen<=1024 Bytes��
	Output��
	��;
	Return��
	>=0���ɹ�,ʵ�ʶ�ȡ����
	-1����ʱ
	-2����δ���
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGReadDevInfo(char* devInfo, int readLen);

	/******************************************************************************
	Function:
	���û�ȡ�豸���кţ���sn
	Input��
	��
	Output��
	char* sn����ȡ�������кţ�16 Bytes�������snΪ�գ���ֻ��ȡ����������sn����ȡ��
	Return��
	0�����û��ȡ�豸���кųɹ�
	-1����ʱ
	Others��
	���к�Ϊ�ַ���
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevClientSN(char* sn);



	// 55 project functions
	int TGVM661JCOMAPI_API register_user_finger(char *buff, const char* user_id, const char* username, int cert_num, const char* finger_name, SW_CERT* certs);
	int TGVM661JCOMAPI_API get_user_lst(char* buf, int *num, int *len);
	int TGVM661JCOMAPI_API load_user(SW_CERT* certs, sel_finger_ret2* fingers, char* username, char* user_id, int cert_num, int f_num);
	int TGVM661JCOMAPI_API get_cert_content_func(char *content);
	int TGVM661JCOMAPI_API admin_start_register(char *buff, char* username);
	int TGVM661JCOMAPI_API admin_login(sel_admin_ret* sel_admins, int num, char* admin_name);

	int TGVM661JCOMAPI_API TGDevGetSN(char *sn);

#ifdef FRONT
	/******************************************************************************
	*�����豸�˱ȶ���ؽӿ�
	*******************************************************************************/

	/******************************************************************************
	Function:
	�����豸��ע��
	Input��
	int retImgMode��1���豸���ؼ���ͼƬ���� ��0���豸�����ؼ���ͼƬ����
	char* userName:�û�ID��<50Bytes��
	Output��
	��
	Return��
	0������ɹ�����ѭ������ TGGetFuncMoreReturn��ȡע����̷���ֵ
	-1������ʧ��
	Others��
	ѭ������ TGGetDevRegIdentReturn,��ȡע����̷���ֵ��
	retImgModeΪ1ʱ����TGGetDevRegIdentReturn�ķ���ֵΪVOICE_BIʱ��
	����TGGetDevImage��ȡ����ͼƬ���ݡ�
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDevRegFinger(int retImgMode, char* userName);

	/******************************************************************************
	Function:
	�����豸����֤
	Input��
	int retImgMode��1���豸���ؼ���ͼƬ���� ��0���豸�����ؼ���ͼƬ����
	Output��
	��
	Return��
	0������ɹ�,����� TGGetFuncMoreReturn��ȡ��֤����ֵ
	-1������ʧ��
	Others��
	���� TGGetDevRegIdentReturn��ȡ��֤���
	retImgModeΪ1ʱ����TGGetDevRegIdentReturn�ķ���ֵΪVOICE_BIʱ��
	����TGGetDevImage��ȡ����ͼƬ���ݡ�
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDevIdentFinger(int retImgMode);

	/*****************************************************************************
	Function:
	�����豸��������֤
	Input��
	int retImgMode��1���豸���ؼ���ͼƬ���� ��0���豸�����ؼ���ͼƬ����
	Output��
	��
	Return��
	0������ɹ�,��ѭ������ TGGetDevRegIdentReturn��ȡ��֤���
	-1������ʧ��
	Others��
	ѭ������ TGGetDevRegIdentReturn��ȡ��֤���
	retImgModeΪ1ʱ����TGGetDevRegIdentReturn�ķ���ֵΪVOICE_BIʱ��
	����TGGetDevImage��ȡ����ͼƬ���ݡ�
	**************************************************************************/
	int TGVM661JCOMAPI_API TGDevContinueIdentFinger(int retImgMode);

	/**************************************************************************
	Function:
	��ȡ�豸ע����豸������֤ʱ�ķ���ֵ
	Input��
	int timeOutMs:��ʱ��ms��
	Output��
	char* templId��ע��ɹ�����֤�ɹ�ʱ���ص�ID(<50 Bytes)
	Return��
	����ֵΪ������CMD�ĺ궨��ֵ,���ݺ�����ʾ��Ӧ�����
	Others��
	�����ڻ�ȡ�豸��ע����豸����֤ʱ�ķ���ֵ��
	***************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevRegIdentReturn(char* tmplId, int timeOutMs);

	/***************************************************************************
	Function:
	ȡ���豸��ע�����֤
	Input��
	��
	Output��
	��
	Return��
	0������ɹ�
	-1������ʧ��
	Others��
	��
	****************************************************************************/
	int TGVM661JCOMAPI_API TGCancelDevRegIdent(void);

	/****************************************************************************
	Function:
	��ȡ�豸ģ������
	Input��
	int maxTemplNumMode��0���豸����ע���ģ������1���豸�п�ע������ģ����
	Output��
	��
	Return��
	>=0��ģ����
	-1:��ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTmplNum(int maxTemplNumMode);

	/*****************************************************************************
	Function:
	��ȡ�豸ģ����Ϣ�б�
	Input��
	��
	Output��
	int* templNum���豸����ע���ģ����
	char* templNameList���豸��ģ����Ϣ�б� ��templNum * 50 Bytes��
	Return��
	0����ȡ�豸ģ����Ϣ�б�ɹ�
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTmplInfo(int* templNum, char* templNameList);

	/*****************************************************************************
	Function:
	ɾ���豸��ָ����IDģ�塣
	Input��
	char* templId����ɾ����ID��,����"0"
	Output��
	��
	Return��
	0��ɾ���ɹ�
	1���豸�в����ڴ�ɾ����ID
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDelDevTmpl(char* templId);

	/*****************************************************************************
	Function:
	����豸�е�ģ�塣
	Input��
	��
	Output��
	��
	Return��
	0����ճɹ�
	1���豸�в�����ģ��
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGEmptyDevTmpl();

	/*****************************************************************************
	Function:
	�ϴ��豸��ָ��IDģ�嵽������
	Input��
	char* templId���豸�д��ϴ���ģ��ID��������"0"
	Output��
	unsigned char* tmplData�����յ���ģ�����ݣ�17632 Bytes��
	int* tmplSize�����յ���ģ���С
	Return��
	0���ϴ��ɹ�
	1���豸�в����ڴ��ϴ���ģ��
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGUpDevTmpl(char* tmplId, unsigned char* tmplData, int* tmplSize);

	/******************************************************************************
	Function:
	�豸���ϴ�ģ�����������ģ��������豸������ģ�壩��
	Input��
	��
	Output��
	unsigned char* tmplPkgData�����յ���ģ������ݣ�<��17632+50��*300 Bytes)
	int* tmplPkgSize�����յ���ģ�����С
	Return��
	0���ϴ��ɹ�
	1���豸�в�����ģ��
	-1����ʱ
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGUpDevTmplPkg(unsigned char* tmplPkgData, int* tmplPkgSize);

	/******************************************************************************
	Function:
	����������ָ��IDģ�嵽�豸��
	Input��
	char* tmplId��������ģ���ID��������"0"
	unsigned char* tmplData�������ص�ģ������
	int tmplSize�������ص�ģ�����ݵĴ�С
	Output��
	��
	Return��
	0�����سɹ�
	-1:��ʱ
	-2:ģ�����
	-3:ָ��������
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDownDevTmpl(char* tmplId, unsigned char* tmplData, int tmplSize);

	/******************************************************************************
	Function:
	��������ģ������豸��������豸�е�ģ�壩��
	Input��
	unsigned char* tmplPkgData:�����ص�ģ�������
	int tmplPkgSize�������ص�ģ�����ݵĴ�С
	Output��
	��
	Return��
	0�����سɹ�
	-1:��ʱ
	-2:ģ�������
	-3:ָ�����������豸�н��������ģ����
	Others��
	��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDownDevTmplPkg(unsigned char* tmplPkgData, int tmplPkgSize);
#endif // FRONT

#ifdef FACTORY
	/*****************************************************************************
	*����������ؽӿڣ����������ͻ�
	*******************************************************************************/

	/******************************************************************************
	Function:
	���û�ȡ�豸���кţ���sn
	Input��
	��
	Output��
	char* sn����ȡ�������кţ�16 Bytes�������snΪ�գ���ֻ��ȡ����������sn����ȡ��
	Return��
	0�����û�ȡ�豸���кųɹ�
	-1����ʱ
	Others��
	���к�Ϊ�ַ���
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevSN(char* sn);

	/******************************************************************************
	Function:
	���ò���ȡͼ���ȡ��ʼ�м���ʼ��
	Input��
	��
	Output��
	char* rowcol��ͼ���ȡ�Ŀ�ʼ�м���ʼ�У�rowcolΪ�գ�ֻ��ȡ��rowcol��Ϊ�գ��������ٻ�ȡ��
	Return��
	0���ɹ�
	-1����ʱ
	Others��
	��ʼ�м���ʼ��Ϊ�ַ���
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevRC(char* rowcol);

	/******************************************************************************
	Function:
	��ȡ����TF��״̬
	Input��
	��
	Output��
	char* tf����ȡ����TF��״̬����0�����쳣����1����������
	Return��
	0����ȡ����TF��״̬�ɹ�
	-1����ʱ
	Others��
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTF(char* tf);

	/******************************************************************************
	Function:
	��ȡ�豸ͼ��(�������ָ)
	Input��
	��
	Output��
	unsigned char* imageData��ͼ������(208+500*200 Bytes)
	Return��
	0���豸��ȡͼ��ɹ�
	-1��ץͼ��ʱ
	-2:�豸�Ͽ�
	-3:����ȡ��
	Others��
	��
	*****************************************************************************/
	//int TGVM661JCOMAPI_API TGGetDevImageWithoutFinger(unsigned char* pImageData);
#endif // FACTORY
#ifdef __cplusplus 
}
#endif

#endif


#endif