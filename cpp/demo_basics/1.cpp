#include <iostream>

using namespace std;

class complex {
    double re;
    double im;
public:
    // constructor and copy constructor
    complex(double re=0, double im=0): re(re),im(im) {};
    //complex(const complex &c){ }
    // operators
    // Operators can be defined in two ways
    // 1. Non static member function
    // 2. Non member function with one extra argument
    complex operator=(const complex &c) {
        this->re = c.re;
        this->im = c.im;
        return *this;
    }

    friend complex& operator+(complex a,complex b);
    friend complex& operator*(complex a,complex b);
    friend complex& operator-(complex a,complex b);

    //
    // methods
    void  show() {
        std::cout << re<< " + " << im <<"j";
    }

};

complex& operator+(complex a,complex b) {
    complex *sum = new complex;
    sum->re = a.re + b.re;
    sum->im = a.im + b.im;
    return *sum;
}

complex& operator*(complex a,complex b) {
    complex *product = new complex;
    product->re = (a.re * b.re) - (a.im * b.im);
    product->im = (a.re * b.im) + (a.im * b.re);
    return *product;

};

complex& operator-(complex a,complex b) {
    complex *diff = new complex;
    diff->re = a.re - b.re;
    diff->im = a.im - b.im;
    return *diff;
};

int main() {

    std::cout << "Demo Program with basic Cpp" << endl;
    complex z1(1,2),z2;
    z1.show();
    cout << endl;
    z2.show();
    cout << endl;
    z2 = z1;
    z2.show();
    cout << endl;

    complex summ = z1 + z2;
    summ.show();
    cout << endl;

    summ = z1 * z2;
    summ.show();
    cout << endl;

    return 0;
}
