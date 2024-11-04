#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H

#include "student.h"
#include <map>
#include <string>

class GradeCalculator {
private:
    std::map<std::string, Student>& students;
    double calculateFinalGrade(const std::vector<double>& grades);

public:
    GradeCalculator(std::map<std::string, Student>& studs);
    bool writeOutputFile(const std::string& outputFilename);
};

#endif
