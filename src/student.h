#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>
#include <vector>

struct Student {
    std::string id;
    std::string name;
    std::map<std::string, std::vector<double> > courses;
};

#endif