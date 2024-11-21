#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <string>
#include <map>
#include "../src/student.h"
#include "../src/filehandler.h"
#include "../src/gradecalculator.h"

class TestSuite {
private:
    int passed;
    std::string name; // name of test (has to match testfile name)
    int total;
    std::map<std::string, Student> testStudents;  
    std::map<std::string, Student> testStudentsExpected; 
    std::map<int, StudentFinal> testFinalStudentsExpected; 

    
    void printResult(const std::string& testName, bool passed);
    
    // Helper methods
    void setupTestData();  // Initialize test data
    
    // Individual test methods
    bool testNameFileHandlerRead();
    bool testCourseFileHandlerRead();
    bool testGradeCalculatorConstructor();

public:
    TestSuite(std::string name);
    void runAllTests();
    void printSummary();
};

#endif 