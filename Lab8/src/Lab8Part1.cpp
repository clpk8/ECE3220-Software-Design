#include <iostream>
#include <math.h>
using namespace std;

class BaseConic {
protected:
    double x;
    double y;
    
public:
    // Notice the default values. They don't need to be 0
    BaseConic(double x0 = 0, double y0 = 0){x = x0; y = y0;}
    virtual ~BaseConic(){};
    void Move(double nx, double ny){x = nx; y = ny;}
    virtual double Area() = 0; // a pure virtual function ==> ABC
    virtual void display() = 0;
    virtual void resize(double scale) = 0; //pure virtual function
};
class Ellipse : public BaseConic {
private:
    double a;     // semi-major axis
    double b;     // semi-minor axis
    double angle; // orientation angle
    
public:
    Ellipse(double x0, double y0, double a0, double b0, double an0);
    ~Ellipse(){}
    virtual double Area() {return 3.1416*a*b;}
    void Rotate(double nang);
    virtual void display();
    void GetVertices();
    virtual void resize(double scale){a+=scale; b+=scale;}
};
void Ellipse::Rotate(double nang){
    angle += nang;
    
}
//I do this because in MAC in having trouble do x0=0;
Ellipse::Ellipse(double x0,double y0,double a0,double b0,double an0) : BaseConic(x0,y0) {
    // x and y are set in the BaseConic constuctor
    a = a0;
    b = b0;
    angle = an0;
}

void Ellipse::display() {
    cout << "x = " << x << ", y = " << y << ", a = " << a << ", b = " << b
    << ", angle = " << angle << ", Area = " << this->Area() << endl;
}

void Ellipse::GetVertices(){
    cout <<"angle is "<< angle <<endl;
    double x1,y1;
    x1 = x*cos(angle) - y*sin(angle);
    y1 = x*sin(angle) - y*cos(angle);
    if(a > b){
        cout<<"vertices are: ("<<x1+a<<","<<y1<<") and ("<<x1-a<<","<<y1<<")."<<endl;
    }
    else{
        cout<<"vertices are: ("<<x1<<","<<y1+b<<") and ("<<x1<<","<<y1-b<<")."<<endl;
        
    }
}
class Circle : public BaseConic {
private:
    double r;     // radius
    
public:
    virtual double Area() {return 3.1416*r*r;}
    Circle(double x0,double y0,double r0) : BaseConic(x0,y0){r = r0;}
    virtual void display();
    bool inside(double x0, double y0);
    virtual void resize(double r0){r += r0;}
};

void Circle::display() {
    cout << "x = " << x << ", y = " << y << ", r = " << r
    << ", Area = " << this->Area() << endl;
}

bool Circle::inside(double x0, double y0){
    double xrange1 = x+r;
    double xrange2 = x-r;
    double yrange1 = y+r;
    double yrange2 = y-r;
    
    if(x0 <= xrange1 && x0 >= xrange2 && y0 <= yrange1 && y0 >= yrange2){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    cout<<"-------------------Ellipse test-----------------------"<<endl;
    Ellipse e1(5,3,3,4,10);
    e1.display();
    e1.GetVertices();
    e1.resize(1.8);
    e1.display();
    e1.GetVertices();
    e1.Rotate(13);
    e1.display();
    e1.GetVertices();
    
    cout<<"-------------------Circle test-----------------------"<<endl;
    Circle c0(0,1,10);
    c0.display();
    cout << "is (3,5) inside? 1 of yes 2 for no:" <<c0.inside(3, 5) << endl;
    cout << "is (18,-7) inside? 1 of yes 2 for no:" <<c0.inside(18, -7) << endl;
    cout << "is (11,-10) inside? 1 of yes 2 for no:" <<c0.inside(11, -10) << endl;
    cout << "is (-10,11) inside? 1 of yes 2 for no:" <<c0.inside(-10, 11) << endl;
    c0.resize(30);
    cout << "==================after rezide=====================" <<endl;
    cout << "is (11,-10) inside? 1 of yes 2 for no:" <<c0.inside(11, -10) << endl;
    cout << "is (18,-7) inside? 1 of yes 2 for no:" <<c0.inside(18, -7) << endl;
    
    c0.display();
    
    //create ABC
    // BaseConic b(1,3); give me error stating it is a abstract class
    
    
    cout<<"-------------------ABC pointers-----------------------"<<endl;
    BaseConic *bptr1 = &e1;
    BaseConic *bptr2 = &c0;
    BaseConic &bref1 = e1;
    
    bptr1->display();
    bref1.display();
    bptr2->display();
    
    BaseConic *bptr3 = new Ellipse(1,1,2,3,0.8);
    bptr3->display();
    bptr3->Move(3, 4);
    bptr3->display();
    bptr3->resize(13);
    bptr3->display();
    
    cout<<"changed value by pointer"<<endl;
    bptr1->Move(13, 23);
    bptr1->display();
    e1.display();
    
    cout<<"changed value by reference"<<endl;
    bref1.Move(3, 4);
    bptr1->display();
    
    
    cout<<"-------------------ABC operation to circle-----------------------"<<endl;
    
    BaseConic *bptr4 = new Circle(3,3,10);
    bptr4->display();
    bptr4->resize(-2);
    bptr4->display();
    
    delete bptr3;
    delete bptr4;
}






