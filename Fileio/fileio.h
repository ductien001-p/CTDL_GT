#ifndef FILEIO_H
#define FILEIO_H

#include "../struct/struct.h"
#include <fstream>
using namespace std;

struct AppContext;

void loadMonHoc(DSMonHoc &ds);
void saveMonHoc(const DSMonHoc &ds);

void loadLop(DSLop &ds);
void saveLop(const DSLop &ds);

void loadSinhVien(DSLop &dsLop);
void saveSinhVien(const DSLop &dsLop);

void loadDiemThi(DSLop &dsLop);
void saveDiemThi(const DSLop &dsLop);

void loadCauHoi(NodeBST *&root);
void saveCauHoi(NodeBST *root);

void saveNode(NodeBST *root, ofstream &out);

void loadDatabase(AppContext &app);
void saveDatabase(const AppContext &app);

#endif