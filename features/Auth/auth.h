
#ifndef AUTH_H
#define AUTH_H

#include "global.h"

void themTaiKhoanGV(const char *username,
                    const char *password);
bool dangNhap(const char *username, const char *password);

void dangXuat(void);


#endif /* AUTH_H */
