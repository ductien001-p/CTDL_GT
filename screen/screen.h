#ifndef SCREEN_H
#define SCREEN_H

struct AppContext;

void menuGV(AppContext &app);
void menuSV(AppContext &app);

// Sub-menus
void lopMenu(AppContext &app);
void sinhVienMenu(AppContext &app);
void monHocMenu(AppContext &app);
void cauHoiMenu(AppContext &app);
void diemMenu(AppContext &app);

// Student sub-menus
void thiMenu(AppContext &app);
void xemDiemMenu(AppContext &app);
void xemKetQuaMenu(AppContext &app);

#endif
