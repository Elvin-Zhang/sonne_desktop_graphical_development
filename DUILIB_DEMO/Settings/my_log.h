#pragma once

#include<time.h>
#include "str_utils.h"
#include "sqlite_utils.h"

/**
 *     sonne
 *     2017-07-21
 *     д��־
 */
namespace MYLOG {

	using namespace std;

	/**
	 *     sonne
	 *     2017-07-21
	 *     д��־���������ݡ�����Ա�����ͣ�
	 *     ��־���ݣ�����Ա�����ݡ�ʱ�䡢��־���ͣ�
	 */
	void write_log(char *ch_content, int type, char *manager_name) ;
}