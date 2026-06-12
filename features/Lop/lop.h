#ifndef LOP_H
#define LOP_H

#include "struct/struct.h"
#include "struct/global.h"
#include <stdio.h>

void themLop(const char *malop, const char *tenlop, int soSV);
bool themSinhVienVaoLop(const char *malop,
                        const char *masv,
                        const char *ho,
                        const char *ten,
                        int phai,
                        const char *password);
void Indanhsachlop();
void InDanhSachSinhVienTrongLop(const char *malop);
#endif