#include <cstring>

#include "hamhotro.h"
// Ham ho tro
bool soSanhChuoi(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return false;

        i++;
    }

    return s1[i] == s2[i];
}

void saoChepChuoi(char *dich, const char *nguon)
{
    int i = 0;

    while (nguon[i] != '\0')
    {
        dich[i] = nguon[i];
        i++;
    }

    dich[i] = '\0';
}

void xoaKhoangTrangThua(char str[])
{
    int i = 0, j = 0;

    // Bỏ khoảng trắng đầu chuỗi
    while (str[i] == ' ')
    {
        i++;
    }

    bool truocDoLaKhoangTrang = false;

    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
            truocDoLaKhoangTrang = false;
        }
        else
        {
            // Chỉ giữ lại 1 khoảng trắng giữa các từ
            if (!truocDoLaKhoangTrang)
            {
                str[j++] = ' ';
                truocDoLaKhoangTrang = true;
            }
        }

        i++;
    }

    // Xóa khoảng trắng cuối nếu có
    if (j > 0 && str[j - 1] == ' ')
    {
        j--;
    }

    str[j] = '\0';
}

bool coKhoangTrangGiua(const char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
            return true;
    }
    return false;
}