//
// Created by troy on 1/3/17.
//

#include "TrapezoidInterpolationTest.h"
#include "interpolation/trapezoid_interpolation.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TrapezoidInterpolationTest);                      // 注册到全局测试集

void TrapezoidInterpolationTest::test_move_forward() {
    TrapezoidInterpolation algorithm;
    algorithm.position = 300;
    algorithm.velocity = 20;
    algorithm.acceleration = 2;
    algorithm.deceleration = 2;

    algorithm.start(0, 0, 0);
    algorithm.move(5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(25, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(10, algorithm.get_velocity(), 0.1);

    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(100, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(20, algorithm.get_velocity(), 0.1);

    algorithm.move(12.5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(150, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(20, algorithm.get_velocity(), 0.1);

    algorithm.move(15);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(200, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(20, algorithm.get_velocity(), 0.1);

    algorithm.move(20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(275, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(10, algorithm.get_velocity(), 0.1);

    algorithm.move(25);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(300, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);

    algorithm.move(30);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(300, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);
}

void TrapezoidInterpolationTest::test_move_backward() {
    TrapezoidInterpolation algorithm;
    algorithm.position = -300;
    algorithm.velocity = -20;
    algorithm.acceleration = -2;
    algorithm.deceleration = -2;

    algorithm.start(0, 0, 0);
    algorithm.move(5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-25, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10, algorithm.get_velocity(), 0.1);

    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-100, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-20, algorithm.get_velocity(), 0.1);

    algorithm.move(12.5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-150, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-20, algorithm.get_velocity(), 0.1);

    algorithm.move(15);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-200, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-20, algorithm.get_velocity(), 0.1);

    algorithm.move(20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-275, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-10, algorithm.get_velocity(), 0.1);

    algorithm.move(25);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-300, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);

    algorithm.move(30);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-300, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);
}

void TrapezoidInterpolationTest::test_move_nonlinear() {
    TrapezoidInterpolation algorithm;
    algorithm.position = 200;
    algorithm.velocity = 20;
    algorithm.acceleration = 2;
    algorithm.deceleration = 2;

    algorithm.start(0, 0, 0);
    algorithm.move(5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(25, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(10, algorithm.get_velocity(), 0.1);

    algorithm.move(10);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(100, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(20, algorithm.get_velocity(), 0.1);

    algorithm.move(15);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(175, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(10, algorithm.get_velocity(), 0.1);

    algorithm.move(20);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(200, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);

    algorithm.move(25);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(200, algorithm.get_position(), 0.1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0, algorithm.get_velocity(), 0.1);
}
