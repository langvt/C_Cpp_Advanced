#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define in 0
#define adddata 1
#define delbook 2
#define addbook 3
#define out 4

class book {
protected:
    string title;
    string author;
    int quantity;
    int id;

public:
    book() : title(""), author(""), quantity(0) {}

    book(string tensach, string tacgia, int soluong, int idsach)
        : title(tensach), author(tacgia), quantity(soluong), id(idsach) {}

    void nhapthongtinsach() {
        cout << "Nhap ten sach: ";
        cin.ignore();
        getline(cin, title);

        cout << "Nhap tac gia: ";
        getline(cin, author);

        cout << "Nhap so luong sach : ";
        cin >> quantity;
        cin.ignore();

    }

    int layidsach() {
        return id;
    }

    void setnewID(int newId) {
        id = newId;
    }

    int soluong() {
        return quantity;
    }

    string layThongTin() {
        return "id:" + to_string(id) + "\nten sach: " + title + "\ntac gia: " + author + "\nSo luong: " + to_string(quantity);
    }
};

class library {
private:
    vector<book> sachtrongthuvien;
    static int maxId;

public:
    void datasach() {
        book bk;
        maxId++;
        bk.nhapthongtinsach();
        bk.setnewID(maxId);     
        sachtrongthuvien.push_back(bk);
    }

    void trasach(int id, int SLsach) {
        int n = sachtrongthuvien.size();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (sachtrongthuvien[i].layidsach() == id) {
                found = true;
                sachtrongthuvien[i].setnewID(sachtrongthuvien[i].soluong() + SLsach);
                cout << "Da cap nhat thong tin sach co ID " << id << endl;
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay sach" << id << endl;
        }
    }

        void muonsach(int id, int SLsach) {
        int n = sachtrongthuvien.size();
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (sachtrongthuvien[i].layidsach() == id) {
                found = true;
                sachtrongthuvien[i].setnewID(sachtrongthuvien[i].soluong()  - SLsach);
                cout << "Da cap nhat thong tin sach co ID " << id << endl;
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay sach" << id << endl;
        }
    }




    void displayAvailableBooks() const {
        for (auto book : sachtrongthuvien) {
            cout << book.layThongTin() << endl;
            cout << "-------------" << endl;
        }
    }
};

int library::maxId = 0;

int main() {
    library thuvien;
    int soluongsach;
    int idsach, soLuong;
    int nhapkey;
    

    do {
        cout << "Vui long nhap database cho thu vien" << endl;
        cout << "so loai sach(>0) :";
        cin >> soluongsach;
        
    } while (soluongsach < 0);

    for (int i = 0; i < soluongsach; i++) {
        thuvien.datasach();
    }
    do {
        cout << "Vui long lam theo huong dan: "<< endl;
        cout << "Nhap 0:In ra data sach trong thu vien danh sach  "<< endl;
        cout << "Nhap 1:Danh cho nhan vien add sach vao data "<< endl;
        cout << "Nhap 2:Danh cho KHG muon sach "<< endl;
        cout << "Nhap 3:Danh cho KHG tra sach"<< endl;
        cout << "Nhap 4:thoat chuong trinh"<< endl;
    
    
        cin >> nhapkey;
        switch (nhapkey)
        {
        case in:
            cout << "Data sach trong thu vien:"<< endl;;
            thuvien.displayAvailableBooks();
            break;

        case adddata:
            cout << "Cap nhat them Data:"<< endl;;      
            thuvien.datasach(); 
            thuvien.displayAvailableBooks();  
            break;

        case delbook :
            cout << "vui long nhap id sach va SL muon:"<< endl;;
            cin >> idsach >> soLuong;
            thuvien.trasach(idsach,soLuong);
            thuvien.displayAvailableBooks(); 
            break;

        case addbook:
            cout << "vui long nhap id sach va SL tra:"<< endl;;
            cin >> idsach >> soLuong;
            thuvien.trasach(idsach,soLuong);
            thuvien.displayAvailableBooks(); 
            break;
        
        default:
            cout << "Cam on da su dung dich vu"<< endl;
            break;
        }
    }
    while (nhapkey!=out);
    

    return 0;
}
