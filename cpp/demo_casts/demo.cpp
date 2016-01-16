#include <iostream>

// Demo File for handling different type casts
/*
 *  const_cast ---- to cast away const-ness of a variable
 *  static_cast ---- c type casting of a pointer to a data type TO another pointer to a data type, here both share same class heirarchy and are related
 *  dynamic_cast --- runtime type checking based cast to downcast from base to derived when derived may not be lnown at compile time
 *  reinterpret_cast --- casting into unrelated type
 *
 *
 * */

using namespace std;

class Base {
public:
    // Dynamic casts require polymorphic classes. Atleast one virtual function.
    virtual void show() {
        cout << __FUNCTION__ <<":"<<__LINE__<<endl;
    };
};

class Derived:public Base
{
public:
    void show() {
        cout << __FUNCTION__ <<":"<<__LINE__<<endl;
    };
};

class Other {
public:
    void show() {
        cout << __FUNCTION__ <<":"<<__LINE__<<endl;
    }
};


int main() {
    Base *B = new Base;
    Derived *D = new Derived;
    Other *O = new Other;

    Base *Bd = D; // can be static casted too

    Bd->show();

    // static cast
    Bd = static_cast<Base*>(D);
    // This will still call the method from the derived class because this method is virtual.
    Bd->show();

    // Downcasting from Base to Derived, applicable only for polymorphic base classes.
    D = dynamic_cast<Derived*>(Bd);
    // we should add null checks on the pointer now.
    cout << "Dynamic cast returns " << D<<endl;
    if(D) {
        D->show();
    }

    // Type casting into an unrelated type.
    O  = reinterpret_cast<Other*>(D);
    O->show();


    return 0;
}
