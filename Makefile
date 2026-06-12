CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
INCLUDES = -I. -Istruct -IFileio -Ifeatures/Auth -Ifeatures/Lop -IValidator

SRCS = main.cpp struct/global.cpp Fileio/fileio.cpp features/Auth/auth.cpp features/Lop/lop.cpp Validator/input_validate.cpp
TARGET = quiz_app.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

clean:
	-del /Q /F $(TARGET) 2>nul