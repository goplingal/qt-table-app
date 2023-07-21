#ifndef VAG_H
#define VAG_H
#include <QString>
#include <iostream>

class Vag
{
public:
    int a;
    int b;
    QString c;
    QString d;
    QString e;

    Vag(int a = 0, int b = 0, QString c = "", QString d = "", QString e = "");

    Vag& operator = (const Vag & v);

    ~Vag();
};

template <typename T>

class Cont
{
public:
    T *a;
    int n;
    class Iter;

    Cont(int n1 = 0)
    {
        n = n1;
        a = new T[n];
    }

    void Push_Back(T x)
    {
        T *a1 = new T[n + 1];
        for (int i = 0; i < n; i++)
        {
            a1[i] = a[i];
        }
        a1[n] = x;
        n++;
        a = new T[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = a1[i];
        }
    }

    void Delete()
    {
        if (n == 0)
        {
            return;
        }
        delete[] a;
        n = 0;
    }

    void Del_Num(int h)
    {
        if (h < 0 && h > n)
        {
            std::cerr << "Invalid index" << std::endl;
        }
        else
        {
            T *a1 = new T[n - 1];
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (i != h)
                {
                    a1[j] = a[i];
                    j++;
                }
            }
            n--;
            a = new T [n];
            for (int i = 0; i < n; i++)
            {
                a[i] = a1[i];
            }
        }
    }

    void Change(T a1, int h)
    {
        for (int i = 0; i < n; i++)
        {
            if (i == h)
            {
                a[i] = a1;
            }
        }
    }

    int Cnt()
    {
        return n;
    }

    T &operator[] (int i)
    {
        return a[i];
    }

    Iter Begin()
    {
        return a;
    }

    Iter End()
    {
        return a + n;
    }

    friend std::ostream& operator << (std::ostream &out, const Cont <T>& n);

    class Iter
    {
    public:
        T *elem;

        Iter(T *x)
        {
            elem = x;
        }

        T& operator+ (int i)
        {
            return *(elem + i);
        }

        T& operator- (int i)
        {
            return *(elem - i);
        }

        T& operator++ (int)
        {
            return *elem++;
        }

        T& operator-- (int)
        {
            return *elem--;
        }

        T& operator++ ()
        {
            return *++elem;
        }

        T& operator-- ()
        {
            return *--elem;
        }

        bool operator!= (const Iter& i)
        {
            return elem != i.elem;
        }

        bool operator== (const Iter& i)
        {
            return elem == i.elem;
        }

        T& operator* ()
        {
            return *elem;
        }
    };
};

#endif // VAG_H
