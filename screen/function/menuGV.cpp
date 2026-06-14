// #include "screen/include/menuGV.h"
// #include <cstdlib>
// #include <iostream>

// #include "screen.h"
// #include "../struct/app_context.h"
// #include "screen/include/MenuDangNhap.h"
// using namespace std;
// //=========================================Menu Giao vien===========================//
// void menuGV(AppContext &app)
// {
//     (void)app;
//     int choice;

//     do
//     {
//         system("cls");

//         cout << "====================================\n";
//         cout << "          MENU GIAO VIEN\n";
//         cout << "====================================\n";
//         cout << "1. Quan ly lop\n";
//         cout << "2. Quan ly sinh vien\n";
//         cout << "3. Quan ly mon hoc\n";
//         cout << "4. Quan ly cau hoi\n";
//         cout << "5. Bang diem\n";
//         cout << "0. Dang xuat\n";
//         cout << "------------------------------------\n";
//         cout << "Lua chon: ";
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             lopMenu(app);
//             break;
//         case 2:
//             sinhVienMenu(app);
//             break;
//         case 3:
//             monHocMenu(app);
//             break;
//         case 4:
//             cauHoiMenu(app);
//             break;
//         case 5:
//             diemMenu(app);
//             break;
//         }

//     } while (choice != 0);
// }