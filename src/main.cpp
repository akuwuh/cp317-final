#include "filehandler.h"
#include "gradecalculator.h"
#include <iostream>

int main() {
    std::map<std::string, Student> students;

    NameFileHandler nameHandler("../input/NameFile.txt", students);
    if (!nameHandler.readFile()) {
        std::cerr << "Error processing name file" << std::endl;
        return 1;
    }

    CourseFileHandler courseHandler("../input/CourseFile.txt", students);
    if (!courseHandler.readFile()) {
        std::cerr << "Error processing course file" << std::endl;
        return 1;
    }

    GradeCalculator calculator(students);
    if (!calculator.writeOutputFile("../output/output.txt")) {
        std::cerr << "Error writing output file" << std::endl;
        return 1;
    }

    std::cout << "Grade processing completed successfully!" << std::endl;
    return 0;
}