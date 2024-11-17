#include "testsuite.h"
#include <iostream>

int main() {
    try {
        TestSuite test("test1");
        test.runAllTests();
        test.printSummary();
    } catch (const std::exception& e) {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
