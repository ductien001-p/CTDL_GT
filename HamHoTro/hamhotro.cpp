#include <cstring>
#include "conio.h"
#include "hamhotro.h"
#include <iostream>
#include <iomanip>
#include "decoration/decoration.h"

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

bool chuoiRong(const char *s)
{
    return (s == nullptr || s[0] == '\0');
}

bool chiToanKhoangTrang(const char *s)
{
    if (s == nullptr)
        return true;

    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != ' ' && s[i] != '\t')
            return false;
        i++;
    }

    return true;
}
