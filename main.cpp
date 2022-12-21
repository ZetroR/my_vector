#include <iostream>
#include <vector>


class vector
{
    int sz;
    double* elem;
public:
    explicit vector(int s);
    vector(std::initializer_list<double> lst);
    vector(const vector& vect);
    vector(vector&& vect);
    vector& operator=(const vector& vect);
    vector& operator=(vector&& vect);

    ~vector() {delete[] elem;}

    int size() const {return sz;}
    double get(int n) const {return elem[n];}
    void set(int n, double v) {elem[n]=v;}

};
vector::vector(int s)
:sz{s}, elem{new double[s]}
{
    for(int i=0; i<s; ++i)
    { elem[i]=0; }
}
vector::vector(std::initializer_list<double> lst)
:sz(lst.size()), elem{new double[sz]}
{
    std::copy(lst.begin(), lst.end(), elem);
}
vector::vector(const vector& vect)
:sz{vect.sz}, elem{new double[vect.sz]}
{
    std::copy(&vect.elem[0], &vect.elem[sz-1], elem);
}
vector::vector(vector&& vect)
:sz{vect.sz}, elem{vect.elem}
{
    vect.sz = 0;
    vect.elem = nullptr;
}
vector& vector::operator=(const vector& vect)
{
    double* p = new double[vect.sz];
    std::copy(vect.elem, vect.elem+vect.sz,p);
    delete[] elem;
    elem = p;
    sz = vect.sz;
    return *this;
}
vector& vector::operator=(vector&& vect)
{
    delete[] elem;
    elem = vect.elem;
    sz = vect.sz;
    vect.sz = 0;
    vect.elem = nullptr;
    return *this;
}

int main()
{
    vector v  = {0, 0, 3.5};
    vector v2 = v;

    v.set(1,99);
    v2.set(0,88);
    std::cout << v.get(0) << ' ' << v2.get(1) << '\n';

    vector v3(10);
    v3.set(4, 10);
    v2=v3;
    v3.set(4, 0);
    std::cout << v2.get(4);
}
