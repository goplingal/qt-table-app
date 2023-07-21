#include "Vag.h"

Vag::Vag(int a, int b, QString c, QString d, QString e)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
}

Vag& Vag::operator = (const Vag & v)
{
    a = v.a;
    b = v.b;
    c = v.c;
    d = v.d;
    e = v.e;
    return *this;
}

Vag::~Vag()
{

}
