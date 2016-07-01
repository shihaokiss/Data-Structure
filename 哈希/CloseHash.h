#include"Configer.h"

/*线性探测*/
namespace LineExplore
{

/*状态*/
enum Status
{
	EMPTY,
	EXIT,
	DELETE
};

/*哈希表中的节点结构*/
template<class K,class V>
struct HashTableNode
{
	HashTableNode(){}
	HashTableNode(const K& key, const V& value)
	:_key(key), _value(value)
	{}
	HashTableNode& operator = (const HashTableNode& data)
	{
		_key = data._key;
		_value = data._value;
		return *this;
	}
	K _key;
	V _value;
};

/*哈希表*/
template<class K,class V,template<class> class HashFun>
class Hash
{
public:
	typedef HashTableNode<K,V> Node;
	/*构造函数*/
	Hash(size_t capacity)
	{
		int index = _GetIndexFun(capacity);
		HashTable = new Node[_PrimeList[index]];
		StatusTable = new Status[_PrimeList[index]];
		for (size_t i = 0; i < _PrimeList[index]; ++i)
			StatusTable[i] = EMPTY;
		_size = 0;
		_capacity = _PrimeList[index];
	} 

	/*基本的操作*/
	size_t size(){return _size;}
	bool _Insert(const Node& data);
	bool _Delete(const K& key);
	int _Find(const K& key);
	bool _Alter(const K& key,const V& value);
	void _Show();

protected:
	Node* HashTable;
	Status* StatusTable;
	size_t _capacity;
	size_t _size;

	size_t _GetIndexFun(const size_t capacity)
	{
		for (int i = 0; i < _PrimeSize; ++i)
			if (_PrimeList[i] > capacity)
				return i;
	}
};

template<class K, class V, template<class> class HashFun>
bool Hash<K, V, HashFun>::_Insert(const Node& data)
{
	if (_size * 10 / _capacity > 8)
	{
		int index = _GetIndexFun(_capacity);
		Hash<K, V, HashFun> NewHash(_PrimeList[index]);
		for (size_t i = 0; i < _capacity; ++i)
		{
			if (StatusTable[i] == EXIT)
			NewHash._Insert(HashTable[i]);
		}
		swap(NewHash.HashTable, HashTable);
		swap(NewHash.StatusTable, StatusTable);
		swap(NewHash._capacity, _capacity);
	}
	else
	{
		int index = HashFun<K>()(data._key) % _capacity;
		while (StatusTable[index])
			index == _capacity ? (index = 0) : ++index;
			

		StatusTable[index] = EXIT;
		HashTable[index] = data;
		_size++;
		return true;
	}
}

template<class  K,class V,template<class> class HashFun>
int Hash<K, V, HashFun>::_Find(const K& key)
{
	int index = HashFun<K>()(key) % _capacity;
	while (StatusTable[index])
	{
		if ((StatusTable[index] != DELETE) && (HashTable[index]._key == key))
			return index;
		index == _capacity ? index = 0 : index++;
	}
	return -1;
}

template<class K, class V, template<class> class HashFun>
bool Hash<K, V, HashFun>::_Delete(const K& key)
{
	int index = _Find(key);
	return index >= 0 ? (StatusTable[index] = DELETE, --_size, true) : false;
}

template<class K,class V,template<class> class HashFun>
bool Hash<K, V, HashFun>::_Alter(const K& key,const V& value)
{
	int index = _Find(key);
	if (index >= 0)
	{
		HashTable[index]._value = value;
		return true;
	}
	return false;
}

template<class K,class V,template<class> class HashFun>
void Hash<K, V, HashFun>::_Show()
{
	for (int i = 0; i < _capacity; ++i)
	if (StatusTable[i] == EXIT)
		cout << "[" << HashTable[i]._key << "] : " << HashTable[i]._value << endl;
	else
		cout << "[" << "未定义" << "] : " << "" << endl;
}


void Test()
{
	Hash<int, string, HashFuner> HASHTABLE(10);
	HashTableNode<int, string> Node[10] = { { 0, "aa" }, { 0, "bb" },
	{ 0, "cc" }, { 0, "dd" },
	{ 0, "ee" }, { 0, "ff" } };
	for (int i = 0; i < 6; ++i)
	{
		HASHTABLE._Insert(Node[i]);
	}
	HASHTABLE._Show();
	HASHTABLE._Delete(0);
	HASHTABLE._Delete(0);
	cout << endl;
	HASHTABLE._Show();
}



}


/*二次探测*/
namespace TwiceExplore
{

	/*状态*/
	enum Status
	{
		EMPTY,
		EXIT,
		DELETE
	};

	/*哈希表中的节点结构*/
	template<class K, class V>
	struct HashTableNode
	{
		HashTableNode(){}
		HashTableNode(const K& key, const V& value)
			:_key(key), _value(value)
		{}
		HashTableNode& operator = (const HashTableNode& data)
		{
			_key = data._key;
			_value = data._value;
			return *this;
		}
		K _key;
		V _value;
	};

	/*哈希表*/
	template<class K, class V, template<class> class HashFun>
	class Hash
	{
	public:
		typedef HashTableNode<K, V> Node;
		/*构造函数*/
		Hash(size_t capacity)
		{
			int index = _GetIndexFun(capacity);
			HashTable = new Node[_PrimeList[index]];
			StatusTable = new Status[_PrimeList[index]];
			for (size_t i = 0; i < _PrimeList[index]; ++i)
				StatusTable[i] = EMPTY;
			_size = 0;
			_capacity = _PrimeList[index];
		}

		/*基本的操作*/
		size_t size(){ return _size; }
		bool _Insert(const Node& data);
		bool _Delete(const K& key);
		int _Find(const K& key);
		bool _Alter(const K& key, const V& value);
		void _Show();

	protected:
		Node* HashTable;
		Status* StatusTable;
		size_t _capacity;
		size_t _size;

		size_t _GetIndexFun(const size_t capacity)
		{
			for (int i = 0; i < _PrimeSize; ++i)
			if (_PrimeList[i] > capacity)
				return i;
		}
	};

	template<class K, class V, template<class> class HashFun>
	bool Hash<K, V, HashFun>::_Insert(const Node& data)
	{
		if (_size * 10 / _capacity > 8)
		{
			int index = _GetIndexFun(_capacity);
			Hash<K, V, HashFun> NewHash(_PrimeList[index]);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (StatusTable[i] == EXIT)
					NewHash._Insert(HashTable[i]);
			}
			swap(NewHash.HashTable, HashTable);
			swap(NewHash.StatusTable, StatusTable);
			swap(NewHash._capacity, _capacity);
		}
		else
		{
			int index = HashFun<K>()(data._key) % _capacity;
			for (int i = 1; StatusTable[index] != EMPTY; ++i)
			{
				index += 2 * i - 1;
				index %= _capacity;
			}
				
			StatusTable[index] = EXIT;
			HashTable[index] = data;
			_size++;
			return true;
		}
	}

	template<class  K, class V, template<class> class HashFun>
	int Hash<K, V, HashFun>::_Find(const K& key)
	{
		int index = HashFun<K>()(key) % _capacity;	
		for (int i = 1; StatusTable[index] != EMPTY; ++i)
		{
			if ((StatusTable[index] != DELETE) && (HashTable[index]._key == key))
			return index;
			index += 2 * i - 1;
			index %= _capacity;
		}
		return -1;
	}

	template<class K, class V, template<class> class HashFun>
	bool Hash<K, V, HashFun>::_Delete(const K& key)
	{
		int index = _Find(key);
		return index >= 0 ? (StatusTable[index] = DELETE, --_size, true) : false;
	}

	template<class K, class V, template<class> class HashFun>
	bool Hash<K, V, HashFun>::_Alter(const K& key, const V& value)
	{
		int index = _Find(key);
		if (index >= 0)
		{
			HashTable[index]._value = value;
			return true;
		}
		return false;
	}

	template<class K, class V, template<class> class HashFun>
	void Hash<K, V, HashFun>::_Show()
	{
		for (int i = 0; i < _capacity; ++i)
		if (StatusTable[i] == EXIT)
			cout << "[" << HashTable[i]._key << "] : " << HashTable[i]._value << endl;
		else
			cout << "[" << "未定义" << "] : " << "" << endl;
	}
}