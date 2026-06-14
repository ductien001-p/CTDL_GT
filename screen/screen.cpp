// LOGIN
#include <cstdlib>
#include <iostream>

#include "screen.h"
#include "../struct/app_context.h"
#include "menuDangNhap/MenuDangNhap.h"
using namespace std;
void startScreen(AppContext& app)
{
    int choice;

    do
    {
        system("cls");

        cout << "====================================\n";
        cout << "      HE THONG THI TRAC NGHIEM\n";
        cout << "====================================\n";
        cout << "1. Dang nhap\n";
        cout << "0. Thoat\n";
        cout << "------------------------------------\n";
        cout << "Lua chon: ";

        cin >> choice;

        switch(choice)
        {
        case 1:
        {
            if (manHinhDangNhap(app))
            {
                if (app.session.giaovien)
                    menuGV(app);
                else
                    menuSV(app);
            }
            break;
        }

        case 0:
            break;

        default:
            system("pause");
        }

    } while(choice != 0);
}

bool loginScreen(AppContext& app)
{
    system("cls");

    string user;
    string pass;

    cout << "Tai khoan: ";
    cin >> user;

    cout << "Mat khau: ";
    cin >> pass;

    if(user == "GV" && pass == "GV")
    {
        app.session.username = user;
        app.session.giaovien = true;
        return true;
    }

    // TODO:
    // tim sinh vien trong dsLop

    app.session.username = user;
    app.session.giaovien = false;

    return true;
}

// Lop
void lopMenu(AppContext& app)
{
    (void)app;
    int choice;

    do
    {
        system("cls");

        cout << "========== QUAN LY LOP ==========\n";
        cout << "1. Them lop\n";
        cout << "2. Xoa lop\n";
        cout << "3. Sua lop\n";
        cout << "4. Danh sach lop\n";
        cout << "0. Quay lai\n";

        cout << "Lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Them lop...\n";
            break;

        case 2:
            cout << "Xoa lop...\n";
            break;

        case 3:
            cout << "Sua lop...\n";
            break;

        case 4:
            cout << "In danh sach lop...\n";
            break;
        }

        if (choice != 0)
            system("pause");

    } while (choice != 0);
}

// Mon hoc
void monHocMenu(AppContext& app)
{
    (void)app;
    int choice;

    do
    {
        system("cls");

        cout << "========= QUAN LY MON HOC =========\n";
        cout << "1. Them mon hoc\n";
        cout << "2. Xoa mon hoc\n";
        cout << "3. Sua mon hoc\n";
        cout << "4. Danh sach mon hoc\n";
        cout << "0. Quay lai\n";

        cout << "Lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Them mon hoc...\n";
            break;

        case 2:
            cout << "Xoa mon hoc...\n";
            break;

        case 3:
            cout << "Sua mon hoc...\n";
            break;

        case 4:
            cout << "In danh sach mon hoc...\n";
            break;
        }

        if (choice != 0)
            system("pause");

    } while (choice != 0);
}
// Cau hoi
void cauHoiMenu(AppContext& app)
{
    (void)app;
    int choice;

    do
    {
        system("cls");

        cout << "======== QUAN LY CAU HOI ========\n";
        cout << "1. Them cau hoi\n";
        cout << "2. Xoa cau hoi\n";
        cout << "3. Sua cau hoi\n";
        cout << "4. Tim cau hoi\n";
        cout << "5. Danh sach cau hoi\n";
        cout << "0. Quay lai\n";

        cout << "Lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Them cau hoi...\n";
            break;

        case 2:
            cout << "Xoa cau hoi...\n";
            break;

        case 3:
            cout << "Sua cau hoi...\n";
            break;

        case 4:
            cout << "Tim cau hoi...\n";
            break;

        case 5:
            cout << "In danh sach cau hoi...\n";
            break;
        }

        if (choice != 0)
            system("pause");

    } while (choice != 0);
}
// Diem
void diemMenu(AppContext& app)
{
    (void)app;
    system("cls");

    cout << "========== BANG DIEM ==========\n";
    cout << "1. Xem bang diem lop\n";
    cout << "2. Xem bang diem mon hoc\n";

    system("pause");
}

//======================================Menu Sinh vien======================================//
void menuSV(AppContext& app)
{
    (void)app;
    int choice;

    do
    {
        system("cls");

        cout << "====================================\n";
        cout << "          MENU SINH VIEN\n";
        cout << "====================================\n";
        cout << "1. Thi trac nghiem\n";
        cout << "2. Xem diem\n";
        cout << "3. Xem chi tiet bai thi\n";
        cout << "0. Dang xuat\n";

        cout << "Lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            thiMenu(app);
            break;
        case 2:
            xemDiemMenu(app);
            break;
        case 3:
            xemKetQuaMenu(app);
            break;
        }

    } while (choice != 0);
}

// Thi
void thiMenu(AppContext& app)
{
    (void)app;
    system("cls");

    cout << "========== THI TRAC NGHIEM ==========\n";
    cout << "Chon mon hoc\n";
    cout << "Nhap so cau hoi\n";
    cout << "Nhap thoi gian thi\n";

    system("pause");
}
// Xem diem
void xemDiemMenu(AppContext& app)
{
    (void)app;
    system("cls");

    cout << "========== KET QUA HOC TAP ==========\n";
    cout << "Danh sach diem cac mon\n";

    system("pause");
}
// Xem ket qua chi tiet
void xemKetQuaMenu(AppContext& app)
{
    (void)app;
    system("cls");

    cout << "======= CHI TIET BAI THI =======\n";
    cout << "Cau 1 ...\n";
    cout << "Dap an dung: A\n";
    cout << "Ban chon: B\n";

    system("pause");
}