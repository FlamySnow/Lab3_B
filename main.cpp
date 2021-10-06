#include "Printed_Circuit_Board.h"

using namespace Lab3B;

int main() {
    int a = 0;
    short c1, c2;
    printedCircuitBoard::Contact c;
    printedCircuitBoard p;
    std::cout << "Hello! You can do many things to printed circuit board, in particular:" << std::endl;
    do {
        std::cout << "0. Quit;" << std::endl;
        std::cout << "1. Print information about PCB;" << std::endl;
        std::cout << "2. Add contact on PCB;" << std::endl;
        std::cout << "3. Establish connect between contacts;" << std::endl;
        std::cout << "4. Get contacts that are in the same group;" << std::endl;
        std::cout << "5. Get length of the track between contacts;" << std::endl;
        std::cout << "6. Get information about specific contact by number;" << std::endl;
        std::cout << "7. Delete last contact from PCB." << std::endl;
        std::cout << "Make your choice: --> ";
        checkInput(a);
        std::cout << std::endl;
        try {
            switch (a) {
                case 1: {
                    std::cout << p;
                }
                    break;
                case 2: {
                    std::cout << "Enter type (0 for input, 1 for output), the first and the second coordinates of a contact: --> ";
                    checkInput(c);
                    p += c;
                }
                    break;
                case 3: {
                    std::cout << "Enter number of the first contact: --> ";
                    checkInput(c1);
                    std::cout << "Enter number of the second contact: --> ";
                    checkInput(c2);
                    p.establishConnect(c1, c2);
                }
                    break;
                case 4: {
                    std::cout << p.groupOfContacts();
                }
                    break;
                case 5: {
                    std::cout << "Enter number of the first contact: --> ";
                    checkInput(c1);
                    std::cout << "Enter number of the second contact: --> ";
                    checkInput(c2);
                    std::cout << "Length of track: --> " << p(c1, c2) << std::endl;
                }
                break;
                case 6: {
                    std::cout << "Enter number of contact: --> ";
                    checkInput(c1);
                    c = p[c1];
                    std::cout << c;
                }
                break;
                case 7: {
                    p--;
                }
                break;
                case 0: {
                    break;
                }
                default: {
                    std::cout << "Enter only numbers from 0 to 7!" << std::endl;
                }
                    break;
            }
        }
        catch (std::exception &e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    } while (a != 0);
    return 0;
}