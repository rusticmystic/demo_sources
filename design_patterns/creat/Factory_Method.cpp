/**
 * Factory Method is to creating objects as Template Method is to implementing an algorithm.
 * An increasingly popular definition of factory method is: a static method of a class that returns an
 * object of that class' type. But unlike a constructor, the actual object it returns might be an instance
 * of a subclass. Unlike a constructor, an existing object might be reused, instead of a new object created.
 * Unlike a constructor, factory methods can have different and more descriptive name
 *
 * The Factory Method defines an interface for creating objects, but lets subclasses decide which classes to instantiate.
 * /
 */
 class Stooge
{
  public:
    // Factory Method
    static Stooge *make_stooge(int choice);
    virtual void slap_stick() = 0;
};

int main()
{
  vector<Stooge*> roles;
  int choice;
  while (true)
  {
    cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
    cin >> choice;
    if (choice == 0)
      break;
    roles.push_back(Stooge::make_stooge(choice));
  }
  for (int i = 0; i < roles.size(); i++)
    roles[i]->slap_stick();
  for (int i = 0; i < roles.size(); i++)
    delete roles[i];
}

class Larry: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Larry: poke eyes\n";
    }
};
class Moe: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Moe: slap head\n";
    }
};
class Curly: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Curly: suffer abuse\n";
    }
};

Stooge *Stooge::make_stooge(int choice)
{
  if (choice == 1)
    return new Larry;
  else if (choice == 2)
    return new Moe;
  else
    return new Curly;
}
