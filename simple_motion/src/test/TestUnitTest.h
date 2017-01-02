//
// Created by troy on 12/30/16.
//


#pragma once

#ifndef TESTUNITTEST_H
#define TESTUNITTEST_H

#include <cppunit/extensions/HelperMacros.h>      // 必须的头文件

class TestUnitTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TestUnitTest);         // 测试集声明开始
        CPPUNIT_TEST(test_success);           // 测试函数1
        CPPUNIT_TEST(test_fail);              // 测试函数2
        CPPUNIT_TEST(test_double_success);    // 测试函数3
        CPPUNIT_TEST(test_double_fail);       // 测试函数4
    CPPUNIT_TEST_SUITE_END();                 // 测试集声明结束

public:
    void test_success();

    void test_fail();

    void test_double_success();

    void test_double_fail();
};


#endif //TESTUNITTEST_H
