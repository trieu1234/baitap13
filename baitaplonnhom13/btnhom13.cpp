#include <iostream>
#include <string>
#include <iomanip>  
using namespace std;

struct SeatNode {
    int seatNumber;
    bool isBooked;
    string classType;
    long long tien;  
    string idCard;    
    string ten;
    string gioitinh;
    int tuoikh;
    string idCardNumber; 
    SeatNode* left;
    SeatNode* right;

    SeatNode(int seatNum, const string& type, long long seatTien)  
        : seatNumber(seatNum), isBooked(false), classType(type), tien(seatTien), tuoikh(0), left(NULL), right(NULL) {}
};

long long tinhgia(long long giabth, int tuoi) {
    if (tuoi >= 12) {
        return giabth;
    } else if (tuoi>= 2) {
        return giabth * 0.75; 
    } else {
        return 100;  
    }
}

SeatNode* insertSeat(SeatNode* node, int seatNumber, const string& classType, long long tien) {
    if (node == NULL) {
        return new SeatNode(seatNumber, classType, tien);
    }
    if (seatNumber < node->seatNumber) {
        node->left = insertSeat(node->left, seatNumber, classType, tien);
    } else if (seatNumber > node->seatNumber) {
        node->right = insertSeat(node->right, seatNumber, classType, tien);
    }
    return node;
}

SeatNode* findSeat(SeatNode* node, int seatNumber) {
    if (node == NULL || node->seatNumber == seatNumber) {
        return node;
    }
    if (seatNumber < node->seatNumber) {
        return findSeat(node->left, seatNumber);
    }
    return findSeat(node->right, seatNumber);
}

void bookSeat(SeatNode* root, int seatNumber, const string& idCard, const string& idCardNumber, const string& ten, const string& gioitinh, int tuoi) {
    SeatNode* seat = findSeat(root, seatNumber);
    if (seat == NULL) {
        cout << "Khong tim thay ghe so " << seatNumber << ".\n";
    } else if (seat->isBooked) {
        cout << "Ghe so " << seatNumber << " da duoc dat truoc.\n";
    } else if (idCard.empty() || (idCard != "CCCD" && idCard != "HoChieu" && idCard != "GiayKhaiSinh")) {
        cout << "Khong the dat ve vi thieu giay to hop le (CCCD, Hochieu, Giaykhaisinh).\n";
    } else {
        seat->isBooked = true;
        seat->idCard = idCard;
        seat->idCardNumber = idCardNumber;
        seat->ten = ten;
        seat->gioitinh = gioitinh;
        seat->tuoikh = tuoi;
        long long giacuoi = tinhgia(seat->tien, tuoi);
        cout << "Da dat thanh cong ghe so " << seatNumber << " (Hang: " << seat->classType << ", Gia: " << giacuoi
             << ") cho " << ten << " (" << gioitinh << ", Tuoi: " << tuoi << ").\n";
    }
}

void cancelSeat(SeatNode* root, int seatNumber) {
    SeatNode* seat = findSeat(root, seatNumber);
    if (seat == NULL) {
        cout << "Khong tim thay ghe so " << seatNumber << ".\n";
    } else if (!seat->isBooked) {
        cout << "Ghe so " << seatNumber << " chua duoc dat truoc.\n";
    } else {
        seat->isBooked = false;
        seat->idCard.clear();
        seat->idCardNumber.clear();
        seat->ten.clear();
        seat->gioitinh.clear();
        seat->tuoikh = 0;
        cout << "Da huy dat ghe so " << seatNumber << " (Hang: " << seat->classType << ").\n";
    }
}

void displaySeats(SeatNode* node) {
    if (node == NULL) return;
    displaySeats(node->left);
    cout << "Ghe so " << node->seatNumber << " (Hang: " << node->classType << ", Gia: " << node->tien << "): " 
         << (node->isBooked ? "Da dat" : "Trong");
    if (node->isBooked) {
        cout << " - Khach hang: " << node->ten << ", (" << node->gioitinh << ", Tuoi: " << node->tuoikh
             << ", CCCD/Ho chieu/Giay khai sinh: " << node->idCard << " - So: " << node->idCardNumber << ")";
    }
    cout << endl;
    displaySeats(node->right);
}

void showAllSeats(SeatNode* root) {
    displaySeats(root);
}

void ghedavachuadat(SeatNode* root, int& tongdat, int& tongchuadat) {
    if (root == NULL) return;

    if (root->isBooked) {
       tongdat++;
    } else {
        tongchuadat++;
    }

    ghedavachuadat(root->left, tongdat, tongchuadat);
    ghedavachuadat(root->right, tongdat, tongchuadat);
}

int main() {
    SeatNode* seatRoot = NULL;
    for (int i = 1; i <= 30; ++i) {
        seatRoot = insertSeat(seatRoot, i, "Thuong gia", 1500000);  
    }
    for (int i = 31; i <= 70; ++i) {
        seatRoot = insertSeat(seatRoot, i, "Pho thong dac biet", 1000000);
    }
    for (int i = 71; i <= 120; ++i) {
        seatRoot = insertSeat(seatRoot, i, "Pho thong", 700000);
    }

    int choice, seatNumber, customerAge;
    string idCard, idCardNumber, ten, gioitinh;
    do {
        cout << "\n--- QUAN LY GHE ---\n";
        cout << "1. Hien thi trang thai ghe\n";
        cout << "2. Dat ghe\n";
        cout << "3. Huy dat ghe\n";
        cout << "4. Xem so ghe da dat va chua dat\n";
        cout << "5. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showAllSeats(seatRoot);
                break;
            case 2:
                cout << "Nhap so ghe muon dat (1 - 120): ";
                cin >> seatNumber;
                if (seatNumber < 1 || seatNumber > 120) {
                    cout << "So ghe khong hop le!\n";
                    break;
                }
                cout << "Nhap thong tin giay to (CCCD, HoChieu hoac GiayKhaiSinh) khach hang (bat buoc): ";
                cin.ignore();
                getline(cin, idCard);
                if (idCard.empty() || (idCard != "CCCD" && idCard != "HoChieu" && idCard != "GiayKhaiSinh")) {
                    cout << "Khong the dat ve vi thieu giay to hop le.\n";
                    break;
                }
                cout << "Nhap so " << idCard << ": ";
                cin >> idCard;
                cout << "Nhap ten khach hang: ";
                cin >> ten;
                cout << "\nNhap gioi tinh khach hang: ";
                cin >> gioitinh;
                cout << "\nNhap tuoi khach hang: ";
                cin >> customerAge;
                bookSeat(seatRoot, seatNumber, idCard, idCardNumber, ten, gioitinh, customerAge);
                break;
            case 3:
                cout << "Nhap so ghe muon huy (1 - 120): ";
                cin >> seatNumber;
                if (seatNumber < 1 || seatNumber > 120) {
                    cout << "So ghe khong hop le!\n";
                    break;
                }
                cancelSeat(seatRoot, seatNumber);
                break;
            case 4: {
                int tongdat = 0, tongchuadat = 0; 
                ghedavachuadat(seatRoot, tongdat, tongchuadat);  
                cout << "So ghe da dat: " << tongdat << endl;
                cout << "So ghe chua dat: " << tongchuadat << endl;
                break;
            }
            case 5:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
