#ifndef DECORATION_H
#define DECORATION_H
#include <iomanip>
#include <iostream>

void gotoXY(int x, int y);

void setColor(int color);

void clearScreen();

void veKhung(
    int x,
    int y,
    int width,
    int height);

void veTieuDe(
    int x,
    int y,
    int width,
    const char *title);

void veKhungManHinh(
    int x,
    int y,
    int width,
    int height,
    const char *title);

void veKhungTieuDe(
    int x,
    int y,
    int width);


int menuConsole(
    const char *title,
    const char *items[],
    int soLuong);

// thong bao
void veKhungThongBao(
    int x,
    int y,
    int width,
    int height);

void choNhanPhim(
    int x,
    int y);
void hienThongBao(
    int x,
    int y,
    const char *thongbao,
    bool thanhcongs);
#endif