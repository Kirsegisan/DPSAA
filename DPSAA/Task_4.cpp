#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>

using namespace std;

void Out(int x[], int n) {
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

long c = 0, m = 0;


void directMergeNUMS(const int& size) {
    std::fstream fileA, fileB, fileC;
    int n = 1;
    while (n < size) {
        // фаза разделения
        fileB.open("B.txt", std::ios::out | std::ios::trunc);
        fileC.open("C.txt", std::ios::out | std::ios::trunc);
        fileA.open("A.txt", std::ios::in);
        for (int i = 0; i < size; i++) {
            int word;
            fileA >> word;
            if (i % (2 * n) < n) fileB << " " << word;
            else fileC << " " << word;
        }
        fileA.close();
        fileB.close();
        fileC.close();

        // фаза слияния
        fileB.open("B.txt", std::ios::in);
        fileC.open("C.txt", std::ios::in);
        fileA.open("A.txt", std::ios::out | std::ios::trunc);
        int wordB, wordC;
        for (int portion = 0; portion <= size / (2 * n); portion++) {
            int curSizeB = n;
            int curSizeC = n;
            if (fileB.eof()) curSizeB = 0;
            else fileB >> wordB;
            if (fileC.eof()) curSizeC = 0;
            else fileC >> wordC;
            while (curSizeB != 0 && curSizeC != 0) {
                if (wordB <= wordC) {
                    fileA << wordB << " ";
                    curSizeB--;
                    if (fileB.eof()) curSizeB = 0;
                    if (curSizeB != 0) fileB >> wordB;
                }
                else {
                    fileA << wordC << " ";
                    curSizeC--;
                    if (fileC.eof()) curSizeC = 0;
                    if (curSizeC != 0) fileC >> wordC;
                }
            }
            while (curSizeB != 0) {
                fileA << wordB << " ";
                curSizeB--;
                if (fileB.eof()) break;
                if (curSizeB != 0) fileB >> wordB;
            }
            while (curSizeC != 0) {
                fileA << wordC << " ";
                curSizeC--;
                if (fileC.eof()) break;
                if (curSizeC != 0) fileC >> wordC;
            }
        }
        fileA.close();
        fileB.close();
        fileC.close();
        n *= 2;
    }
}


void insertionSortNUMS(int* A, int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

void naturalMergeNUMS(const int& size) {
    std::fstream fileA, fileB, fileC;
    int bufSize = 4;
    int* buf = new int[bufSize];
    fileB.open("B.txt", std::ios::out | std::ios::trunc);
    fileC.open("C.txt", std::ios::out | std::ios::trunc);
    fileA.open("A.txt", std::ios::in);
    int i = 0, j = 0;
    bool isB = false;
    int word;
    while (i < size) {
        fileA >> word;
        i++;
        buf[j] = word;
        j++;
        if (j == bufSize) {
            insertionSortNUMS(buf, bufSize);
            isB = !isB;
            while (j > 0) {
                if (isB) fileB << " " << buf[bufSize - j];
                else fileC << " " << buf[bufSize - j];
                j--;
            }
        }
    }
    if (j != 0) {
        insertionSortNUMS(buf, j);
        isB = !isB;
        i = 0;
        while (i < j) {
            if (isB) fileB << " " << buf[i];
            else fileC << " " << buf[i];
            i++;
        }
    }
    delete[] buf;
    fileA.close();
    fileB.close();
    fileC.close();


    fileB.open("B.txt", std::ios::in);
    fileC.open("C.txt", std::ios::in);
    fileA.open("A.txt", std::ios::out | std::ios::trunc);
    while (!fileB.eof()) {
        fileB >> word;
        fileA << " " << word;
    }
    while (!fileC.eof()) {
        fileC >> word;
        fileA << " " << word;
    }
    fileA.close();
    fileB.close();
    fileC.close();
    while (true) {
        // фаза разделения
        fileB.open("B.txt", std::ios::out | std::ios::trunc);
        fileC.open("C.txt", std::ios::out | std::ios::trunc);
        fileA.open("A.txt", std::ios::in);
        isB = true;
        fileA >> word;
        int prevWord = word;
        fileB << " " << word;
        int series = 1;
        while (!fileA.eof()) {
            fileA >> word;
            if (prevWord > word) {
                isB = !isB;
                series++;
            }
            if (isB) fileB << " " << word;
            else fileC << " " << word;
            prevWord = word;
        }
        fileA.close();
        fileB.close();
        fileC.close();
        if (series == 1) return;
        // фаза слияния
        fileB.open("B.txt", std::ios::in);
        fileC.open("C.txt", std::ios::in);
        fileA.open("A.txt", std::ios::out | std::ios::trunc);
        int wordB, wordC;
        int prevWordB, prevWordC;
        fileB >> wordB;
        fileC >> wordC;
        for (int pair = 0; pair < series / 2; pair++) {
            bool endB = false, endC = false;
            while (!endB && !endC) {
                if (wordB <= wordC) {
                    fileA << " " << wordB;
                    if (fileB.eof()) {
                        endB = true;
                        break;
                    }
                    prevWordB = wordB;
                    fileB >> wordB;
                    if (prevWordB > wordB) endB = true;
                }
                else {
                    fileA << " " << wordC;
                    if (fileC.eof()) {
                        endC = true;
                        break;
                    }
                    prevWordC = wordC;
                    fileC >> wordC;
                    if (prevWordC > wordC) endC = true;
                }
            }
            while (!endB) {
                fileA << " " << wordB;
                if (fileB.eof()) break;
                prevWordB = wordB;
                fileB >> wordB;
                if (prevWordB > wordB) break;
            }
            while (!endC) {
                fileA << " " << wordC;
                if (fileC.eof()) break;
                prevWordC = wordC;
                fileC >> wordC;
                if (prevWordC > wordC) break;
            }
        }
        while (!fileB.eof()) {
            fileA << " " << wordB;
            fileB >> wordB;
        }
        while (!fileC.eof()) {
            fileA << " " << wordC;
            fileC >> wordC;
        }
        fileA.close();
        fileB.close();
        fileC.close();
    }
}




void straight_merge(int size) {
    fstream fileA, fileB, fileC;
    int n = 1;
    while (n < size) {
        fileB.open("B.txt", std::ios::out | std::ios::trunc);
        fileC.open("C.txt", std::ios::out | std::ios::trunc);
        fileA.open("A.txt", std::ios::in);
        for (int i = 0; i < size; i++) {
            std::string line;
            std::getline(fileA, line);
            if (i % (2 * n) < n) fileB << line << std::endl;
            else fileC << line << std::endl;
        }
        fileA.close();
        fileB.close();
        fileC.close();
        // фаза слияния
        fileB.open("B.txt", std::ios::in);
        fileC.open("C.txt", std::ios::in);
        fileA.open("A.txt", std::ios::out | std::ios::trunc);
        std::string lineB, lineC, wordB, wordC;
        for (int portion = 0; portion <= size / (2 * n); portion++) {
            int curSizeB = n;
            int curSizeC = n;
            if (fileB.eof()) {
                curSizeB = 0;
            }
            else {
                std::getline(fileB, lineB);
                std::stringstream streamB(lineB);
                for (int i = 0; i < 5; i++) {
                    streamB >> wordB;
                }
            }
            if (fileC.eof()) {
                curSizeC = 0;
            }
            else {
                std::getline(fileC, lineC);
                std::stringstream streamC(lineC);
                for (int i = 0; i < 5; i++) {
                    streamC >> wordC;
                }
            }
            while (curSizeB != 0 && curSizeC != 0) {
                if (wordB <= wordC) {
                    fileA << lineB << std::endl;
                    curSizeB--;
                    if (fileB.eof()) {
                        curSizeB = 0;
                    }
                    if (curSizeB != 0) {
                        std::getline(fileB, lineB);
                        std::stringstream streamB(lineB);
                        for (int i = 0; i < 5; i++) {
                            streamB >> wordB;
                        }
                    }
                }
                else {
                    fileA << lineC << std::endl;
                    curSizeC--;
                    if (fileC.eof()) {
                        curSizeC = 0;
                    }
                    if (curSizeC != 0) {
                        std::getline(fileC, lineC);
                        std::stringstream streamC(lineC);
                        for (int i = 0; i < 5; i++) {
                            streamC >> wordC;
                        }
                    }
                }
            }
            while (curSizeB != 0) {
                fileA << lineB << std::endl;
                curSizeB--;
                if (fileB.eof()) break;
                if (curSizeB != 0) {
                    std::getline(fileB, lineB);
                    std::stringstream streamB(lineB);
                    for (int i = 0; i < 5; i++) {
                        streamB >> wordB;
                    }
                }
            }
            while (curSizeC != 0) {
                fileA << lineC << std::endl;
                curSizeC--;
                if (fileC.eof()) break;
                if (curSizeC != 0) {
                    std::getline(fileC, lineC);
                    std::stringstream streamC(lineC);
                    for (int i = 0; i < 5; i++) {
                        streamC >> wordC;
                    }
                }
            }
        }
        fileA.close();
        fileB.close();
        fileC.close();
        n *= 2;
    }
}

void insertionSort(string* A, int n) {
    for (int i = 1; i < n; i++) {
        string key_i = A[i], word_i;
        stringstream stream_i(key_i);

        for (int k = 0; k < 5; k++)
            stream_i >> word_i;

        int j = i - 1;
        string key_j = A[j], word_j;
        stringstream stream_j(key_j);
        for (int k = 0; k < 5; k++)
            stream_j >> word_j;

        while (j >= 0 && stoi(word_j) > stoi(word_i)) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key_i;
    }
}

void naturalMerge(int size, int bufSize) {
    fstream fileA, fileB, fileC;
    string* buf = new string[bufSize];

    fileB.open("B.txt", ios::out | ios::trunc);
    fileC.open("C.txt", ios::out | ios::trunc);
    fileA.open("A.txt", ios::in);
    bool openB = true, openC = true;


    int i = 0, j = 0;
    bool isB = false;
    string line;
    while (i < size) {
        getline(fileA, line);
        i++;
        buf[j] = line;
        j++;
        if (j == bufSize) {
            insertionSort(buf, bufSize);
            isB = !isB;
            while (j > 0) {
                if (isB) {
                    if (openB) { fileB << buf[bufSize - j]; openB = false; }
                    else fileB << endl << buf[bufSize - j];
                }
                else {
                    if (openC) { fileC << buf[bufSize - j]; openC = false; }
                    else fileC << endl << buf[bufSize - j];
                }
                j--;
            }
        }
    }
    if (j != 0) {
        insertionSort(buf, j);
        isB = !isB;
        i = 0;
        while (i < j) {
            if (isB) {
                if (openB) { fileB << buf[i]; openB = false; }
                else fileB << endl << buf[i];
            }
            else {
                if (openC) { fileC << buf[i]; openC = false; }
                else fileC << endl << buf[i];
            }
            i++;
        }
    }
    delete[] buf;
    fileA.close();
    fileB.close();
    fileC.close();

    fileB.open("B.txt", ios::in);
    fileC.open("C.txt", ios::in);
    fileA.open("A.txt", ios::out | ios::trunc);
    bool openA = true;

    while (!fileB.eof()) {
        getline(fileB, line);
        if (openA) { fileA << line; openA = false; }
        else fileA << endl << line;
    }
    while (!fileC.eof()) {
        getline(fileC, line);
        if (openA) { fileA << line; openA = false; }
        else fileA << endl << line;
    }
    fileA.close();
    fileB.close();
    fileC.close();

    while (true) {
        fileB.open("B.txt", ios::out | ios::trunc);
        fileC.open("C.txt", ios::out | ios::trunc);
        fileA.open("A.txt", ios::in);
        openB = true; openC = true;

        isB = true;
        getline(fileA, line);
        string prevline = line, prevWord, word;
        stringstream stream(line);
        for (int k = 0; k < 5; k++)
            stream >> word;
        stringstream stream_1(prevline);
        for (int k = 0; k < 5; k++)
            stream_1 >> prevWord;

        if (openB) { fileB << line; openB = false; }
        else fileB << endl << line;
        int series = 1;

        while (!fileA.eof()) {
            getline(fileA, line);
            stringstream stream(line);
            for (int k = 0; k < 5; k++)
                stream >> word;
            if (prevWord > word) {
                isB = !isB;
                series++;
            }
            if (isB) {
                if (openB) { fileB << line; openB = false; }
                else fileB << endl << line;
            }
            else {
                if (openC) { fileC << line; openC = false; }
                else fileC << endl << line;
            }


            prevline = line;
            stringstream stream_2(prevline);
            for (int k = 0; k < 5; k++)
                stream_2 >> prevWord;
        }
        fileA.close();
        fileB.close();
        fileC.close();
        if (series == 1) return;

        fileB.open("B.txt", ios::in);
        fileC.open("C.txt", ios::in);
        fileA.open("A.txt", ios::out | ios::trunc);
        openA = true;

        string lineB, lineC, wordB, wordC;
        string prevLineB, prevLineC, prevWordB, prevWordC;

        getline(fileB, lineB);
        stringstream stream_3(lineB);
        for (int k = 0; k < 5; k++)
            stream_3 >> wordB;

        getline(fileC, lineC);
        stringstream stream_4(lineC);
        for (int k = 0; k < 5; k++)
            stream_4 >> wordC;
        for (int pair = 0; pair < series / 2; pair++) {
            bool endB = false, endC = false;
            while (!endB && !endC) {
                if (wordB <= wordC) {
                    if (openA) { fileA << lineB; openA = false; }
                    else fileA << endl << lineB;
                    if (fileB.eof()) {
                        endB = true;
                        break;
                    }
                    prevLineB = lineB;
                    prevWordB = wordB;
                    getline(fileB, lineB);
                    stringstream stream(lineB);
                    for (int k = 0; k < 5; k++)
                        stream >> wordB;
                    if (prevWordB > wordB) endB = true;
                }
                else {
                    if (openA) { fileA << lineC; openA = false; }
                    else fileA << endl << lineC;
                    if (fileC.eof()) {
                        endC = true;
                        break;
                    }
                    prevLineC = lineC;
                    prevWordC = wordC;
                    getline(fileC, lineC);
                    stringstream stream(lineC);
                    for (int k = 0; k < 5; k++)
                        stream >> wordC;
                    if (prevWordC > wordC) endC = true;
                }
            }
            while (!endB) {
                if (openA) { fileA << lineB; openA = false; }
                else fileA << endl << lineB;
                if (fileB.eof()) break;
                prevLineB = lineB;
                prevWordB = wordB;

                getline(fileB, lineB);
                stringstream stream(lineB);
                for (int k = 0; k < 5; k++)
                    stream >> wordB;

                if (prevWordB > wordB) break;
            }
            while (!endC) {
                if (openA) { fileA << lineC; openA = false; }
                else fileA << endl << lineC;
                if (fileC.eof()) break;
                prevLineC = lineC;
                prevWordC = wordC;

                getline(fileC, lineC);
                stringstream stream(lineC);
                for (int k = 0; k < 5; k++)
                    stream >> wordC;

                if (prevWordC > wordC) break;
            }
        }
        while (!fileB.eof()) {
            if (openA) { fileA << lineB; openA = false; }
            else fileA << endl << lineB;
            getline(fileB, lineB);
        }
        while (!fileC.eof()) {
            if (openA) { fileA << lineC; openA = false; }
            else fileA << endl << lineC;
            getline(fileC, lineC);
        }
        fileA.close();
        fileB.close();
        fileC.close();
    }
}


int Task_4()
{
    setlocale(LC_ALL, "Russian");

    auto begin = chrono::steady_clock::now();

    //    naturalMerge(8, 2);
    //    straight_merge(8);
    //    directMergeNUMS(16);
    //naturalMergeNUMS(20);

    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);

    cout << "Время: " << elapsed_ms.count() << " ms\n";

    return 0;


}
