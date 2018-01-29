//
//  main.cpp
//  ECE3220Lab7
//
//  Created by linChunbin on 10/31/17.
//  Copyright © 2017 linChunbin. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
//Message class definition
class Message{
    //friend class
    friend class MessageStack;
protected:
    string message1;
public:
    Message();//default constructor
    Message(string);//parametric constructor
    virtual ~Message();//virtual destructor
    virtual void printInfo();//virtual function
    void getMessage();
    void setMessage(string x);
};
//printInfo function defination
void Message::printInfo(){
    cout<<"Print info from Message!" << endl;
    cout << "message is " << message1 << endl;
}
//set a message by a string
void Message::setMessage(string x){
    message1 = x;
}
//get message from user
void Message::getMessage(){
    cout << "Please enter a message to convert" << endl;
    getline(cin,message1);
  //  cout << "Message is " << message1 << endl;
}
Message::~Message(){
}
//default constructor
Message::Message(){
}
//parametric constructor
Message::Message(string m){
    message1 = m;
}
// MorseCodeMessage class
class MorseCodeMessage : public Message{
    //have the same friend class
    friend class MessageStack;
private:
    //private members
    vector<string> MC;//to store the MorseCode that was translated from message
    //alpha and MSC match index.
    vector<char> alpha= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
        'q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
    vector<string> MSC{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
        "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",
        ".--","-..-","-.--","--..","-----",".----","..---","..--","...-",".....",
        "-....","--...","---..","----."};
    string oneString;//used to store MorseCode into one string
    int index; //match index
    int indexOfError; //used to find error
public:
    //public methods
    string getMSC(char x);
    void Translate();
    void printInfo();
    void ToOneString();
    ~MorseCodeMessage();
    MorseCodeMessage();
    MorseCodeMessage(string m);
    bool checkMessage();
    void setMessage(string x);
    void reset();
};
//reset the private member for next message
void MorseCodeMessage::reset(){
    MC.clear();
    oneString.clear();
}
//used on default constructor
void MorseCodeMessage::setMessage(string x){
    message1 = x;
}
//check if there are something that is not able to translate
bool MorseCodeMessage::checkMessage(){
    int i = 0;
    while(i < message1.size()){
        if(isalnum(message1[i]) || isspace(message1[i])){
        }
        else{
            indexOfError = i;
            return false;
        }
        i++;
    }
    return true;
}
//get MorseCode into one string
void MorseCodeMessage::ToOneString(){
    for(int i = 0; i < MC.size(); i ++){
        oneString += MC[i] + " ";
    }
    
}
//destructor
MorseCodeMessage::~MorseCodeMessage(){
    
}
//default onstructor
MorseCodeMessage::MorseCodeMessage(){
    if (checkMessage() == true){
        Translate();
        ToOneString();
    }
    else{
        cout << "You can only enter number and alpha! " << message1[indexOfError] << " is not right" << endl;
    }
}
//paramrtric constructor, extend parametric constructor from message
MorseCodeMessage::MorseCodeMessage(string m) : Message(m){
    
    if (checkMessage() == true){
        Translate();
        ToOneString();
    }
    else{
        cout << "You can only enter number and alpha! " << message1[indexOfError] << " is not right" << endl;
    }
}
//make all the alpha to lower case
string MorseCodeMessage::getMSC(char x){
    index = 0;
    x = tolower(x);
    int i = 0;
    while(1){
        if(alpha[i] == x){
            break;
        }
        else{
            index++;
        }
        i++;
    }
    return MSC[index];
}
//translate into morse code
void MorseCodeMessage::Translate(){
    MC.clear();
    int i = 0;
    string slash = "/";
    while(i < message1.size()){
        if(isspace(message1[i]) == 1){
            MC.push_back(slash);
        }
        else{
            string x = getMSC(message1[i]);
            MC.push_back(x);
        }
        i++;
    }
}
//printInfo occur on dynamic binding
void MorseCodeMessage::printInfo(){
    cout<< "Print info from MorseCodeMessage" << endl;
    cout << "The Code of " << message1 << " is: "  << endl;
    for(int i = 0; i < MC.size(); i++){
        cout << MC[i] << " ";
    }
    cout << endl;
}
//struct definetion of linked list
typedef struct Nodes {
    string message;
    string code;
    Nodes *next;
    
}Node;
//class MessageStack
class MessageStack{
    //friend function that can do operation
    friend void operation(MorseCodeMessage MC1,  MessageStack S1);
private:
    Node *pptr; //stands for privous printer
public:
    MessageStack(){pptr = NULL;} //defualt constructor
    void push(MorseCodeMessage M);
    void pop();
    void print();
    ~MessageStack();//destructor
    
};
//destructor to delete pointer
MessageStack::~MessageStack(){
    delete pptr;
}
//push the Message
void MessageStack::push(MorseCodeMessage M){
    Node* ptr = new Node;
    ptr->message = M.message1;
    ptr->code = M.oneString;
    ptr->next = pptr;
    pptr = ptr;
    M.oneString.clear();
    M.message1.clear();
    M.MC.clear();
}
//pop the message out, using LIFO
void MessageStack::pop(){
    Node *ptr;
    if(pptr == NULL){
        cout<<"Nothing to pop" << endl;
    }
    else{
        ptr = pptr;
        pptr = pptr->next;
        delete ptr;
    }
}
//print the current Stack
void MessageStack::print(){
    Node *ptr = pptr;
    
    cout<<"current stack is:" << endl;
    while(ptr != NULL){
        
        cout << "Message is " << ptr->message <<endl;
        cout << "Morse code is" << ptr->code << endl;
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
    
}
//do operation to the stack
void operation(MorseCodeMessage MC1, MessageStack S1){
    
    
    int option;
    do{
        //menu
        cout<<"enter what you want to do "<<endl;
        cout<<"1.pop"<<endl;
        cout<<"2.print"<<endl;
        cout<<"3.enter another message"<<endl;
        cout<<"4.quit" << endl;
        cin>>option;
        switch(option){
                
            case 1:{
                S1.pop();
                break;
            }
            case 2:{
                S1.print();
                break;
            }
            case 4:{
                cout<<"Bye"<<endl;
                break;
            }
            case 3:{
                MC1.reset();
                cin.ignore();
                MC1.getMessage();
                MC1.Translate();
                MC1.ToOneString();
                if(MC1.checkMessage() == true){
                    S1.push(MC1);
                }
                else{
                    cout<<"someting wrong, enter again"<<endl;
                }
                
                break;
            }
            default:{
                cout<<"someting wrong, enter again"<<endl;
            }
        }
    }while (option != 4);
}
//main function
int main(int argc, const char * argv[]) {
    //without arguments
    if(argc == 1){
        string x;
        cout << "Parametric constructor"<< endl;
        cout << "enter what you want to be converted" << endl;
        getline(cin,x);
        //construct the object with string x
        MorseCodeMessage MC1(x);
        MessageStack S1;
        S1.push(MC1);
        //make sure everything is character
        if(MC1.checkMessage() == true){
            operation(MC1,S1);
        }
        else{
            cout << "Plese restart the program!!"<< endl;
        }
        //dynamic binding
                Message *DB;
                x = "lalala";
                int i;
                cout<< "Press 1 for print in Message class" <<endl;
                cout<< "press 2 for print in MorseCodeMessage class" << endl;
                cin >> i;
                //binding is not known till user choose
                if(i == 1){
                    DB = new Message(x);
                }
                else{
                    DB = new MorseCodeMessage(x);
                }
        
                DB->printInfo();
        
        
    }
    //other cases
    else{
        string x;
        cout<< "default"<< endl;
        //default constructor
        MorseCodeMessage MC1;
        MessageStack S1;
        for(int i = 1; i < argc; i++){
            x = argv[i];
            MC1.setMessage(x);//set all the argument to each message
            MC1.Translate();
            MC1.ToOneString();
            S1.push(MC1);
            MC1.reset();
        }
        if(MC1.checkMessage() == true){
            operation(MC1,S1);
        }
        else{
            cout << "Plese restart the program!!"<< endl;
        }
        
    }
    
    return 0;
}
