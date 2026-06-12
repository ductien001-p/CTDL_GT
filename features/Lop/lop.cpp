#include "features/Lop/lop.h"
#include "struct/global.h"
#include "Fileio/fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

void themLop(const char *malop, const char *tenlop, int soSV)
{
    if (soLop >= MAX_LOP)
        return;
    if (soSV < 0 || !malop || !tenlop || malop[0] == '\0' || tenlop[0] == '\0')
        return;

    if (timLop(malop) >= 0)
        return;

    dsLop[soLop] = (Lop *)malloc(sizeof(Lop));
    if (dsLop[soLop] == NULL)
        return;

    strncpy(dsLop[soLop]->malop, malop, LEN_MALOP - 1);
    dsLop[soLop]->malop[LEN_MALOP - 1] = '\0';
    strncpy(dsLop[soLop]->tenlop, tenlop, LEN_TENLOP - 1);
    dsLop[soLop]->tenlop[LEN_TENLOP - 1] = '\0';
    dsLop[soLop]->soSV = soSV;
    dsLop[soLop]->dsSV = NULL;
    soLop++;
}

bool themSinhVienVaoLop(const char *malop,
                        const char *masv,
                        const char *ho,
                        const char *ten,
                        int phai,
                        const char *password)
{
    if (!malop || !masv || !ho || !ten || !password)
        return false;

    if (malop[0] == '\0' || masv[0] == '\0' || ho[0] == '\0' || ten[0] == '\0' || password[0] == '\0')
        return false;

    if (!(phai == PHAI_NAM || phai == PHAI_NU))
        return false;

    int idx = timLop(malop);
    if (idx < 0 || !dsLop[idx])
        return false;

    if (timSV(masv))
        return false;

    SinhVien *node = (SinhVien *)malloc(sizeof(SinhVien));
    if (!node)
        return false;

    strncpy(node->masv, masv, LEN_MASV - 1);
    node->masv[LEN_MASV - 1] = '\0';
    strncpy(node->ho, ho, LEN_HO - 1);
    node->ho[LEN_HO - 1] = '\0';
    strncpy(node->ten, ten, LEN_TEN - 1);
    node->ten[LEN_TEN - 1] = '\0';
    node->phai = phai;
    strncpy(node->password, password, LEN_PASS - 1);
    node->password[LEN_PASS - 1] = '\0';
    node->dsDiem = NULL;
    node->tiep = NULL;

    if (!dsLop[idx]->dsSV)
    {
        dsLop[idx]->dsSV = node;
    }
    else
    {
        SinhVien *p = dsLop[idx]->dsSV;
        while (p->tiep)
            p = p->tiep;
        p->tiep = node;
    }

    dsLop[idx]->soSV++;
    return true;
}

void Indanhsachlop()
{
    printf("Danh sach lop:\n");
    for (int i = 0; i < soLop; i++)
    {
        if (dsLop[i] == NULL)
            continue;
        printf("Lop %d: %s %s %d\n", i, dsLop[i]->malop, dsLop[i]->tenlop, dsLop[i]->soSV);
    }
}

void InDanhSachSinhVienTrongLop(const char *malop)
{
    int idx = timLop(malop);
    if (idx < 0 || !dsLop[idx])
    {
        printf("Khong tim thay lop co ma %s\n", malop ? malop : "(null)");
        return;
    }

    printf("Danh sach sinh vien lop %s - %s:\n", dsLop[idx]->malop, dsLop[idx]->tenlop);

    SinhVien *p = dsLop[idx]->dsSV;
    if (!p)
    {
        printf("(Lop chua co sinh vien)\n");
        return;
    }

    int stt = 1;
    while (p)
    {
        printf("%d. %s | %s %s | %s\n",
               stt,
               p->masv,
               p->ho,
               p->ten,
               (p->phai == PHAI_NAM ? "Nam" : "Nu"));
        stt++;
        p = p->tiep;
    }
}