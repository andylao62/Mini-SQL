#ifndef _BufferManage_H
#define _BufferManage_H

#define OneBlockSize 4096 //the size of one Block is 4KB
#define BlockNum 300//the max number of the blocks
#define EMPTY '\0'

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
	���еĻ�����Ϣ���ڴ���
	�����Ϣ���ַ������顢��š�������λ����
*/
class Block
{
public:
	string fileName;/*��ʾfileName�ļ����ڴ��*/
	bool Dirty;/*�Ƿ��޸�*/
	bool isEmpty;/*�Ƿ�Ϊ��*/
	bool Pin;/*�Ƿ���*/
	int  blockIndex;/*��ʾ��Ӧ��fileName�ļ��Ŀ��*/
	int  LRU;/*��ʾδʹ�ô���*/
	char data[OneBlockSize + 1];/*�ڴ��д洢����Ϣ*/

	Block()/*���غ���*/
	{
		initialize();
	}

	void initialize()/*��ʼ��*/
	{
		fileName = "";
		Dirty = false;
		isEmpty = true;
		Pin = false;
		blockIndex = 0;
		LRU = 0;
		for (int i = 0; i < OneBlockSize; i++) data[i] = EMPTY;
		data[OneBlockSize] = '\0';
	}

	string readBlockSeg(int start, int end)/*�õ��ڴ���Ϣstart-endλ�õ��ַ���*/
	{
		string content = "";
		for (int i = start; i < end; i++)
		{
			content += data[i];
		}
		return content;
	}
};

class BufferManage
{
public:
	Block bufferBlock[BlockNum];

	BufferManage();
	~BufferManage();

	void BufferFlush(int bufferIndex);
	/*��buffercache�����һ��д���ļ���*/

	int GetBufferIndex(string fileName, int blockIndex);
	/*�����ļ������ֺͿ�ŵõ��ڴ��е��±꣬���ػ�������bufferIndex*/

	void BufferRead(string fileName, int blockIndex, int bufferIndex);
	/*�Ӵ����ж�ȡ��Ϣ�浽�ڴ���*/

	void RecordBuffer(int bufferIndex);
	/*��¼buffer���ô���������LRU�㷨*/

	int GetEmptyBuffer();
	/*�ҵ����еĻ�������*/

	int checkInBuffer(string fileName, int blockIndex);
	/*���Ҵ����иÿ��Ƿ��Ѿ�д�����ڴ�*/

	void BufferPin(int bufferIndex);
	/*����������ס��ʹ�䲻�ɱ��滻*/

	void deleteFile(string fileName);
	/*ɾ�������ļ�*/

	void writeToFile(int bufferIndex);
	/*���ڴ��еĿ�д���ļ��в�������ڴ�*/
};

#endif 
