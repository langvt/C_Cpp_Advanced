#include <iostream>
#include <string>

using namespace std;

class BankAccount{
    private:
       unsigned long accountNumber;
       long long balance;
       string ownername ;

    public:
    BankAccount (unsigned long stk,long long sodu, string ten ) : accountNumber(stk),balance(sodu),ownername(ten)  {}
    void displayInfo(){
        cout<<"accountNumber: "<<accountNumber<<endl;
		cout<<"balance: "<<balance<<endl;
		cout<<"ownerName: "<<ownername<<endl;
    }
    void guitien(long long themtien){
        balance = balance +themtien;
        cout<<"da gui tien OK, so du moi la: "<<balance<<endl;
    }
    void ruttien(long long ruttien){
        
        if((balance>0)&&(balance>=ruttien)) {
            balance = balance -ruttien;
            cout<<"rut tien OK, so du con lai: "<<balance<<endl;
        }
        else{
            cout<<"rut tien NOK,so du khong du, vui long nhap lai"<<endl;    

        }
    }
};
int main(void){
    BankAccount bank(123123,99999,"thai");
    bank.displayInfo();
    cout<<"--------------"<<endl;
    bank.guitien(100000);
    bank.displayInfo();
    cout<<"--------------"<<endl;
    bank.ruttien(10000000);
    bank.displayInfo();
    cout<<"--------------"<<endl;
    bank.ruttien(1000);
    bank.displayInfo();

    return 0;

}

    





 
