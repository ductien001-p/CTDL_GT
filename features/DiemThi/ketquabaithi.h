#ifndef KETQUABAI_THI_H
#define KETQUABAI_THI_H

#include "../../struct/struct.h"
#include "../../HamHoTro/hamhotro.h"
KetQuaBaiThi *taoKetQua(
    int id,
    char tlSV,
    char dungSai);

void themKetQua(
    DiemThi *dt,
    KetQuaBaiThi *kq);
#endif