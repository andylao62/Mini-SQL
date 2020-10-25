#ifndef _API_H
#define _API_H
/*
API ģ��������ϵͳ�ĺ��ģ�����Ҫ����Ϊ�ṩִ�� SQL ���Ľӿڣ��� Interpreter ����á�
�ýӿ��� Interpreter ������� �ɵ������ڲ���ʾΪ���룬���� Catalog Manager �ṩ����Ϣȷ��ִ�й���
������ Record Manager��Index Manager �� Catalog Manager �ṩ����Ӧ�ӿڽ���ִ�У��󷵻�ִ�н���� Interpreter ģ��
*/
#include "h/CatalogManager.h"
#include "h/IndexManage.h"
#include "h/RecordManage.h"
#include <vector>
using namespace std;


class API {
public:
	API() {};
	sqlresponse Createtable(string tablename, vector<attribute> attr);
	sqlresponse Createindex(string tablename, string indexname,string attr);
	
	sqlresponse Droptable(string tablename);
	sqlresponse Dropindex(string indexname);

	sqlresponse Select(requirement require,int print);
	sqlresponse Insert(string tablename, vector<element> data);
	sqlresponse Delete(requirement require);

	
	void printout(table mytable, vector<vector<element>> rows);

	RecordManage rm;
	CatalogManager cm;
	IndexManager im;
};

#endif