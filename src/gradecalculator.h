#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H

#include "student.h"
#include <map>
#include <string>

#include "../tests/testsuite.h"

class GradeCalculator {
private:
    std::map<int, StudentFinal> finalStudents;
    std::vector<int> orderedId; 
    double calculateFinalGrade(const std::vector<double>& grades);

public:
    GradeCalculator(std::map<std::string, Student>& studs);
    bool writeOutputFile(const std::string& outputFilename);

    friend class TestSuite; 
};



#endif
