#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Функция для вычисления таблицы смещений (префикс-функции)
void preprocess(const string& pattern, vector<int>& last) {
    int m = pattern.size();
    last.assign(256, -1);  // Инициализируем массив значением -1
    for (int i = 0; i < m; ++i) {
        last[pattern[i]] = i;  // Запоминаем последнюю позицию символа
    }
}

// Реализация алгоритма Бойера-Мура-Хорспула для поиска последнего вхождения
int bmhLastOccurrence(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m > n) {
        return -1;  // Невозможно найти образец длиннее текста
    }

    vector<int> last(256);  // Массив для хранения последней позиции символа
    preprocess(pattern, last);

    int i = n - 1;  // Начнем с конца текста
    while (i >= m - 1) {
        int k = 0;
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
        }
        if (k == m) {
            return i - m + 1;  // Найдено последнее вхождение
        }

        // Вычисляем сдвиг
        i -= max(1, k - last[text[i - m]]);
    }
    return -1;  // Не найдено
}

int main() {
    string text = "abacadabra";
    string pattern = "aba";
    int result = bmhLastOccurrence(text, pattern);
    if (result != -1) {
        cout << "Последнее вхождение подстроки начинается на позиции: " << result << endl;
    }
    else {
        cout << "Подстрока не найдена." << endl;
    }
    return 0;
}
