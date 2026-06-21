#include "input_validate.h"
#include <ctype.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include "../../HamHoTro/hamhotro.h"
using namespace std;

bool laSo(char c)
{
    return c >= '0' && c <= '9';
}

bool laChuThuong(char c)
{
    return c >= 'a' && c <= 'z';
}

bool laChuHoa(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool laChu(char c)
{
    return laChuThuong(c) || laChuHoa(c);
}

bool laChuHoaVaSo(char c)
{
    return laChuHoa(c) || laSo(c);
}

bool laKiTuNgang(char c)
{
    return c == '-';
}

bool hopLe(char c, InputType type)
{
    switch (type)
    {
    case SO:
        return laSo(c);

    case CHUTHUONG:
        return laChuThuong(c);

    case MASINHVIEN:
        return laChuHoaVaSo(c);

    case MALOP:
        return laChuThuong(c) || laSo(c) || laChu(c) || laKiTuNgang(c);

    case HOTEN:
        return laChu(c) || c == ' ';

    case TENLOP:
        return laChu(c) || c == ' ' || laSo(c);

    case MATKHAU:
        return c != ' ';
    case DAPAN:
        return c == 'A' || c == 'B' || c == 'C' || c == 'D';
    case MAMONHOC:
        return laChuHoaVaSo(c);
    case TENMONHOC:
        return laChu(c) || c == ' ' || laSo(c);
    case SOTINCHI:
        return laSo(c);

    default:
        return false;
    }
}

void nhap(char ketqua[], InputType type)
{
    string s;
    char c;

    while (true)
    {

        c = _getch();
        if (c == 13)
        {
            if (!s.empty())
            {
                break;
            }
            else
            {
                continue;
            }
        }

        if (c == 8) // Backspace
        {
            if (!s.empty())
            {
                s.pop_back();
                cout << "\b \b";
            }
            continue;
        }

        if (hopLe(c, type))
        {
            // (TÃ¹y chá»n) Cháº·n nháº­p nhiá»u chá»¯ náº¿u lÃ  DAPAN
            if (type == DAPAN && s.length() >= 1)
            {
                continue;
            }

            s += c;
            cout << c;
        }
    }

    cout << endl;
    saoChepChuoi(ketqua, s.c_str());
}