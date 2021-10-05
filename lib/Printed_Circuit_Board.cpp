//
// Created by flamy on 05/10/21.
//

#include "Printed_Circuit_Board.h"

namespace Lab3B {
    printedCircuitBoard::Contact::Contact() {
        type = notStated;
        x = 0;
        y = 0;
        numberOfContact = -1;
    }

    printedCircuitBoard::Contact::Contact(contactType t, int x, int y) {
        if (t != 0 && t != 1)
            throw std::invalid_argument("Incorrect type of contact!");
        type = t;
        this->x = x;
        this->y = y;
        numberOfContact = -1;
    }

    /*printedCircuitBoard::Contact printedCircuitBoard::inputContact() {
        int x, y, t;
        contactType type;
        std::cout << "Enter type of contact (0 for input, 1 for output): --> ";
        checkInput(t);
        type = isCorrectType(t);
        std::cout << "Enter the first coordinate of contact: --> ";
        checkInput(x);
        std::cout << "Enter the second coordinate of contact: --> ";
        checkInput(y);
        Contact c(type, x, y);
        return c;
    }*/



    contactType printedCircuitBoard::isCorrectType(int t) {
        if (t == 0)
            return in;
        if (t == 1)
            return out;
        throw std::invalid_argument("Incorrect type of contact");
    }

    /*void printedCircuitBoard::print() const {
        if (currentNumber == 0) {
            std::cout << "The PCB has no contacts!" << std::endl;
            return;
        }
        for (int i = 0; i < currentNumber; ++i) {
            std::cout << "Number of contact: --> " << i << std::endl;
            std::cout << "Type of contact: --> ";
            if (contacts[i].type == in)
                std::cout << "input" << std::endl;
            if (contacts[i].type == out)
                std::cout << "output" << std::endl;
            std::cout << "First coordinate: --> " << contacts[i].x << std::endl;
            std::cout << "Second coordinate: --> " << contacts[i].y << std::endl;
            if (contacts[i].numberOfContact == -1)
                std::cout << "This contact is disconnected from other contacts" << std::endl;
            else
                std::cout << "Number of related contact: --> " << contacts[i].numberOfContact << std::endl;
            std::cout << std::endl;
        }
    } */

    bool printedCircuitBoard::isCorrectConnection(short c1, short c2) {
        if (!isCorrectNumber(c1) || !isCorrectNumber(c2))
            throw std::invalid_argument("There is no such contact(s)!");
        if (contacts[c1].type == contacts[c2].type)
            return false;
        if (contacts[c1].numberOfContact != -1 || contacts[c2].numberOfContact != -1)
            return false;
        return true;
    }

    /*void printedCircuitBoard::addContact(Contact c) {
        if (currentNumber == maxNumber) {
            throw std::overflow_error("Cannot add more contacts!");
        }
        if (!isCorrectCoordinates(c.x, c.y))
            throw std::invalid_argument("There is a contact at this place already!");
        contacts[currentNumber] = c;
        currentNumber++;
    }*/

    void printedCircuitBoard::establishConnect(short c1, short c2) {
        if (!isCorrectConnection(c1, c2))
            throw std::invalid_argument("Cannot establish connect between these contacts");
        contacts[c1].numberOfContact = c2;
        contacts[c2].numberOfContact = c1;
    }

    printedCircuitBoard printedCircuitBoard::groupOfContacts() const {
        printedCircuitBoard group;
        int t;
        std::cout << "Enter type of contact (0 for in, 1 for out): --> ";
        checkInput(t);
        contactType type = isCorrectType(t);
        for (int i = 0; i < currentNumber; ++i) {
            if (contacts[i].type == type) {
                group += contacts[i];
            }
        }
        return group;
    }

    double printedCircuitBoard::lengthOfTrack(short c1, short c2) {
        if (!isCorrectNumber(c1) || !isCorrectNumber(c2))
            throw std::invalid_argument("There are no such contacts");
        if (contacts[c1].numberOfContact != c2) {
            throw std::invalid_argument("These contacts are not connected");
        }
        int x1 = contacts[c1].x;
        int x2 = contacts[c2].x;
        int y1 = contacts[c1].y;
        int y2 = contacts[c2].y;
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    bool printedCircuitBoard::isCorrectCoordinates(int x, int y) {
        for (int i = 0; i < currentNumber; ++i) {
            if (contacts[i].x == x && contacts[i].y == y)
                return false;
        }
        return true;
    }

    std::istream &operator>>(std::istream & s, printedCircuitBoard::Contact& c) {
        int x, y, t;
        contactType type;
        s >> t >> x >> y;
        if (!s) {
            s.setstate(std::ios::failbit);
        }
        else {
            type = printedCircuitBoard::isCorrectType(t);
            c.x = x;
            c.y = y;
            c.type = type;
        }
        return s;
    }

    std::ostream &operator<<(std::ostream & s, const printedCircuitBoard & p) {
        if (p.currentNumber == 0)
            s << "The PCB is empty!" << std::endl;
        else {
            for (int i = 0; i < p.currentNumber; ++i) {
                s << std::endl << "Number of contact: --> " << i << std::endl;
                s << p.contacts[i];
            }
        }
        return s;
    }

    printedCircuitBoard& printedCircuitBoard::operator+=(const printedCircuitBoard::Contact& c) {
        if (currentNumber == maxNumber) {
            throw std::overflow_error("Cannot add more contacts!");
        }
        if (!isCorrectCoordinates(c.x, c.y))
            throw std::invalid_argument("There is a contact at this place already!");
        contacts[currentNumber] = c;
        currentNumber++;
        return *this;
    }

    const printedCircuitBoard::Contact printedCircuitBoard::operator[](short n) {
        if (!isCorrectNumber(n))
            throw std::invalid_argument("There is no such contact in the PCB!");
        return contacts[n];
    }

    std::ostream &operator<<(std::ostream & s, const printedCircuitBoard::Contact & c) {
        s << "Type of contact: --> ";
        if (c.type == in)
            s << "input" << std::endl;
        if (c.type == out)
            s << "output" << std::endl;
        s << "First coordinate: --> " << c.x << std::endl;
        s << "Second coordinate: --> " << c.y << std::endl;
        if (c.numberOfContact == -1)
            s << "This contact is disconnected from other contacts" << std::endl;
        else
            s << "Number of related contact: --> " << c.numberOfContact << std::endl;
        return s;
    }
}