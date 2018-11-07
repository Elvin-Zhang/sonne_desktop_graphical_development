#pragma comment(lib,"hid.lib")

#include "lib_x64\TGHidApi.h"
#pragma comment(lib,"lib_x64\\TGHidApi.lib")

#ifdef MY661TCPDLL_EXPORTS
#define MY661TCPDLL_API __declspec(dllexport)
#else
#define MY661TCPDLL_API __declspec(dllimport)
#endif

#define VID 0x0525
#define PID 0xA4AC
#define INREPORTBYTELEN 1025
#define OUTREPORTBYTELEN 1025


namespace MYHID {

	int app_exit = 0, count = 0;
	int fd = -1;

	HANDLE hIsDevExitThread;

	SP_DEVICE_INTERFACE_DETAIL_DATA *Dev;
	HANDLE hWriteHandle, hReadHandle;

	int init_hid_dev() {
		SP_DEVICE_INTERFACE_DETAIL_DATA *Dev;
		unsigned long	numBytesReturned;
		BOOL			bResult;
		HIDP_CAPS		Capabilities;
		PHIDP_PREPARSED_DATA		HidParsedData;
		OVERLAPPED		HidOverlapped;
		HANDLE			ReportEvent;

		unsigned short InputReportByteLength[1] = { 0 };
		unsigned short OutputReportByteLength[1] = { 0 };
		char vendorid[16];
		char productid[16];
		char vernum[64];
		char manufaturer[64];
		char product[64];
		int ret;

		Dev = HidFindDevices(VID, PID, InputReportByteLength, OutputReportByteLength);
		if (NULL == Dev) {
			printf("Can not find out the dev...\n");
			return -1;
		}

		printf("InputReportByteLength :%d \n", *InputReportByteLength);
		printf("OutputReportByteLength :%d \n", *OutputReportByteLength);

		ret = GetProductInfo(Dev, vendorid, productid, vernum, manufaturer, product);
		if (ret != 0) {
			printf("Can not Get Product Info ...\n");
			return -1;
		}
		printf("vendorid :%s\n", vendorid);
		printf("productid :%s\n", productid);
		printf("vernum :%s\n", vernum);
		printf("manufaturer :%s\n", manufaturer);
		printf("product :%s\n", product);


		hWriteHandle = CreateFile(Dev->DevicePath, GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			(LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING,
			0,
			NULL);

		hReadHandle = CreateFile(Dev->DevicePath, GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			(LPSECURITY_ATTRIBUTES)NULL,
			OPEN_EXISTING,
			0,
			NULL);


		/*DevHandle = CreateFile(Dev->DevicePath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING,
		0,
		NULL
		);*/

		HidD_SetNumInputBuffers(hReadHandle,512);

		HidD_GetPreparsedData(hReadHandle, &HidParsedData);
		/* extract the capabilities info */
		HidP_GetCaps(HidParsedData, &Capabilities);
		/* Free the memory allocated when getting the preparsed data */
		HidD_FreePreparsedData(HidParsedData);

		return 0;
	}


	void free_hid_dev() {
		free(Dev);
	}


	int ReadHidDev(char *buf, int len) {
		char rBuffer[OUTREPORTBYTELEN * 2] = { 0 };
		DWORD dwRet, bResult;

		/*	if (len == 0) {
		len = INREPORTBYTELEN;
		bResult = ReadFile(hReadHandle, rBuffer, len, &dwRet, NULL);
		if (bResult == 1){
		if (strstr(&rBuffer[1], "device:") != NULL){
		bResult = ReadFile(hReadHandle, &rBuffer[len], len, &dwRet, NULL);
		if (bResult == 1){
		for (int i = 0; i < len; i++)
		buf[i] = rBuffer[i + 1];
		for (int i = 0; i < len; i++)
		buf[64 + i] = rBuffer[len + 1 + i];
		}
		}
		}
		//if (GetLastError()) return	GetLastError();
		len = strlen(buf);
		printf("cmd : %d %d [%s]\n", len,dwRet, buf);
		}
		else if (len > 0){
		if (len<INREPORTBYTELEN) len = INREPORTBYTELEN-1;

		int total = 0;
		for (; total < len;){
		bResult = ReadFile(hReadHandle, rBuffer, INREPORTBYTELEN, &dwRet, NULL);
		//if (GetLastError()) return	GetLastError();
		if (bResult == 1){
		for (int i = 0; i < 64; i++)
		buf[total+i] = rBuffer[i + 1];
		}
		total += 64;
		printf("data : %d [%d]\n",len, total);	
		}

		}*/
		if (len == 0) {
			len = INREPORTBYTELEN;
			bResult = ReadFile(hReadHandle, rBuffer, len, &dwRet, NULL);
			if (bResult == 1){
				//	if (strstr(&rBuffer[1], "device:") != NULL){
				for (int i = 0; i < len; i++)
					buf[i] = rBuffer[i + 1];
				//	}
			}
			//if (GetLastError()) return	GetLastError();
			len = strlen(buf);
			//printf("cmd : %d %d %d\n", len, dwRet,count);
		}
		else if (len > 0){
			if (len<INREPORTBYTELEN) len = INREPORTBYTELEN - 1;

			int total = 0;
			for (; total < len;){
				bResult = ReadFile(hReadHandle, rBuffer, INREPORTBYTELEN, &dwRet, NULL);
				//if (GetLastError()) return	GetLastError();
				if (bResult == 1){
					for (int i = 0; i < INREPORTBYTELEN - 1; i++)
						buf[total + i] = rBuffer[i + 1];
				}
				total += INREPORTBYTELEN - 1;
				//printf("data : %d [%d][%d]\n", len,dwRet, total);
			}
			//printf("data : %d [%d]\n", len, total);
		}
		if (len <= 0){
			if (count >= 10){
				len = -3;	
				count = 0;
			}
		}
		return len;
	}


	int WriteHidDev(char *buf, int len) {
		int length = 0;
		char wBuffer[OUTREPORTBYTELEN] = { 0 };
		DWORD dwRet;
		BOOL bRet;
		BOOLEAN blRet;

		wBuffer[0] = 0;

		//memcpy(&wBuffer[1], lpBuffer, dwSize);

		length = len;

		while (length>0){
#ifdef HID_DEV_H3
			for (int i = 0; i < OUTREPORTBYTELEN - 9; i++)
				wBuffer[i + 1] = buf[len - length + i];

			blRet = HidD_SetOutputReport(hWriteHandle, wBuffer, OUTREPORTBYTELEN);
			bRet = WriteFile(hWriteHandle, wBuffer, OUTREPORTBYTELEN, &dwRet, NULL);
			//if (GetLastError()) return	GetLastError();

			length -= dwRet - 9;

			//printf("end.....%d %d %d\n", len, dwRet, length);

			if (length<0 || dwRet<0)break;
#endif
#ifdef HID_DEV_JZ
			for (int i = 0; i < OUTREPORTBYTELEN-1; i++)
				wBuffer[i + 1] = buf[len - length + i];

			bRet = WriteFile(hWriteHandle, wBuffer, OUTREPORTBYTELEN, &dwRet, NULL);
			//if (GetLastError()) return	GetLastError();
			length -= dwRet-1;

			//printf("end.....%d %d %d\n", len, dwRet, length);

			if (length<0 || dwRet<0)break;
#endif
		}

		return 0;
	}


	int readComm(int fd, char* buf, int len, int timeout) {
		return ReadHidDev(buf, len);
	}


	int writeComm(int fd, char* buf, int len) {
		return WriteHidDev(buf, len);
	}



	/**
	 *���ߣ�sonne
	 *���ڣ�2017-08-03
	 *��ע: hid���ͽṹ��
	 */
	int TG_NetSendCmdPackage(Package send_pack) {
		//send(sClient,(char *)&send_pack,1024,0);
		writeComm(fd, (char *)&send_pack, 1024);
		return 0;
	}


	/**
	 *���ߣ�sonne
	 *���ڣ�2017-08-03
	 *��ע: hid��������
	*/
	int TG_NetSendDataPackage(char * data,int length) {
		//send(sClient, data, length, 0);
		writeComm(fd, data, length);
		return 0;
	}

	/**
	* ��      ��:  sonne
	* ��      ��:  ѭ���ж��ж������Ƿ�����̻߳ص�����
	* �޸� ��¼��  2017-4-8 2017-4-19 2017-4-20 sonne ����ΪSockRecvAndJudgeIsLink��ͳһ�������
    *              2017-08-03   ��Ϊhid��	 
	*/
	DWORD WINAPI sock_recv_and_judge_is_link(LPVOID lpParamter) {
		int ret;
		while (true) {
			if (init_hid_dev() < 0){
				printf("hid dev falil !! \n");
				fd = -1;
				continue;
			}else
				fd = 30;

			for (;;) {
				//���տͻ�������  
				memset(&recv_pack, 0, BUF_SIZE);   
				ret = readComm(fd, (char *)&recv_pack, CMD_SIZE, 0);
				if (SOCKET_ERROR == ret)  {  
					MessageBox(GetForegroundWindow(), "�豸�Ѷ�ʧ��", NULL, NULL);	
					break;
				}
				if(ret == CMD_SIZE) {
					// ָ���
					if (recv_pack.cmd1 != HEART_BEAT)
					{
						// �����ָ�����������ȫ�ֱ���
						recv_cmd = recv_pack;
						if (recv_pack.cmd1 == REGISTER_SUCCESS)
						{
							 ret = readComm(fd, (char *)&recv_cert, recv_pack.length, 0);
							 //ret = recv(sClient, (char *)&recv_cert, recv_pack.length, 0);							 
							 flag = true;//����Աע�����֤��+�����
						}
						if(recv_pack.cmd1 == VALIDATE_SUCCESS)
						{
							MessageBox(NULL, "��֤�ɹ�����", NULL, NULL);
							IsAbleLogin = TRUE;//�յ���֤�ɹ�������
							//��֤�ɹ��ڴ˴���ȡ�û�id
							LoginUsrId = recv_pack.cmd2;
						}
						if(recv_pack.cmd1 == VALIDATE_FAILED)
						{
							MessageBox(NULL, "��֤ʧ�����������֤", NULL, NULL);

							//��֤ʧ�ܼ�����֤���˴���֤�����豸�ϵģ���Ҫ��֤�����ϵģ���δ��
							Package send_pack_begagain;
							memset(&send_pack_begagain,0,CMD_SIZE);
							send_pack_begagain.id = 0;
							send_pack_begagain.cmd1 = VALIDATE_REQ;//������֤
							send_pack_begagain.length = 0;

							writeComm(fd, (char *)&send_pack_begagain, CMD_SIZE);
							//send(sClient,(char *)&send_pack_begagain,CMD_SIZE,0);
							IsAbleLogin = FALSE;//�յ���֤�ɹ�������
						}

						if(recv_pack.cmd1 == CERT_DATA_B_CRC_RIGHT)
							MessageBox(NULL, "����֤��ɹ���", NULL, NULL);
				
						if(recv_pack.cmd1 == CERT_DATA_B_CRC_ERR)
							MessageBox(NULL, "����֤��ʧ�ܣ������²�����", NULL, NULL);

						/*
						* 2017.06.09 sonne
						* ��λ��֤����֤�ɹ�
						*/
						if (recv_pack.cmd1 == VALIDATE_UPPER_SUCCESS)
						{
							g_user_type = recv_pack.cert_type;
							is_pc_login_success = DEV_VALIDATE_SUCCESS;//�յ���֤�ɹ�������
						}

						/*
						* 2017.06.09 sonne
						* ��λ��֤����֤ʧ��
						*/
						if (recv_pack.cmd1 == VALIDATE_UPPER_FAILED)
							is_pc_login_success = DEV_VALIDATE_FAIL;
					}
				}
			}
		}  

		free_hid_dev();    
	}

	/**
	* ��      ��:	sonne
	* ��      ��:  �����̣߳��ж��Ƿ����
	* �޸�  ��¼�� 2017-4-8 
	*/
	void CreatRecvThread(void) {
		hIsDevExitThread = CreateThread(NULL, 0, sock_recv_and_judge_is_link, NULL, 0, NULL);
	}

}
