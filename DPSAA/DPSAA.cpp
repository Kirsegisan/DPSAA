#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <string>
#include <cstdlib>
#include "Task_4.cpp"
#include "Task_5_1.cpp"
#include "T3.cpp"
#include "T2C.cpp"
#include "T2B (1).cpp"

#pragma comment(linker, "/STACK:16777216")


using namespace std;


struct Node {
    int val;
    Node* next;
    Node(int _val) : val(_val), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;


    list() : first(nullptr), last(nullptr) {}


    bool isEmpty() {
        return first == nullptr;
    }


    void pushBack(int _val) {
        Node* p = new Node(_val);
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
        last -> next = p;
        last = p;
    }


    void pushFirst(int val) {
        Node* p = new Node(val);
        p->next = first;
        first = p;
    }


    void print() {
        if (isEmpty()) return;
        Node* p = first;
        while(p) {
            std::cout << p->val << " ";
            p = p->next;
        }
        std::cout << endl;
    }


    Node* find(int _val) {
        Node* p = first;
        while (p && p->val != _val) p = p->next;
        return(p && p->val == _val) ? p : nullptr;
    }


    void removeFirst() {
        Node* buf = first;
        first = first->next;
        delete buf;
    }


    void removeLast() {
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->next != nullptr) {
            slow = fast;
            fast = fast->next;
        }
        slow->next = fast->next;
        delete fast;
    }





    void remove(int _val) {
        if (isEmpty()) return;
        if (first->val == _val) {
            removeFirst();
            return;
        }
        else if (last->val == _val) {
            removeLast();
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val) {
            slow = fast;
            fast = fast->next;
        }
        slow->next = fast->next;
        delete fast;
    }

};


list* generateRandomList(int n) {
    srand(time(0));
    int x = 0;
    list* l = new list();
    int* arr = new int[n];
    for (int i = 0;i < n; i++) {
        arr[i] = (rand() % 10);
    }
    sort(arr, arr + n);
    for (int j = 0;j < n; j++) {
        l->pushBack((arr[j] * 10) + (rand() % 10));
    }
    return l;
}


list* enterList() {
    int input;
    int previousValue = 0;
    list* l = new list();
    while (true)
    {
        std::cout << "To end enter -1" << std::endl;
        std::cout << "Enter next value: ";
        std::cin >> input;
        if (input == -1) {
            std::cout << "End enter " << std::endl;
            return l;
        }
        else if (previousValue <= input && input / 10 == 0) {
            l->pushBack(input);
            previousValue = input;
        }

        else if (previousValue / 10 <= input / 10 && input / 10 != 0) {
            l->pushBack(input);
            previousValue = input;
        }


        else {
            std::cout << "You should enter int value according to the rule: " << std::endl;
            std::cout << "Length of value {0 < n < 3} " << std::endl;
            std::cout << "Next value >= previous value at the first sign" << std::endl;

        }
    }
}


void V2()
{
    int size;
    std::cin >> size;
    size;
    int * data = new int[size];
    int angle;
    for (int i = 0; i < size; i++)
    {
        std::cin >> angle;
        if (0 <= angle && angle < 8) {
            data[i] = angle;
        }
        else 
        {
            std::cout << "Wrong value";
            i--;
        }
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
    vector<int> answer;
    answer = T2A(data, size);
    for (int i = 0; i < answer.size(); i++)
    {
        std::cout << answer[i] << "  ";
    }
}

//int main()
//{
//    std::cout << "Generate random list? (Y/N)   ";
//    char inputChar;
//    int inputInt;
//    list* l = new list();
//    bool isGenerated = true;
//    while (isGenerated) {
//        std::cout << std::endl;std::cout << std::endl;
//        std::cin >> inputChar;
//        std::cout << std::endl;
//        switch (inputChar) {
//        case 'Y': case'y':
//            std::cout << "Enter length: ";
//            std::cin >> inputInt;
//            std::cout << std::endl;
//            l = generateRandomList(inputInt);
//            std::cout << "Generated list: " << std::endl;
//            l->print();
//            isGenerated = false;
//            break;
//        case 'N': case'n':
//            l = enterList();
//            std::cout << "Generated list: " << std::endl;
//            l->print();
//            isGenerated = false;
//            break;
//        default:
//            std::cout << "You should enter Y or N";
//            continue;
//        }
//    }
//
//    while (true)
//    {
//        std::cout << std::endl;
//        std::cout << "To end enter -1" << std::endl;
//        std::cout << std::endl;
//        std::cout << "1) Print" << std::endl;
//        std::cout << "2) Push back" << std::endl;
//        std::cout << "3) Push first" << std::endl;
//        std::cout << "4) Find" << std::endl;
//        std::cout << "5) Remove" << std::endl;
//        std::cout << "6) Remove first" << std::endl;
//        std::cout << "7) Remove last" << std::endl;
//        std::cout << std::endl;
//        std::cout << "chose function: ";
//
//        std::cin >> inputInt;
//        switch (inputInt)
//        {
//        case -1:
//            return 0;
//        case 1:
//            std::cout << std::endl;
//            l->print();
//            continue;
//        case 2:
//            std::cout << std::endl;
//            std::cout << "Enter value: ";
//            std::cin >> inputInt;
//            std::cout << std::endl;
//            l->pushBack(inputInt);
//            continue;
//        case 3:
//            std::cout << std::endl;
//            std::cout << "Enter value: ";
//            std::cin >> inputInt;
//            std::cout << std::endl;
//            l->pushFirst(inputInt);
//            continue;
//        case 4:
//            std::cout << std::endl;
//            std::cout << "Enter value: ";
//            std::cin >> inputInt;
//            std::cout << std::endl;
//            std:: cout << l->find(inputInt) << std::endl;
//            std::cout << std::endl;
//            continue;
//        case 5:
//            std::cout << std::endl;
//            std::cout << "Enter value: ";
//            std::cin >> inputInt;
//            std::cout << std::endl;
//            l->remove(inputInt);
//            continue;
//        case 6:
//            std::cout << std::endl;
//            l->removeFirst();
//            continue;
//        case 7:
//            std::cout << std::endl;
//            l->removeLast();
//            continue;
//        default:
//            std::cout << "You should enter index of function" << std::endl;
//            break;
//        }
//    }
//
//    return 0;
//}


void DZ_Empty() {
    cout << "Task not found" << endl;
}

void generator() {
    ofstream outFile;
    outFile.open("input.txt", std::ofstream::out | std::ofstream::trunc);
    for (int i = 999999; i >= 100000; i--) {
        outFile << i << "\n";
    }
    outFile.close();
}
    

int main() {
    setlocale(LC_ALL, "Russian");

    int task;
    while (true)
    {
        std::cout << "Какоe задание вывести?" << std::endl;
        std::cin >> task;
        void (*psl)() = DZ_Empty;
        switch (task)
        {
            case 1: {
                psl = Task_2B;
                break;
            }
            case 2: {
                psl = Task_2V;
                break;
            }
            case 3: {
                psl = Task3;
                break;
            }
            case 0: {
                psl = generator;
                break;
            }
            case 4: {
                psl = Task_5_1;
                break;
            }
            case 5: {
                psl = T1V;
                break;
            }
            case 6: {
                psl = V2;
                break;
            }
            default: {
                cout << "Допустимые значения: 1/2/3";
                break;
            }
        }
        psl();
    }
}
