#include <iostream>

using namespace std;

ostream& operator<<(ostream& o, string& s)
{
	o << s.c_str();
	return o;
}

istream& operator>>(istream& i, string& s)
{
	char buf[256];
	i >> buf;
	string tmp(buf);
	s = tmp;

	return i;
}


template<typename T>
class AbstractList
{
protected:
	T _default;
public:
	virtual void sort(bool(*f) (T* first, T* second)) = 0;
	virtual T get(int index) = 0;
	virtual void set(int index, T data) = 0;
	virtual void insert(int index, T data) = 0;
	virtual T remove(int index) = 0;
	virtual int len() = 0;
	void push(T data)
	{
		insert(0, data);
	}
	virtual T pop()
	{
		if (empty())
			return _default;
		else
			return remove(0);
	}
	virtual bool empty()
	{
		return len() == 0;
	}
	virtual ostream& print(ostream& o)
	{
		for (int i = 0; i < len(); i++)
		{
			o << get(i) << endl;
		}
		return o;
	}
	virtual istream& read(istream& in)
	{
		int i;
		in >> i;
		for (int i = 0; i < i; i++)
		{
			T tmp;
			in >> tmp;
			insert(len(), tmp);
		}
		return in;
	}
};

template <typename T>
class NewList : public AbstractList<T>
{
	int count;
	T _data;
	NewList* next;
public:
	NewList(NewList* Next)
	{
		this->count = 0;
		this->next = Next;
	}
	NewList(T Default)
	{
		this->count = 0;
		this->_default = Default;
		this->next = new NewList(NULL);
	}
	NewList()
	{
		this->count = 0;
		this->next = new NewList(NULL);
	}
	NewList(T Data, T Default, NewList* Next)
	{
		this->count = 0;
		this->_default = Default;
		this->_data = Data;
		this->next = Next;
	}
	NewList(const NewList& a)
	{
		this->count = a.count + 1;
		this->_data = a._data;
		this->_default = a._default;
		this->next = a.next;
	}
	NewList& operator = (NewList& a)
	{
		NewList* tmp = new NewList;
		tmp->_default = a._default;
		tmp->_data = a._data;
		tmp->next = a.next;
		tmp->count = a.count + 1;
		return *tmp;
	}
	virtual ~NewList()
	{
		if (this->count != 0)
		{
			next = NULL;
		}
	}
	virtual int len()
	{
		int i = 0;
		NewList* tmp;
		tmp = this;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		return i - 1;
	}
	virtual T get(int index)
	{
		//if (index >= len() || index < 0)
		//	return _default;
		int i = 0;
		NewList* tmp;
		tmp = this;
		while (i < index)
		{
			tmp = tmp->next;
			i++;
		}
		return tmp->_data;
	}
	virtual void set(int index, T data)
	{
		if (next->next == NULL || index < 0 || index >= len())
			return;
		int i = 0;
		NewList* tmp;
		tmp = this;
		while (i < index)
		{
			tmp = tmp->next;
			i++;
		}
		tmp->_data = data;
	}
	virtual void insert(int index, T data)
	{
		if (next == NULL || index < 0)
			return;
		NewList* tmp1 = this;
		int i = 0;
		while (i < index && tmp1->next != NULL)
		{
			tmp1 = tmp1->next;
			i++;
		}

		NewList* tmp = new NewList;
		tmp->_data = data;
		if (tmp1->next != NULL)
		{
			tmp->next = tmp1->next;
		}
		else
		{
			tmp->next = NULL;
		}
		tmp1->next = tmp;
	}

	virtual T remove(int index)
	{
		int i = 0;
		NewList* tmp = this;
		while (i < index)
		{
			tmp = tmp->next;
			i++;
		}
		NewList* tmp1 = tmp->next;
		tmp->next = tmp1->next;
		T _data1 = tmp1->_data;
		delete tmp1;
		return _data1;
	}
	virtual void sort(bool(*f) (T* first, T* second))
	{
		NewList* tmp = this;
		NewList* tmp1 = this;
		NewList* _next = this;
		NewList* prev = this;
		for (int i = 0; i < len(); i++)
			for (int k = 0; k < len() - 1; k++)
			{
			if (f(&(tmp->_data), &(tmp->next->_data)))
			{
				tmp1 = tmp->next;
				_next = tmp1->next;
				prev->next = tmp1;
				tmp1->next = tmp;
				tmp->next = _next;
			}
			prev = tmp;
			tmp = tmp->next;
			}
	}
};

template <typename T>
bool gr(T* first, T* second)
{
	if (*first > *second)
		return true;
	return false;
}

NewList<string>* get_init()
{
	NewList<string>* init = new NewList<string>("EMPTY!");
	return init;
}
