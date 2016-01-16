/* Sample usage of some STL templates */

#include<iostream>
/*Template Headers which can be used*/
#include<list>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<string>

/* TBD: set , dequeue, vector    */

/*template for iterating using iterator*/
template<class T>
T display(T& start,T& end)
{
   //T::iteratorIt=t.begin();
   //It=;
    while(start!=end) {
        std::cout << " " <<*start;
        start++;
    }
}

/*Demo usage of list STL template*/
int demo_list() {
    //declare list  object
    std::list<std::string> Members;
    std::string temp;
    bool exit;
    //Input a sentence from commandline
    std::cout << "Enter Name: Type exit to stop " <<std::endl;

    while(std::cin >> temp && temp!="exit") {
    // Adding member to list at back
        Members.push_back(temp);
        std::cout << temp <<" added to list."<< std::endl;
    }

    //size of list
    std::cout << "the list has " << Members.size() << " Members" <<std::endl;

    //Iteration over a list, wee need an iterator
    std::list<std::string>::iterator It,end;
    //using the iterator to traverse
    end=Members.end();//set iterator to end,useless step
    It=Members.begin();

    //loop to iterate
    while(It!=end) {
        std::cout << " " <<*It;
        It++;
    }
    std::cout << std::endl;
    //adding an element at iterator
    end--;//point to second last element
    Members.insert(end,"Here");

    //delete element use pop.
    //reset iterator to begin
    It=Members.begin();
    end=Members.end();
    display(It,end);

}

/*Demo usage of stack STL template*/
int demo_stack() {
    std::stack<char> A;

    A.push('A');
    A.push('B');
    A.push('+');

    std::cout << "Stack Top is " << A.top() << std::endl;
    std::cout << "Removing First Element" << std::endl;
    A.pop();
    std::cout << "Stack Top is " << A.top() << std::endl;


}



/* Demo usage of queue STL template*/
int demo_queue() {
    std::queue<int> MyQueue;
    //std::queue<int>::iterator It,end;

    int Loop;
    //queuing elements
    if(MyQueue.empty()) {
        std::cout << "Queue is Empty" << std::endl;
        std::cout << "Enter Elements" << std::endl;


        for (Loop=0; Loop<10; Loop++)
        {
            MyQueue.push(Loop);
        }

        std::cout << "Front of queue:: " << MyQueue.front() << std::endl;
        MyQueue.pop();
        std::cout << "Processed element " << std::endl;
        std::cout << "Front of queue:: " << MyQueue.front() << std::endl;


        //display full queue and destroy
        std::cout << "Elements of Queue" << std::endl;
        while(!MyQueue.empty()) {
            std::cout << " " << MyQueue.front();
            MyQueue.pop();
        }
        std::cout <<"\n" << std::endl;
    }




}

/* Demo usage of map STL template*/
int demo_map() {
    int i;
    std::map<std::string,std::string> MyMap;
    std::string keys[7]= {"sun","mon","tue","wed","thu","fri","sat"};

    std::string duty[7]= {"Eddie","Sim","Mike","Sam","Sonu","Zoobi","Hui"};

    //we use pair data type template and inset it into rap
    //adding values  to keys
    for(i=0; i<7; i++) {}
    MyMap.insert(std::pair<std::string,std::string>(keys[1],keys[2]));



}

/*Advanced map usage*/
int advanced_map ()
{
    std::map<char,int> mymap;

    // first insert function version (single parameter):
    mymap.insert ( std::pair<char,int>('a',100) );
    mymap.insert ( std::pair<char,int>('z',200) );

    std::pair<std::map<char,int>::iterator,bool> ret;
    ret = mymap.insert ( std::pair<char,int>('z',500) );
    if (ret.second==false) {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    std::map<char,int>::iterator it = mymap.begin();
    mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
    mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

    // third insert function version (range insertion):
    std::map<char,int> anothermap;
    anothermap.insert(mymap.begin(),mymap.find('c'));

    // showing contents:
    std::cout << "mymap contains:\n";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::cout << "anothermap contains:\n";
    for (it=anothermap.begin(); it!=anothermap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}

/* Demo usage of set STL template*/
int demo_set() {





}


/* Demo usage of map vector template*/
int demo_vector() {



}



/*Demo template of templates*/

//template<class T>
//int demo(const T&){

//}

/* Main Program */
int main() {

    //
    //demo_list();
    demo_stack();
    demo_queue();
    demo_map();


}
