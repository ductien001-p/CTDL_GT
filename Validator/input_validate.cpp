#include "input_validate.h"
#include <ctype.h>
#include <string>
#include <conio.h>
#include <iostream>
using namespace std;
bool hopLe(char c, InputType type)
{
    switch (type)
    {
    case NUMBER:
        return isdigit((unsigned char)c);

    case LETTER:
        return isalpha((unsigned char)c);

    case ALPHANUMERIC:
        return isalnum((unsigned char)c);

    case NAME:
        return isalpha((unsigned char)c) || c == ' ';

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