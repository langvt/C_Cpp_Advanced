#include <iostream>
#include <string>

using namespace std;

    /*  private: chi dung trong class doituong(class cha) va class con va doi tuong object cung khong the truy cap duoc
        protected: class con co the ke thua nhung doi tuong object khong the truy cap duoc
        public: cac class con va doi tuong object co the truy cap duoc */

class DoiTuong 
{

    protected:
        string Ten;
        int Tuoi;
        string GioiTinh;

    public:
        void setThongTin(string ten, string gioitinh, int tuoi);
        void hienthi();
};

void DoiTuong :: setThongTin(string ten, string gioitinh, int tuoi)
{
    Ten = ten;
    GioiTinh = gioitinh;
    Tuoi = tuoi;
}

void DoiTuong :: hienthi()
{
    cout << "Ten: " << Ten<< endl;
    cout << "gioi tinh: " << GioiTinh<< endl;
    cout <<"tuoi: "<< Tuoi << endl;
}

class SinhVien : public DoiTuong
{
    private: 
         int MSSV;

    public:
        void setThongTin(string ten, string gioitinh, int tuoi, int mssv);
        void hienthi();
};


void SinhVien :: setThongTin(string ten, string gioitinh, int tuoi, int mssv)
{
    Ten = ten;
    GioiTinh = gioitinh;
    Tuoi = tuoi;
    MSSV = mssv;
}

void SinhVien :: hienthi()
{
    cout << "Ten: " << Ten<< endl;
    cout << "gioi tinh: " << GioiTinh<< endl;
    cout <<"tuoi: "<< Tuoi << endl;
    cout << "ma so: " << MSSV << endl;
}
int main ()
{
    DoiTuong dt1;
    dt1.setThongTin("x", "nam", 10);
    dt1 .hienthi();
    cout << endl;

    SinhVien sv1;
    sv1 .setThongTin("y", "nu", 11, 101);
    sv1 .hienthi();
}