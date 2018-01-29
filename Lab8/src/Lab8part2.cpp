//Lab6Part2.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
int i = 0;
//decleared the class Sginal
class Signal{
	//private data members and methods
	private:
		char fn[25];
		double average;
		double scale_val,offset_val;
		void readFile(string filename)throw(const char*, char);
		double max;
		int length;
	public:
		int getLength(){return length;};
		double getmax(){return max;};
		void setLength(int l){length = l;};
		void setMax(double m){max = m;};
		void getMax();
		void getAverage();
		vector<double> datavec;
		vector<double> modified_datavec;
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
		void Save_file(string filename);
		int checkfile = 0; //if ifnull = 1, which means unable to open file
		void operator+(const double x);
		void operator*(const double x);


};
//equivlent to offset
void Signal::operator+(const double x){
	int i = 0;
	while(i < length){
		modified_datavec[i] = modified_datavec[i] + x;
		i++;
	}
}
//equivlent to scale
void Signal::operator*(const double x){
	int i = 0;
	while(i < length){
		if(modified_datavec[i] != 0){
			modified_datavec[i] = modified_datavec[i] * x;

		}
		else{
			modified_datavec[i] = modified_datavec[i] * -x;

		}
		i++;
	}
}

//destructor, empty because we changed the data to vectors
Signal::~Signal(){

}
//print function
void Signal::print(){
	i = 0;
	cout<< "Current max is:" << setiosflags(ios::fixed) << setprecision(4) << max <<endl;
	cout<< "Current length is:" << setiosflags(ios::fixed) << setprecision(4) << length << endl;
	cout<< "Current average is:" << setiosflags(ios::fixed) << setprecision(4) << average << endl;
}
//read file
void Signal::readFile(string filename)throw(const char*, char){
	cout << filename << endl;
	int i = 0;
	ifstream infile;
	infile.open(filename);
	if (infile.is_open()){
		infile>>length;
		infile>>max;
		while (i < length){
			datavec.resize(length);
			modified_datavec.resize(length);
			infile>>datavec.at(i);
			modified_datavec.at(i) = datavec.at(i);
			i++;
		}
		infile.close();
		if(modified_datavec.empty() == true){
            //if vector is empty, it will thorow to constructor
			throw "it is empty";
		}
		getMax();
		getAverage();
	}
	else {
        //if file was not opened, it will get thrown to constructor
		cerr <<"Unalble to open a File" << endl;
		checkfile = 1;

	}

}
//get Max function
void Signal::getMax(){
	int i = 0;
	max = modified_datavec.at(i);
	while (i < modified_datavec.size()){
		i++;
		if(modified_datavec[i] > max){
			max = modified_datavec[i];
		}
	}
}
//get average function
void Signal::getAverage(){
	double sum = 0;
	int i = 0;
	while(i < length){
		sum += modified_datavec[i];
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
void Signal::normalize(){
	i = 0;
	double min = modified_datavec[i];
	while (i < modified_datavec.size()){
		i++;
		if(modified_datavec[i] < min){
			min = modified_datavec[i];
		}
	}
	i = 0;
	while (i < modified_datavec.size()){
		if(min == max){
			modified_datavec[i] = modified_datavec[i] * 0.5;
			scale_val = 0.5;
		}
		else{
			modified_datavec[i] = ((modified_datavec[i] - min)/(max - min));
			if (modified_datavec[i]!= 0){
				scale_val = modified_datavec[i] / modified_datavec[i];
			}
		}
		i++;
	}
	getMax();
}
//do the center operation
void Signal::center(){
	getAverage();
	i = 0;
	offset_val = -average;
	cout<<"Aaverage is!!!!!" << offset_val << endl;
	this->operator+(offset_val);
	getMax();
}
//save the file
void Signal::Save_file(string filename){
	int i = 0;
	ofstream outfile;
	outfile.open(filename);
	if(outfile.is_open()){
		outfile << length << "  ";
		outfile <<  setiosflags(ios::fixed) << setprecision(4) << max << endl;
		while (i < modified_datavec.size()){
			outfile << modified_datavec[i] << endl;
			i++;
		}
	}
}
//offset is changed to using the operator
void Signal::offset(double offset_factor){
	offset_val = offset_factor;
	this->operator+(offset_val);
	getMax();
}
void Signal::scale(double scale_factor){
	scale_val = scale_factor;
	this->operator*(scale_val);
	getMax();
}
//default constructor, set everything to 0;
Signal::Signal(){
	length = 0;
	max = 0;
	average = 0;
}
//parametric constructor which take a integer;
Signal::Signal(int filenum){
	char filename [25];
	sprintf(filename,"Raw_data_%02d.txt",filenum);
	cout<< "The file name is " << filename << endl;
	strcpy(fn, filename);
    
    //second try block
    //it will go to readFile function
	try{
		readFile(filename);
	}
	catch(const char * s){
		cout<< "program got thrown\n"<< s << " is the error message" << endl;
		throw 'q';//rethrow for main to check

	}

}
//parametric constructor which take a character pointer;
Signal::Signal(char* filename){
	strcpy(fn, filename);
	try{
		readFile(filename);
	}
	catch(const char * s){
		cout<< "program got thrown\n"<< s << " is the error message" << endl;
		throw 'q';//rethrow for main to check
	}

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
	char filename[25];
	do{
		menu();
		cin >> option;
		switch(option){
			case 'o':{
					 cout << "\n\nYou've choosen offset, Please enter the offset value:" << endl;
					 try{
						 cin >> val;
                         //this means if cin is not a double
						 if(!cin){
							 throw 'q';

						 }


					 }
					 catch(char q){
						 cout<<  "You've entered wrong value"<<endl;
						 throw 'q';//rethrow to main for continous handling
					 }
					 offset(val);
					 break;
				 }
			case 's':{
					 cout << "\n\nYou've choosen scale, Please enter the scale factor:" << endl;
					 try{
						 cin >> val;
                         //this means if cin is not a double
						 if(!cin){
							 throw 'q';
						 }
						 else if(val == 0){
                             //you can not scale by 0, this will get throw back to main
							 throw 0;
						 }

					 }
					 catch(char q){
						 cout<<  "You've entered wrong value"<<endl;
						 throw 'q';//rethrow back to main for continous handling
					 }

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
					 cout << "Please enter what do you want to save as, follow by .txt"<< endl;
					 cin >> filename;
					 Save_file(filename);
					 break;
				 }
			default:{
					cout<<"wrong input, please select again"<<endl;
				}
		}
	}while(option != 'd');

}
//declear non-member operator
Signal operator+(Signal &lhs,Signal &rhs){
	int length1, length2;
	length1 = lhs.getLength();
	length2 = rhs.getLength();
	if(length1 == length2){
		Signal signal3;
		signal3.setLength(length1);
		int i = 0;
		while(i < length1){
			signal3.modified_datavec.push_back(rhs.datavec[i]);
			signal3.modified_datavec[i] += lhs.datavec[i];
			i++;
		}
		signal3.getAverage();

		signal3.setMax(lhs.getmax());

		return signal3;
	}
	else{
		cout<< "different length object!" << endl;
		return EXIT_FAILURE;
	}

}
//throwing object
class bad_addition{
	private:
		Signal s1;
		Signal s2;
	public:
		bad_addition(Signal a, Signal b) : s1(a), s2(b){}
		void msg();
};
void bad_addition::msg(){
	cout<<"Length are not equal" << endl;
	cout<<"size of the first Sgianl are " << s1.getLength()<<endl;
	cout<<"size of the second Sgianl are " << s2.getLength()<<endl;
}
//function that has specification only throw an object
Signal NonMemberAdding(Signal &s1, Signal &s2) throw(bad_addition){
    
    //second try block
	try{
		if(s1.getLength() != s2.getLength()){
            //throw an object
			throw bad_addition(s1, s2);
		}
	}
	catch(bad_addition & ba){
        //catchs the message, and do the rethrown back 
		cout<<"this is rethrow"<<endl;
		throw;
	}
	//if it went pass all the throw, which means that length are equal
	//so i go ahead do the operation, return a S3
	Signal s3;
	s3 = operator+(s1,s2);
	return s3;

}
int main(int argc, char * argv[]) {
	Signal *signal;
	char filename[25];//to store file name
	//switch argc to know how this program will be called
	switch(argc){
		case 1:{
                   //default case
			       Signal signal1;
			       if(signal1.checkfile == 1){
				       return EXIT_FAILURE;
			       }
			       signal1.print();
			       break;
		       }
		case 3:{ //when the argc is 3, there are actually 2 ways it can be different
			       if ((strcmp(argv[1],"-n")) == 0){
				       //get the file name, then call the constructor that take a int.
				       int filenum = strtod(argv[2],NULL);

                       //First try block
				       try{
                           //go to parametric constructor that takes an int
					       signal = new Signal(filenum);
					       if(signal->checkfile == 1){
						       throw 0;
					       }

				       }
				       catch(const char q){
					       cout<<"error found, file is empty"<<endl;
					       return EXIT_FAILURE;

				       }
				       catch(const char* s){
					       cout<<s<<endl;
				       }
				       catch(...){
					       cout<<"generall exceptrion" << endl;
					       return EXIT_FAILURE;
				       }

				       signal->print();
                       //try block to test operations
                       //here it goes to operation function
				       try{
					       signal->operations();
				       }
				       catch(const int s){
					       cerr<<"error found, scale by 0 is not allowed."<< endl;
				       }
				       catch(...){
					       cerr<<"general expection"<<endl;

				       }


			       }
			       else if((strcmp(argv[1],"-f")) == 0){
				       //store the filename, then call the constructor that take a char*
				       strcpy(filename, argv[2]);
                       
                       
                       //same logic as privous one
				       try{
					       signal = new Signal(filename);
					       if(signal->checkfile == 1){
						       throw 0;
					       }
				       }
				       catch(const char q){
					       cout<<"error found, file is empty"<<endl;
					       return EXIT_FAILURE;

				       }
				       catch(const char* s){
					       cout<<s<<endl;
				       }
				       catch(...){
					       cout<<"generall exceptrion" << endl;
					       return EXIT_FAILURE;
				       }



				       signal->print();
				       try{
					       signal->operations();
				       }
				       catch(const int s){
					       cerr<<"error found, scale by 0 is not allowed."<< endl;
				       }
				       catch(...){
					       cerr<<"general expection"<<endl;

				       }
                       
                       //here it to handle the adding of different length
                       //i selected raw_data_12 for test
                       //only if the file opened through command line is file 12
                       //otherwise program will be thrown
				       Signal *signal2 = new Signal(12);
				       Signal *signal3 = new Signal;
                       
                       //try block here, will goes to the handling function i created
				       try{
					       *signal3 = NonMemberAdding(*signal, *signal2);
                           
                           //if nothithign where thrown, printout the datas.
					       while(i < signal3->getLength()){
						       cout<< signal3->modified_datavec[i] << endl;
						       i++;
					       }
				       }
				       catch(bad_addition & ba){
					       ba.msg();
					       cout<<"caught in -f case"<< endl;
				       }

				       catch(...){
					       cout<<"general expection";
				       }


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



