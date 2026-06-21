#ifndef MONHOC_H
#define MONHOC_H

#include "../../struct/struct.h"

bool themMonHoc(
    DSMonHoc &ds,
    const MonHoc &mh);

bool xoaMonHoc(
    DSMonHoc &ds,
    const char *maMH);

MonHoc *timMonHoc(
    DSMonHoc &ds,
    const char *maMH);

bool suaMonHoc(
    DSMonHoc &ds,
    const char *maMH,
    const MonHoc &moi);

void inDSMonHoc(
    const DSMonHoc &ds);

void inMotMonHoc(
    const MonHoc &mh);

#endif