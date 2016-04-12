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
public :
    virtual void sort(bool (*f) (T* first, T* second)) = 0;
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
        for (int i = 0; i < len(); i ++)
        {
            o << get(i) << endl;
        }
        return o;
    }
 
    virtual istream& read(istream& in)
    {
        int count;
        in >> count;
        for (int i = 0 ; i < count ; i ++)
        {
            T tmp;
            in >> tmp;
            insert(len(), tmp);
        }
        return in;
    }
 
};
 
template<typename T>
class SingleList : public AbstractList<T>
{
    T _data;
    int count;
protected:
    T _default;
public :
 
    SingleList(T def, T data)
    {
        _default = def;
        _data = data;
        count = 0;
    }
    virtual void sort(bool (*f) (T* first, T* second))
    {
        return;
    }
    virtual T get(int index)
    {
        return _data;
    }
    virtual void set(int index, T data)
    {
        _data = data;
        count = 1;
    }
    virtual void insert(int index, T data)
    {
        set(index, data);
        count = 1;
    }
    virtual T remove(int index)
    {
        count = 0;
        return _data;
    }
    virtual int len()
    {
        return count;
    }
};
