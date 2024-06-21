#include <iostream>
#include <windows.h>

using namespace std;

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor() {
    setTextColor(7); // Set text color back to default (white)
}

int main() {
    setTextColor(10);
    std::cout << "Hello, what is your name?" << std::endl;
    setTextColor(11);
    std::cout << "Hello, what is your name?" << std::endl;

    setTextColor(12);
    std::cout << "Hello, what is your name?" << std::endl;

    setTextColor(13);
    std::cout << "Hello, what is your name?" << std::endl;

    setTextColor(14);
    std::cout << "Hello, what is your name?" << std::endl;
    
    setTextColor(15);
    std::cout << "Hello, what is your name?" << std::endl;

    setTextColor(9);
    std::cout << "Hello, what is your name?" << std::endl;

        setTextColor(8);
    std::cout << "Hello, what is your name?" << std::endl;

        setTextColor(7);
    std::cout << "Hello, what is your name?" << std::endl;

    
        setTextColor(6);
    std::cout << "Hello, what is your name?" << std::endl;

    
        setTextColor(5);
    std::cout << "Hello, what is your name?" << std::endl;

    
        setTextColor(4);
    std::cout << "Hello, what is your name?" << std::endl;
    return 0;
}
