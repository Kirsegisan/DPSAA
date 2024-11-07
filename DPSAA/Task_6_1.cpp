#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Reader {
    int number;          // номер абонемента
    string fullName;    // ФИО
    string address;     // адрес
    Reader* next;       // указатель на следующий элемент в цепочке

    Reader(int num, const string& name, const string& addr)
        : number(num), fullName(name), address(addr), next(nullptr) {}
};

class HashTable {
private:
    vector<Reader*> table;
    int size;
    int count; // количество элементов в таблице

    int hashFunction(int key) {
        return key % size;
    }

    void rehash() {
        vector<Reader*> oldTable = table;
        size *= 2;
        table.clear();
        table.resize(size, nullptr);
        count = 0;

        for (Reader* node : oldTable) {
            while (node) {
                insert(node->number, node->fullName, node->address);
                Reader* temp = node;
                node = node->next;
                delete temp; // освобождаем память
            }
        }
    }

public:
    HashTable(int initialSize = 10)
        : size(initialSize), count(0) {
        table.resize(size, nullptr);
    }

    ~HashTable() {
        for (Reader* node : table) {
            while (node) {
                Reader* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    void insert(int number, const string& fullName, const string& address) {
        if ((float)count / size >= 0.7) {
            rehash();
        }

        int index = hashFunction(number);
        Reader* newReader = new Reader(number, fullName, address);

        if (!table[index]) {
            table[index] = newReader;
        }
        else {
            Reader* current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newReader;
        }

        count++;
    }

    Reader* search(int number) {
        int index = hashFunction(number);
        Reader* current = table[index];
        while (current) {
            if (current->number == number) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool remove(int number) {
        int index = hashFunction(number);
        Reader* current = table[index];
        Reader* previous = nullptr;

        while (current) {
            if (current->number == number) {
                if (previous) {
                    previous->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                count--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            Reader* current = table[i];
            if (current) {
                cout << "Index " << i << ": ";
                while (current) {
                    cout << "{" << current->number << ", " << current->fullName << ", " << current->address << "} ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
};

void userInterface() {
    HashTable hashTable;

    // Автоматическое заполнение таблицы
    hashTable.insert(12345, "Имя1", "Адресс1");
    hashTable.insert(23456, "Имя2", "Адресс2");
    hashTable.insert(34567, "Имя3", "Адресс3");
    hashTable.insert(45678, "Имя4", "Адресс4");
    hashTable.insert(56789, "Имя5", "Адресс5");

    while (true) {
        cout << "Введите команду (insert, search, delete, display, exit): ";
        string command;
        cin >> command;
if (command == "insert") {
            int number;
            string name, address;
            cout << "Введите номер абонемента: ";
            cin >> number;
            cout << "Введите ФИО: ";
            cin.ignore();
            getline(cin, name);
            cout << "Введите адрес: ";
            getline(cin, address);
            hashTable.insert(number, name, address);
            cout << "Запись добавлена." << endl;
        }
        else if (command == "search") {
            int number;
            cout << "Введите номер абонемента для поиска: ";
            cin >> number;
            Reader* result = hashTable.search(number);
            if (result) {
                cout << "Найдено: ФИО: " << result->fullName << ", Адрес: " << result->address << endl;
            }
            else {
                cout << "Запись не найдена." << endl;
            }
        }
        else if (command == "delete") {
            int number;
            cout << "Введите номер абонемента для удаления: ";
            cin >> number;
            if (hashTable.remove(number)) {
                cout << "Запись удалена." << endl;
            }
            else {
                cout << "Запись не найдена." << endl;
            }
        }
        else if (command == "display") {
            hashTable.display();
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда. Попробуйте снова." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    userInterface();
    return 0;
}
