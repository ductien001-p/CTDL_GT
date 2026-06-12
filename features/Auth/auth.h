
#ifndef AUTH_H
#define AUTH_H

#include "struct/global.h"

void themTaiKhoanGV(const char *username,
                    const char *password);
bool dangNhap(const char *username, const char *password);

void dangXuat(void);

void hienThongTinDangNhap(void);

#endif /* AUTH_H */
