#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    string group;
    int studentId;
    int grades[4];

public:
    Student() {}

    Student(const string& name, const string& group, int studentId, const int* grades) : name(name), group(group), studentId(studentId) {
        for (int i = 0; i < 4; ++i) {
            this->grades[i] = grades[i];
        }
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Group: " << student.group << ", Student ID: " << student.studentId << ", Grades: ";
        for (int i = 0; i < 4; ++i) {
            os << student.grades[i] << " ";
        }
        return os;
    }
};

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open input file" << endl;
        return 1;
    }

    list<Student> students;
    string name, group;
    int studentId, grades[4];

    while (inputFile >> name >> group >> studentId >> grades[0] >> grades[1] >> grades[2] >> grades[3]) {
        students.emplace_back(name, group, studentId, grades);
    }
    inputFile.close();

    // Вывод исходного контейнера list
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Unable to open output file" << endl;
        return 1;
    }

    outputFile << "Original List Container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }
    outputFile << endl;

    students.sort([](const Student& a, const Student& b) {
        return a.name < b.name;
        });

    // Вывод контейнера list после сортировки
    outputFile << "Sorted List Container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }
    outputFile << endl;

    // Копирование вектора из отсортированного списка
    vector<Student> studentsVector(students.begin(), students.end());

    // Вывод контейнера vector, скопированного из исходного контейнера list
    outputFile << "Copied Vector Container from List:" << endl;
    for (const auto& student : studentsVector) {
        outputFile << student << endl;
    }

    outputFile.close();

    return 0;
}