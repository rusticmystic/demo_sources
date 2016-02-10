/* From sourcemaking.com 
 * Compose objects into tree structures to represent whole-part hierarchies. 
 * Composite lets clients treat individual objects and compositions of objects uniformly
 * 
 * Menus that contain menu items, each of which could be a menu.
 * Row-column GUI layout managers that contain widgets, 
 * each of which could be a row-column GUI layout manager.
 * Directories that contain files, each of which could be a directory.
 * Containers that contain Elements, each of which could be a Container
 * 
 * It supports RECURSIVE COMPOSITION
 * 
 * Composite and Decorator have similar structure diagrams, reflecting the fact that both rely
 * on recursive composition to organize an open-ended number of objects.
 * */

#include <iostream>
#include <vector>
using namespace std;

// 2. Create an "interface" (lowest common denominator)
class Component
{
  public:
    virtual void traverse() = 0;
};

class Leaf: public Component
{
    // 1. Scalar class   3. "isa" relationship
    int value;
  public:
    Leaf(int val)
    {
        value = val;
    }
    void traverse()
    {
        cout << value << ' ';
    }
};

class Composite: public Component
{
    // 1. Vector class   3. "isa" relationship
    vector < Component * > children; // 4. "container" coupled to the interface
  public:
    // 4. "container" class coupled to the interface
    void add(Component *ele)
    {
        children.push_back(ele);
    }
    void traverse()
    {
        for (int i = 0; i < children.size(); i++)
        // 5. Use polymorphism to delegate to children
          children[i]->traverse();
    }
};

int main()
{
  Composite containers[4];

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 3; j++)
      containers[i].add(new Leaf(i *3+j));

  for (i = 1; i < 4; i++)
    containers[0].add(&(containers[i]));

  for (i = 0; i < 4; i++)
  {
    containers[i].traverse();
    cout << endl;
  }
}
