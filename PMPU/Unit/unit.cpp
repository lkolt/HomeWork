#include <iostream>
#include "unit.h"

using namespace std;

// Конструктор - создает новый экземпляр класса Unit с нулевыми значениями
Unit :: Unit(){
    unit_name = "";
    res_name = "";
    coord = {0, 0};
    num = 0;
    need.clear();
    needNum.clear();
}

// Деструктор - уничтожает экземпляр класса
Unit :: ~Unit(){
    unit_name = "";
    res_name = "";
    coord = {0, 0};
    num = 0;
    need.clear();
    needNum.clear();
}

// Определение оператора присвоить
Unit & Unit :: operator = (const Unit &tmp){
    if (this != &tmp){             // Если this == &tmp, то это та же память, значит ничего менять не надо (самоприсваивание)
        unit_name = tmp.unit_name; // Иначе переприсваиваем все поля
        coord = tmp.coord;
        res_name = tmp.res_name;
        num = tmp.num;
        need = tmp.need;
        needNum = tmp.needNum;
    }
    return *this;
}

// Конструктор копирования - копирует содержимое tmp в this
Unit :: Unit(const Unit &tmp){
    unit_name = tmp.unit_name;
    coord = tmp.coord;
    res_name = tmp.res_name;
    num = tmp.num;
    need.clear();
    needNum.clear();
    for (int i = 0; i < (int)tmp.need.size(); ++i){
        need.push_back(tmp.need[i]);
        needNum.push_back(tmp.needNum[i]);
    }
}

// Определение оператора ввода из потока
istream & operator >> (istream &stream, Unit &tmp){
    // считываем название юнита
    getline(stream, tmp.unit_name); // считываем строку
    if (tmp.unit_name == ""){       // если она оказалась пустой (перевод строки), то считываем еще раз
        if (!getline(stream, tmp.unit_name)){ // если не смогли считать, то ошибка ввода - прекращаем считывание
            return stream;
        }
    }

    // считываем координаты юнита
    double x, y;
    if (!(stream >> x >> y)){ // если не смогли считать, то ошибка ввода - прекращаем считывание
        return stream;
    }
    tmp.coord = {x, y};

    //  считываем название юнита
    getline(stream, tmp.res_name);
    if (tmp.res_name == ""){
        if (!getline(stream, tmp.res_name)){ // если не смогли считать, то ошибка ввода - прекращаем считывание
            return stream;
        }
    }

    // считываем количество производимых ресурсов
    if (!(stream >> tmp.num)){
        return stream;
    }

    // считываем количество необходимых ресурсов
    int n = 0;
    if (!(stream >> n)){
        return stream;
    }

    // считываем названия необходимых ресурсов
    for (int i = 0; i < n; ++i){
        string x;
        while (x == ""){
            if (!(getline(stream, x))){
                return stream;
            }
        }
        int y;
        if (!(stream >> y)){
            return stream;
        }
        tmp.need.push_back(x); // добавляем считанную строку в вектор
        tmp.needNum.push_back(y);
    }
    return stream;
}

// Определение оператора вывода в поток
ostream & operator << (ostream &stream, Unit &tmp){
    stream << tmp.unit_name << endl;
    stream << tmp.coord.first << " " << tmp.coord.second << endl;
    stream << tmp.res_name << endl;
    stream << tmp.num << endl;
    stream << tmp.need.size() << endl;
    for (int i = 0; i < (int)tmp.need.size(); ++i){
        stream << tmp.need[i] << endl;
        stream << tmp.needNum[i] << endl;
    }
    return stream;
}

// Определение оператора меньше
bool Unit :: operator < (const Unit &tmp){
    // сравниваем по координатам
    if (coord != tmp.coord){
        return (coord < tmp.coord);
    }

    // сравниваем по имени юнита
    return (unit_name < tmp.unit_name);
}

// Определение оператора равества
bool Unit :: operator == (const Unit &tmp){
    return (unit_name == tmp.unit_name && coord == tmp.coord);
}

// Определение оператора больше
bool Unit :: operator > (const Unit &tmp){
    return !(*this < tmp || *this == tmp);
}

// Функция возведения в квадрат
double sqr(double a){
    return a * a;
}

// Функция подсчета расстояния от точки a до точки b
double dist(pair <double, double> a, pair <double, double> b){
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

// Функция проверки
bool Unit :: check(string nm, pair <double, double> c, double d){
    bool f1 = (unit_name == nm || nm == "*");
    bool f2 = (dist(coord, c) <= d);
    return (f1 & f2);
}

// Количество ресурсов, которые может произвести этот юнит
double Unit :: howManyUnits(vector <string> res_have, vector <double> res_num){
    // запомним сколько каждого ресурса мы имеем с помощью ассоциативного массива
    map <string, double> res_h;
    for (int i = 0; i < (int)res_have.size(); ++i){
        res_h[res_have[i]] += res_num[i];
    }

    // запомним сколько каждого ресурса нам нужно с помощью ассоциативного массива
    map <string, double> res_n;
    for (int i = 0; i < (int)need.size(); ++i){
        res_n[need[i]] += needNum[i];
    }

    // найдем минимальное количество ресурсов, которых нужно, среди тех, кто есть
    double minimum = res_have.size();
    for (int i = 0; i < (int)need.size(); ++i){
        minimum = min(minimum, res_h[need[i]] / res_n[need[i]]);
    }

    // вернем ответ
    return minimum * num;
}

//
vector <string> Unit :: getNeed(){
    return need;
}

vector <int> Unit :: getNeedNum(){
    return needNum;
}
//
double Unit :: getNum(){
    return num;
}

string Unit :: getRes(){
    return res_name;
}
