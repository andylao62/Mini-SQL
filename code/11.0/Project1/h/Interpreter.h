#ifndef _Interpreter_H
#define _Interpreter_H

/*
Interpreter ģ��ֱ�����û���������Ҫʵ�����¹��ܣ� 
1. �������̿��ƣ�������������ʼ�� ->������������������ʾ��������ѭ�� -> �˳������̡� 
2. ���ղ������û�������������������ڲ����ݽṹ��ʾ��ͬʱ���������﷨��ȷ�ԺͲ���������ȷ�ԣ�
����ȷ ��������� API ���ṩ�ĺ���ִ�в���ʾִ�н�����Բ���ȷ��������ʾ������Ϣ�� 
*/

#include <string>
#include "h/API.h"
#include "h/Exception.h"
using namespace std;

class Interpreter {
public:
	Interpreter();
	void getcmd();
	/*
	1. split it into several query if ';' exists;
	2. check syntax error: whether it ends with ';'
		error type: 
	3. analyse each query, delete the white space.
	*/

	void normalize();
	/* 
	in this function , we need to make the input query easy to split
	*/

	int process();
	/*
	1. analyse which type the query belongs to
		if not exists throw "command not exists"
	2. go into each function to process this query
	*/

	void sql_insert(stringstream &ss);
	/*
	format: insert into ���� values(v1,v2...);
	check: table exists? attribute match? 
	*/

	void sql_delete(stringstream &ss);
	/*
	format: delete from ���� where ������
	check: table exists? attribute match? 
	*/

	void sql_exit();
	/*
	exit
	*/

	void sql_execfile(string file_path);
	/*
	exec the file
	*/

	void sql_select(stringstream &ss);
	/*
	format: select ���� from ���� where ������
	check: table exists? attribute match?
	*/

	void create_table(stringstream &ss);
	/*
	create table ���� 
(  
	���� ����() ,  
	���� ����() ,    
	���� ����() ,  
	primary key ( ���� )
	); 
	*/

	void drop_table(stringstream &ss);
	/*
	drop table ������
	*/

	void create_index(stringstream &ss);
	/*
	create index ������ on ���� ( ���� ); 
	check: table exist? attribute exist? have index or not?
	*/

	void drop_index(stringstream &ss);
	/*
	drop index ���� on ������
	check: attribute exist? table exist? index exist?
	*/

	element changeformat(string tablename, string target,int count);

private:
	string query;
	API api;
};

#endif