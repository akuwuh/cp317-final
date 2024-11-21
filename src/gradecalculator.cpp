#include "gradecalculator.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cassert>

// constructor
GradeCalculator::GradeCalculator(std::map<std::string, Student>& studs)  {
    assert(&studs); // offensive
    // deep copies student
    for (const auto& [id, student] : studs) {
        StudentFinal studentFinal;
        studentFinal.id = id; 
        studentFinal.name = student.name;
        this->finalStudents[stoi(id)] = studentFinal;
        for (const auto& [courseCode, grades] : student.courses) {
            double finalGrade = this->calculateFinalGrade(grades);
            this->finalStudents[stoi(id)].courses[courseCode] = this->calculateFinalGrade(grades); 
        }
        this->orderedId.push_back(stoi(id));
    }

    sort(this->orderedId.begin(), this->orderedId.end());
}

// calculate final grade for a course
double GradeCalculator::calculateFinalGrade(const std::vector<double>& grades) {
    assert(&grades);
    assert(grades.size() == 4); // offensive programming

    double test1 = grades[0]; 
    double test2 = grades[1];
    double test3 = grades[2];
    double final_test = grades[3];

    return std::round(((test1 * 0.2) + (test2 * 0.2) + (test3 * 0.2) + (final_test * 0.4)) * 10.0) / 10.0;
}

bool GradeCalculator::writeOutputFile(const std::string& outputFilename) {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFilename << std::endl;
        return false;
    }

    for (const auto& id : this->orderedId) {
        for (const auto& [courseCode, finalGrade] : this->finalStudents[id].courses) {
            outFile << std::fixed << std::setprecision(1);
            outFile << this->finalStudents[id].id << "," 
                   << this->finalStudents[id].name << "," 
                   << courseCode << "," 
                   << finalGrade << "\n";
        }
    }
    

    outFile.close();
    return true;
}