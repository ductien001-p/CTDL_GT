#include "cauhoi.h"
#include "../../HamHoTro/hamhotro.h"
using namespace std;

void chenCauHoiLoadfile(
    NodeBST *&root,
    const CauHoi &ch)
{
    if (root == nullptr)
    {
        root = new NodeBST;
        root->data = ch;
        root->trai = root->phai = nullptr;
        return;
    }

    if (ch.id < root->data.id)
        chenCauHoiLoadfile(root->trai, ch);
    else
        chenCauHoiLoadfile(root->phai, ch);
}
