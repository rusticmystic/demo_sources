/* From sourcemaking.com
 * 
 * Without violating encapsulation, capture and externalize an object's internal state
 * so that the object can be returned to this state late
 * 
 * For UNDO or ROLLBACK
 * 
 * Need to restore an object back to its previous state (e.g. "undo" or "rollback" operations).
 * 
 * 
 * The Memento design pattern defines three distinct roles:

    Originator - the object that knows how to save itself.
    Caretaker - the object that knows why and when the Originator needs to save and restore itself.
    Memento - the lock box that is written and read by the Originator, and shepherded by the Caretaker.

 * 
 * Example :
 * This pattern is common among do-it-yourself mechanics repairing drum brakes on their cars. 
 * The drums are removed from both sides, exposing both the right and left brakes. 
 * Only one side is disassembled and the other serves as a Memento of how the brake parts fit together. 
 * Only after the job has been completed on one side is the other side disassembled. 
 * When the second side is disassembled, the first side acts as the Memento
 * Command and Memento act as magic tokens to be passed around and invoked at a later time. 
 * In Command, the token represents a request; in Memento, it represents the internal state 
 * of an object at a particular time
 * 
 * MEMENTO can be only passed by a value
 * Discussion. A memento is an object that stores a snapshot of the internal state of another object. 
 * It can be leveraged to support multi-level undo of the Command pattern. 
 * In this example, before a command is run against the Number object, Number's current state is saved in Command's static memento history list,
 * and the command itself is saved in the static command history list. Undo() simply "pops" 
 * the memento history list and reinstates Number's state from the memento. Redo() "pops" the command history list. 
 * Note that Number's encapsulation is preserved, and Memento is wide open to Number. 

 * */
 
#include <iostream.h>
class Number;

class Memento
{
  public:
    Memento(int val)
    {
        _state = val;
    }
  private:
    friend class Number; // not essential, but p287 suggests this
    int _state;
};

class Number
{
  public:
    Number(int value)
    {
        _value = value;
    }
    void dubble()
    {
        _value = 2 * _value;
    }
    void half()
    {
        _value = _value / 2;
    }
    int getValue()
    {
        return _value;
    }
    Memento *createMemento()
    {
        return new Memento(_value);
    }
    void reinstateMemento(Memento *mem)
    {
        _value = mem->_state;
    }
  private:
    int _value;
};

class Command
{
  public:
    typedef void(Number:: *Action)();
    Command(Number *receiver, Action action)
    {
        _receiver = receiver;
        _action = action;
    }
    virtual void execute()
    {
        _mementoList[_numCommands] = _receiver->createMemento();
        _commandList[_numCommands] = this;
        if (_numCommands > _highWater)
          _highWater = _numCommands;
        _numCommands++;
        (_receiver-> *_action)();
    }
    static void undo()
    {
        if (_numCommands == 0)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        _commandList[_numCommands - 1]->_receiver->reinstateMemento
          (_mementoList[_numCommands - 1]);
        _numCommands--;
    }
    void static redo()
    {
        if (_numCommands > _highWater)
        {
            cout << "*** Attempt to run off the end!! ***" << endl;
            return ;
        }
        (_commandList[_numCommands]->_receiver->*(_commandList[_numCommands]
          ->_action))();
        _numCommands++;
    }
  protected:
    Number *_receiver;
    Action _action;
    static Command *_commandList[20];
    static Memento *_mementoList[20];
    static int _numCommands;
    static int _highWater;
};

Command *Command::_commandList[];
Memento *Command::_mementoList[];
int Command::_numCommands = 0;
int Command::_highWater = 0;

int main()
{
  int i;
  cout << "Integer: ";
  cin >> i;
  Number *object = new Number(i);

  Command *commands[3];
  commands[1] = new Command(object, &Number::dubble);
  commands[2] = new Command(object, &Number::half);

  cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  cin >> i;

  while (i)
  {
    if (i == 3)
      Command::undo();
    else if (i == 4)
      Command::redo();
    else
      commands[i]->execute();
    cout << "   " << object->getValue() << endl;
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin >> i;
  }
}
 
 



