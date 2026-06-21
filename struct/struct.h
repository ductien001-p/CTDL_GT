
#ifndef STRUCTS_H
#define STRUCTS_H

#include <pthread.h>

#define MAX_MON_HOC 300
#define MAX_LOP 10000
#define MAX_CAU_HOI_THI 200
#define MAX_GIAO_VIEN 100

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

#define PHAI_NAM 0
#define PHAI_NU 1

#define ROLE_SINHVIEN 0
#define ROLE_GIANGVIEN 1

typedef struct
{
    char mamh[LEN_MAMH];
    char tenmh[LEN_TENMH];
    int soTinChi;
    int soCauHoiThi;
    int soPhutThi;
    int daXoa;
} MonHoc;

typedef struct
{
    MonHoc ds[MAX_MON_HOC];
    int n;
} DSMonHoc;

typedef struct KetQuaBaiThi
{
    int idCauHoi;
    char tlSinhVien;
    char tlDungSai;
    struct KetQuaBaiThi *tiep;
} KetQuaBaiThi;

typedef struct DiemThi
{
    char mamh[LEN_MAMH];
    float diem;
    int soCauDung;
    int tongCau;
    int soPhutThi;
    long thoiGianThi;

    KetQuaBaiThi *dsKetQua;

    struct DiemThi *tiep;
} DiemThi;

typedef struct SinhVien
{
    char masv[LEN_MASV];
    char ho[LEN_HO];
    char ten[LEN_TEN];
    int phai;
    char password[LEN_PASS];

    DiemThi *dsDiem;

    struct SinhVien *tiep;
} SinhVien;

typedef struct
{
    char malop[LEN_MALOP];
    char tenlop[LEN_TENLOP];
    int soSV;
    SinhVien *dsSV;
} Lop;

typedef struct
{
    Lop *ds[MAX_LOP];
    int n;
} DSLop;

typedef struct
{
    int id;
    char mamh[LEN_MAMH];
    char noidung[LEN_NOIDUNG];
    char A[LEN_LUACHON];
    char B[LEN_LUACHON];
    char C[LEN_LUACHON];
    char D[LEN_LUACHON];
    char dapan;
    int daXoa;
} CauHoi;

typedef struct NodeBST
{
    CauHoi data;
    struct NodeBST *trai;
    struct NodeBST *phai;
    int height;
} NodeBST;

typedef struct
{
    int tongPhut;
    int giayCon;
    volatile int done;
    volatile int timeUp;
    pthread_mutex_t mutex;
} ThiState;

typedef struct
{
    ThiState *state;
} TimerArg;

#endif