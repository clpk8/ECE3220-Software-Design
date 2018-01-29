// Lab6_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab6_vectors.cpp -o Lab6_vectors -std=c++11
//      or:  g++ Lab6_vectors.cpp -o Lab6_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
    vector<int> ivec1(5), ivec2; // ivec1 have 5 copies of a value-initialized object, ivec2 hods int
    vector<double> dvec1{5.1}, dvec2(5,1.5); // decv1 has one element5.1.      devec 2 has 5 elements, they all 1.5
    vector<string> svec1 = {"hello", "world"};
    // vector<myClass> myCvec;    // you can have vectors of objects
    // in general: vector<Type> vec;    // vector is a "template"
    
    for(int i = 0; i < ivec1.size(); i++)
        cout << ivec1[i] << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    for(auto i:ivec1)    // This is equivalent to the above for loop
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    for(auto i:dvec1)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    for(auto i:dvec2)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    for(auto i:svec1)
        cout << i << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    cout << "Original size: " << ivec2.size() << endl;
    ivec2.push_back(50);
    cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
    cout << "\n------------------------------------------------------------------" << endl;
    
    
    // ***********************************************************************
    // Try all the ways to initialize a vector shown in Table 3.4. Use the
    // vectors above and/or declare new vectors.
    // Some of those operations have already been used, but write your
    // own examples.
    
    // Do exercises 3.14 and 3.15 from Lippman (page 102)
    
    // Try all the vector operations shown in table 3.5. Use the vectors above
    // or define new ones. Try different types.
    // ***********************************************************************
    cout<< "\n=======================================================" << endl;
    //my examples of different vectors
    class test{
    public:
        int i = 2;
        
    };
    //vector of different types
    vector<test> obj1; //type of class test
    vector<test> obj2(obj1);
    vector<double> obj3{10,24.466,235.66};
    vector<float> obj4(9,9.9999);
    vector<string> obj5 = {"lalala","test","all"};
    vector<int> obj6(9);
    
    
    for(auto i:obj3)
        cout << i <<  endl;
    cout << "\n------------------------------------------------------------------" << endl;
    for(auto i:obj4)
        cout << i <<  endl;
    cout << "\n------------------------------------------------------------------" << endl;
    for(auto i:obj5)
        cout << i <<  endl;
    cout << "\n------------------------------------------------------------------" << endl;
    for(auto i:obj6)
        cout << i <<  endl;
    cout<< "\n=======================================================" << endl;
    //here is excercise 3.14
    cout<< "enter value for ex3.14" << endl;
    vector<int> ex314(5);
    for(int i = 0; i < ex314.size();i++){
        cin >> ex314.at(i);
    }
    cout << "\n------------------------------------------------------------------" << endl;
    for(auto i:ex314)
        cout<< i << endl;
    //here is excercise 3.15
    cout<< "enter value for ex3.15, string" << endl;
    vector<string> ex315(5);
    for(int i = 0; i < ex315.size();i++){
        cin >> ex315.at(i);
    }
    cout << "\n------------------------------------------------------------------" << endl;
    for(auto i:ex315)
        cout<< i << endl;
    
    cout << "\n------------------------------------------------------------------" << endl;
    //used of some vector functions
    cout << "is object 6 empyt?    "      << obj6.empty() << endl;
    cout << "what is size of ex315??  "   << ex314.size() << endl;
    cout << "what you want to add to the end of ex315" << endl;
    int t;
    cin >> t;
    ex314.push_back(t);
    cout << "The current size of ex315 is: " << ex314.size() << endl;
    cout << ex315[2] << "is the 3rd value of ex315" << endl;
    cout<< "\n=======================================================" << endl;
    //used some other vector functions
    cout << "obj4 second value" <<  obj4[1] << endl;
    obj4 = {3, 15, 79, 33, 909, 234};
    cout << "new obj4 second value" <<  obj4[1] << endl;
    
    
    
    
    return 0;
}



