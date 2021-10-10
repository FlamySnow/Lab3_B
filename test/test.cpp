//
// Created by flamy on 06/10/21.
//

#include "gtest/gtest.h"
#include "../lib/Printed_Circuit_Board.h"

using namespace Lab3B;

TEST (ContactConstructors, EmptyConstructor) {
    printedCircuitBoard::Contact c;
    ASSERT_EQ(notStated, c.type);
    ASSERT_EQ(0, c.x);
    ASSERT_EQ(0, c.y);
    ASSERT_EQ(-1, c.numberOfContact);
}

TEST (ContactConstructors, InitialConstructor) {
    printedCircuitBoard::Contact c(in, 1, 2);
    ASSERT_EQ(in, c.type);
    ASSERT_EQ(1, c.x);
    ASSERT_EQ(2, c.y);
    ASSERT_EQ(-1, c.numberOfContact);
    printedCircuitBoard::Contact c1 (out, -1, 0);
    ASSERT_EQ(out, c1.type);
    ASSERT_EQ(-1, c1.x);
    ASSERT_EQ(0, c1.y);
    ASSERT_EQ(-1, c1.numberOfContact);
}

//there is only one way to call exception, in other ways compiler doesn't allow you to do that
TEST (ContactConstructors, InitialConstructorException) {
    ASSERT_ANY_THROW(printedCircuitBoard::Contact c = printedCircuitBoard::Contact (notStated, 3, 4));
}

TEST (PCBConstructor, EmptyConstructor) {
    printedCircuitBoard p;
    ASSERT_EQ(0, p.getCurrentNumber());
}

TEST (PCBMethods, Adding) {
    printedCircuitBoard::Contact c (in, 1, 3);
    printedCircuitBoard p;
    p += c;
    ASSERT_EQ(in, p[0].type);
    ASSERT_EQ(1, p[0].x);
    ASSERT_EQ(3, p[0].y);
    ASSERT_EQ(-1, p[0].numberOfContact);
    c.type = out;
    c.x = -23;
    c.y = 5;
    p += c;
    ASSERT_EQ(out, p[1].type);
    ASSERT_EQ(-23, p[1].x);
    ASSERT_EQ(5, p[1].y);
    ASSERT_EQ(-1, p[1].numberOfContact);
}

TEST (PCBMethods, AddingOverflow) {
    printedCircuitBoard::Contact c (in, 0, 5);
    printedCircuitBoard p;
    p += c;
    int i = 1;
    while (i != p.getMaxNumber()) {
        c.x = i;
        p += c;
        ++i;
    }
    c.x = i + 1;
    ASSERT_ANY_THROW(p += c);
}

TEST (PCBMethods, AddingException) {
    printedCircuitBoard::Contact c (out, 3, -8);
    printedCircuitBoard p;
    p += c;
    ASSERT_ANY_THROW(p += c);
    c.type = out;
    ASSERT_ANY_THROW(p += c);
}

TEST (PCBMethods, Deleting) {
    printedCircuitBoard::Contact c (in, 1, 2);
    printedCircuitBoard p;
    p += c;
    p--;
    ASSERT_EQ(0, p.getCurrentNumber());
    p += c;
    c.x = 2;
    p += c;
    c.y = 3;
    p += c;
    --p;
    ASSERT_EQ(2, p.getCurrentNumber());
}

TEST (PCBMethods, DeletingException) {
    printedCircuitBoard p;
    ASSERT_ANY_THROW(p--);
    ASSERT_ANY_THROW(--p);
}

TEST (PCBMethods, GettingContact) {
    printedCircuitBoard p;
    printedCircuitBoard::Contact c (in, 2, 1);
    p += c;
    c.type = out;
    c.x = 1;
    c.y = 9;
    p += c;
    ASSERT_EQ(in, p[0].type);
    ASSERT_EQ(2, p[0].x);
    ASSERT_EQ(1, p[0].y);
    ASSERT_EQ(out, p[1].type);
    ASSERT_EQ(1, p[1].x);
    ASSERT_EQ(9, p[1].y);
}

TEST (PCBMethods, GettingContactExceptions) {
    printedCircuitBoard p;
    ASSERT_ANY_THROW(p[0]);
    printedCircuitBoard::Contact c (in, 1, 2);
    p += c;
    ASSERT_ANY_THROW(p[1]);
    ASSERT_ANY_THROW(p[-9]);
}

TEST (PCBMethods, Establishing) {
    printedCircuitBoard p;
    printedCircuitBoard::Contact c1 (in, 1, 1);
    printedCircuitBoard::Contact c2 (out, 2, 3);
    p += c1;
    p += c2;
    c1.x = 0;
    p += c1;
    c2.y = 4;
    p += c2;
    c1.x = 2;
    p += c1;
    c2.y = 98;
    p += c2;
    p.establishConnect(0, 1);
    p.establishConnect(5, 2);
    ASSERT_EQ(1, p[0].numberOfContact);
    ASSERT_EQ(0, p[1].numberOfContact);
    ASSERT_EQ(2, p[5].numberOfContact);
    ASSERT_EQ(5, p[2].numberOfContact);
}

TEST (PCBMethods, EstablishingException) {
    printedCircuitBoard p;
    printedCircuitBoard::Contact c1 (in, 1, 1);
    printedCircuitBoard::Contact c2 (out, 2, 3);
    p += c1;
    p += c2;
    c1.x = 0;
    p += c1;
    c2.y = 4;
    p += c2;
    c1.x = 2;
    p += c1;
    c2.y = 98;
    p += c2;
    ASSERT_ANY_THROW(p.establishConnect(-1, 0));
    ASSERT_ANY_THROW(p.establishConnect(0, 8));
    ASSERT_ANY_THROW(p.establishConnect(0, 2));
    ASSERT_ANY_THROW(p.establishConnect(1, 3));
    p.establishConnect(0, 3);
    ASSERT_ANY_THROW(p.establishConnect(0, 4));
}

TEST (PCBMethods, Length) {
    printedCircuitBoard p;
    printedCircuitBoard::Contact c1 (in, 1, 1);
    printedCircuitBoard::Contact c2 (out, 1, 2);
    p += c1;
    p += c2;
    p.establishConnect(0, 1);
    c1.x = 9;
    c2.x = 6;
    c2.y = -3;
    p += c1;
    p += c2;
    p.establishConnect(2, 3);
    ASSERT_EQ(1, p(0, 1));
    ASSERT_EQ(5, p(2, 3));
    ASSERT_EQ(5, p(3, 2));
}

TEST (PCBMethods, LengthException) {
    printedCircuitBoard p;
    printedCircuitBoard::Contact c1 (in, 1, 1);
    printedCircuitBoard::Contact c2 (out, 1, 2);
    p += c1;
    p += c2;
    p.establishConnect(0, 1);
    c1.x = 9;
    c2.x = 6;
    c2.y = -3;
    p += c1;
    p += c2;
    ASSERT_ANY_THROW(p(0, 15));
    ASSERT_ANY_THROW(p(-5, 2));
    ASSERT_ANY_THROW(p(2, 8));
    ASSERT_ANY_THROW(p(0, 2));
}

TEST (PCBMethods, groupOfContacts) {
    printedCircuitBoard p;
    printedCircuitBoard group = p.groupOfContacts(0);
    ASSERT_EQ(0, group.getCurrentNumber());
    printedCircuitBoard::Contact c1 (in, 1, 1);
    printedCircuitBoard::Contact c2 (out, 2, 3);
    p += c1;
    p += c2;
    c1.x = 0;
    p += c1;
    c2.y = 4;
    p += c2;
    c1.x = 2;
    p += c1;
    c2.y = 98;
    p += c2;
    group = p.groupOfContacts(0);
    for (int i = 0; i < group.getCurrentNumber(); ++i) {
        ASSERT_EQ(group[i].type, in);
    }
    group = p.groupOfContacts(1);
    for (int i = 0; i < group.getCurrentNumber(); ++i) {
        ASSERT_EQ(out, group[i].type);
    }
}

TEST (PCBMethods, groupOfContactsException) {
    printedCircuitBoard p;
    ASSERT_ANY_THROW(p.groupOfContacts(9));
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}