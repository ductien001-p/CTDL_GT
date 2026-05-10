
#ifndef STRUCTS_H
#define STRUCTS_H

#include <pthread.h> /* ThiState dùng mutex */

#define MAX_MON_HOC 300     /* Tối đa môn học trong DS tuyến tính */
#define MAX_LOP 10000       /* Tối đa lớp trong mảng con trỏ      */
#define MAX_CAU_HOI_THI 200 /* Tối đa câu hỏi 1 lần thi           */

/* Độ dài chuỗi      */
#define LEN_MAMH 16
#define LEN_TENMH 128
#define LEN_MALOP 16
#define LEN_TENLOP 64
#define LEN_MASV 16
#define LEN_HO 64
#define LEN_TEN 32
#define LEN_PASS 32
#define LEN_NOIDUNG 512
#define LEN_LUACHON 256

/* Giới tính */
#define PHAI_NAM 0
#define PHAI_NU 1

/* Trạng thái tài khoản */
#define ROLE_SINHVIEN 0
#define ROLE_GIANGVIEN 1

/* 2. MÔN HỌC  —  DS tuyến tính (mảng cố định MAX_MON_HOC)/*/

typedef struct
{
    char mamh[LEN_MAMH];   /* Mã môn học – khoá chính, duy nhất */
    char tenmh[LEN_TENMH]; /* Tên môn học                        */
    int soTinChi;          /* Số tín chỉ (tuỳ chọn, dễ mở rộng) */
    int daXoa;             /* Flag xoá mềm: 0 = còn, 1 = đã xoá */
} MonHoc;

/* 3. KẾT QUẢ BÀI THI  —  DSLK đơn (1 node = 1 câu đã thi)*/
typedef struct KetQuaBaiThi
{
    int idCauHoi;    /* Id câu hỏi trong BST               */
    char tlSinhVien; /* Đáp án SV chọn: 'A','B','C','D'    */
                     /* '\0' = bỏ câu (hết giờ / skip)     */
    char tlDungSai;  /* 1 = đúng, 0 = sai                  */
    struct KetQuaBaiThi *tiep;
} KetQuaBaiThi;

/* 4. ĐIỂM THI  —  DSLK đơn (1 node = điểm 1 môn) */
typedef struct DiemThi
{
    char mamh[LEN_MAMH]; /* Mã môn học tương ứng               */
    float diem;          /* Điểm thi (0.0 – 10.0)              */
    int soCauDung;       /* Số câu trả lời đúng                */
    int tongCau;         /* Tổng số câu đã thi                 */
    int soPhutThi;       /* Số phút thi thực tế được cấp       */
    long thoiGianThi;    /* Unix timestamp lúc thi (time_t)    */

    /* Danh sách chi tiết từng câu đã làm (chức năng h)            */
    KetQuaBaiThi *dsKetQua;

    struct DiemThi *tiep;
} DiemThi;

/*5. SINH VIÊN  —  DSLK đơn (nằm trong 1 Lop) */
typedef struct SinhVien
{
    char masv[LEN_MASV];     /* Mã SV – khoá chính, duy nhất toàn HT */
    char ho[LEN_HO];         /* Họ và tên lót                         */
    char ten[LEN_TEN];       /* Tên (để sắp xếp theo tên)            */
    int phai;                /* PHAI_NAM / PHAI_NU                    */
    char password[LEN_PASS]; /* Mật khẩu (nên hash thực tế)          */

    /* Con trỏ đến DS điểm các môn đã thi                            */
    DiemThi *dsDiem;

    struct SinhVien *tiep;
} SinhVien;

/* 6. LỚP  —  1 phần tử trong mảng con trỏ */
typedef struct
{
    char malop[LEN_MALOP];   /* Mã lớp – khoá chính, duy nhất  */
    char tenlop[LEN_TENLOP]; /* Tên lớp                         */
    int soSV;                /* Số sinh viên hiện có            */
    SinhVien *dsSV;          /* Trỏ đến DSLK sinh viên của lớp  */
} Lop;

/*CÂU HỎI  —  Dữ liệu lưu trong mỗi node BST*/
typedef struct
{
    int id;                    /* Khoá BST – tự tăng, duy nhất        */
    char mamh[LEN_MAMH];       /* Thuộc môn học nào                   */
    char noidung[LEN_NOIDUNG]; /* Nội dung câu hỏi                    */
    char A[LEN_LUACHON];       /* Lựa chọn A                          */
    char B[LEN_LUACHON];       /* Lựa chọn B                          */
    char C[LEN_LUACHON];       /* Lựa chọn C                          */
    char D[LEN_LUACHON];       /* Lựa chọn D                          */
    char dapan;                /* Đáp án đúng: 'A','B','C','D'        */
    int daXoa;                 /* Flag xoá mềm                        */
} CauHoi;

/*NODE BST  —  Bao bọc CauHoi + con trái/phải*/
typedef struct NodeBST
{
    CauHoi data;
    struct NodeBST *trai; /* Id nhỏ hơn */
    struct NodeBST *phai; /* Id lớn hơn */
} NodeBST;

/* 8. THI STATE  —  Trạng thái phiên thi (dùng cho 2 thread)
    Được tạo mới mỗi lần gọi batDauThi() */
typedef struct
{
    int tongPhut;          /* Số phút được cấp                  */
    int giayCon;           /* Giây còn lại – timer ghi, main đọc*/
    volatile int done;     /* Main set=1 khi SV nộp hết câu     */
    volatile int timeUp;   /* Timer set=1 khi hết giờ           */
    pthread_mutex_t mutex; /* Bảo vệ giayCon / done / timeUp    */
} ThiState;

/* Tham số truyền vào thread timer */
typedef struct
{
    ThiState *state;
} TimerArg;

#endif /* STRUCTS_H */