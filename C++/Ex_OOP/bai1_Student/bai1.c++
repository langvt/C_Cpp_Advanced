#include <iostream>
#include <string>

using namespace std;

class Student{
    private:
    string name;
    int old;
    float score;
    public:
    Student(string ten,int tuoi,float diem ) : name(ten),old(tuoi),score(diem){}
   
    void displayInfo(){
        cout<<"ten: "<<name<<endl;
        cout<<"tuoi: "<<old<<endl;
        cout<<"diem: "<<score<<endl;

    }
};

int main(void){
    
    Student st("thai",30,9.9);
    st.displayInfo();

    return 0;

}

