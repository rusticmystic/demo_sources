#include <iostream>

/* this should emulate pointer */
/* template smart pointer without reference counting */
template <class T>
class SP {
    T * pPointer;

public:
    // constructor
    SP(T *pValue): pPointer(pValue) {

    }

    // destructor
    ~SP () {
        delete pPointer;
    }

    // operators
    T * operator-> () {
        return pPointer;
    }

    T & operator* () {
        return *pPointer;
    }

    SP &operator=(SP &k) {
        pPointer = k.pPointer;
        return *this;
    }
};

/* Class for refcount */
class Ref {
    unsigned int Count;
public:

    Ref(int C=0): Count(C) {

    }

    void AddRef() {
        Count++;
    }

    int ReleaseRef() {
        Count--;
        return Count;
    }

    int Debug() {
        return Count;
    }
};

/* advanced template smart pointer without reference counting */
template <class T>
class ASP {
    T   * pPointer;
    Ref * RefCount;

public:
    // constructor
    ASP(T *pValue): pPointer(pValue),RefCount(0) {
        RefCount = new Ref();
        RefCount->AddRef();
    }

    ASP(): pPointer(0),RefCount(0) {
        RefCount = new Ref();
        RefCount->AddRef();
    }

    // copy contructor
    ASP(const ASP<T> &asp): pPointer(asp.pPointer),RefCount(asp.RefCount) {

        RefCount->AddRef();
    }

    // destructor
    ~ASP () {

        if(RefCount->ReleaseRef()==0) {
            delete pPointer;
            delete RefCount;
        }
    }

    // operators
    T * operator-> () {
        return pPointer;
    }

    T & operator* () {
        return *pPointer;
    }

    void Debug() {
        std::cout << "Value:  RefCount:" << RefCount->Debug() << std::endl;
    }

    ASP &operator=(ASP &k) {

        // Avoid self assignment
        if(this!=&k) {

            // remove previous ref
            if(RefCount->ReleaseRef()==0) {
                delete pPointer;
                delete RefCount;
            }

            pPointer = k.pPointer;
            RefCount = k.RefCount;
            RefCount->AddRef();

        }
        return *this;
    }
};

int main() {

    // int hello;
    std::cout << "Sample Program for Smart Pointers\n"<<std::endl;

    // This will work as a pointer to an int object
    SP  <int>  s(new int(10));
    ASP <int>  a(new int(10));

    {

        ASP <int>   k;
        ASP <int>   n;
        k=a;
        n=k;


        // This will work as a pointer to a string object
        SP<std::string> Name(new std::string("Shivdeep"));

        std::cout << *s << std::endl;
        std::cout << Name->length() << std::endl;

        k.Debug();

    }
    a.Debug();

    return 0;
}
