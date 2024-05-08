#include <iostream>
#include <string>
#include <vector>

#define in 0
#define intb 1
#define add 2
#define del 3
define  fix 4


 

using namespace std;

class sinhvien {
protected:
    string tensv;
    int tuoisv;
    int idsv;
    float diemtoansv;
    float diemlysv;
    float diemhoasv;
    float diemtrungbinhsv;

public:
    sinhvien() : tuoisv(0), idsv(0), diemtoansv(0.0), diemlysv(0.0), diemhoasv(0.0), diemtrungbinhsv(0.0) {}

    sinhvien(string name, int old, int id, float diemtoan, float diemly, float diemhoa)
        : tensv(name), tuoisv(old), idsv(id), diemtoansv(diemtoan), diemlysv(diemly), diemhoasv(diemhoa) {}

    void nhapthongtinsv() {
        cout << "Nhap ten sinh vien: ";
        cin.ignore();
        getline(cin, tensv);

        cout << "Nhap tuoi sinh vien: ";
        cin >> tuoisv;

        do {
        cout << "Nhap diem toan sinh vien (0>>10): ";
        cin >> diemtoansv;
        } while (diemtoansv < 0 || diemtoansv >10 );
        
       

        do {
            cout << "Nhap diem ly sinh vien (0>>10): ";
            cin >> diemlysv;
        } while (diemlysv < 0 || diemlysv > 10);

        do {
            cout << "Nhap diem hoa sinh vien (0>>10): ";
            cin >> diemhoasv;
        } while (diemhoasv < 0 || diemhoasv > 10);
    }

    float diemtrungbinh() {
        diemtrungbinhsv = (diemtoansv + diemlysv + diemhoasv) / 3;
        return diemtrungbinhsv;
    }

    string layXepLoai()  {
        float dtb = diemtrungbinh();
        if (dtb > 8) {
            return "Gioi";
        } else if (dtb >= 6.5 && dtb < 8) {
            return "Kha";
        } else {
            return "TB";
        }
    }

    string layThongTin()  {
        return "Ten: " + tensv + "\nTuoi: " + to_string(tuoisv) + "\nID: " + to_string(idsv) +
               "\nDiem Toan: " + to_string(diemtoansv) + "\nDiem Ly: " + to_string(diemlysv) +
               "\nDiem Hoa: " + to_string(diemhoasv) + "\nDiem Trung Binh: " + to_string(diemtrungbinhsv) +
               "\nXep loai: " + layXepLoai();
    }

    int layIdSV()  {
        return idsv;
    }
    void setIdSV(int newId) {
        idsv = newId;
    }
 
};

class danhsachSV {
private:
    vector<sinhvien> danhsachsinhvien;
    static int maxId ;
    

public:
   
    void xoasv(int id) {
        int n = danhsachsinhvien.size();
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (danhsachsinhvien[i].layIdSV() == id) {
            found = true;
             // Xóa sinh viên tại vị trí i
            danhsachsinhvien.erase(danhsachsinhvien.begin() + i);
             cout << "Da xoa sinh vien co ID " << id << endl;

            break; // Kết thúc vòng lặp khi tìm thấy sinh viên cần sửa
            }   
        }  
        if (!found) {
        cout << "Khong tim thay sinh vien co ID " << id << endl;   
        }

    }

    void suaThongTinSV(int id) {
        int n = danhsachsinhvien.size();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (danhsachsinhvien[i].layIdSV() == id) {
                found = true;
                cout << "Nhap thong tin moi cho sinh vien:\n";
                sinhvien svMoi;
                svMoi.nhapthongtinsv();
                svMoi.diemtrungbinh();
                danhsachsinhvien[i] = svMoi;
                cout << "Da cap nhat thong tin cho sinh vien co ID " << id << endl;

                break; // Kết thúc vòng lặp khi tìm thấy sinh viên cần sửa
            }
        }

        if (!found) {
            cout << "Khong tim thay sinh vien co ID " << id << endl;
        }
    }


    void sapXepTheoDiemTB() {
        int n = danhsachsinhvien.size();
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                 
                if (danhsachsinhvien[j].diemtrungbinh() > danhsachsinhvien[j + 1].diemtrungbinh()) {
                    // Hoán đổi vị trí
                    sinhvien temp = danhsachsinhvien[j];
                    danhsachsinhvien[j] = danhsachsinhvien[j + 1];
                    danhsachsinhvien[j + 1] = temp;
                }
            }
        }
    }

    void inThongTinDanhSach() const {
        for (auto sv : danhsachsinhvien) {
            cout << sv.layThongTin() << endl;
            cout << "-------------" << endl;
        }
    }

    void nhapThemSV() {
        sinhvien sv;
        maxId++;
        sv.setIdSV(maxId);
        sv.nhapthongtinsv();
        sv.diemtrungbinh();
        danhsachsinhvien.push_back(sv);
    }
};

int danhsachSV::maxId = 0;

int main() {
    danhsachSV dssv;
    int nhapkey;
    
    int soluongsv;

    do {
        cout << "Nhap so luong sinh vien (khong duoc am): ";
        cin >> soluongsv;
    } while (soluongsv < 0);

    for (int i = 0; i < soluongsv; i++) {
        dssv.nhapThemSV();
    }
    cout << "Vui long lam theo huong dan: "<< endl;
    cout << "Nhap 0:In ra danh sach sinh vien "<< endl;
    cout << "Nhap 1:In ra danh sach sinh vien theo diem TB"<< endl;
    cout << "Nhap 2:them sinh vien va in ra theo diem TB"<< endl;
    cout << "Nhap 3:xoa sinh vien va in ra theo diem TB"<< endl;
    cout << "Nhap 4:sua sinh vien va in ra theo diem TB"<< endl;
    cout << "Nhap 5:thoat chuong trinh"<< endl;
    cin>>nhapkey;
    switch (nhapkey)
    {
    case  in:
        cout << "Danh sach sinh vien:\n";
        dssv.inThongTinDanhSach();
        break;
    case  intb:
        dssv.sapXepTheoDiemTB();
        cout << "Danh sach sinh vien sau khi sap xep theo diem trung binh:\n";
        dssv.inThongTinDanhSach();
        break;
    case add:
        dssv.nhapThemSV();        
        break;    
    
    default:
        break;
    }




  

    return 0;
}
