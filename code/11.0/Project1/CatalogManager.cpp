#include <iostream>
#include "h/CatalogManager.h"
#include "h/IndexManage.h"
#include "h/BufferManage.h"
#include "h/Exception.h"


/*
Catalog Manager ����������ݿ������ģʽ��Ϣ��������
1. ���ݿ������б�Ķ�����Ϣ������������ơ������ֶΣ��У����������������ڸñ��ϵ�������
2. ����ÿ���ֶεĶ�����Ϣ�������ֶ����͡��Ƿ�Ψһ�ȡ�
3. ���ݿ������������Ķ��壬���������������������Ǹ��ֶ��ϵȡ� Catalog Manager �������ṩ���ʼ�����������Ϣ�Ľӿڣ�
�� Interpreter �� API ģ��ʹ�á�
*/
using namespace std;


table CatalogManager::Createtable(const string &table_name, const vector<attribute> &attrs) {
	
	if (!Hastable(table_name)) {
		table mytable(table_name, attrs);
		mytable.writeout();
		return mytable;
	}
	
	else {
		throw table_exist(table_name);
	}
}

bool  CatalogManager::Hastable(const string &table_name) {
	ifstream file((table_name + ".cmtable").c_str());
	if (!file)return false;
	else return true;
}

table CatalogManager::Gettable(const string &table_name) {
	if (Hastable(table_name)) {
		table mytable;
		mytable.getin(table_name);
		return mytable;
	}
	else {
		throw table_not_exist(table_name);
	}
}

//drop the file
//drop the index
void  CatalogManager::Droptable(const string &table_name) {
	if (CatalogManager::Hastable(table_name)) {
		table mytable = Gettable(table_name);

		for (int i = 0; i < mytable.attr.size(); i++) {
			if(mytable.attr[i].HasIndex)
				Dropindex(mytable.attr[i].Index);
		}

		remove((table_name + ".cmtable").c_str());
	}
	else {
		throw table_not_exist(table_name);
	}
}

/*
Catalog Manager ����������ݿ������ģʽ��Ϣ��
������
1. ���ݿ������б�Ķ�����Ϣ��
����������ơ������ֶΣ��У����������������ڸñ��ϵ������� 

2. ����ÿ���ֶεĶ�����Ϣ�������ֶ����͡��Ƿ�Ψһ�ȡ� 

3. ���ݿ������������Ķ��壬���������������������Ǹ��ֶ��ϵȡ� 
Catalog Manager �������ṩ���ʼ�����������Ϣ�Ľӿڣ�
�� Interpreter �� API ģ��ʹ��
*/

attribute CatalogManager::Getattribute(string tablename, string attrname) {
	table mytable = CatalogManager::Gettable(tablename);
	for (int i = 0; i < mytable.attr.size(); i++) {
		if (mytable.attr[i].name == attrname) {
			attribute attr = mytable.attr[i];
			return attr;
		}
	}
}

bool CatalogManager::Hasattribute(string tablename, string attrname) {
	table mytable = CatalogManager::Gettable(tablename);
	for (int i = 0; i < mytable.attr.size(); i++) {
		if (mytable.attr[i].name == attrname)return true;
	}
	return false;
}


bool CatalogManager::Hasindex(const string &index_name) {
	ifstream file((index_name + ".cmindex").c_str());
	if (!file)return false;
	else return true;
}


bool CatalogManager::Createindex(const string &table_name, const string &index_name, const string &attrname) {
	if (!CatalogManager::Hastable(table_name)) throw table_not_exist(table_name);

	if (CatalogManager::Hasindex(index_name))throw index_exist(index_name);

	table mytable = Gettable(table_name);

	for (int i = 0; i < mytable.AttrCount; i++) {
		if (mytable.attr[i].name == attrname) {
			if (mytable.attr[i].IsUnique == true || mytable.attr[i].Isprimary) {
				if (mytable.attr[i].HasIndex == 0) {
					mytable.attr[i].HasIndex = 1;
					mytable.attr[i].Index = index_name;

					mytable.writeout();
				}
				else throw index_exist(index_name);
			}
			else throw not_unique(attrname);
		}
	}

	cmIndex myindex(table_name,index_name,attrname);
	myindex.writeout();
	return true;
}


bool  CatalogManager::Dropindex(const string &index_name) {
	if (Hasindex(index_name)) {
		cmIndex myindex = Getindex(index_name);
		string tablename = myindex.tablename;
		string indexname = myindex.attrname;
		table mytable = Gettable(tablename);
		
		for (int i = 0; i < mytable.attr.size(); i++) {
			if (mytable.attr[i].name == indexname) {
				mytable.attr[i].HasIndex = 0;
				mytable.attr[i].Index = "";
				break;
			}
		}

		mytable.writeout();

		remove((index_name + ".cmindex").c_str());
		return true;
	}
	else throw index_not_exist(index_name);
}


cmIndex CatalogManager::Getindex(const string &index_name) {
	if (Hasindex(index_name)) {
		cmIndex myindex;
		myindex.getin(index_name);
		return myindex;
	}
	else throw index_not_exist(index_name);
}