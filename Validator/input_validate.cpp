#include "input_validate.h"
#include <ctype.h>
#include <string>
#include <conio.h>
#include <iostream>
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

    case HOTEN:
        return laChu(c) || c == ' ';

    case MATKHAU:
        return c != ' ';

    default:
        return false;
    }
}

string nhap(InputType type)
{
    string s;
    char c;

    while (true)
    {
        c = _getch();

        if (c == 13) // Enter
            break;

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
            s += c;
            cout << c;
        }
    }

    cout << endl;
    return s;
}