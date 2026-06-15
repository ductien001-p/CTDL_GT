#include "decoration.h"
#include <windows.h>
int menuConsole(
    const char *title,
    const char *items[],
    int soLuong)
{
    int chon = 0;

    while (true)
    {
        system("cls");

        setColor(11);

        cout << "========================================\n";
        cout << "          " << title << endl;
        cout << "========================================\n\n";

        for (int i = 0; i < soLuong; i++)
        {
            if (i == chon)
            {
                setColor(14);

                cout << " > "
                     << items[i]
                     << endl;
            }
            else
            {
                setColor(7);

                cout << "   "
                     << items[i]
                     << endl;
            }
        }

        setColor(8);

        cout << "\nSu dung phim mui ten len/xuong de di chuyen";
        cout << "\nNhan Enter de chon";

        int key = _getch();

        if (key == 224)
        {
            key = _getch();

            switch (key)
            {
            case 72: // len
                chon--;

                if (chon < 0)
                    chon = soLuong - 1;

                break;

            case 80: // xuong
                chon++;

                if (chon >= soLuong)
                    chon = 0;

                break;
            }
        }
        else if (key == 13)
        {
            setColor(7);

            return chon;
        }
    }
}