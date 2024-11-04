#include "filehandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// FileHandler implementation
FileHandler::FileHandler(const std::string& fname) : filename(fname) {}

// NameFileHandler implementation
NameFileHandler::NameFileHandler(const std::string& fname, std::map<std::string, Student>& studs)
    : FileHandler(fname), students(studs) {}

bool NameFileHandler::readFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening name file: " << filename << std::endl;
        return false;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, firstName, lastName;
        
        std::getline(ss, id, ',');
        std::getline(ss, firstName, ',');
        std::getline(ss, lastName);

        id.erase(remove_if(id.begin(), id.end(), isspace), id.end());
        firstName.erase(remove_if(firstName.begin(), firstName.end(), isspace), firstName.begin());
        lastName.erase(remove_if(lastName.begin(), lastName.end(), isspace), lastName.begin());

        Student student;
        student.id = id;
        student.name = firstName + " " + lastName;
        students[id] = student;
    }

    file.close();
    return true;
}

// CourseFileHandler implementation
CourseFileHandler::CourseFileHandler(const std::string& fname, std::map<std::string, Student>& studs)
    : FileHandler(fname), students(studs) {}

bool CourseFileHandler::readFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening course file: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, courseCode;
        std::vector<double> grades;
        std::string grade;

        std::getline(ss, id, ',');
        std::getline(ss, courseCode, ',');

        id.erase(remove_if(id.begin(), id.end(), isspace), id.end());
        courseCode.erase(remove_if(courseCode.begin(), courseCode.end(), isspace), courseCode.end());

        for (int i = 0; i < 4; i++) {
            std::getline(ss, grade, ',');
            grades.push_back(std::stod(grade));
        }

        if (students.find(id) != students.end()) {
            students[id].courses[courseCode] = grades;
        }
    }

    file.close();
    return true;
}