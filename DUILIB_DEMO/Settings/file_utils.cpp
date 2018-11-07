#include "file_utils.h"

#pragma once

namespace FILE_OPERATION
{
	using namespace std;

	void init_cers_path() {
		// ֤��·��
		//GetModuleFileName(NULL,(LPSTR)g_cers_path,sizeof(g_cers_path));
		getcwd(g_cers_path, 256); 
		strcat(g_cers_path,"\\cers");

		getcwd(g_manager_cers_path, 256); 
		strcat(g_manager_cers_path, "\\manager_cers"); 

		// �ж�Ŀ¼�Ƿ���ڣ�����
		fstream _file;
		_file.open(g_cers_path,ios::in);
		if(!_file) {
			_mkdir(g_cers_path);
		} 
		_file.open(g_manager_cers_path,ios::in);
		if(!_file) {
			_mkdir(g_manager_cers_path);
		} 
	}

	
	/*
	 *   sonne
	 *   ��ָ���ļ�ĩβд���µ�һ��
	 *   2017-09-20
	 */
	void write_next_line( char *path, const char *content) {
		ofstream file_out(path, ios::app);
        file_out << content<< "\n";
		file_out.close();
	}



	/**
	*   ���ߣ�sonne
	*   ���ڣ�2017-05-18
	*   ���ܣ������û�����ȡ��Ӧ֤��·��
	**/
	void get_file_path_by_usrname(char *path, const char* usrname, int usr_type) {
		//char FilePath[500] = {0};
		if (usr_type == USER_TYPE_OF_MANAGE) {
			strcpy(path,g_manager_cers_path);
			strcat(path, "\\");
			strcat(path, usrname);
			strcat(path, ".dat");
			//MessageBox(NULL,FilePath,NULL,NULL);
			//MessageBox(NULL,FilePath,NULL,NULL);
		} else {
			strcpy(path,g_cers_path);
			strcat(path, "\\");
			strcat(path, usrname);
			strcat(path, ".dat");
		}
	}

	/**
	*   ���ߣ�LYF
	*   ���ڣ�2017-05-16
	**/
	void writeDataHex(unsigned char * my_array,int length,char *string)
	{
		int i = 0;
		FILE *fp;
		fp = fopen(string,"wb+");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		while(i < length)
		{        
			fwrite(&my_array[i],sizeof(unsigned char ),1,fp);
			i++;
		}
		fclose(fp);
	}

	/**
	* ��      ��:	sonne
	* ��  ��  ��:   readTxt
	* ��      ��:   �ļ����ַ���ȡ
	*/
	char* readTxt(string file)
	{
		char ch_arr[6200] = {0};

		int i = 0;
		if (!file.empty())
		{
			ifstream infile; 
			infile.open(file.data());   //���ļ����������ļ��������� 
			assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 
			char c;
			infile >> noskipws;
			while (!infile.eof())
			{
				infile>>c;
				ch_arr[i] = c;
				i++;
			}
			ch_arr[i-1] = '\0';			//����infile.eof()�Ǹ���֪����ĺ���������һλ������i-1δ��0
			infile.close();             //�ر��ļ������� 
		}
		return ch_arr;
	}

	/**
	* ��      ��:	sonne
	* ��  ��  ��:   Remove_data_hex
	* ��      ��:   ɾ���ļ�����
	*/
	bool Remove_data_hex(char* usrname, int usr_type) {
		char path[500] = {0};
	    get_file_path_by_usrname(path, usrname, usr_type);
		//char PathName[500] = {0};
		//memcpy(PathName,path,500);
		//MessageBox(NULL,PathName,NULL,NULL);
		if(remove(path) != 0)
			return false;
		return true;
	}

	/**
	* ��      ��:	LYF
	* ��  ��  ��:   read_data_hex���ܺ�readTxt��ͬ����������������ǰ����·���ַ��������߿�����ָ��
	* ��      ��:   �ļ����ַ���ȡ
	*/
	void read_data_hex(unsigned char *buf,int length,char *string)
	{
		int i = 0;
		int re;
		FILE *fp;
		fp = fopen(string,"rb");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		fread(buf,sizeof(unsigned char),length,fp);
		fclose(fp);
	}


	/*
	** ���ߣ�sonne
	** ���ڣ�2017-06-12
	** ˵������ȡ�ƶ�Ŀ¼�������ļ�·�����ļ���
	 */
	void getFileNamesAndPaths32Bit(string path, vector<string>& files, vector<string>& file_name)
	{
		//�ļ����  
		 long   hFile = 0;
		  //�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
		struct _finddata_t fileinfo;
		//�ַ��������·��
	    string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
		{
			do
			{
				//�����Ŀ¼,����֮
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFileNamesAndPaths32Bit(p.assign(path).append("\\").append(fileinfo.name), files, file_name);
				}
				//�������,�����б�  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					file_name.push_back(fileinfo.name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose������������
			_findclose(hFile);
		}
	}


	/*
	** ���ߣ�sonne
	** ���ڣ�2017-06-12
	** ˵������ȡ�ƶ�Ŀ¼�������ļ�·�����ļ���
	*/
	void getFileNamesAndPaths(string path, vector<string>& files, vector<string>& file_name)
	{
		//�ļ����  
		__int64   hFile = 0;
		//�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
		//struct _finddata_t fileinfo;
		struct __finddata64_t fileinfo;
		//�ַ��������·��
		string p;
		if ((hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
		{
			do
			{
				//�����Ŀ¼,����֮
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					    getFileNamesAndPaths(p.assign(path).append("\\").append(fileinfo.name), files, file_name);
				}
				//�������,�����б�  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					file_name.push_back(fileinfo.name);
				}
			} while (_findnext64(hFile, &fileinfo) == 0);
			//_findclose������������
			_findclose(hFile);
		}
	}

	void read_data_hex(char *buf,int length,const char *string)
	{
		int i = 0;
		int re;
		FILE *fp;
		fp = fopen(string,"rb");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		fread(buf,sizeof(unsigned char),length,fp);
		fclose(fp);
	}
}