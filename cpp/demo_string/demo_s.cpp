#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void ostream_demo()
{

    // Declare a string stream
    ostringstream ostr;

    // Writing to a string stream.
    ostr << "Hello how are you" << endl;

    // Retrieving a string from a string stream
    cout << ostr.str();

}

void istream_demo()
{

    // Declaring input string stream , it is the sting stream fro which we can read input
    istringstream istr("10");

    // Checking the data in the string stream
    cout << istr.str();

    // Read the value from string to an integer.
    int d;
    istr >> d;

}

void demo_string(){
     // CPP string is basically defined as: typedef basic_string<char> string;

     string Line("Initial Value");
     Line. 


};
void demo_basic_string()
{
 // generic string container for array of data types
 // basic_string<int> int_arr;
};

int main() {

    ostream_demo();
    istream_demo();

    return 0;
}
