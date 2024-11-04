#include "gradecalculator.h"
#include <fstream>
#include <iomanip>
#include <iostream>

GradeCalculator::GradeCalculator(std::map<std::string, Student>& studs) : students(studs) {}

double GradeCalculator::calculateFinalGrade(const std::vector<double>& grades) {
    return (grades[0] * 0.2 + grades[1] * 0.2 + grades[2] * 0.2 + grades[3] * 0.4);
}

bool GradeCalculator::writeOutputFile(const std::string& outputFilename) {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        return false;
    }

    outFile << "Student ID,Student Name,Course Code,Final Grade\n";

    for (const auto& [id, student] : students) {
        for (const auto& [courseCode, grades] : student.courses) {
            double finalGrade = calculateFinalGrade(grades);
            outFile << std::fixed << std::setprecision(1);
            outFile << student.id << "," 
                   << student.name << "," 
                   << courseCode << "," 
                   << finalGrade << "\n";
        }
    }

    outFile.close();
    return true;
}