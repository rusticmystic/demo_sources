#include <iostream>
#include <cstdlib>

using namespace std;

int
func_1 ()
{
  cout << __FUNCTION__ << endl;
  cout << "Throw A" << endl;
  unsigned int s = 100;
  throw s;
  return 1;
}

int
func_2 ()
{
  cout << __FUNCTION__ << endl;
  cout << "Throw B" << endl;
  throw ("ME");
  return 1;
}

int
main ()
{

  try
  {
    func_1 ();
    func_2 ();
  }

  catch (unsigned int num)
  {
    cout << num << endl;

  }

  catch (const char *message)
  {
    cout << message << endl;

  }

  return 0;
}
