#include "testsuite.h"
#include <iostream>
#include <sstream>
#include <fstream>

TestSuite::TestSuite(std::string name) : name(name), passed(0), total(0) {
    this->setupTestData();
}

// Trim white space
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// delimiting function
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s);
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    
    return tokens;
}

// Function to load test students from a file
bool loadTestStudentsExpected(const std::string& filename, std::map<std::string, Student>& testStudentsExpected) {
    std::ifstream infile(filename);
    
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "' for reading." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        line = trim(line);

        // skip
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string id, first_name, last_name;
        
        // id + full name
        ss >> id >> first_name >> last_name;
        std::string full_name = first_name + " " + last_name;

        // init
        Student student;
        student.id = id;
        student.name = full_name;

        // courses
        std::string course_entry;
        while (ss >> course_entry) {
            // delimited by commas 
            std::vector<std::string> tokens = split(course_entry, ',');
            if (tokens.empty()) {
                continue; // skip if no tokens 
            }

            std::string course_name = tokens[0];
            std::vector<double> grades;

            for (size_t i = 1; i < tokens.size(); ++i) { // index 1 and onwards are test grades
                double grade = std::stod(tokens[i]);
                grades.push_back(grade);
            }

            student.courses[course_name] = grades;
        }

        testStudentsExpected[id] = student;
    }

    infile.close();
    return true;
}

void TestSuite::printResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

void TestSuite::setupTestData() {
    std::string expectedDataFile = "./testfiles/" + this->name + "/students_expected.txt";
    if (!loadTestStudentsExpected(expectedDataFile, this->testStudentsExpected)) {
        std::cerr << "Error: Failed to load expected test data from '" << expectedDataFile << "'." << std::endl;
        throw std::runtime_error("Failed to load test data.");
    }
}

// helper
bool verifyNameFileStudentMap (const std::map<std::string, Student> & input, const std::map<std::string, Student> & expected, const std::string& testName) {
    if (input.size() != expected.size()) {
        std::cerr << "[FAIL] " << testName << ": Size mismatch." << std::endl;
        std::cerr << "\tExpected: " << expected.size() << std::endl; 
        std::cerr << "\tGot: " << input.size() << std::endl;
        return false;
    }
    for (const auto& [key, val] : input) {   
        if (val.name != expected.at(key).name) {
            std::cerr << "[FAIL] " << testName << ": Name mismatch for key '" << key << "'." << std::endl;
            std::cerr << "\tExpected: " << expected.at(key).name << std::endl;
            std::cerr << "\tGot: " << val.name << std::endl;
            return false;
        }
        if (val.id != expected.at(key).id) {
            std::cerr << "[FAIL] " << testName << ": ID mismatch for key '" << key << "'." << std::endl;
            std::cerr << "\tExpected: " << expected.at(key).id << std::endl;
            std::cerr << "\tGot: " << val.id << std::endl;
            return false;
        }
    }
    return true;
}

bool TestSuite::testNameFileHandlerRead() {
    std::string inputFilePath = "./testfiles/" + this->name + "/names.txt";
    try {
        NameFileHandler nameHandler(inputFilePath, this->testStudents);
        if (!nameHandler.readFile()) {
            std::cerr << "[FAIL] testNameFileHandlerRead: Unable to read file." << std::endl;
            return false;
        }
        if (!verifyNameFileStudentMap(this->testStudents, this->testStudentsExpected, "testNameFileHandlerRead")) {
            return false;
        }
        return true;
    } catch (const std::exception& e) {
        std::cout << "[FAIL] testNameFileHandlerRead: " << e.what() << std::endl;
        return false;
    }
}



bool verifyCourseFileStudentMap(const std::map<std::string, Student>& input, const std::map<std::string, Student>& expected, const std::string& testName) {
    if (input.size() != expected.size()) { // size mismatch
        std::cerr << "[FAIL] " << testName << ": Size mismatch." << std::endl;
        std::cerr << "\tExpected: " << expected.size() << std::endl; 
        std::cerr << "\tGot: " << input.size() << std::endl;
        return false;
    }
    // iterate through every student
    for (const auto& [key, val] : input) {
        if (val.courses != expected.at(key).courses) {
            std::cerr << "[FAIL] " << testName << ": Courses Mismatch for " << val.id << "" << std::endl;
            std::cerr << "\tExpected: \n";
            for (const auto& [k, v] : val.courses) {
                std::cerr << "\t" << k << ": " << '[';
                for(auto& i : v) std::cerr << i << ',';
                std::cerr << "\b]" << std::endl; 
            }
            std::cerr << std::endl;
            std::cerr << "\tGot: \n";
            for (const auto& [k, v] : expected.at(key).courses) {
                std::cerr << "\t" << k << ": " << '[';
                for(auto& i : v) std::cerr << i << ',';
                std::cerr << "\b]" << std::endl; 
            }
        
            return false;
        }
        
    }
    return true;
}

// have to run after nameFileHandler
bool TestSuite::testCourseFileHandlerRead() {
    std::string inputFile = "./testfiles/" + this->name + "/courses.txt";
    CourseFileHandler courseHandler(inputFile, this->testStudents);
    try {
        if (!courseHandler.readFile()) {
            std::cerr << "[FAIL] testCourseFileHandlerRead: Unable to read course file." << std::endl;
            return false;
        }
        if (!verifyCourseFileStudentMap(this->testStudents, this->testStudentsExpected, "testCourseFileHandlerRead")) {
            return false;
        }
        return true; // Ensure return value on success
    } catch (const std::exception& e) {
        std::cout << "[FAIL] testCourseFileHandlerRead: " << e.what() << std::endl;
        return false;
    }
}

bool TestSuite::testGradeCalculatorOutput() {
    
}

void TestSuite::runAllTests() {
    total = 0;
    passed = 0;
    
    bool result;
    
    result = testNameFileHandlerRead();
    total++;
    if (result) passed++;
    printResult("Name File Handler Read Test", result);
    
    result = testCourseFileHandlerRead();
    total++;
    if (result) passed++;
    printResult("Course File Handler Read Test", result);
    
    result = testGradeCalculatorOutput();
    total++;
    if (result) passed++;
    printResult("Grade Calculator Output Test", result);
}



void TestSuite::printSummary() {
    std::cout << "\nTest Summary:\n";
    std::cout << "Passed: " << passed << "/" << total << " tests\n";
    std::cout << "Success Rate: " << (total > 0 ? (passed * 100.0 / total) : 0) << "%\n";
}