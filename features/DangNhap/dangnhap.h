#ifndef DANGNHAP_H
#define DANGNHAP_H

struct AppContext;

bool kiemTraDangNhap(AppContext &app, const char *username, const char *password);
void dangXuat(AppContext &app);
#endif