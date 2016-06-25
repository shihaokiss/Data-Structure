#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

/*简介*/
//HashTable-散列表/哈希表，是根据关键字（key）而直接访问在
//内存存储位置的数据结构。 它通过一个关键值的函数将所需的数据
//映射到表中的位置来访问数据，这个映射函数叫做散列函数，存放
//记录的数组叫做散列表


/*****************减少哈希冲突的素数表（_capacity）*********************/

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

/*****************将字符串转换为能减少哈希冲突的整形的公式*********************/

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

/*类型的转换（任意类型到整形的转换）*/
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