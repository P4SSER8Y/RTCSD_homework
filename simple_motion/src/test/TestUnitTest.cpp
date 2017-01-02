//
// Created by troy on 12/30/16.
//

#include "TestUnitTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestUnitTest, "unit_test");  // 注册为单一测试集

void TestUnitTest::test_success() {
    CPPUNIT_ASSERT(true);
    CPPUNIT_ASSERT(1 == 1);
}

void TestUnitTest::test_fail() {
    CPPUNIT_ASSERT(1 == 1);
    CPPUNIT_ASSERT(false);
}

void TestUnitTest::test_double_success() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 1.2, 0.5);
}

void TestUnitTest::test_double_fail() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 1.2, 0.1);
}

