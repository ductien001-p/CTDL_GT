CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
INCLUDES = -I. -Istruct -IFileio -IHamHoTro -IValidator -Iscreen -Ifeatures/DangNhap -Ifeatures/DiemThi -Ifeatures/Lop -Ifeatures/MonHoc -Ifeatures/SinhVien

SRCS = main.cpp \
	Fileio/fileio.cpp \
	decoration/decoration.cpp \
	HamHoTro/hamhotro.cpp \
	Validator/input_validate.cpp \
	features/DangNhap/dangnhap.cpp \
	features/DiemThi/diemthi.cpp \
	features/DiemThi/ketquabaithi.cpp \
	features/Lop/lop.cpp \
	features/MonHoc/monhoc.cpp \
	features/SinhVien/sinhvien.cpp \
	features/CauHoi/cauhoi.cpp \
	features/Thi/thi.cpp \
	screen/function/menuCauhoi.cpp \
	screen/function/menuGV.cpp \
	screen/function/menuLop.cpp \
	screen/function/menuMonhoc.cpp \
	screen/function/menuQLSV.cpp \
	screen/function/menuBangDiem.cpp \
	screen/function/menuDangNhap.cpp \
	screen/function/menuQL_Thi_SV.cpp
TARGET = quiz_app.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

clean:
	-del /Q /F $(TARGET) 2>nul