//
// Created by smsqo on 2022/4/19.
//

#define DLLEXPORT

#include <iostream>

/// putchard - putchar that takes a double and returns 0.
extern "C" DLLEXPORT int draw(int X) {
    fputc((char) X, stdout);
    return 0;
}

/// printd - printf that takes a double prints it as "%f\n", returning 0.
extern "C" DLLEXPORT int printd(double X) {
    fprintf(stdout, "%f\n", X);
    return 0;
}

extern "C" DLLEXPORT int printi(int X) {
    fprintf(stdout, "%d\n", X);
    return 0;
}

extern "C" DLLEXPORT double inputd() {
    char text[0x100];
    scanf("%s", text);
    return std::stod(text);
}

extern "C" DLLEXPORT int inputi() {
    char text[0x100];
    scanf("%s", text);
    return std::stoi(text);
}