#ifndef FILEHANDLERS_H
#define FILEHANDLERS_H

#include <string>
#include <map>
#include "student.h"

// Base class for file handling
class FileHandler {
protected:
    std::string filename;

public:
    FileHandler(const std::string& fname);
    virtual ~FileHandler() = default;
    virtual bool readFile() = 0;
};

// Derived class for handling name file
class NameFileHandler : public FileHandler {
private:
    std::map<std::string, Student>& students;

public:
    NameFileHandler(const std::string& fname, std::map<std::string, Student>& studs);
    bool readFile() override;
};

// Derived class for handling course file
class CourseFileHandler : public FileHandler {
private:
    std::map<std::string, Student>& students;

public:
    CourseFileHandler(const std::string& fname, std::map<std::string, Student>& studs);
    bool readFile() override;
};

#endif