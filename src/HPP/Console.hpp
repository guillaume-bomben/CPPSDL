#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <conio.h>
#include "Matrix.hpp"

class Console
{
public:
    static void run(){
        Matrix matrix = Matrix();

        bool running = true;
        bool change = true;
        bool lose = false;

        while(running){
            if (change){
                std::cout << "2048 :\n" << std::endl;
                std::cout << matrix.getElement(0, 0) << " " << matrix.getElement(0, 1) << " " << matrix.getElement(0, 2) << " " << matrix.getElement(0, 3) << std::endl;
                std::cout << matrix.getElement(1, 0) << " " << matrix.getElement(1, 1) << " " << matrix.getElement(1, 2) << " " << matrix.getElement(1, 3) << std::endl;
                std::cout << matrix.getElement(2, 0) << " " << matrix.getElement(2, 1) << " " << matrix.getElement(2, 2) << " " << matrix.getElement(2, 3) << std::endl;
                std::cout << matrix.getElement(3, 0) << " " << matrix.getElement(3, 1) << " " << matrix.getElement(3, 2) << " " << matrix.getElement(3, 3) << std::endl << std::endl;
                change = false;
            }
            int ch = getch();
            if (ch == 224) {
                ch = getch();
                switch (ch) {
                    case 72: //up
                        matrix.moveMatrix('u');
                        lose = !matrix.addNumber();
                        change = true;
                        break;
                    case 80: //down
                        matrix.moveMatrix('d');
                        lose = !matrix.addNumber();
                        change = true;
                        break;
                    case 77: //right
                        matrix.moveMatrix('r');
                        lose = !matrix.addNumber();
                        change = true;
                        break;
                    case 75: //left
                        matrix.moveMatrix('l');
                        lose = !matrix.addNumber();
                        change = true;
                        break;
                    case 113:
                        running = false;
                        break;
                    default: std::cout << "unknown\n";
                }
            }
            if (lose){
                std::cout << "You lose";
                running = false;
            }
        }
    };
};

#endif