//
// Created by troy on 1/2/17.
//

#include "LinearInterpolationTest.h"

#include "interpolation/linear_interpolation.h"

CPPUNIT_TEST_SUITE_REGISTRATION(LinearInterpolationTest);                      // 注册到全局测试集

void LinearInterpolationTest::test_normal_1() {
    LinearInterpolation algorithm;
    algorithm.position = 1000;
    algorithm.velocity = 10;

    algorithm.start(0, 0, 0);
    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(100, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(10, algorithm.get_velocity(), 0.1);
}

void LinearInterpolationTest::test_normal_2() {
    LinearInterpolation algorithm;
    algorithm.position = -1000;
    algorithm.velocity = -10;

    algorithm.start(0, 0, 0);
    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-100, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10, algorithm.get_velocity(), 0.1);
}

void LinearInterpolationTest::test_normal_3() {
    LinearInterpolation algorithm;
    algorithm.position = 1000;
    algorithm.velocity = 10;

    algorithm.start(0, 0, 0);
    algorithm.move(10);
    algorithm.move(1000);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1000, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0);
}

void LinearInterpolationTest::test_normal_4() {
    LinearInterpolation algorithm;
    algorithm.position = 1000;
    algorithm.velocity = 1000;

    algorithm.start(0, 0, 0);
    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1000, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);
}

