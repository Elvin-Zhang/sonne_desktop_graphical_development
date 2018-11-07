
#include "page_utils.h"


	/**
	 * ����everyPage��total��currentPage������ҳ��Ϣ����
	 */
    c_page_info c_page_utils::create_page(int every_page,long total,int current_page) {
        every_page = get_every_page(every_page);
        current_page = get_current_page(current_page);
        long total_page = get_total_page(every_page, total);
        int begin_index = get_begin_index(every_page, current_page);
        bool has_pre_page = get_has_pre_page(current_page);
        bool has_next_page = get_has_next_page(total_page, current_page);
        return c_page_info(every_page, total, total_page, current_page,
                begin_index, has_pre_page,  has_next_page);
	}


	/**
	 * ��ҳ
	 */
	void c_page_utils::get_next_page(c_page_info *page_info) {
		if ((*page_info).is_has_next_page()) 
			c_page_utils::set_page_info(page_info, (*page_info).get_every_page(), (*page_info).get_total_count(), (*page_info).get_current_page()+1);
	}


	/**
	 * ��һҳ
	 */
	void c_page_utils::get_pre_page(c_page_info *page_info) {
		if ((*page_info).is_has_pre_page()) 
			c_page_utils::set_page_info(page_info, (*page_info).get_every_page(), (*page_info).get_total_count(), (*page_info).get_current_page()-1);
	}


	/**
	 * ��һҳ
	 */
	void c_page_utils::get_first_page(c_page_info *page_info) {
		c_page_utils::set_page_info(page_info, (*page_info).get_every_page(), (*page_info).get_total_count(), 1);
	}


	/**
	 * ���һҳ
	 */
	void c_page_utils::get_last_page(c_page_info *page_info) {
		c_page_utils::set_page_info(page_info, (*page_info).get_every_page(), (*page_info).get_total_count(), (*page_info).get_total_page());
	}


	/**
	 * ����everyPage��total��currentPage���������ҳ��Ϣ����
	 */
    void c_page_utils::set_page_info(c_page_info *page_info,int every_page,long total,int current_page) {
        every_page = get_every_page(every_page);
        current_page = get_current_page(current_page);
        long total_page = get_total_page(every_page, total);
        int begin_index = get_begin_index(every_page, current_page);
        bool has_pre_page = get_has_pre_page(current_page);
        bool has_next_page = get_has_next_page(total_page, current_page);
        (*page_info).set_every_page(every_page);
        (*page_info).set_current_page(current_page);
        (*page_info).set_total_page(total_page);
        (*page_info).set_begin_index(begin_index);
        (*page_info).set_has_next_page(has_next_page);
        (*page_info).set_has_pre_page(has_pre_page);
        (*page_info).set_total_count(total);
	}
    

    /**
     * ���ÿҳ��ʾ��¼��
     */
    int c_page_utils::get_every_page(int every_page){
		if (every_page == 0)
			return 12;
		return every_page;
	}
    

    /**
     * ��õ�ǰҳ
     */
    int c_page_utils::get_current_page(int current_page) {
		if (current_page == 0)
			return 1;
		return current_page;
	}

    
    /**
     * �����ҳ��
     */
    long c_page_utils::get_total_page(int every_page,long total) {
        long total_page = 0;
        if(total != 0 &&total % every_page == 0)
            total_page = total / every_page;
        else 
            total_page = total / every_page + 1;
        return total_page;
	}
    

    /**
     * �����ʼλ��
     */
    int c_page_utils::get_begin_index(int every_page,int current_page) {
		return (current_page - 1) * every_page;
	}

    
    /**
     * ����Ƿ�����һҳ
     */
    bool c_page_utils::get_has_pre_page(int current_page) {
		if (current_page == 1)
			return false;
		return true;
	}


    /**
     * ����Ƿ�����һҳ
     */
    bool c_page_utils::get_has_next_page(long total_page, int current_page) {
		if (current_page == total_page || total_page == 0)
			return false;
		return true;
	}