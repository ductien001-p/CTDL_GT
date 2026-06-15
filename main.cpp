#include "struct/app_context.h"
#include "screen/include/MenuDangNhap.h"
#include "screen/include/menuGV.h"
#include "screen/include/menuQLSV.h"
#include "screen/include/menuQL_Thi_SV.h"
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
            menuGV(app);
        }
        else
        {
            menuQuanLyThiSinhVien(app);
        }

        dangXuat(app);
    }

    saveDatabase(app);

    return 0;
}