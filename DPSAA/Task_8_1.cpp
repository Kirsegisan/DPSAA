#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

// Структура для хранения символа, частоты и его кода
struct Symbol {
    char character;
    double frequency;
    string code;
};

// Функция для сортировки символов по убыванию частоты
bool compareFrequency(const Symbol &a, const Symbol &b) {
    return a.frequency > b.frequency;
}

// Рекурсивная функция для разделения символов и присвоения кодов
void generateCodes(vector<Symbol> &symbols, int start, int end, string prefix) {
    if (start == end) {
        symbols[start].code = prefix;
        return;
    }

    double totalFrequency = 0;
    for (int i = start; i <= end; ++i)
        totalFrequency += symbols[i].frequency;

    double halfFrequency = 0;
    int mid = start;
    while (mid <= end && halfFrequency + symbols[mid].frequency <= totalFrequency / 2) {
        halfFrequency += symbols[mid].frequency;
        ++mid;
    }
    --mid;

    // Рекурсивно обрабатываем левую и правую части
    generateCodes(symbols, start, mid, prefix + "0");
    generateCodes(symbols, mid + 1, end, prefix + "1");
}

int main() {
    string text = "Ана, дэус, рики, паки, Дормы кормы констунтаки, Дэус дэус канадэус – бац!";
    map<char, int> frequencyMap;

    // Подсчет частоты символов
    for (char c : text) {
        if (c != '\0')
            frequencyMap[c]++;
    }

    vector<Symbol> symbols;
    int totalSymbols = text.size();

    // Заполнение вектора символов
    for (auto &pair : frequencyMap) {
        Symbol s;
        s.character = pair.first;
        s.frequency = (double)pair.second / totalSymbols;
        symbols.push_back(s);
    }

    // Сортировка по частоте
    sort(symbols.begin(), symbols.end(), compareFrequency);

    // Генерация кодов
    generateCodes(symbols, 0, symbols.size() - 1, "");

    // Вывод результатов
    cout << "Символ\tЧастота\tКод\n";
    for (auto &s : symbols) {
        cout << s.character << "\t" << s.frequency * 100 << "%\t" << s.code << endl;
    }

    return 0;
}
