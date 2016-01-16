#include <iostream>

class node
{
    class node *next;
    int data;

public:
    node(int data=0,node *next=0): data(data),next(next) {}

    int getData()
    {
        return data;
    };

    void setNext(node& N)
    {
        next = &N;
    }
    node & getNext()
    {
        return *next;

    }
};


class list
{

    node *next;
    node *head;
    int  count;

public:

    list():next(0),head(0),count(0) {}

    void push(node &N)
    {
        if(isEmpty()) {
            head = &N;
            next = &N;

        } else {
            next->setNext(N);
            next = &N;

        }

        count++;
    }

    node& pop() {
        if(!isEmpty())
        {
            node *ret;
            ret = head;
            head = &(head->getNext());

            count--;
            return *ret;
        }

    }

    bool isEmpty() {
        if(!count) {
            return 1;
        }
	else return 0;
    }

   void show() {
   
   for(int i=0;i<count;i++)
   {
   
   }
   }


};

int main()
{

    node N(12),M(10),P(1);

    std::cout << N.getData() << std::endl;
    list l;

    l.push(N);
    l.push(M);
    l.push(P);

    node &k = l.pop();

    std::cout << "POP THE ELEMENT:D:" << std::endl;
    std::cout << k.getData() << std::endl;

    k = l.pop();
    std::cout << "POP THE ELEMENT:D:" << std::endl;
    std::cout << k.getData() << std::endl;

    k = l.pop();
    std::cout << "POP THE ELEMENT:D:" << std::endl;
    std::cout << k.getData() << std::endl;

    return 0;
}

