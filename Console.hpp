#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

#include "Size.hpp"

class {
public:
    template<class T>
    void print(const T& value) {
        std::cout << value;
    }

    template<class T, class... Args>
    void print(const T& value, const Args&... args) {
        print(value);
        print(args...);
    }

    template <class T>
    T input(const char* text = "") {
        print(text);
        T value;
        std::cin >> value;
        return value;
    }

    std::string readLine() {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    void setColor(int color) {
        const auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void resetColor() {
        const auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7); // Default color
    }

    void clear() {
        system("cls");
    }

    Size size() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        const Size size(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
        return size;
    }
} console;