/* =============================================================
 * fileio.h  —  Prototype đọc / ghi file nhị phân
 *              Hệ thống Thi Trắc Nghiệm
 * =============================================================
 *
 * CHIẾN LƯỢC LƯU FILE:
 *   Vấn đề cốt lõi: con trỏ (pointer) trong RAM không có ý nghĩa
 *   khi ghi ra file và đọc lại ở lần chạy sau (địa chỉ thay đổi).
 *
 *   Giải pháp áp dụng cho từng DS:
 *   ┌────────────────┬───────────────────────────────────────────┐
 *   │ DS             │ Chiến lược                                │
 *   ├────────────────┼───────────────────────────────────────────┤
 *   │ MonHoc         │ fwrite/fread mảng thẳng (không pointer)   │
 *   │ Lop            │ Ghi metadata lớp, đếm số SV              │
 *   │ SinhVien       │ Ghi dữ liệu SV (không ghi ptr dsDiem)     │
 *   │ DiemThi        │ Ghi sau SV, liên kết bằng MASV            │
 *   │ KetQuaBaiThi   │ Ghi sau DiemThi, liên kết bằng MASV+MAMH  │
 *   │ BST CauHoi     │ Duyệt inorder → file, đọc lại → insert   │
 *   │ nextId         │ 1 số nguyên đơn giản                      │
 *   └────────────────┴───────────────────────────────────────────┘
 *
 * ĐỊNH DẠNG FILE NHỊ PHÂN:
 *   Mỗi file bắt đầu bằng FILE_HEADER để kiểm tra tính hợp lệ.
 *   Sau đó là dữ liệu theo từng record.
 *
 * TRẢ VỀ:
 *   Các hàm lưu/tải trả về:
 *     FILE_OK      (0)  — thành công
 *     FILE_ERR_OPEN(-1) — không mở được file
 *     FILE_ERR_DATA(-2) — dữ liệu bị hỏng / sai header
 *     FILE_ERR_MEM (-3) — không cấp phát được bộ nhớ
 * ============================================================= */

#ifndef FILEIO_H
#define FILEIO_H

#include "struct.h"
#include "global.h"
#include <stdio.h>

/* -------------------------------------------------------------
 * MÃ TRẢ VỀ
 * ------------------------------------------------------------- */
#define FILE_OK 0
#define FILE_ERR_OPEN (-1)
#define FILE_ERR_DATA (-2)
#define FILE_ERR_MEM (-3)

/* -------------------------------------------------------------
 * MAGIC NUMBER kiểm tra header file
 * Thay đổi khi cấu trúc dữ liệu thay đổi (version mới)
 * ------------------------------------------------------------- */
#define FILE_MAGIC_MON 0x4D4F4E01u    /* 'MON\x01' */
#define FILE_MAGIC_LOP 0x4C4F5001u    /* 'LOP\x01' */
#define FILE_MAGIC_SV 0x53563001u     /* 'SV0\x01' */
#define FILE_MAGIC_DIEM 0x44494501u   /* 'DIE\x01' */
#define FILE_MAGIC_KQBT 0x4B51425401u /* 'KQBT\x01'*/
#define FILE_MAGIC_BST 0x42535401u    /* 'BST\x01' */
#define FILE_MAGIC_ID 0x49443001u     /* 'ID0\x01' */

/* Header chung đầu mỗi file */
typedef struct
{
    unsigned int magic; /* Magic number xác định loại file     */
    int version;        /* Phiên bản cấu trúc (hiện tại = 1)  */
    int soRecord;       /* Số record đã ghi vào file           */
    long checksum;      /* Tổng kiểm tra đơn giản              */
} FileHeader;

/* =============================================================
 * NHÓM 1: MÔN HỌC
 *   File: data/monhoc.bin
 *   Cấu trúc: FileHeader | MonHoc[0] | MonHoc[1] | ...
 * ============================================================= */

/**
 * luuDsMonHoc() — Ghi toàn bộ dsMon[] ra file.
 *   Ghi cả record daXoa=1 để giữ nguyên cấu trúc mảng.
 * @return FILE_OK hoặc mã lỗi
 */
int luuDsMonHoc(const char *duongDan);

/**
 * taiDsMonHoc() — Đọc file và khôi phục dsMon[], soMon.
 *   Kiểm tra magic number, version trước khi đọc data.
 * @return FILE_OK hoặc mã lỗi
 */
int taiDsMonHoc(const char *duongDan);

/* =============================================================
 * NHÓM 2: LỚP VÀ SINH VIÊN
 *   Hai DS này liên kết nhau nên lưu/tải cùng nhóm.
 *
 *   File lop:     data/lop.bin
 *   File sinhvien: data/sinhvien.bin
 *
 *   Định dạng data/lop.bin:
 *     FileHeader
 *     [soLop lần] {
 *       char malop[LEN_MALOP]
 *       char tenlop[LEN_TENLOP]
 *       int  soSV
 *     }
 *
 *   Định dạng data/sinhvien.bin:
 *     FileHeader
 *     [tổng số SV lần] {
 *       char malop[LEN_MALOP]   <- để biết SV thuộc lớp nào
 *       char masv[LEN_MASV]
 *       char ho[LEN_HO]
 *       char ten[LEN_TEN]
 *       int  phai
 *       char password[LEN_PASS]
 *     }
 * ============================================================= */

/**
 * luuDsLop() — Ghi metadata của các lớp (không ghi SV).
 */
int luuDsLop(const char *duongDan);

/**
 * taiDsLop() — Đọc file và khôi phục dsLop[], soLop.
 *   Cấp phát Lop mới cho mỗi record, dsSV = NULL ban đầu.
 */
int taiDsLop(const char *duongDanLop);

/**
 * luuDsSinhVien() — Ghi toàn bộ SV của mọi lớp.
 *   Mỗi record ghi kèm malop để liên kết khi load lại.
 *   Không ghi dsDiem (lưu riêng).
 */
int luuDsSinhVien(const char *duongDan);

/**
 * taiDsSinhVien() — Đọc file SV, cấp phát node, móc vào đúng lớp.
 *   Phải gọi taiDsLop() trước để dsLop[] đã có các Lop.
 *   dsDiem của mỗi SV sẽ = NULL, chờ taiDsDiem() móc vào.
 */
int taiDsSinhVien(const char *duongDan);

/* =============================================================
 * NHÓM 3: ĐIỂM THI VÀ KẾT QUẢ CHI TIẾT
 *
 *   File diem:  data/diem.bin
 *   File kqbt:  data/ketqua.bin
 *
 *   Định dạng data/diem.bin:
 *     FileHeader
 *     [số node DiemThi lần] {
 *       char masv  [LEN_MASV]   <- khoá liên kết
 *       char mamh  [LEN_MAMH]
 *       float diem
 *       int   soCauDung
 *       int   tongCau
 *       int   soPhutThi
 *       long  thoiGianThi
 *     }
 *
 *   Định dạng data/ketqua.bin:
 *     FileHeader
 *     [số node KetQuaBaiThi lần] {
 *       char masv  [LEN_MASV]   <- liên kết SV
 *       char mamh  [LEN_MAMH]   <- liên kết DiemThi
 *       int  idCauHoi
 *       char tlSinhVien
 *       char tlDungSai
 *     }
 * ============================================================= */

/**
 * luuDsDiem() — Ghi tất cả DiemThi của mọi SV trong mọi lớp.
 */
int luuDsDiem(const char *duongDan);

/**
 * taiDsDiem() — Đọc file, cấp phát DiemThi, móc vào SV tương ứng.
 *   Phải gọi taiDsSinhVien() trước.
 */
int taiDsDiem(const char *duongDan);

/**
 * luuDsKetQua() — Ghi tất cả KetQuaBaiThi của mọi DiemThi.
 */
int luuDsKetQua(const char *duongDan);

/**
 * taiDsKetQua() — Đọc file, cấp phát node, móc vào DiemThi tương ứng.
 *   Phải gọi taiDsDiem() trước.
 */
int taiDsKetQua(const char *duongDan);

/* =============================================================
 * NHÓM 4: CÂY BST CÂU HỎI
 *
 *   File: data/cauhoi.bin
 *   Chiến lược: duyệt inorder (id tăng dần) → ghi từng CauHoi.
 *   Khi load: đọc lần lượt → gọi bstInsert() để xây lại cây cân.
 *   (Do inorder → id tăng dần, cây sẽ lệch phải → nên dùng
 *    insertion ngẫu nhiên hoặc balanced BST khi mở rộng sau.)
 *
 *   Định dạng data/cauhoi.bin:
 *     FileHeader
 *     [số node lần] {
 *       CauHoi data    <- struct đặc (không có pointer)
 *     }
 * ============================================================= */

/**
 * luuBST() — Duyệt inorder gocBST, ghi từng CauHoi ra file.
 *   Ghi cả node daXoa=1 để nextId không bị lệch.
 */
int luuBST(const char *duongDan);

/**
 * taiBST() — Đọc file, insert từng CauHoi vào BST.
 *   Tự động cập nhật nextId = max(id đọc được) + 1.
 */
int taiBST(const char *duongDan);

/* =============================================================
 * NHÓM 5: NEXT ID
 *   File: data/nextid.bin — chỉ 1 số nguyên
 * ============================================================= */

/**
 * luuNextId() — Ghi nextId ra file.
 */
int luuNextId(const char *duongDan);

/**
 * taiNextId() — Đọc nextId từ file.
 *   Nếu file không tồn tại, giữ nguyên nextId = 1.
 */
int taiNextId(const char *duongDan);

/* =============================================================
 * NHÓM 6: HÀM TIỆN ÍCH TỔNG HỢP
 * ============================================================= */

/**
 * luuTatCa() — Gọi tuần tự tất cả hàm lưu.
 *   Dùng đường dẫn từ globals.h (FILE_LOP, FILE_MON, ...).
 *   In thông báo lỗi nếu có bất kỳ hàm nào thất bại.
 * @return số lượng lỗi (0 = thành công hoàn toàn)
 */
int luuTatCa(void);

/**
 * taiTatCa() — Gọi tuần tự tất cả hàm tải theo đúng thứ tự phụ thuộc:
 *   MonHoc → Lop → SinhVien → Diem → KetQua → BST → NextId
 * @return số lượng lỗi (0 = thành công hoàn toàn)
 */
int taiTatCa(void);

/**
 * taoThuMucData() — Tạo thư mục data/ nếu chưa có (portable).
 * @return 0 nếu OK, -1 nếu lỗi tạo thư mục
 */
int taoThuMucData(void);

/**
 * inLoi() — In thông báo lỗi ra stderr, kèm tên file và mã lỗi.
 *   Dùng nội bộ bởi các hàm lưu/tải.
 */
void inLoi(const char *tenHam, const char *duongDan, int maLoi);

/* =============================================================
 * NHÓM 7: GIẢI PHÓNG BỘ NHỚ
 *   Gọi khi thoát chương trình để tránh memory leak.
 * ============================================================= */

/** Giải phóng toàn bộ DSLK SV của 1 lớp (đệ quy DiemThi + KetQua) */
void giaiPhongDsSV(SinhVien *dau);

/** Giải phóng DSLK DiemThi của 1 SV (đệ quy KetQuaBaiThi) */
void giaiPhongDsDiem(DiemThi *dau);

/** Giải phóng DSLK KetQuaBaiThi của 1 DiemThi */
void giaiPhongDsKetQua(KetQuaBaiThi *dau);

/** Giải phóng toàn bộ BST (đệ quy hậu thứ tự) */
void giaiPhongBST(NodeBST *goc);

/** Giải phóng tất cả: gọi các hàm trên theo đúng thứ tự */
void giaiPhongTatCa(void);

#endif /* FILEIO_H */