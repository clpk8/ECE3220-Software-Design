#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef struct Nodes {
    string message;
    string code;
    Nodes *nextPtr;
    
}Node;

class Stack{
private:
    Node *pptr;
public:
    Stack(){pptr = NULL;} //default cosntructor
    void push();
    void pop();
    void print();
    ~Stack();
    
};
Stack::~Stack(){
    delete pptr;
}
void Stack::push(){
    cout<<"push function here" << endl;
    Node *ptr = new Node;
    string x;
    cout<<"enter massage" << endl;
    cin >> x;
    ptr->message = x;
    ptr->nextPtr = pptr;
    pptr = ptr;
    
}
void Stack::pop(){
    cout<<"pop function here" << endl;
    Node *ptr;
    if(pptr == NULL){
        cout<<"Nothing to print, empty stach" << endl;
    }
    else{
        ptr = pptr;
        pptr = pptr->nextPtr;
        delete ptr;
    }
}
void Stack::print(){
    cout<<"lalala"<<endl;
    Node *ptr = pptr;
    cout<<"Stack :" << endl;
    while(ptr != NULL){
        cout << ptr->message <<endl;
        ptr = ptr->nextPtr;
    }
    cout << "NULL" << endl;
}

int main(void){
    Stack s1;
    int option;
    do{
        cout<<"enter what you want to do "<<endl;
        cout<<"1.push"<<endl;
        cout<<"2.pop"<<endl;
        cout<<"3.print"<<endl;
        cout<<"4.quit"<<endl;
        cin>>option;
        switch(option){
            case 1:{
                s1.push();
                break;
            }
            case 2:{
                s1.pop();
                break;
            }
            case 3:{
                s1.print();
                break;
            }
            case 4:{
                cout<<"Bye"<<endl;
            }
            default:{
                cout<<"someting wrong, enter again"<<endl;
            }
        }
    }while (option != 4);
    
    return 0;
}
