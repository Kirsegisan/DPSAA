#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Узел дерева Хаффмана
struct HuffmanNode {
    char character;
    HuffmanNode *left, *right;

    HuffmanNode(char ch) : character(ch), left(nullptr), right(nullptr) {}
    HuffmanNode() : character('\0'), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева Хаффмана из кодов символов
HuffmanNode* buildHuffmanTree(const map<char, string> &huffmanCodes) {
    HuffmanNode *root = new HuffmanNode();

    for (const auto &pair : huffmanCodes) {
        char character = pair.first;
        string code = pair.second;
        HuffmanNode *current = root;

        for (char bit : code) {
            if (bit == '0') {
                if (!current->left) current->left = new HuffmanNode();
                current = current->left;
            } else if (bit == '1') {
                if (!current->right) current->right = new HuffmanNode();
                current = current->right;
            }
        }
        current->character = character;
    }

    return root;
}

// Функция для декодирования строки с использованием дерева Хаффмана
string decodeHuffman(const string &encodedString, HuffmanNode *root) {
    string decodedString = "";
    HuffmanNode *current = root;

    for (char bit : encodedString) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (!current->left && !current->right) { // Лист дерева
            decodedString += current->character;
            current = root;
        }
    }

    return decodedString;
}

// Удаление дерева
void deleteTree(HuffmanNode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Пример кодов Хаффмана для "Абрамович Юрий Александрович"
    map<char, string> huffmanCodes = {
        {'А', "00"}, {'б', "11000"}, {'р', "011"}, {'а', "01"}, {'м', "11001"},
        {'о', "010"}, {'в', "111"}, {'и', "101"}, {'ч', "11100"}, {' ', "1101"},
        {'Ю', "11101"}, {'й', "11110"}, {'е', "11111"}, {'л', "11010"},
        {'с', "11011"}, {'д', "10000"}, {'н', "10001"}, {'к', "10010"}
    };

    // Закодированная строка
    string encodedString = "00 11000 011 01 11001 010 111 101 11100 1101 11101 101 011 11110 1101 00 010 111 101 10000 010 011 10001 01 11010 11111 01 10010";
    // Удаляем пробелы для обработки
    encodedString.erase(remove(encodedString.begin(), encodedString.end(), ' '), encodedString.end());

    // Построение дерева Хаффмана
    HuffmanNode *root = buildHuffmanTree(huffmanCodes);

    // Декодирование строки
    string decodedString = decodeHuffman(encodedString, root);
    cout << "Декодированная строка: " << decodedString << endl;

    // Очистка памяти
    deleteTree(root);

    return 0;
}
