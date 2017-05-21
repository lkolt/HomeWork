#include <iostream>
#include "unit.h"

using namespace std;

// Конструктор
List :: List(){ // Присвоим всем полям нулевые значения
    value = Unit();
    nxt = NULL;
    isEmpty = true;
}

// Конструктор с заданными полями
List :: List(Unit val, List* next, bool em){ // Присвоим всем полям нужные значения
    value = val;
    nxt = next;
    isEmpty = em;
}

// Деструктор
List :: ~List(){
    while (nxt != NULL){    // Пройдемся по всем элементам списка
        List *cur = nxt;
        nxt = nxt->nxt;
        cur->nxt = NULL;
        delete(cur);
    }
}

// Определение оператора присвоить
List & List :: operator = (const List &cpy){
    if (this == &cpy){ // самоприсваивание
        return *this;
    }
    value = cpy.value;     //
    nxt = new List();      // скопируем 1 элемент
    isEmpty = cpy.isEmpty; // Копируем со 2 из-за того, что cpy - это константа


    List *cur = this->nxt; // Начиная со 2, скопируем остальные поля
    List *last = this;     // last - предпоследний элемент
    List *tmp = cpy.nxt;

    while (tmp != NULL){

        *cur = *tmp;           //
        List *nw = new List(); // Скопируем текущий элемент
        cur->nxt = nw;         //

        last = cur;            //
        cur = nw;              // Перейдем к следующему элементу
        tmp = tmp->nxt;        //
    }

    last->nxt = NULL;
    return *this;
}

// Конструтор копирования
List :: List(const List &cpy){

    value = cpy.value;     //
    nxt = new List();      // скопируем 1 элемент
    isEmpty = cpy.isEmpty; // Копируем со 2 из-за того, что cpy - это константа


    List *cur = this->nxt; // Начиная со 2, скопируем остальные поля
    List *last = this;     // last - предпоследний элемент
    List *tmp = cpy.nxt;

    while (tmp != NULL){

        *cur = *tmp;           //
        List *nw = new List(); // Скопируем текущий элемент
        cur->nxt = nw;         //

        last = cur;            //
        cur = nw;              // Перейдем к следующему элементу
        tmp = tmp->nxt;        //
    }

    last->nxt = NULL;
}

// Определение оператора считывания из потока
istream & operator >> (istream &stream, List &tmp){
    List *cur = &tmp;
    List *last = cur;
    while (stream >> cur->value){         // Пробуем считать текущий элемент
        List *nw = new List();            // Если получилось, то создадим новый элемент
        cur->isEmpty = false;
        cur->nxt = nw;
        last = cur;
        cur = nw;
    }

    if (last == cur){                    // Если не получилось, то завершаем считывание
        cur->isEmpty = true;             // Если мы ничего не считали, то скажем, что список пустой
    } else {
        last->nxt = NULL;
    }
    return stream;
}

// Определение оператор вывода в поток
ostream & operator << (ostream &stream, List &tmp){
    if (tmp.isEmpty){     // Если список пустой, то ничего выводить не надо
        return stream;
    }

    List *cur = &tmp;     // Иначе выводим все элементы по порядку
    while (cur != NULL){
        stream << cur->value;
        cur = cur->nxt;
    }

    return stream;
}

// Добавление в конец списка
void List :: add(Unit val){
    if (isEmpty){    // Если список пустой, то заполним его 1 элемент входящим элементом
        value = val;
        nxt = NULL;
        isEmpty = false;
        return;
    }

    List *cur = this;          // Иначе дойдем до конца списка
    while (cur->nxt != NULL){
        cur = cur->nxt;
    }

    List *nw = new List(val, NULL, false);  // И добавим этот элемент в конец
    cur->nxt = nw;
}

// Сортировка списка пузырьком
void List :: sort_(){
    if (isEmpty){
        return;
    }

    bool isSorted = false;
    while (!isSorted){                         // Пока список не отсортирован
        isSorted = true;
        List *cur = this;
        List *next = cur->nxt;

        while (next != NULL){                  // Бежим по всему списку
            if (cur->value > next->value){     // Пытаемся поменять 2 соседних элемента
                swap(cur->value, next->value);
                isSorted = false;
            }

            cur = cur->nxt;
            next = next->nxt;
        }
    }
}

// Добавление в список с сохранением порядка сортировки
void List :: addSort(Unit val){
    if (isEmpty){              // Если список пустой, то добавим элемент на 1 место
        value = val;
        nxt = NULL;
        isEmpty = false;
        return;
    }

    if (val < value){                              // Если первый элемент меньше входного, то входной станет первым
        List *sec = new List(value, nxt, isEmpty); // Создадим второй элемент
        List *nw = new List(val, sec, false);      // Создадим первый элемент
        *this = *nw;                               // Переприсвоим первый элемент
        return;
    }

    List *cur = this;                // Пройдемся по списку
    while (cur->nxt != NULL){
        if (val < cur->nxt->value){  // Найдем где должен стоять элемент
            break;
        }
        cur = cur->nxt;
    }

    List *nw = new List(val, cur->nxt, false);  // Вставим его туда
    cur->nxt = nw;
}

// Слияние 2 листов
void List :: addList(List next){
    if (next.isEmpty){ // Если 2 список пустой, то ничего делать не надо
        return;
    }

    if (isEmpty){      // Если наш список пустой, то просто скажем, что наш список - это второй список
        List *nw = NULL;
        if (next.nxt != NULL){
            nw = new List(*next.nxt);
        }
        value = next.value;
        nxt = nw;
        isEmpty = false;
        return;
    }

    List *cur = this;
    while (cur->nxt != NULL){ // Дойдем до конца нашего списка
        cur = cur->nxt;
    }
    List *nw = new List(next); // Скопируем второй список
    cur->nxt = nw;             // Добавим в наш список новый список
}

// Вывести все элементы, которые подходят под условия
int List :: write(string nm, pair <double, double> c, double d){
    if (isEmpty){ // Если список пустой, то ничего делать не надо
        return 0;
    }

    List *cur = this;
    int cnt = 0;
    while (cur != NULL){                 // Пройдемся по списку
        if (cur->value.check(nm, c, d)){ // Делаем проверку и если надо, то выводим
            cout << cur->value;
            cout << endl;
            cnt++;
        }
        cur = cur->nxt;
    }
    return cnt;
}

// Удалить все элементы, которые подходят под условия
int List :: remove_(string nm, pair <double, double> c, double d){
    if (isEmpty){ // Если список пустой, то ничего удалить мы не можем
        return 0;
    }

    int cnt = 0;
    while (nxt != NULL && value.check(nm, c, d)){ // Пока первый элемент подходит под условия, удаляем его
        List *next = nxt;
        value = nxt->value;
        nxt = nxt->nxt;
        next->nxt = NULL;
        delete(next);
        next = NULL;
        cnt++;
    }

    if (value.check(nm, c, d)){                   // Если удалили все, то говорим, что список пустой
        isEmpty = true;
        cnt++;
        return cnt;
    }

    List *last = this;
    List *cur = nxt;
    while (cur != NULL){                          // Пройдемся по всему списку
        if (cur->value.check(nm, c, d)){          // Если надо, удалим
            last->nxt = cur->nxt;
            List *del = cur;
            cur = cur->nxt;
            del->nxt = NULL;
            delete(del);
            del = NULL;
            cnt++;
        } else {
            last = cur;
            cur = cur->nxt;
        }
    }
    return cnt;
}

// Сколько ресурсов нужно для имеющихся юнитов
vector <pair <string, double> > List :: resourcesNeed(){
    vector <pair <string, double> > need;
    if (isEmpty){  // Если список пустой, то ничего не надо
        need.clear();
        return need;
    }

    List *cur = this;
    while (cur != NULL){              // Пройдемся по списку
        vector <string> h = cur->value.getNeed(); // Добавим все, что надо
        vector <int> m = cur->value.getNeedNum();

        for (int i = 0; i < (int)h.size(); i++){
            bool isFound = 0;
            for (int j = 0; j < (int)need.size(); j++){
                if (h[i] == need[j].first){
                    need[j].second += m[i];
                    isFound = true;
                    break;
                }
            }
            if (!isFound){
                need.push_back(make_pair(h[i], m[i]));
            }
        }

        cur = cur->nxt;
    }

    return need;
}

vector <pair <string, double> > List :: resourcesProduce(){
    vector <pair <string, double> > prod;
    if (isEmpty){ // Если список пустой, то ничего не производим
        prod.clear();
        return prod;
    }

    List *cur = this;

    while (cur != NULL){            // Пройдем по всему списку
        double res = cur->value.getNum(); // Добавим все, что надо
        string name = cur->value.getRes();

        bool isFound = 0;
        for (int i = 0; i < (int)prod.size(); i++){
            if (name == prod[i].first){
                prod[i].second += res;
                isFound = true;
                break;
            }
        }

        if (!isFound){
            prod.push_back(make_pair(name, res));
        }

        cur = cur->nxt;
    }

    return prod;
}
