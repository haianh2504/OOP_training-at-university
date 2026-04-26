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
#include <cmath>
using namespace std;

// Hàm kiểm tra logic
template<typename T>
bool logicHopLe(T value, T start, T end)
{
    if(start <= value && value <= end)
    {
        return true;
    }
    return false;
}

// COMPOSITION - Luận văn
class LUANVAN
{
    private:
    string tenLuanVan;
    float diemLuanVan;
    public:
    // constructor
    LUANVAN(string tlv = "Không xác định.", float dlv = 0.0) : tenLuanVan(tlv), diemLuanVan(dlv)
    {
        // nếu có tham trị -> kiểm tra logic
        if(!setTenLuanVan(tlv) || !setDiemLuanVan(dlv))
        {
            throw invalid_argument("Lỗi: Khởi tạo luận văn không thành công.");
        }
    };
    // Tên luận văn
    string getTenLuanVan()
    {
        return tenLuanVan;
    }
    bool setTenLuanVan(string tlv)
    {
        if(tlv == " ") return false;
        tenLuanVan = tlv;
        return true;
    };
    // Điểm Luận văn
    float getDiemLuanVan() const
    {
        return diemLuanVan;
    };
    bool setDiemLuanVan(float dlv)
    {
        if(0.0 <= dlv && dlv <= 10.0)
        {
            diemLuanVan = dlv;
            return true;
        }
        // không cập nhật nếu sai
        return false;
    };
    // destructor
    ~LUANVAN(){};
};

// ABSTRACT CLASS - SINH VIÊN
class SINHVIEN{
    protected:
    string hoTen = "Không xác định.";
    string diaChiNha = "Không xác định.";
    int tongTinChi = MIN_TINCHI;
    float diemTrungBinh = MIN_DIEM;
    bool DauTotNghiep;
    // CONST
    // const
    static const int MIN_TINCHI = 0;
    static const int MAX_TINCHI = 150;
    static const float MIN_DIEM = 0.0f;
    static const float MAX_DIEM = 10.0f;
    // constructor
    SINHVIEN(string ht, string dcn, int ttc, float dtb)
    {
        if(!logicHopLe(dtb, MIN_DIEM, MAX_DIEM) || !logicHopLe(ttc, MIN_TINCHI, MAX_TINCHI))
        {
            throw invalid_argument("Lỗi: Khởi tạo sinh viên không thành công.");
        };
        chuanHoaDiem(diemTrungBinh);
    };

    public:
    // Họ tên
    bool setHoTen(string &ht)
    {
        if(ht == " ") return false;
        hoTen = ht;
        return true;
    }
    string getHoTen() const
    {
        return hoTen;
    }
    // Tổng tín chỉ
    bool setTongTinChi(int ttc)
    {
        if(!logicHopLe(ttc, MIN_TINCHI, MAX_TINCHI)) return false;
        tongTinChi = ttc;
        return true;
    };
    int getTinChi() const
    {
        return tongTinChi;
    }
    // Địa chỉ nhà
    bool setDiaChiNha(string &dcn)
    {
        if(dcn == " ") return false;
        diaChiNha = dcn;
        return true;
    }
    string getDiaChiNha() const
    {
        return diaChiNha;
    }
    // Chuẩn hóa điểm
    void chuanHoaDiem(float &diem)
    {
        diem = round(diem*100)/100.0f;
    }
    // Điểm trung bình
    bool setDiemTrungBinh(float dtb)
    {
        if(!logicHopLe(dtb, 0.0f, 10.0f)) return false;
        chuanHoaDiem(dtb);
        diemTrungBinh = dtb;
        return true;
    }
    float getDiemTrungBinh() const
    {
        return diemTrungBinh;
    }

    // Kiểm tra tình trạng tốt nghiệp 
    virtual void KiemTraTotNghiep() = 0;
    // Nhập thông tin
    virtual void nhapThongTin() = 0;
    // Xuất thông tin
    virtual void xuatThongTin() = 0;
    // Destructor
    virtual ~SINHVIEN(){};
};

// SINH VIÊN CAO ĐẲNG
class CAODANG : public SINHVIEN
{
    private:
    // mã số sinh viên cao đẳng
    static long maSoSinhVien;
    float diemThiTotNghiep;
    // const
    static const int TINCHI_TOTNGHIEP = 110;
    static const float DIEMTB_TOTNGHIEP = 5.0f;
    static const float DIEMTHITN_TOTNGHIEP = 5.0f;

    public:
    // constructor
    CAODANG(const string &ht,const string &dcn, int ttc, float dtb, float dttn) : SINHVIEN(ht, dcn, ttc, dtb), diemThiTotNghiep(dttn)
    {
        if(!logicHopLe(dttn, MIN_DIEM, MAX_DIEM))
        {
            throw invalid_argument("Lỗi: Khởi tạo sinh viên cao đẳng không thành công.");
        };
        // nếu thành công
        maSoSinhVien += 1;
        chuanHoaDiem(dtb);
        chuanHoaDiem(dttn);
        // xét tốt nghiệp
        KiemTraTotNghiep();
    }
    // Điểm thi tốt nghiệp
    bool setDiemThiTotNghiep(float dttn)
    {
        if(!logicHopLe(dttn, MIN_DIEM, MAX_DIEM)) return false;
        chuanHoaDiem(dttn);
        diemThiTotNghiep = dttn;
        KiemTraTotNghiep();
        return true;
    };
    float getDiemThiTotNghiep() const
    {
        return diemThiTotNghiep;
    }

    // Xét tình trạng tốt nghiệp
    void KiemTraTotNghiep() override {
        if(tongTinChi >= TINCHI_TOTNGHIEP  && diemTrungBinh >= DIEMTB_TOTNGHIEP && diemThiTotNghiep >= DIEMTHITN_TOTNGHIEP)
        {
            DauTotNghiep = true;
        }
        else DauTotNghiep = false;
    };
    // Nhập thông tin
    void nhapThongTin() override
    {

    };
    // Xuất thông tin
    void xuatThongTin() override
    {

    };

};
// Khởi tạo giá trị mã số sinh viên - CAO ĐẲNG
long CAODANG::maSoSinhVien = 0;

// SINH VIÊN ĐẠI HỌC
class DAIHOC : public SINHVIEN
{
    private:
    // mã số sinh viên đại học
    static long maSoSinhVien;
    LUANVAN luanVan; // luận văn
    // const
    static const int TINCHI_TOTNGHIEP = 145;
    static const float DIEMTHITN_TOTNGHIEP = 5.0f;
    static const float DIEMLUANVAN_TOTNGHIEP = 5.0f;
    static const float MIN_DIEM = 0.0f;
    static const float MAX_DIEM = 10.0f;

    public:
    // constructor
    DAIHOC(string &ht, string &dcn, int ttc, float dtb, const LUANVAN &lv) : SINHVIEN(ht, dcn, ttc, dtb), luanVan(lv)
    {
        if(!logicHopLe(lv.getDiemLuanVan(), MIN_DIEM, MAX_DIEM))
        {
            throw invalid_argument("Lỗi: Khởi tạo sinh viên đại học không thành công.");
        };
        maSoSinhVien += 1;
        // chuẩn hóa điểm trung bình
        chuanHoaDiem(dtb);
        // chuẩn hóa điểm luận văn
        float diemLuanVan = luanVan.getDiemLuanVan();
        chuanHoaDiem(diemLuanVan);
        luanVan.setDiemLuanVan(diemLuanVan);
        // kiểm tra tốt nghiệp
        KiemTraTotNghiep();
    };
    // Luận văn
    // lấy điểm luận văn
    float getDiemLuanVan() const
    {
        return luanVan.getDiemLuanVan();
    }
    
};