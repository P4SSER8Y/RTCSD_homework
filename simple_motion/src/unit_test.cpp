//
// Created by troy on 12/30/16.
//

#include <iostream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;

    if (argc <= 1) {
        std::cout << "=== global test ===" << std::endl;
        CppUnit::TestFactoryRegistry &registry =
                CppUnit::TestFactoryRegistry::getRegistry();
        runner.addTest(registry.makeTest());
    } else {
        std::cout << "=== test suit: " << argv[1] << " ===" << std::endl;
        CppUnit::TestFactoryRegistry &registry =
                CppUnit::TestFactoryRegistry::getRegistry(argv[1]);
        runner.addTest(registry.makeTest());
    }

    runner.run();
}
