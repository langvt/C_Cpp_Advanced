#include <iostream>

using namespace std;

class Shape {
    protected:
    int canh;
    int chieucao;
    float dientich;
    float chuvi;
    public:
    void calculateArea(int a,int h){
       canh =a ;
       chieucao =h;
       dientich =0.5*a*h;
    }
    void display_S(){
        cout<<"dien tich la: "<<dientich<<endl;
    }

    virtual void calculatePerimeter(int a){
         
        canh = a ;
        chuvi = 3*a;
         
    }
    void display_P(){
        cout<<"chu vi la: "<<chuvi<<endl;
    }
};


class Circle :protected Shape{
    protected:
        int bankinh;
    public:
        void calculateArea(int r){
        dientich = 3.14*r*r;    
        }
        void calculatePerimeter(int r){
       
        chuvi =2*3.14*r;      
    }
};

int main(void){
    Shape tamgiac;
    Circle tron;
    tamgiac.calculatePerimeter(5);
    tamgiac.display_P();

     cout << "-------------" << endl;
    tron.calculatePerimeter(4);
    tron.display_P();

    return 0;


}
