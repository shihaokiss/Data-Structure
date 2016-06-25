#include"Configer.h"
namespace HashBucket
{
	//哈希桶，一个链表（有待优化-->红黑树）
	template<class K,class V>
	struct Node
	{
		Node(){};
		Node(const K& key, const V& value)
			:_key(key), _value(value), _next(NULL)
		{}
		K _key;
		V _value;
		Node<K, V>* _next;
	};

	template<class K,class V,class HashFun = HashFuner<K>>
	class Hash
	{
		typedef Node<K, V> Node;
	public:
		Hash(size_t size)
		{
			int index = _GetIndexFun(size);
			_Vector.resize(_PrimeList[index]);
			_size = 0;
		}

		bool _Insert(const K& key, const V& value);
		bool _Delete(const Node& data);
		Node* _Find(const K& key);
		void _Show();

	private:
		vector<Node*> _Vector;
		size_t _size;

		size_t _GetIndexFun(const size_t capacity)
		{
			for (int i = 0; i < _PrimeSize; ++i)
			if (_PrimeList[i] > capacity)
				return i;
		}
	};

	template<class K,class V,class HashFun>
	bool Hash<K, V, HashFun>::_Insert(const K& key, const V& value)
	{
		if (_size == _Vector.size())   //负荷因子为 1 ，需要扩容了
		{
			for (int i = 0; i < _Vector.size(); ++i)
			{
				Node* cur = _Vector[i];
				while (cur)
				{
					_Insert(cur->_key,cur->_value);
					cur = cur->_next;
				}
			}
		}
		else
		{
			Node* tmp = new Node(key, value);
			int index = HashFun()(key) % _Vector.size();
			tmp->_next = _Vector[index];
			_Vector[index] = tmp;
			return true;
		}
	}

	template<class K, class V, class HashFun>
	bool Hash<K, V, HashFun>::_Delete(const Node& data)
	{
		int index = HashFun()(data._key) % _Vector.size();
		if (_Vector[index])
		{
			Node* cur = _Vector[index];
			Node* prev = _Vector[index];
			while (cur)
			{
				if (cur->_value == data._value)
				{
					if (cur == _Vector[index])
						_Vector[index] = cur->_next;
					else
						prev->_next = cur->_next;
					delete cur;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
		}
		return false;
	}

	template<class K, class V, class HashFun>
	Node<K,V>* Hash<K, V, HashFun>::_Find(const K& key)
	{
		int index = HashFun()(key) % _Vector.size();
		if (_Vector[index])
		{
			Node* cur = _Vector[index];
			while (cur)
			{
				if (cur->_value == value)
					return cur;
				else
					cur = cur->_next;
			}
		}
		return NULL;
	}

	template<class K, class V, class HashFun>
	void Hash<K, V, HashFun>::_Show()
	{
		for (int i = 0; i < _Vector.size(); ++i)
		{
			if (_Vector[i])
			{
				cout << "[" << i << "] : ";
				Node* cur = _Vector[i];
				while (cur)
				{
					cout << cur->_value << " -> ";
					cur = cur->_next;
				}

				cout << endl;
			}
			else
				cout << "[" << i << "] : NULL" << endl;
		}
	}

	void Test()
	{
		Hash<int, string> HASHTABLE(10);
		
		HASHTABLE._Insert(0,"aa");
		HASHTABLE._Insert(0, "bb");
		HASHTABLE._Insert(0, "cc");
		HASHTABLE._Insert(0, "dd");
		HASHTABLE._Insert(0, "ee");
		HASHTABLE._Insert(2, "ff");
		HASHTABLE._Insert(20, "gg");
		HASHTABLE._Insert(200, "hh");

		Node<int,string> data1(0, "aa");
		Node<int, string> data2(200, "hh");
		HASHTABLE._Show();
		HASHTABLE._Delete(data1);
		HASHTABLE._Delete(data2);
		cout << endl;
		HASHTABLE._Show();
	}
}