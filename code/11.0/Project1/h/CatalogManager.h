#ifndef _CatalogManager_H
#define _CatalogManager_H
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "h/Global.h"
#include "h/IndexManage.h"
#include "h/BufferManage.h"
/*
Catalog Manager ����������ݿ������ģʽ��Ϣ�������� 
1. ���ݿ������б�Ķ�����Ϣ������������ơ������ֶΣ��У����������������ڸñ��ϵ������� 
2. ����ÿ���ֶεĶ�����Ϣ�������ֶ����͡��Ƿ�Ψһ�ȡ� 
3. ���ݿ������������Ķ��壬���������������������Ǹ��ֶ��ϵȡ� 
	Catalog Manager �������ṩ���ʼ�����������Ϣ�Ľӿڣ�
�� Interpreter �� API ģ��ʹ�á� 
*/
using namespace std;

class cmIndex {
public:
	string tablename;
	string indexname;
	string attrname;

	cmIndex() {};
	cmIndex(string tablename, string indexname, string attrname) {
		this->tablename = tablename;
		this->indexname = indexname;
		this->attrname = attrname;
	}

	void writeout() {
		ofstream output;
		output.open((indexname + ".cmindex").c_str());
		output << tablename << " " <<indexname << " " << attrname << endl;
		output.close();
	}

	void getin(string indexname) {
		ifstream file;
		file.open((indexname + ".cmindex").c_str());
		file >> tablename >> indexname >> attrname;
		file.close();
	}
	/*friend ostream& operator<<(ostream& output, const cmIndex& obj)
	{
		output << obj.tablename << " " << obj.indexname << " " << obj.attrname << endl;
		return output;
	}

	friend istream& operator>>(istream& input, cmIndex& obj)
	{
		input >> obj.tablename >> obj.indexname >> obj.attrname;
		return input;
	}*/
};


class CatalogManager {
public:
	BufferManage buffer;


	table Createtable(const string &table_name, const vector<attribute> &attrs);
	void Droptable(const string &table_name);
	bool Hastable(const string &table_name);
	table Gettable(const string &table_name);
	
	
	bool Createindex(const string &table_name, const string &index_name, const string& attr_index);
	bool Dropindex(const string &index_name);
	bool Hasindex(const string &index_name);
	cmIndex Getindex(const string &index_name);

	bool Hasattribute(string table ,string attrname);
	attribute Getattribute(string table,string attrname);
};

#endif