#include "filehandler.h"
#include "gradecalculator.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string nameFilePath;
    std::string courseFilePath;
    std::string outputFilePath;
    
    if (argc == 1) {
        nameFilePath = "../input/NameFile.txt";
        courseFilePath = "../input/CourseFile.txt";
        outputFilePath = "../output/output.txt";
    } else if (argc == 4) {
        nameFilePath = argv[1]; 
        courseFilePath = argv[2];
        outputFilePath = argv[3];
    } else {
        std::cerr << "Error not enough arguments" << std::endl;
        return 1;
    }

    std::map<std::string, Student> students;

    NameFileHandler nameHandler(nameFilePath, students);
    if (!nameHandler.readFile()) {
        std::cerr << "Error processing name file" << std::endl;
        return 1;
    }

    CourseFileHandler courseHandler(courseFilePath, students);
    if (!courseHandler.readFile()) {
        std::cerr << "Error processing course file" << std::endl;
        return 1;
    }

    GradeCalculator calculator(students);
    if (!calculator.writeOutputFile(outputFilePath)) {
        std::cerr << "Error writing output file" << std::endl;
        return 1;
    }

    std::cout << "Grade processing completed successfully!" << std::endl;
    return 0;
}