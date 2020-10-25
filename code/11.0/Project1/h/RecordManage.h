#pragma once
#include"BufferManage.h"
#include"Global.h"
#include<sstream>
#define EMPTY '\0'

typedef pair<int, int> tag;

class RecordManage {
public:
	BufferManage bm;

	void CreateTable(table &t);
	/*����һ����ϢΪRecordTable�ı��ļ�*/

	void DropTable(table &t);
	/*ɾ����ϢΪRecordTable�ı��ļ�*/

	tag InsertRecord(table &t, vector<element>colomns);
	/*���ؼ�¼���ڵ�bufferIndex��dataPosition��
	������ڴ��ж�λ��¼*/

	Data select(table &t);
	/*���������Ĳ��ң��Ա��ļ����б�����
	����ÿ����¼������ѡ���������飬
	���س���Ӧ������ֵ��*/

	vector<element>select(table &t, tag T);
	/*����tag�ҵ���¼������*/

	void Delete(table &t, tag T);
	/*����tag�ҵ���¼����ɾ��*/

	void Delete(table &t);
	/*ɾ��������ļ�¼*/

	vector<tag> FindAllTag(table &t);

private:
	string transtostring(table &t, vector<element>colomns);
	/*��vector<element>ת��Ϊ�ַ���������뻺����*/

	vector <element> transtoelement(table &t, string str);
	/*�ӻ����л�ȡ�ַ���Ȼ��ת��Ϊvector<element>��api*/

	int mallocBlockInTableFile(table &t);
	/*�������ļ����ٻ���*/
};