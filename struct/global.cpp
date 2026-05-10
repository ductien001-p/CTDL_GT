#define GLOBALS_IMPL
#include "global.h"
/* =============================================================
 * A. DANH SÁCH LỚP  —  mảng con trỏ
 *    Mỗi phần tử là con trỏ tới 1 Lop được cấp phát động.
 *    dsLop[i] = NULL nếu chưa dùng.
 * ============================================================= */
Lop *dsLop[MAX_LOP] = {NULL};
int soLop = 0;
/* =============================================================
 * B. DANH SÁCH MÔN HỌC  —  mảng tuyến tính (giá trị, không pointer)
 *    Dùng field daXoa=1 để xoá mềm, tránh dịch chuyển mảng.
 * ============================================================= */
MonHoc dsMon[MAX_MON_HOC] = {0};
int soMon = 0;

GiaoVien dsGiaoVien[MAX_GIAO_VIEN] = {0};
int soGiaoVien = 0;
/* =============================================================
 * C. GỐC CÂY BST CÂU HỎI
 *    Toàn bộ câu hỏi của mọi môn chung 1 BST, phân biệt qua mamh.
 * ============================================================= */
NodeBST *gocBST = NULL;
/* =============================================================
 * D. BỘ ĐẾM ID CÂU HỎI  —  tự tăng
 *    Khi load từ file: nextId = max(id đã load) + 1.
 * ============================================================= */
int nextId = 1;
/* =============================================================
 * E. PHÂN QUYỀN  —  cờ isAdmin
 *    0 = sinh viên đang đăng nhập
 *    1 = giảng viên (tài khoản GV/GV)
 * ============================================================= */
int isAdmin = 0;
SinhVien *svDangNhap = NULL; /* Con trỏ đến SV đang đăng nhập (nếu isAdmin=0) */
