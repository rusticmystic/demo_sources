/* Define an object that encapsulates how a set of objects interact. 
 * Mediator promotes loose coupling by keeping objects from referring to each other explicitly, 
 * and it lets you vary their interaction independently.
 * 
 * The Mediator defines an object that controls how a set of objects interact. 
 * Loose coupling between colleague objects is achieved by having colleagues communicate with the Mediator, 
 * rather than with each other. The control tower at a controlled airport demonstrates this pattern very well
 * 
 * Mediator and Observer are competing patterns. The difference between them is that Observer distributes communication by introducing
 * "observer" and "subject" objects, whereas a Mediator object encapsulates the communication between other objects.
 * 
 * For REUSE we prefer Observor objects
 * Mediator can leverage Observer for dynamically registering colleagues and communicating with them.
 * 
 * Mediator is similar to Facade in that it abstracts functionality of existing classes
 * 
 * Here in this example 
 * In usual representaion of a linked list Node objects interact directly with each other, recursion is required,
 * removing a Node is hard, and it is not possible to remove the first node.
 * 
 * A "mediating" List class focuses and simplifies all the administrative responsibilities, and
 * the recursion (which does not scale up well) has been eliminated
 * */
 
class Node
{
  public:
    Node(int v)
    {
        m_val = v;
    }
    int get_val()
    {
        return m_val;
    }
  private:
    int m_val;
};

class List
{
  public:
    void add_node(Node *n)
    {
        m_arr.push_back(n);
    }
    void traverse()
    {
        for (int i = 0; i < m_arr.size(); ++i)
          cout << m_arr[i]->get_val() << "  ";
        cout << '\n';
    }
    void remove_node(int v)
    {
        for (vector::iterator it = m_arr.begin(); it != m_arr.end(); ++it)
        if ((*it)->get_val() == v)
        {
            m_arr.erase(it);
            break;
        }
    }
  private:
    vector m_arr;
};

int main()
{
  List lst;
  Node one(11), two(22);
  Node thr(33), fou(44);
  lst.add_node(&one);
  lst.add_node(&two);
  lst.add_node(&thr);
  lst.add_node(&fou);
  lst.traverse();
  lst.remove_node(44);
  lst.traverse();
  lst.remove_node(22);
  lst.traverse();
  lst.remove_node(11);
  lst.traverse();
}
