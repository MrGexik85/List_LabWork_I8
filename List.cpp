#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "Element.cpp"

// Объект 'список'
class List {
    Element *pfront;
    Element *pback;
    int listSize;
    public:
        // Конструктор для списка
        List() : pfront(NULL), pback(NULL), listSize(0){}

        // Деструктор для списка
        ~List(){
            Element* next = pfront;
            while(next){
                Element* temp = next;
                next = temp->next;
                delete temp;
            }
        }

        // Считывание из файла
        // Создается упорядоченный список (от максимального показателя к минимальному)
        bool getListFromFile(std::string filename){
            std::ifstream in(filename.c_str(), std::ios_base::binary | std::ios_base::in);
            if(in.is_open()){
                Element temp(0, 0);
                while(in>>temp){
                    pushElementSort(temp);
                }
                in.close();
                return true;
            } else {
                return false;
            }
        }

        // Запись в файл
        bool putListInFile(std::string filename){
            std::ofstream out(filename.c_str(), std::ios_base::binary | std::ios_base::out);
            if(out.is_open()){
                Element* next = pfront;
                while(next){
                    out << *next;
                    next = next->next;
                }
                out.close();
                return true;
            } else {
                return false;
            }
        }

        // Вставка элемента в начало списка
        // Принимает: объект вставляемого элемента
        void pushInFront(Element el){
            if(pfront){
                Element* first = pfront;
                pfront = new Element(el.coef, el.exp);
                pfront->next = first;
                first->previous = pfront;
            } else {
                pfront = new Element(el.coef, el.exp);
                pback = pfront;
            }
            listSize++;
        }

        // Вставка элемента в конец списка
        // Принимает: объект вставляемого элемента
        void pushInBack(Element el){
            if(pfront){
                Element* last = pback;
                pback = new Element(el.coef, el.exp);
                pback->previous = last;
                last->next = pback;
            } else {
                pfront = new Element(el.coef, el.exp);
                pback = pfront;
            }
            listSize++;
        }

        // Вставка элемента в произвольное место списка
        // Принимает: объект вставляемого элемента, индекс, куда нужно вставить
        // Возвращает: удалось ли вставить элемент в указанную позицию
        bool pushElement(Element pushEl, int index){
            if(index < listSize && index >= 0){
                Element* el = pfront;
                for(int i = 0; i < index; i++){
                    el = el->next;
                }
                if(el->previous){
                    Element *next = el;
                    Element *prev = el->previous;

                    Element* pEl = new Element(pushEl.coef, pushEl.exp);
                    pEl->next = next;
                    pEl->previous = prev;

                    next->previous = pEl;
                    prev->next = pEl;

                    listSize++;
                } else {
                    pushInFront(pushEl);
                }
                return true;
            } else if (index == listSize){
                pushInBack(pushEl);                
                return true;
            } else {
                return false;
            }
        }

        // Вставка элемента в упорядоченный список. Упорядоченность: от максимального показателя к минимальному
        // Принимает: объект вставляемого элемента, индекс, куда нужно вставить
        void pushElementSort(Element el){
            Element *temp = pfront;
            while(temp && el.exp < temp->exp){
                temp = temp->next;
            }
            if(temp){
                if(temp->previous){
                    Element *next = temp;
                    Element *prev = temp->previous;

                    Element* pEl = new Element(el.coef, el.exp);
                    pEl->next = next;
                    pEl->previous = prev;

                    next->previous = pEl;
                    prev->next = pEl;

                    listSize++;
                } else {
                    pushInFront(el);
                }
            } else {
                pushInBack(el);
            }
        }

        // пока затычка
        void showList(int itemPerPage = 10, int page = 0, Element *pStart = NULL){
            Element *pEl = pStart ? pStart : pfront;
            system("cls");
            std::cout << "||  №  ||    COEF   ||    EXP    ||" << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            int answ = 1;
            while(pEl){
                std::cout << "||" << std::setw(5) << answ+itemPerPage*page << "||" << std::setw(11) << pEl->coef << "||" << std::setw(11) << pEl->exp << "||" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                answ++;
                if(answ > itemPerPage){
                    break;
                }
                pEl = pEl->next;
            }
            int ch;
            std::cout << std::endl << "1. Следующая страница" << std::endl;
            std::cout << "2. Предыдущая страница" << std::endl;
            std::cout << "3. Выход в главное меню" << std::endl;
            std::cin >> ch;
            switch(ch){
                case 1: {
                    if(pEl && pEl->next){
                        showList(itemPerPage, ++page, pEl->next);
                    } else {
                        if(pEl){
                            for(int i = 0; i < itemPerPage-1; i++){
                                pEl = pEl->previous;
                            }
                            showList(itemPerPage, page, pEl);
                        } else {
                            pEl = pback;
                            for(int i = 0; i < answ-2; i++){
                                pEl = pEl->previous;
                            }
                            showList(itemPerPage, page, pEl);
                        }
                    }
                    break;
                }
                case 2: {
                    if(page == 0){
                        showList(itemPerPage, page);
                    } else {
                        if(pEl){
                            for(int i = 0; i < itemPerPage*2-1; i++){
                                pEl = pEl->previous;
                            }
                            showList(itemPerPage, --page, pEl);
                        } else {
                            pEl = pback;
                            for(int i = 0; i < answ-2+itemPerPage; i++){
                                pEl = pEl->previous;
                            }
                            showList(itemPerPage, --page, pEl);
                        }
                    }
                    break;
                }
                case 3: return;
            }
        }

        void showListReverse(int itemPerPage = 10, int page = 0, Element *pStart = NULL){
            Element *pEl = pStart ? pStart : pback;
            system("cls");
            std::cout << "||  №  ||    COEF   ||    EXP    ||" << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            int answ = 1;
            while(pEl){
                std::cout << "||" << std::setw(5) << listSize - (answ+itemPerPage*page) + 1 << "||" << std::setw(11) << pEl->coef << "||" << std::setw(11) << pEl->exp << "||" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                ++answ;
                if(answ > itemPerPage){
                    break;
                }
                pEl = pEl->previous;
            }
            int ch;
            std::cout << std::endl << "1. Следующая страница" << std::endl;
            std::cout << "2. Предыдущая страница" << std::endl;
            std::cout << "3. Выход в главное меню" << std::endl;
            std::cin >> ch;
            switch(ch){
                case 1: {
                    if(pEl && pEl->previous){
                        showListReverse(itemPerPage, ++page, pEl->previous);
                    } else {
                        if(pEl){
                            for(int i = 0; i < itemPerPage-1; i++){
                                pEl = pEl->next;
                            }
                            showListReverse(itemPerPage, page, pEl);
                        } else {
                            pEl = pfront;
                            for(int i = 0; i < answ-2; i++){
                                pEl = pEl->next;
                            }
                            showListReverse(itemPerPage, page, pEl);
                        }
                    }
                    break;
                }
                case 2: {
                    if(page == 0){
                        showListReverse(itemPerPage, page);
                    } else {
                        if(pEl){
                            for(int i = 0; i < itemPerPage*2-1; i++){
                                pEl = pEl->next;
                            }
                            showListReverse(itemPerPage, --page, pEl);
                        } else {
                            pEl = pfront;
                            for(int i = 0; i < answ-2+itemPerPage; i++){
                                pEl = pEl->next;
                            }
                            showListReverse(itemPerPage, --page, pEl);
                        }
                    }
                    break;
                }
                case 3: return;
            }
        }

        // Удаление элемента из начала списка
        // Возвращает: успешно ли произведено удаление
        bool removeFromFront(){
            if(pfront){
                Element* el = pfront;
                pfront = el->next;
                if(pfront){
                    pfront->previous = NULL;
                } else {
                    pback = NULL;
                }
                delete el;
                listSize--;
                return true;
            } else {
                return false;
            }
        }

        // Удаление элемента из конца списка
        // Возвращает: успешно ли произведено удаление
        bool removeFromBack(){
            if(pfront){
                Element* el = pback;
                pback = el->previous;
                if(pback){
                    pback->next = NULL;
                } else {
                    pfront = NULL;
                }
                listSize--;
                return true;
            } else {
                return false;
            }
        }

        // Удаление произвольного элемента из списка
        // Принимает: индекс элемента
        // Возвращает: успешно ли произведено удаление
        bool removeElement(int index){
            if(index < listSize && index >= 0){
                Element* el = pfront;
                for(int i = 0; i < index; i++){
                    el = el->next;
                }
                if(el->previous){
                    if(el->next){
                        Element *next = el->next;
                        Element *prev = el->previous;
                        prev->next = next;
                        next->previous = prev;
                        delete el;
                        listSize--;
                        return true;
                    } else {
                        return removeFromBack();
                    }
                } else {
                    return removeFromFront();
                }
            } else {
                return false;
            }
        }

        // Дифференцирование уравнения (индивидуальное задание)
        void differentiate(){
            Element* temp = pfront;
            int index = 0;
            while(temp){
                temp->coef *= temp->exp;
                temp->exp -= 1;
                int cf = temp->coef;
                temp = temp->next;
                if(cf == 0){
                    removeElement(index);
                } else {
                    index++;
                }
            }
        }
};
