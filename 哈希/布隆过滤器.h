#pragma once
#include"Configer.h"

namespace Bulong
{
	namespace HashFun
	{
		template<class T>
		size_t BKDRHash(const char *str)
		{
			register size_t hash = 0;
			while (size_t ch = (size_t)*str++)
			{
				hash = hash * 131 + ch;
			}
			return hash;
		}

		template<class T>
		size_t SDBMHash(const char *str)
		{
			register size_t hash = 0;
			while (size_t ch = (size_t)*str++)
			{
				hash = 65599 * hash + ch;
			}
			return hash;
		}

		template<class T>
		size_t RSHash(const char * str)
		{
			size_t hash = 0;
			size_t magic = 63689;
			while (size_t ch = (size_t)*str++)
			{
				hash = hash * magic + ch;
				magic *= 378551;
			}
			return hash;
		}


		template<class T>
		size_t APHash(const char *str)
		{
			register size_t hash = 0;
			size_t ch;
			for (long i = 0; ch = (size_t)*str++; i++)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
				}
			}
			return hash;
		}


		template<class T>
		size_t JSHash(const char* str)
		{
			if (!*str)
			{
				return 0;
			}
			size_t hash = 1315423911;
			while (size_t ch = (size_t)*str++)
			{
				hash ^= ((hash << 5) + ch + (hash >> 2));
			}
			return hash;
		}
	}

	class BitMap
	{
	public:
		BitMap() :_size(0)
		{}
		BitMap(int size)
		{
			_array.resize((size >> 5) + 1);
			_size = 0;
		}
		bool Set(int data)
		{
			int index = data >> 5;
			int position = data % 32;
			if (_array[index] & (1 << position))
				return false;
			else
			{
				_array[index] |= (1 << position);
				++_size;
				return true;
			}

		}
		bool ReSet(int data)
		{
			int index = data >> 5;
			int position = data % 32;
			if (_array[index] & (1 << position))
			{
				_array[index] &= (~(1 << position));
				--_size;
				return true;
			}
			return false;
		}
		bool Check(int data)
		{
			int index = data >> 5;
			int position = data % 32;
			return _array[index] & (1 << position);
		}
		void Clear()
		{
			_array.assign(_array.size(), 0);
		}
	public:
		vector<size_t> _array;
		size_t _size;
	};

	template<class T>
	struct HashFuner1
	{
		size_t operator()(const T& key)
		{
			return HashFun::BKDRHash<T>(key.c_str());
		}
	};
	template<class T>
	struct HashFuner2
	{
		size_t operator()(const T& key)
		{
			return HashFun::SDBMHash<T>(key.c_str());
		}
	};
	template<class T>
	struct HashFuner3
	{
		size_t operator()(const T& key)
		{
			return HashFun::RSHash<T>(key.c_str());
		}
	};
	template<class T>
	struct HashFuner4
	{
		size_t operator()(const T& key)
		{
			return HashFun::APHash<T>(key.c_str());
		}
	};
	template<class T>
	struct HashFuner5
	{
		size_t operator()(const T& key)
		{
			return HashFun::JSHash<T>(key.c_str());
		}
	};

	template<class T,
	class Fun1 = HashFuner1<T>,
	class Fun2 = HashFuner2<T>,
	class Fun3 = HashFuner3<T>, 
	class Fun4 = HashFuner4<T>, 
	class Fun5 = HashFuner5<T> >
	class BuLongFilter
	{
	public:
		BuLongFilter(int size) :_capacity(size)
		{
			_array._array.resize((size >> 5) + 1);
		}
		void Set(const T& key)
		{
			_array.Set(Fun1()(key) % _capacity);
			_array.Set(Fun2()(key) % _capacity);
			_array.Set(Fun3()(key) % _capacity);
			_array.Set(Fun4()(key) % _capacity);
			_array.Set(Fun5()(key) % _capacity);
		}
		bool Check(const T& key)
		{
			if (!_array.Check(Fun1()(key) % _capacity))
				return false;
			if (!_array.Check(Fun2()(key) % _capacity))
				return false;
			if (!_array.Check(Fun3()(key) % _capacity))
				return false;
			if (!_array.Check(Fun4()(key) % _capacity))
				return false;
			if (!_array.Check(Fun5()(key) % _capacity))
				return false;
			return true;
		}
	private:
		BitMap _array;
		size_t _capacity;
	};
}
