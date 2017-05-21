#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>

using namespace std;

class Unit{
    private:
        // Название юнита
        string unit_name;
        // Координаты юнита
        pair <double, double> coord;
        // Название ресурса, который производит юнит
        string res_name;
        // Сколько ресурсов производит юнит
        double num;
        // Какие ресурсы нужны в юните
        vector <string> need;

        vector <int> needNum;

    public:
        // Конструктор
        Unit();
        // Деструктор
        ~Unit();
        // Оператор присваивания
        Unit & operator = (const Unit &tmp);
        // Конструктор копирования
        Unit(const Unit &tmp);
        // Оператор ввода
        friend istream & operator >> (istream &stream, Unit &tmp);
        // Оператор вывода
        friend ostream & operator << (ostream &stream, Unit &tmp);
        // Оператор меньше
        bool operator < (const Unit &tmp);
        // Оператор равно
        bool operator == (const Unit &tmp);
        // Оператор больше
        bool operator > (const Unit &tmp);
        // Функция проверки
        bool check(string name, pair <double, double> c, double d);
        // Cколько юнитов такого типа можно произвести с имеющимися ресурсами
        double howManyUnits(vector <string> res_have, vector <double> res_num);
        // Возвращает количество элементов в need
        vector <string> getNeed();
        vector <int> getNeedNum();
        // Возвращает сколько ресурсов производит юнит
        double getNum();
        string getRes();
};

// возведение числа а в квадрат
double sqr(double a);
// расстояние от точки а до точки b
double dist(pair <double, double> a, pair <double, double> b);


class List{
    private:
        // Элемент типа Unit
        Unit value;
        // Ссылка на следующий элемент листа
        List *nxt;
        // Пустой ли лист
        bool isEmpty;

    public:
        // Конструктор
        List();
        // Конструктор с заданными полями
        List(Unit val, List* next, bool em);
        // Конструтор копирования
        List(const List &cpy);
        // Деструктор
        ~List();
        // Определение оператора присвоить
        List & operator = (const List &tmp);
        // Определение оператора считывания из потока
        friend istream & operator >> (istream &stream, List &tmp);
        // Определение оператор вывода в поток
        friend ostream & operator << (ostream &stream, List &tmp);
        // Добавление в конец списка
        void add(Unit val);
        // Сортировка списка пузырьком
        void sort_();
        // Добавление в список с сохранением порядка сортировки
        void addSort(Unit val);
        // Слияние 2 листов
        void addList(List next);
        // Вывести все элементы, которые подходят под условия
        int write(string nm, pair <double, double> c, double d);
        // Удалить все элементы, которые подходят под условия
        int remove_(string nm, pair <double, double> c, double d);
        // Сколько ресурсов нужно для имеющихся юнитов
        vector <pair <string, double> > resourcesNeed();
        // Сколько ресурсов имеющиеся юниты производят
        vector <pair <string, double> > resourcesProduce();
};
