/* =============================================================
 * globals.h  —  Khai báo biến toàn cục hệ thống Thi Trắc Nghiệm
 * =============================================================
 *
 * QUY TẮC SỬ DỤNG:
 *   • Đúng 1 file .c định nghĩa biến bằng cách:
 *         #define GLOBALS_IMPL
 *         #include "globals.h"
 *     (chọn main.c)
 *
 *   • Mọi file .c còn lại chỉ cần:
 *         #include "globals.h"
 *     → nhận extern declaration, không tạo bản sao.
 *
 * Cơ chế này tránh lỗi "multiple definition" khi link.
 * ============================================================= */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "struct.h"
#include <stdio.h>

/* -------------------------------------------------------------
 * MACRO phân biệt ĐỊNH NGHĨA vs KHAI BÁO
 * ------------------------------------------------------------- */
#ifdef GLOBALS_IMPL
#define EXTERN /* định nghĩa thật sự trong main.c  */
#define INIT(...) = __VA_ARGS__
#else
#define EXTERN extern
#define INIT(...)
#endif

/* =============================================================
 * A. DANH SÁCH LỚP  —  mảng con trỏ
 *    Mỗi phần tử là con trỏ tới 1 Lop được cấp phát động.
 *    dsLop[i] = NULL nếu chưa dùng.
 * ============================================================= */
EXTERN Lop *dsLop[MAX_LOP] INIT({NULL});
EXTERN int soLop INIT(0);
/* soLop = số lớp thực sự đang có (không đếm NULL) */

/* =============================================================
 * B. DANH SÁCH MÔN HỌC  —  mảng tuyến tính (giá trị, không pointer)
 *    Dùng field daXoa=1 để xoá mềm, tránh dịch chuyển mảng.
 * ============================================================= */
EXTERN MonHoc dsMon[MAX_MON_HOC] INIT({0});
EXTERN int soMon INIT(0);
/* soMon = số phần tử đang dùng (gồm cả daXoa=1) */

/* =============================================================
 * C. GỐC CÂY BST CÂU HỎI
 *    Toàn bộ câu hỏi của mọi môn chung 1 BST, phân biệt qua mamh.
 * ============================================================= */
EXTERN NodeBST *gocBST INIT(NULL);

/* =============================================================
 * D. BỘ ĐẾM ID CÂU HỎI  —  tự tăng
 *    Khi thêm câu hỏi mới: id = nextId, rồi nextId++.
 *    Khi load từ file: nextId = max(id đã load) + 1.
 * ============================================================= */
EXTERN int nextId INIT(1);

/* =============================================================
 * E. PHÂN QUYỀN  —  cờ isAdmin
 *    0 = sinh viên đang đăng nhập
 *    1 = giảng viên (tài khoản GV/GV)
 * ============================================================= */
EXTERN int isAdmin INIT(0);

/* =============================================================
 * F. SINH VIÊN ĐANG ĐĂNG NHẬP
 *    NULL nếu là giảng viên hoặc chưa đăng nhập.
 *    Trỏ thẳng vào node trong dsLop (không cấp phát riêng).
 * ============================================================= */
EXTERN SinhVien *svDangNhap INIT(NULL);

/* =============================================================
 * G. CỜ TRẠNG THÁI HỆ THỐNG  (tiện ích)
 * ============================================================= */

/* Dữ liệu đã thay đổi nhưng chưa lưu file → nhắc người dùng  */
EXTERN int daCoDuLieuThayDoi INIT(0);

/* =============================================================
 * H. ĐƯỜNG DẪN FILE LƯU TRỮ  (tập trung 1 chỗ dễ thay đổi)
 * ============================================================= */
EXTERN const char *FILE_LOP INIT("data/lop.bin");
EXTERN const char *FILE_MON INIT("data/monhoc.bin");
EXTERN const char *FILE_BST INIT("data/cauhoi.bin");
EXTERN const char *FILE_SV INIT("data/sinhvien.bin");
EXTERN const char *FILE_DIEM INIT("data/diem.bin");
EXTERN const char *FILE_NEXT_ID INIT("data/nextid.bin");

/* =============================================================
 * I. TIỆN ÍCH TRUY TÌM NHANH (helper — khai báo hàm toàn cục)
 *    Các hàm này được implement trong file tương ứng,
 *    đặt prototype ở đây để mọi module đều dùng được.
 * ============================================================= */

/* Tìm lớp theo mã lớp, trả về index trong dsLop hoặc -1 */
int timLop(const char *malop);

/* Tìm môn học theo mã môn, trả về index trong dsMon hoặc -1 */
int timMon(const char *mamh);

/* Tìm sinh viên theo mã SV trong toàn bộ hệ thống */
SinhVien *timSV(const char *masv);

/* Tìm sinh viên theo mã SV trong 1 lớp cụ thể */
SinhVien *timSVTrongLop(const char *malop, const char *masv);

/* -------------------------------------------------------------
 * Dọn dẹp macro nội bộ — không để lộ ra ngoài
 * ------------------------------------------------------------- */
#undef EXTERN
#undef INIT

#endif /* GLOBALS_H */