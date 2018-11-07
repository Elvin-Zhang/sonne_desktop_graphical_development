#pragma once  

#include <windows.h>

#include "page_info.h"

/**
 *    ���ߣ�sonne
 *    ���ڣ�2017.07-27
 *    ��ע����ҳ������
 */
class c_page_utils  {
private:
public:

	/**
	 * ����everyPage��total��currentPage������ҳ��Ϣ����
	 */
    static c_page_info create_page(int every_page,long total,int current_page);

	/**
	 * ��ҳ
	 */
	static void get_next_page(c_page_info *page_info);

	/**
	 * ��һҳ
	 */
	static void get_pre_page(c_page_info *page_info);


	static void get_first_page(c_page_info *page_info);


	static void get_last_page(c_page_info *page_info);


	/**
	 * ����everyPage��total��currentPage���������ҳ��Ϣ����
	 */
    static void set_page_info(c_page_info *page_info,int every_page,long total,int current_page);
    

    /**
     * ���ÿҳ��ʾ��¼��
     */
    static int get_every_page(int every_page);
    

    /**
     * ��õ�ǰҳ
     */
    static int get_current_page(int current_page);

    
    /**
     * �����ҳ��
     */
    static long get_total_page(int every_page,long total);
    

    /**
     * �����ʼλ��
     */
    static int get_begin_index(int every_page,int current_page);

    
    /**
     * ����Ƿ�����һҳ
     */
    static bool get_has_pre_page(int current_page);


    /**
     * ����Ƿ�����һҳ
     */
    static bool get_has_next_page(long total_page, int current_page);
};