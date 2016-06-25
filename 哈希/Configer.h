#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*���*/
//HashTable-ɢ�б�/��ϣ���Ǹ��ݹؼ��֣�key����ֱ�ӷ�����
//�ڴ�洢λ�õ����ݽṹ�� ��ͨ��һ���ؼ�ֵ�ĺ��������������
//ӳ�䵽���е�λ�����������ݣ����ӳ�亯������ɢ�к��������
//��¼���������ɢ�б�


/*****************���ٹ�ϣ��ͻ��������_capacity��*********************/

const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

/*****************���ַ���ת��Ϊ�ܼ��ٹ�ϣ��ͻ�����εĹ�ʽ*********************/

static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

/*���͵�ת�����������͵����ε�ת����*/
template<class T>
struct HashFuner
{
	size_t operator()(const T & data)
	{
		return data;
	}
};

template<>
struct HashFuner<string>
{
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};