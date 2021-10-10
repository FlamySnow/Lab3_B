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

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}