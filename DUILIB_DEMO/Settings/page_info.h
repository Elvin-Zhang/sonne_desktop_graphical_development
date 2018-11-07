#pragma once  

#include <windows.h>

/**
 *    ���ߣ�sonne
 *    ���ڣ�2017.07-27
 *    ��ע����ҳ��Ϣ��
 */
class c_page_info {

private:
	/**ÿҳ��ʾ����*/
	int every_page;
	
	/**�ܼ�¼��*/
	long total_count;
	
	/**��ҳ��*/
	long total_page;
	
	/**��ǰҳ*/
	int current_page;
	
	/**��ʼ��*/
	int begin_index;
	
	/**�Ƿ�����һҳ*/
	bool has_pre_page;
	
	/**�Ƿ�����һҳ*/
	bool has_next_page;

public:
	c_page_info(int every_page, long total, long total_page, int current_page,
			int begin_index, bool has_pre_page, bool has_next_page);

	c_page_info(int current_page, int every_page);

	c_page_info();

	int get_every_page();

	void set_every_page(int every_page);

	long get_total_count();

	void set_total_count(long total_count);

	long get_total_page();

	void set_total_page(long total_page);

	int get_current_page();

	void set_current_page(int current_page);

    int get_begin_index();

	void set_begin_index(int begin_index);

	bool is_has_pre_page();

	void set_has_pre_page(bool has_pre_page);

	bool is_has_next_page();

	void set_has_next_page(bool has_next_page);

};