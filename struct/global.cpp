#define GLOBALS_IMPL
#include "struct/global.h"
#include <cstring>
#include <stdio.h>
#include <string>
#include <conio.h>
#include <cctype>
#include <iostream>

using namespace std;

int timLop(const char *malop)
{
    if (!malop)
        return -1;

    for (int i = 0; i < soLop; i++)
    {
        if (!dsLop[i])
            continue;

        if (strcmp(dsLop[i]->malop, malop) == 0)
            return i;
    }

    return -1;
}

int timMon(const char *mamh)
{
    if (!mamh)
        return -1;

    for (int i = 0; i < soMon; i++)
    {
        if (strcmp(dsMon[i].mamh, mamh) == 0)
            return i;
    }

    return -1;
}

SinhVien *timSVTrongLop(const char *malop, const char *masv)
{
    if (!malop || !masv)
        return nullptr;

    int idx = timLop(malop);
    if (idx < 0)
        return nullptr;

    SinhVien *p = dsLop[idx]->dsSV;

    while (p)
    {
        if (strcmp(p->masv, masv) == 0)
            return p;
        p = p->tiep;
    }

    return nullptr;
}

SinhVien *timSV(const char *masv)
{
    if (!masv)
        return nullptr;

    for (int i = 0; i < soLop; i++)
    {
        if (!dsLop[i])
            continue;

        SinhVien *hit = timSVTrongLop(dsLop[i]->malop, masv);
        if (hit)
            return hit;
    }

    return nullptr;
}
