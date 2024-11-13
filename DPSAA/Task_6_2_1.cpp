#include <iostream>
#include <string>
using namespace std;

// Функция для линейного поиска первого вхождения подстроки в строке
int linearSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    // Проходим по всем возможным позициям начала подстроки
    for (int i = 0; i <= n - m; ++i) {
        bool found = true;
        for (int j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;  // Возвращаем индекс первого вхождения
        }
    }
    return -1;  // Если не нашли
}

int main() {
    string text = "abcdefg";
    string pattern = "cd";
    int result = linearSearch(text, pattern);
    if (result != -1) {
        cout << "Подстрока найдена на позиции: " << result << endl;
    }
    else {
        cout << "Подстрока не найдена." << endl;
    }
    return 0;
}
