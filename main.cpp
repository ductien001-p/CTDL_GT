#include "struct/app_context.h"
#include "screen/screen.h"
#include "screen/include/MenuDangNhap.h"
#include "features/DangNhap/dangnhap.h"
#include "Fileio/fileio.h"
#include <iostream>
using namespace std;
int main()
{
    cout << "Loading database...\n";
    AppContext app;

    loadDatabase(app);
    cout << "Database loaded successfully!\n";

    while (true)
    {
        bool ok =
            manHinhDangNhap(app);

        if (!ok)
            break;

        if (app.session.giaovien)
        {
            // menuGV(app);
            cout
                << "\nDang nhap thanh cong!\n";
        }
        else
        {
            // menuSV(app);
            cout
                << "\nDang nhap thanh cong!\n";
        }

        dangXuat(app);
    }

    saveDatabase(app);

    return 0;
}