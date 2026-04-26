// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan5

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include <limits>
#include <windows.h>
using namespace std;
// COMPOSITION DATE
class Date
{
    private:
    int ngay;
    int thang;
    int nam;
    static int currentYear;

    public:
    // constructor
    Date(int day = 1, int month = 1, int year = 1970) : ngay(day), thang(month), nam(year){
        // logic kiểm tra
        dateValid(day, month, year);
    }; 

    // Hàm kiểm tra tính đúng đắn của dữ liệu
    void dateValid(int day, int month, int year)
    {
        // Kiểm tra cả 3 dữ liệu tổng quát
        if(isValid(day, 1, 31) && isValid(month, 1, 12) && isValid(year, 1970, 2026))
        {
            int ngayToiDa;
            // kiểm tra bước 2
            if(month == 2)
            {
                ngayToiDa = (namNhuan(year)) ? 29 : 28;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
            else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            {
                ngayToiDa = 31;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
            else
            {
                ngayToiDa = 30;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
        }
        else{
            throw invalid_argument("Lỗi: Thông tin ngày tháng năm không hợp lệ.");
        }
    }
    // Năm nhuận
    bool namNhuan(int year)
    {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? true : false;  
    };
    // display - truyền thống
    void dateDisplay()
    {
        cout << "Ngày " << ngay << " tháng " << thang << " năm " << nam << endl;
    }
    // display - overload
    friend ostream& operator<<(ostream& out, Date &D)
    {
        out << "Ngày " << D.ngay << " tháng " << D.thang << " năm " << D.nam;
        return out;
    }

    // Nhập thông tin - overload
    friend istream& operator>>(istream& in, Date &D)
    {
        int day, month, year;
        cout << "Ngày: "; in >> day;
        cout << "Tháng: "; in >> month;
        cout << "Năm: "; in >> year;

        // kiểm tra tính hợp lệ
        D.dateValid(day, month, year);

        return in;

    }
};
// ABSTRACT CLASS
class GIAODICH
{
    private:
    string maGiaoDich = "Không xác định";
    Date ngayGiaoDich;
    long long donGia = 0;
    public:
    GIAODICH(string &ma_giao_dich, Date &ngay_giao_dich, long long don_gia):maGiaoDich(ma_giao_dich), ngayGiaoDich(ngay_giao_dich), donGia(don_gia)
    {
        // kiểm tra logic
    }
    // Mã giao dịch
    bool setMaGiaoDich(string ma_giao_dich)
    {
        maGiaoDich = ma_giao_dich;
        return 1;
    }
    string getMaGiaoDich()
    {
        return maGiaoDich;
    }
    // Ngày giao dịch
    void 

};