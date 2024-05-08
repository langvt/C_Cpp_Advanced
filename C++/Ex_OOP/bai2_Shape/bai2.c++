#include <iostream>

using namespace std;

class Shape {

public:
    virtual void calculateArea() = 0;

    virtual void calculatePerimeter() = 0;
 
};

class Circle : public Shape {
private:
    int bankinh;
    float dientich;
    float chuvi;


public:
    Circle(int r) : bankinh(r) {}
 
    void calculateArea() override {
        dientich = 3.14 * bankinh * bankinh;
        cout << "Dien tich " << dientich << endl;
    }

    void calculatePerimeter() override {
        chuvi = 2 * 3.14 * bankinh;
        cout << "Chu vi: " << chuvi << endl;
    }
};

class Rectangle  : public Shape {
protected:
    int chieudai;
    int chieurong;
    int dientich;
    int chuvi;

public:
    Rectangle(int a,int b) : chieudai(a), chieurong(b) {}

    void calculateArea() override {
        dientich = chieudai * chieurong;
        cout << "Dien tich " << dientich << endl;
    }

    void calculatePerimeter() override {
        chuvi = 2 * (chieudai+chieurong);
        cout << "Chu vi: " << chuvi << endl;
    }
};

int main(void) {
    Circle tron(5);
    Rectangle dai(4,5);
    tron.calculateArea();
    tron.calculatePerimeter();
    cout<<"------------"<<endl;
    dai.calculateArea();
    dai.calculatePerimeter();
    return 0;
}
