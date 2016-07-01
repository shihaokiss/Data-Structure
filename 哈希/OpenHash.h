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
			int Size = _GetIndexFun(size);
			_Vector.resize(Size);
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
				return _PrimeList[i];
		}
	};

	template<class K,class V,class HashFun>
	bool Hash<K, V, HashFun>::_Insert(const K& key, const V& value)
	{
		if (_size == _Vector.size())   //负荷因子为 1 ，需要扩容了
		{
			int new_size = _GetIndexFun(_Vector.size());
			Hash NewHash(new_size);
			for (int i = 0; i < _Vector.size(); ++i)
			{
				Node* cur = _Vector[i];
				while (cur)
				{
					NewHash._Insert(cur->_key,cur->_value);
					cur = cur->_next;
				}
			}
			swap(_Vector, NewHash._Vector);  //将哈希表重置
		}
		else
		{
			Node* tmp = new Node(key, value);
			int index = HashFun()(key) % _Vector.size();
			tmp->_next = _Vector[index];
			_Vector[index] = tmp;
			_size++;
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
					_size--;
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

}