
#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <string>

#include "struct.h"
#include "../features/Lop/lop.h"
#include "../Fileio/fileio.h"

using namespace std;

struct Database
{
    DSLop dsLop;
    DSMonHoc dsMH;
    NodeBST *rootCH;

    Database()
    {
        khoiTaoDSLop(dsLop);
        dsMH.n = 0;
        rootCH = nullptr;
    }
};

struct Session
{
    string username;
    bool giaovien = false;
    SinhVien *svHientai = nullptr;
};

struct AppContext
{
    Database db;
    Session session;
};

#endif