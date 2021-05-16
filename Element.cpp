#include <cstddef>
#include <fstream>

// Объект 'элемент списка'
struct Element {
    int coef;
    int exp;
    Element* next;
    Element* previous;

    // Конструктор для структуры
    Element(int coef, int exp) : coef(coef), exp(exp), next(NULL), previous(NULL){}
};

// Для записи структуры в бинарный файл
inline std::ofstream& operator<<(std::ofstream& out, const Element& element){
    out.write((char*)&element.coef, sizeof(element.coef));
    out.write((char*)&element.exp, sizeof(element.exp));
    return out;
}

// Для чтения структуры из бинарного файла
inline std::ifstream& operator>>(std::ifstream& in, Element& element) {
    in.read((char*)&element.coef, sizeof(element.coef));
    in.read((char*)&element.exp, sizeof(element.exp));
    return in;
}

