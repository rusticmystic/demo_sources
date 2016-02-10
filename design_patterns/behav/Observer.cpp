/* From sourcemaking.com
 * 
 * One to many
 * Define a one-to-many dependency between objects so that when one object changes state,
 * all its dependents are notified and updated automatically.
 * 
 *  The "View" part of Model-View-Controller.
 * 
 * Define an object that is the "keeper" of the data model and/or business logic (the Subject). 
 * Delegate all "view" functionality to decoupled and distinct Observer objects. 
 * Observers register themselves with the Subject as they are created. 
 * Whenever the Subject changes, it broadcasts to all registered Observers that it has changed, 
 * and each Observer queries the Subject for that subset of the Subject's state that it is responsible for monitoring.
 * 
 * Subject represents the core (or independent or common or engine) abstraction. 
 * Observer represents the variable (or dependent or optional or user interface) abstraction. 
 * The Subject prompts the Observer objects to do their thing. Each Observer can call back to the Subject as needed.
 *  
 * Mediator and Observer are competing patterns.
 * 
 * */

#include <iostream>
#include <vector>
using namespace std;

class AlarmListener
{
  public:
    virtual void alarm() = 0;
};

class SensorSystem
{
    vector < AlarmListener * > listeners;
  public:
    void attach(AlarmListener *al)
    {
        listeners.push_back(al);
    }
    void soundTheAlarm()
    {
        for (int i = 0; i < listeners.size(); i++)
          listeners[i]->alarm();
    }
};

class Lighting: public AlarmListener
{
  public:
     /*virtual*/void alarm()
    {
        cout << "lights up" << '\n';
    }
};

class Gates: public AlarmListener
{
  public:
     /*virtual*/void alarm()
    {
        cout << "gates close" << '\n';
    }
};

class CheckList
{
    virtual void localize()
    {
        cout << "   establish a perimeter" << '\n';
    }
    virtual void isolate()
    {
        cout << "   isolate the grid" << '\n';
    }
    virtual void identify()
    {
        cout << "   identify the source" << '\n';
    }
  public:
    void byTheNumbers()
    {
        // Template Method design pattern
        localize();
        isolate();
        identify();
    }
};
// class inheri.  // type inheritance
class Surveillance: public CheckList, public AlarmListener
{
     /*virtual*/void isolate()
    {
        cout << "   train the cameras" << '\n';
    }
  public:
     /*virtual*/void alarm()
    {
        cout << "Surveillance - by the numbers:" << '\n';
        byTheNumbers();
    }
};

int main()
{
  SensorSystem ss;
  ss.attach(&Gates());
  ss.attach(&Lighting());
  ss.attach(&Surveillance());
  ss.soundTheAlarm();
}
