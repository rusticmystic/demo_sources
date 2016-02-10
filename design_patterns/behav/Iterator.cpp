/* From sourcemaking.com 
 * 
 * Need to "abstract" the traversal of wildly different data structures so that algorithms can be 
 * defined that are capable of interfacing with each transparently.
 * 
 * On modern television sets, a next and previous button are used. When the viewer selects the "next" button, 
 * the next tuned channel will be displayed. Consider watching television in a hotel room in a strange city. 
 * When surfing through channels, the channel number is not important, but the programming is. 
 * If the programming on one channel is not of interest, the viewer can request the next channel, 
 * without knowing its number
 * 
 * Iterator can traverse a Composite. Visitor can apply an operation over a Composite
 * 
 * 
 * */


#include <iostream>
using namespace std;

class Stack
{
    int items[10];
    int sp;
  public:
    friend class StackIter;
    Stack()
    {
        sp =  - 1;
    }
    void push(int in)
    {
        items[++sp] = in;
    }
    int pop()
    {
        return items[sp--];
    }
    bool isEmpty()
    {
        return (sp ==  - 1);
    }
    StackIter *createIterator()const; // 2. Add a createIterator() member
};

class StackIter
{
    // 1. Design an "iterator" class
    const Stack *stk;
    int index;
  public:
    StackIter(const Stack *s)
    {
        stk = s;
    }
    void first()
    {
        index = 0;
    }
    void next()
    {
        index++;
    }
    bool isDone()
    {
        return index == stk->sp + 1;
    }
    int currentItem()
    {
        return stk->items[index];
    }
};

StackIter *Stack::createIterator()const
{
  return new StackIter(this);
}

bool operator == (const Stack &l, const Stack &r)
{
  // 3. Clients ask the container object to create an iterator object
  StackIter *itl = l.createIterator();
  StackIter *itr = r.createIterator();
  // 4. Clients use the first(), isDone(), next(), and currentItem() protocol
  for (itl->first(), itr->first(); !itl->isDone(); itl->next(), itr->next())
    if (itl->currentItem() != itr->currentItem())
      break;
  bool ans = itl->isDone() && itr->isDone();
  delete itl;
  delete itr;
  return ans;
}

int main()
{
  Stack s1;
  for (int i = 1; i < 5; i++)
    s1.push(i);
  Stack s2(s1), s3(s1), s4(s1), s5(s1);
  s3.pop();
  s5.pop();
  s4.push(2);
  s5.push(9);
  cout << "1 == 2 is " << (s1 == s2) << endl;
  cout << "1 == 3 is " << (s1 == s3) << endl;
  cout << "1 == 4 is " << (s1 == s4) << endl;
  cout << "1 == 5 is " << (s1 == s5) << endl;
}



