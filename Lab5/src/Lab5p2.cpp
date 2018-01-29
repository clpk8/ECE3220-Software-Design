//============================================================================
// Name        : Lab5P2.cpp
// Author      : ChunBin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;
int i = 0;
//decleared the class Sginal
class Signal{
    //private data members and methods
private:
    char fn[25];
    int length;
    double max;
    void getMax();
    double average;
    void getAverage();
    double scale_val,offset_val;
    double *data;
    double *modified_data;
    void readFile(char* filename);
public:
    Signal();
    Signal(int filenum);
    Signal(char* filename);
    ~Signal();
    void print();
    void offset(double offset_factor);
    void scale(double scale_factor);
    void center();
    void normalize();
    void Statistics();
    void operations();
    void Save_file(char* filename);
    int checkfile = 0; //if ifnull = 1, which means unable to open file
    
};
//destructor
Signal::~Signal(){
    delete data;
}
//print function
void Signal::print(){
    i = 0;
    cout<< "Current max is:" << max <<endl;
    cout<< "Current length is:" << length << endl;
    cout<< "Current average is:" << average << endl;
}
//get Max function
void Signal::getMax(){
    int i = 0;
    max = modified_data[i];
    while (i < length){
        i++;
        if(modified_data[i] > max){
            max = modified_data[i];
        }
    }
}
//get average function
void Signal::getAverage(){
    double sum = 0;
    int i = 0;
    while(i < length){
        sum += modified_data[i];
        i++;
    }
    average = sum / length;
}
//get the Statistics
void Signal::Statistics(){
    getMax();
    getAverage();
    print();
    
}
//save the file
void Signal::Save_file(char* filename){
    int i = 0;
    char dest[50];
    cout<< "Please enter the name of your file follow by .txt" << endl;
    cin>> dest;
    ofstream outfile;
    outfile.open(dest);
    if(outfile.is_open()){
        outfile << length << "  ";
        outfile << max << endl;
        while (i < length){
            outfile << modified_data[i] << endl;
            i++;
        }
    }
    
}
//read file
void Signal::readFile(char* filename){
    cout << filename << endl;
    int i = 0;
    ifstream infile;
    infile.open(filename);
    if (infile.is_open()){
        infile>>length;
        infile>>max;
        data = new double[length]; // alocating memory for data
        modified_data = new double[length];
        while (i < length){
            infile>>data[i]; //save data to the data
            modified_data[i] = data[i];
            i++;
        }
        infile.close();
        getMax();
        getAverage();
    }
    else {
        data = new double[length];
        cerr <<"Unalble to open a File" << endl;
        checkfile = 1;
    }
    
}
// do the offset operation and save it into modifiedData
void Signal::offset(double offset_factor){
    offset_val = offset_factor;
    i = 0;
    while(i < length){
        modified_data[i] = modified_data[i] + offset_factor;
        i++;
    }
    getMax();
}
// do the scale operation
void Signal::scale(double scale_factor){
    scale_val = scale_factor;
    i = 0;
    while(i < length){
        modified_data[i] = modified_data[i] * scale_factor;
        i++;
    }
    getMax();
}
//do the center operation
void Signal::center(){
    getAverage();
    i = 0;
    offset_val = -average;
    while(i < length){
        modified_data[i] = modified_data[i] - average;
        i++;
    }
    getMax();
}
//do the normalize operation
void Signal::normalize(){
    i = 0;
    int min = modified_data[i];
    while (i < length){
        i++;
        if(modified_data[i] < min){
            min = modified_data[i];
        }
    }
    i = 0;
    while (i < length){
        if(min == max){
            modified_data[i] = modified_data[i] * 0.5;
            scale_val = 0.5;
        }
        else{
            modified_data[i] = ((double)(modified_data[i] - min)/(double)(max - min));
            if (modified_data[i]!= 0){
                scale_val = modified_data[i] / modified_data[i];
            }
        }
        i++;
    }
    getMax();
}



//non-parametric constructor
Signal::Signal(){
    char filename[25] = "Raw_data_01.txt";
    strcpy(fn, filename);
    readFile(filename);
    
}
//parametric constructor which take a integer;
Signal::Signal(int filenum){
    char filename [25];
    sprintf(filename,"Raw_data_%02d.txt",filenum);
    cout<< "The file name is " << filename << endl;
    strcpy(fn, filename);
    readFile(filename);
}
//parametric constructor which take a character pointer;
Signal::Signal(char* filename){
    strcpy(fn, filename);
    readFile(filename);
}
//print out the usgae of the program;
void help(){
    cout << "There are 3 different construcors in this program." <<endl;
    cout << "To call the default, run it without any arguments" <<endl;
    cout << "The default constructor will use Raw_data_01.txt" <<endl;
    cout << "To call the other to pamerator constructors use the following example " <<endl;
    cout << "Lab5.out -n 3                  ----             that will open Raw_data_03.txt" <<endl;
    cout << "Lab5.out -f Raw_data_100.txt   ----             that will open Raw_data_100.txt" <<endl;
    cout << "You can do all the operations after the class is being constructored." <<endl;
    cout << "You can modifie the data until save file is being selected" <<endl;
}
// print the menu of what you can do with it.
void menu(){
    cout<< "Please tell me what do you want to do by entering a single character"<<endl;
    cerr<< "              Warning!!! it is case sensative!!!\n\n"<<endl;
    cout<< "                 o to offset the data "<<endl;
    cout<< "                 s to scale the data "<<endl;
    cout<< "                 C to center te data"<<endl;
    cout<< "                 N to normalize the data "<<endl;
    cout<< "                 S for the statistic of the data "<<endl;
    cout<< "                 d to finish and save the file."<<endl;
    
}
//determind which operation we should do.
void Signal::operations(){
    char option;
    double val;
    do{
        menu();
        cin >> option;
        switch(option){
            case 'o':{
                cout << "\n\nYou've choosen offset, Please enter the offset value:" << endl;
                cin >> val;
                offset(val);
                break;
            }
            case 's':{
                cout << "\n\nYou've choosen scale, Please enter the scale factor:" << endl;
                cin >> val;
                scale(val);
                break;
            }
            case 'C':{
                center();
                break;
            }
            case 'N':{
                normalize();
                break;
            }
            case 'S':{
                Statistics();
                break;
            }
            case 'd':{
                cout << "You've choose the save the file"<< endl;
                Save_file(fn);
                
                break;
            }
            default:{
                help();
            }
        }
    }while(option != 'd');
    
}
int main(int argc, char * argv[]) {
    char filename[25];//to store file name
    //switch argc to know how this program will be called
    switch(argc){
        case 1:{
            Signal signal1;
            if(signal1.checkfile == 1){
                return EXIT_FAILURE;
            }
            signal1.print();
            signal1.operations();
            break;
        }
        case 3:{ //when the argc is 3, there are actually 2 ways it can be different
            if ((strcmp(argv[1],"-n")) == 0){
                //get the file name, then call the constructor that take a int.
                int filenum = strtod(argv[2],NULL);
                Signal signal1(filenum);
                if(signal1.checkfile == 1){
                    return EXIT_FAILURE;
                }
                signal1.print();
                signal1.operations();
                
            }
            else if((strcmp(argv[1],"-f")) == 0){
                //store the filename, then call the constructor that take a char*
                strcpy(filename, argv[2]);
                Signal signal1(filename);
                if(signal1.checkfile == 1){
                    return EXIT_FAILURE;
                }
                signal1.print();
                signal1.operations();
            }
            else{
                help();
                return EXIT_FAILURE;
            }
            break;
        }
        default:{
            cerr << "You've entered something wrong, please run the program again."<< endl;
            help();
            break;
        }
    }
    
    return 0;
}




