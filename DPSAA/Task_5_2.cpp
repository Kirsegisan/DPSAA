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
    char group[100];
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
        student.id = 100000 + i;
        sprintf_s(student.group, "Product%d", i + 1);
        sprintf_s(student.name, "City_%d", i + 1);
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


int binarySearch(const vector<Student>& students, int id) {
    int left = 1;
    int right = students.size();
    int flag = 0;
    int d;
    while (left <= right && flag == 0) {
        d = (left + right) / 2;
        if (students[d].id == id) {
            flag = 1;
        }
        if (id > students[d].id) {
            left = d + 1;
        }
        if (id < students[d].id) {
            right = d - 1;
        }
    }
    if (flag == 1) {
        return d;
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
    int index = binarySearch(students, searchId);
    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;

    if (index != -1) {
        cout << "Товар найден: "
            << "Номер товара: " << students[index].id << ", "
            << "Наименование товара: " << students[index].group << ", "
            << endl;
    }
    else {
        cout << "Такой товар не найден" << endl;
    }

    cout << "Время выполнения поиска: " << elapsed.count() << " мс" << endl;
}


void Task_5_2() {
    setlocale(LC_ALL, "");
    const string textFilename = "D:\\MyApp\\DPSAA\\DPSAA\\students.txt";
    const string binaryFilename = "D:\\MyApp\\DPSAA\\DPSAA\\students.dat";

    vector<int> studentCounts = { 100, 1000, 10000 };
    int searchId;

    for (int count : studentCounts) {
        createTextFile(textFilename, count);
        createBinaryFile(textFilename, binaryFilename);

        cout << "Что ищем? ";
        cin >> searchId;

        searchInFile(binaryFilename, searchId);
        cout << "-------------------------------------------" << endl;
    }
}
