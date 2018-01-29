// Lab6_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab6_strings.cpp -o Lab6_strings -std=c++11
//      or:  g++ Lab6_strings.cpp -o Lab6_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
    string s1, s2("Hello"), s3 = "World";
    cout << "\nEnter a word:" << endl;
    cin >> s1;
    cin.ignore();    // to consume the '\n' character. Otherwise, you may get issues with
    //without this line, it will end without reading
    // the getline() below. Try commenting this out. Any issues?
    //yes, it will skip it.
    
    string s4(s1);
    
    cout << s1 << endl
    << s2 << endl
    << s3 << endl
    << s4 << endl;
    
    s1 = s2 + s3;
    cout << s1 << endl;
    
    // ***********************************************************************
    // Try all the operations in Table 3.2 using the strings above and
    // using new strings that you may declare.
    // Some of those operations have already been used, but write your
    // own examples.
    // ***********************************************************************
    
    // -----------------------------------------------------------------------
    string s5; //declare a new string
    cout<<"\n Enter a string with space" << endl;
    getline(cin,s5); //get line function
    cout<< "string with white space is: " << s5 << endl;
    //use of empty
    cout << "is string empty? true if yes: " << s5.empty()<<endl;
    //use of size
    cout << "the size of string is: " << s5.size() << endl;
    //use of s[i]
    cout << "the 5th dight of s5 is "<< s5[6] << endl;
    
    
    // ***********************************************************************
    // Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
    // 1) change the case of the letters in your input line above (upper to
    //    lowercase and vice-versa).
    // 2) Replace any whitespace with a dot ('.').
    // Print the converted text.
    // ***********************************************************************
    string line;//declare new variable
    cout << "\nEnter some text:" << endl;
    getline(cin, line);
    cout << line << endl;
    
    int i = 0;
    //toupper element by elment
    for (i = 0; i< line.size(); i++){
        line.at(i) = toupper(line.at(i));
    }
    cout << "the upper is " << line << endl;
    //tolower element by element
    for (i = 0; i < line.size();i++){
        line.at(i) = tolower(line.at(i));
    }
    cout<< "the lower is " << line << endl;
    
    cout << "\nEnter some text, finish it with an &:" << endl;
    getline(cin, line, '&');    // the delimiter can be any character
    cout << line << endl;
    //when isspace ==1, change it to '.'
    for (i = 0; i < line.size(); i++){
        if(isspace(line.at(i)) == 1){
            line.at(i) = '.';
        }
    }
    cout<< "modified line is " << line <<endl;
    
    return 0;
}

