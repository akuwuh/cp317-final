#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>
#include <vector>

struct StudentFinal { 
    std::string id;
    std::string name;
    std::unordered_map<std::string, double> courses;
};
struct Student {
    std::string id;
    std::string name;
    std::unordered_map<std::string, std::vector<double> > courses;
};

#endif