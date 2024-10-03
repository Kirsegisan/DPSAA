#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono> 

using namespace std;
using namespace std::chrono;

struct Student {
    int id; // key
    int group;
    char name[100];
};

bool compareById(const Student& a, const Student& b) {
    return a.id < b.id;
}

void createTextFile(const string& filename, int count) {
    ofstream outfile(filename);
    srand(time(0));

    for (int i = 0; i < count; i++) {
        Student student;
        student.id = rand() % 10000;
        student.group = rand() % 10 + 1;
        printf(student.name, "Student_%d", i + 1);
        outfile << student.id << " " << student.group << " " << student.name << endl;
    }
    outfile.close();
}

void createBinaryFile(const string& textFilename, const string& binaryFilename) {
    ifstream textFile(textFilename);
    ofstream binaryFile(binaryFilename, ios::binary);

    Student student;

    while (textFile >> student.id >> student.group >> student.name) {
        binaryFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
    }

    textFile.close();
    binaryFile.close();
}

int linearSearch(const vector<Student>& students, int id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

void searchInFile(const string& binaryFilename, int searchId) {
    ifstream binaryFile(binaryFilename, ios::binary);
    vector<Student> students;
    Student student;

    while (binaryFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        students.push_back(student);
    }

    binaryFile.close();

    auto start = high_resolution_clock::now();
    int index = linearSearch(students, searchId);
    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;

    if (index != -1) {
        cout << "Студент найден: "
            << "ID: " << students[index].id << ", "
            << "Группа: " << students[index].group << ", "
            << "ФИО: " << students[index].name << endl;
    }
    else {
        cout << "Студент с ID " << searchId << " не найден" << endl;
    }

    cout << "Время выполнения поиска: " << elapsed.count() << " мс" << endl;
}

int main() {
    setlocale(LC_ALL, "");
    const string textFilename = "C:\\Users\\112\\Desktop\\students\\students.txt";
    const string binaryFilename = "C:\\Users\\112\\Desktop\\students\\students.dat";

    vector<int> studentCounts = { 100, 1000, 10000 };
    int searchId;

    for (int count : studentCounts) {
        createTextFile(textFilename, count);
        createBinaryFile(textFilename, binaryFilename);

        cout << "Введите номер зачётной книжки " << count << " записями: ";
        cin >> searchId;

        searchInFile(binaryFilename, searchId);
        cout << "-------------------------------------------" << endl;
    }

    return 0;
}
