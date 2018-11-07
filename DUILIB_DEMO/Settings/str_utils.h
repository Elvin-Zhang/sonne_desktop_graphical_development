#pragma once

#include <windows.h>
#include <string>
#include <time.h>
#include <stdio.h>  
#include <assert.h>
#include <TCHAR.H>
#include <vector>
#include "str_utils.h"

/**
 * �ַ�����ز���
 */
namespace STROPERATION {

	bool is_num(char c);


	bool is_chararr_nums(char *c);


	/**
	* ��      ��:	sonne
	* ��      ��:  wchar_t to string 
	*/
	void Wchar_tToString(std::string& szDst, const wchar_t *wchar) ;

	/**
	* ��     �ߣ�sonne
	* ��     �ܣ��ַ���ָ��ת��Ϊ�ַ�������
	*/
	void CharPointerToCharArr(char* char_p, char char_arr[]);

	/**
	* ��     �ߣ�sonne
	* ��     �ܣ�wchar�ַ���ת��Ϊchar�ַ���
	*/
	char* WcharToChar(const wchar_t * wChar);

	/**
	* ��     �ߣ�sonne
	* ��     �ܣ�char�ַ���ת��Ϊwchar�ַ���
	*/
	//WCHAR * charToWchar(const char *s);
	void charToWchar(const char *s, WCHAR* wch);


	/**
	* ��     �ߣ�sonne
	* ��     �ڣ�2017-05-17
	* ��     �ܣ��ж������ַ����Ƿ�����Ƿ��ַ�
	*/
	bool isStrIllegal(const wchar_t * wch);


	/**
	* ��     �ߣ�sonne
	* ��     �ڣ�2017-07-27
	* ��     �ܣ��ַ�����������
	*/
	void link(char *s, const char *t);


	bool check_is_charpointer_null(const char* ch) ;


	/*
	 *  ���ߣ�sonne
	 *  ���ڣ�2017-08-30
	 *  ��ע����־��ӡ��������û���������Խ��������
	 *        �û������ȳ���10��*����
	 */
	void str_len_limit(char *dst, const char *src) ;

	/**
	 *   sonne 2017-11-01
	 *   get string of date,format xxxx-xx-xx
	 */
	void getDateString(char *str_date);


	/**
	*     �ַ����� �� �������ַ��� �໥ת��
	*     2018-02-06
	*/
	int char_array_2_binary_str(const char ch_buf[],int ch_len,char binary_char_buf[],int binary_char_len,int type);

	void wchar_tto_str(std::string& szDst,const wchar_t *wchar);

	void string_to_wstring(std::wstring& szDst, std::string str);

	int dword_bit_set(DWORD *p_data, unsigned char position, int flag);

	BOOL LPCTSR2GUID(LPCTSTR szGUID, GUID &Guid);

	LPCTSTR GUID2LPCTS(GUID Guid);

	BOOL string_to_date(LPCTSTR lpszValue, SYSTEMTIME &time);

	void get_time_string(char *str_time);

	void HexToStr(unsigned char *pbDest, unsigned char *pbSrc, int nLen);

	void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen);

	void StrToHex2(BYTE *pbDest, unsigned char  *pbSrc, int nLen);
	
	int dateComparing(const char* date1, const char* date2);

	int timeCompare(const char* time1, const char* time2);

	bool isStrIllegal2(const char * ch);

	/**
	*   ���ߣ�sonne
	*   ���ڣ�2018-03
	*   ��ע����ȡguid
	*/
	int get_guid(std::string& ch_guid);

	std::string UTF_82ASCII(std::string& strUtf8Code);

	std::string ASCII2UTF_8(std::string& strAsciiCode);

	/**
	* @brief 	Crc Value Compute,Poly is Given As Defined
	* @param
	* @return
	* @note
	*/
	WORD CrcCompute(BYTE *src, int len);

	void writeDataHex(unsigned char * my_array, int length, char *string);

	int read_bit(DWORD c, int pos);

	void HexToStr2(unsigned char *pbDest, BYTE *pbSrc, int nLen);
}
