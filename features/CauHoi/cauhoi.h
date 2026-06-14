#ifndef CAUHOI_H
#define CAUHOI_H
#include "../../struct/struct.h"
#include <fstream>
using namespace std;

NodeBST *taoNode(
    const CauHoi &ch);
bool insertCauHoi(
    NodeBST *&root,
    const CauHoi &ch);
NodeBST *searchCauHoi(
    NodeBST *root,
    int id);
bool deleteCauHoi(
    NodeBST *&root,
    int id);
void LNR(
    NodeBST *root);

void saveLNR(
    NodeBST *root,
    ofstream &out);
int getMaxID(
    NodeBST *root);

int taoIDMoi(
    NodeBST *root);

void chenCauHoiLoadfile(
    NodeBST *&root,
    const CauHoi &ch);
#endif // CAUHOI_H