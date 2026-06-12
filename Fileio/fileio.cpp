#include "Fileio/fileio.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

static void boKhoangDauCuoi(char *s)
{
    if (!s)
        return;

    char *dst = s;
    while (*dst && std::isspace(static_cast<unsigned char>(*dst)))
        dst++;

    if (dst != s)
        memmove(s, dst, strlen(dst) + 1);

    size_t len = strlen(s);

    while (len > 0 && std::isspace(static_cast<unsigned char>(s[len - 1])))
    {
        s[len - 1] = '\0';
        len--;
    }
}

int docDsGiaoVienTuTxt(const char *duongDan)
{
    FILE *f = fopen(duongDan, "r");
    if (!f)
        return FILE_ERR_OPEN;

    soGiaoVien = 0;

    char buf[384];

    while (fgets(buf, sizeof(buf), f))
    {
        boKhoangDauCuoi(buf);

        if (!buf[0])
            continue;

        if (buf[0] == '#')
            continue;

        /* Chỉ 2 token: đăng nhập + mật khẩu (không chứa khoảng trắng) */
        char user[LEN_MASV], pass[LEN_PASS];

        if (sscanf(buf, "%15s %31s", user, pass) >= 2)
        {
            if (soGiaoVien >= MAX_GIAO_VIEN)
                break;

            strncpy(dsGiaoVien[soGiaoVien].username, user, LEN_MASV - 1);
            dsGiaoVien[soGiaoVien].username[LEN_MASV - 1] = '\0';
            strncpy(dsGiaoVien[soGiaoVien].password, pass, LEN_PASS - 1);
            dsGiaoVien[soGiaoVien].password[LEN_PASS - 1] = '\0';
            soGiaoVien++;
        }
    }

    fclose(f);
    return FILE_OK;
}

int luuDsGiaoVienRaTxt(const char *duongDan)
{
    FILE *f = fopen(duongDan, "w");
    if (!f)
        return FILE_ERR_OPEN;

    fprintf(f, "# dong: tai_khoan mat_khau\n");
    fprintf(f, "# comment bat dau bang # \n");

    for (int i = 0; i < soGiaoVien; i++)
        fprintf(f, "%s %s\n", dsGiaoVien[i].username, dsGiaoVien[i].password);

    fclose(f);
    return FILE_OK;
}

int luuDsLop(const char *duongDan)
{
    FILE *f = fopen(duongDan, "w");
    if (!f)
        return FILE_ERR_OPEN;

    fprintf(f, "# dong: ma_lop ten_lop so_sinh_vien\n");
    fprintf(f, "# comment bat dau bang # \n");
    for (int i = 0; i < soLop; i++)
    {
        if (!dsLop[i])
            continue;
        fprintf(f, "%s %s %d\n", dsLop[i]->malop, dsLop[i]->tenlop, dsLop[i]->soSV);
    }
    fclose(f);
    return FILE_OK;
}   
int taiDsLop(const char *duongDan)
{
    FILE *f = fopen(duongDan, "r");
    if (!f)
        return FILE_ERR_OPEN;

    for (int i = 0; i < soLop; i++)
    {
        free(dsLop[i]);
        dsLop[i] = NULL;
    }
    soLop = 0;

    char buf[384];
    while (fgets(buf, sizeof(buf), f))
    {
        boKhoangDauCuoi(buf);
        if (!buf[0])
            continue;
        if (buf[0] == '#')
            continue;
        char malop[LEN_MALOP], tenlop[LEN_TENLOP];
        int soSV;
        if (sscanf(buf, "%15s %63s %d", malop, tenlop, &soSV) == 3)
        {
            if (soLop >= MAX_LOP)
                break;
            if (soSV < 0)
                continue;

            dsLop[soLop] = (Lop *)malloc(sizeof(Lop));
            if (!dsLop[soLop])
                break;

            strncpy(dsLop[soLop]->malop, malop, LEN_MALOP - 1);
            dsLop[soLop]->malop[LEN_MALOP - 1] = '\0';
            strncpy(dsLop[soLop]->tenlop, tenlop, LEN_TENLOP - 1);
            dsLop[soLop]->tenlop[LEN_TENLOP - 1] = '\0';
            dsLop[soLop]->soSV = soSV;
            dsLop[soLop]->dsSV = NULL;
            soLop++;
        }
    }
    fclose(f);
    return FILE_OK;
}

int luuDsSinhVien(const char *duongDan)
{
    FILE *f = fopen(duongDan, "w");
    if (!f)
        return FILE_ERR_OPEN;

    fprintf(f, "# dong: ma_lop|ma_sv|ho|ten|phai(0/1)|mat_khau\n");
    fprintf(f, "# comment bat dau bang # \n");

    for (int i = 0; i < soLop; i++)
    {
        if (!dsLop[i])
            continue;

        for (SinhVien *p = dsLop[i]->dsSV; p; p = p->tiep)
        {
            fprintf(f,
                    "%s|%s|%s|%s|%d|%s\n",
                    dsLop[i]->malop,
                    p->masv,
                    p->ho,
                    p->ten,
                    p->phai,
                    p->password);
        }
    }

    fclose(f);
    return FILE_OK;
}

int taiDsSinhVien(const char *duongDan)
{
    FILE *f = fopen(duongDan, "r");
    if (!f)
        return FILE_ERR_OPEN;

    for (int i = 0; i < soLop; i++)
    {
        if (!dsLop[i])
            continue;

        SinhVien *p = dsLop[i]->dsSV;
        while (p)
        {
            SinhVien *next = p->tiep;
            free(p);
            p = next;
        }
        dsLop[i]->dsSV = NULL;
        dsLop[i]->soSV = 0;
    }

    char buf[512];
    while (fgets(buf, sizeof(buf), f))
    {
        boKhoangDauCuoi(buf);
        if (!buf[0] || buf[0] == '#')
            continue;

        char *malop = strtok(buf, "|");
        char *masv = strtok(NULL, "|");
        char *ho = strtok(NULL, "|");
        char *ten = strtok(NULL, "|");
        char *phaiText = strtok(NULL, "|");
        char *password = strtok(NULL, "|");

        if (!malop || !masv || !ho || !ten || !phaiText || !password)
            continue;

        boKhoangDauCuoi(malop);
        boKhoangDauCuoi(masv);
        boKhoangDauCuoi(ho);
        boKhoangDauCuoi(ten);
        boKhoangDauCuoi(phaiText);
        boKhoangDauCuoi(password);

        int idx = timLop(malop);
        if (idx < 0 || !dsLop[idx])
            continue;

        if (timSV(masv))
            continue;

        int phai = atoi(phaiText);
        if (!(phai == PHAI_NAM || phai == PHAI_NU))
            continue;

        SinhVien *node = (SinhVien *)malloc(sizeof(SinhVien));
        if (!node)
        {
            fclose(f);
            return FILE_ERR_MEM;
        }

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
    }

    fclose(f);
    return FILE_OK;
}