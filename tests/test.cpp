// #include "testsuite.h"
// #include <iostream>

// int main() {
//     try {
//         TestSuite test("test1");
//         test.runAllTests();
//         test.printSummary();
//     } catch (const std::exception& e) {
//         std::cerr << "Initialization failed: " << e.what() << std::endl;
//         return 1;
//     }
//     return 0;
// }


#include "testsuite.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

int main() {
    const std::string testSuitePath = "./testfiles/suite.txt";
    std::vector<std::string> testNames;

    std::ifstream testFile(testSuitePath);
    if (!testFile.is_open()) {
        std::cerr << "Error: Unable to open test suite file at " << testSuitePath << std::endl;
        return 1;
    }

    // Read each test name from the file
    std::string testName;
    while (std::getline(testFile, testName)) {
        // Trim whitespace from the test name (optional but recommended)
        size_t start = testName.find_first_not_of(" \t");
        size_t end = testName.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos) {
            testName = testName.substr(start, end - start + 1);
        }

        // Skip empty lines
        if (!testName.empty()) {
            testNames.push_back(testName);
        }
    }

    testFile.close();

    // Check if any tests were found
    if (testNames.empty()) {
        std::cerr << "Error: No tests found in " << testSuitePath << std::endl;
        return 1;
    }


    try {
        // Iterate over each test name and run the tests
        for (const auto& name : testNames) {
            std::cout << "-------------------" << std::endl;
            std::cout << "Running test: " << name << std::endl;
            std::cout << "-------------------" << std::endl;
            TestSuite test(name);
            test.runAllTests();
            test.printSummary();
            std::cout << "\n" << std::endl;
           
        }

        // Print aggregated summary (optional)
        // aggregateTestSuite.printSummary();

    } catch (const std::exception& e) {
        std::cerr << "Test execution failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "All tests executed." << std::endl;
    return 0;
}
