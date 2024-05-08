#include <iostream>
#include <string>

using namespace std;

typedef enum {
        RED,
        GREEN,
        BLUE
} mausac;

class car{
    private:
    int speed;
    mausac color;
    float fuelCapacity;
    public:
    car (int vt, mausac mau, float xang) : speed(vt),color(mau),fuelCapacity(xang) {}

    void accelerate(int tang){
        speed = speed + tang;
        cout<<"toc do sau khi tang la: "<<speed<<endl;
    }

    void brake(int giam){
        speed = speed -giam;
        cout<<"toc do sau khi giam la: "<<speed<<endl;
    }
    void displayInfo(){
        cout<<"speed: "<<speed<<endl;
        cout<<"color: ";
        switch (color){
            case RED:
                cout<<"red\n";
                break;
            case GREEN:
                cout<<"green\n";
                break;
            case BLUE:
            cout<<"blue\n";
            break;
        
        default:
            cout<<"unknow";
            break;
        }
        
        cout<<"fuelCapacity: "<<fuelCapacity<<endl;
    }
};

int main(void){
    car oto(40,RED,4.2);

    oto.displayInfo();
    cout<<"-----------\n"; 
    oto.accelerate(10);
    oto.displayInfo();
    cout<<"-----------\n"; 
    oto.brake(5);
    oto.displayInfo();

}