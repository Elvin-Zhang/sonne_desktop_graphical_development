#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <io.h>  

#include "my_including.h"
#include "direct.h"
#include "io.h"


#pragma once

namespace FILE_OPERATION
{
	using namespace std;

	void init_cers_path();
	
	/*
	 *   sonne
	 *   ��ָ���ļ�ĩβд���µ�һ��
	 *   2017-09-20
	 */
	void write_next_line( char *path, const char *content);



	/**
	*   ���ߣ�sonne
	*   ���ڣ�2017-05-18
	*   ���ܣ������û�����ȡ��Ӧ֤��·��
	**/
	void get_file_path_by_usrname(char *path, const char* usrname, int usr_type);

	/**
	*   ���ߣ�LYF
	*   ���ڣ�2017-05-16
	*   ���ܣ������û�����ȡ��Ӧ֤��·��
	**/
	void writeDataHex(unsigned char * my_array,int length,char *string);

	/**
	* ��      ��:	sonne
	* ��  ��  ��:   readTxt
	* ��      ��:   �ļ����ַ���ȡ
	*/
	char* readTxt(string file);

	/**
	* ��      ��:	sonne
	* ��  ��  ��:   Remove_data_hex
	* ��      ��:   ɾ���ļ�����
	*/
	bool Remove_data_hex(char* usrname, int usr_type);

	/**
	* ��      ��:	LYF
	* ��  ��  ��:   read_data_hex���ܺ�readTxt��ͬ����������������ǰ����·���ַ��������߿�����ָ��
	* ��      ��:   �ļ����ַ���ȡ
	*/
	void read_data_hex(unsigned char *buf,int length,char *string);


	/*
	** ���ߣ�sonne
	** ���ڣ�2017-06-12
	** ˵������ȡ�ƶ�Ŀ¼�������ļ�·�����ļ���
	 */
	void getFileNamesAndPaths32Bit(string path, vector<string>& files, vector<string>& file_name);


	/*
	** ���ߣ�sonne
	** ���ڣ�2017-06-12
	** ˵������ȡ�ƶ�Ŀ¼�������ļ�·�����ļ���
	*/
	void getFileNamesAndPaths(string path, vector<string>& files, vector<string>& file_name);

	void read_data_hex(char *buf,int length,const char *string);
}