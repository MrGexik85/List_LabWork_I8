#include <iostream>
#include <windows.h>
#include <locale>

#include "List.cpp"

using namespace std;

Element getElement(){
    int cf, ex;
    cout << "Введите коэффициент c" << endl;
    cin >> cf;
    cout << "Введите показатель степени e" << endl;
    cin >> ex;
    return Element(cf, ex);
}

void drawMenu(List &lst){
    int c;

    do{
        system("cls");
        cout << "1. Просмотр списка в прямом направлении" << endl;
        cout << "2. Просмотр списка в обратном" << endl;
        cout << "3. Добавить элемент в начало списка" << endl;
        cout << "4. Добавить элемент в конец списка" << endl;
        cout << "5. Добавить элемент в призвольное место списка" << endl;
        cout << "6. Добавить элемент в упорядоченный список с сохранением упорядоченности" << endl;
        cout << "7. Удалить элемент из начала списка" << endl;
        cout << "8. Удалить элемент из конца списка" << endl;
        cout << "9. Удалить элемент из произвольного места списка" << endl;
        cout << "10. Продифференцировать (задание)" << endl;
        cout << "0. Выход" << endl;

        cin >> c;
        system("cls");
        switch(c){
            case 1:
                lst.showList(5);
                break;
            case 2:
                lst.showListReverse(5);
                break;
            case 3:{
                lst.pushInFront(getElement());
                cout << "Элемент успешно вставлен в начало списка" << endl;
                break;
            }
            case 4: {
                lst.pushInBack(getElement());
                cout << "Элемент успешно вставлен в конец списка" << endl;
                break;
            }
            case 5: {
                int index;
                cout << "Введите индекс для вставки элемента" << endl;
                cin >> index;
                if(lst.pushElement(getElement(), index)){
                    cout << "Элемент успешно вставлен на индекс: " << index << endl;
                } else {
                    cout << "Некорректный индекс" << endl;
                }
                break;
            }
            case 6: {
                lst.pushElementSort(getElement());
                cout << "Элемент успешно вставлен в упорядоченный список" << endl;
                break;
            }
            case 7:{
                if(lst.removeFromFront()){
                    cout << "Элемент успешно удален из начала списка" << endl;
                } else {
                    cout << "Элемент не удален из начала списка (список пуст)" << endl;
                }
                break;
            }
            case 8: {
                if(lst.removeFromBack()){
                    cout << "Элемент успешно удален из конца списка" << endl;
                } else {
                    cout << "Элемент не удален из конца списка (список пуст)" << endl;
                }
                break;
            }
            case 9: {
                int index;
                cout << "Введите индекс удаляемого элемента" << endl;
                cin >> index;
                if(lst.removeElement(index)){
                    cout << "Элемент c индексом: " << index << " успешно удалён" << endl;
                } else {
                    cout << "Не найден элемент с таким индексом" << endl;
                }
                break;
            }
            case 10:
                lst.differentiate();
                cout << "Список успешно продифференцирован" << endl;
                break;
            case 0:
                cout << "До свидания)))" << endl;
                break;
            default:
                cout << "Неверная команда. Попробуйте еще раз" << endl;
                system("pause");
                break;
        }
        system("pause");
    } while(c != 0);
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    List lst;
    lst.getListFromFile("data.bin");
    drawMenu(lst);
    lst.putListInFile("data.bin");
    return 0;
}

