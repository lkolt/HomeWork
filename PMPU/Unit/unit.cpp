#include <iostream>
#include "unit.h"

using namespace std;

// ����������� - ������� ����� ��������� ������ Unit � �������� ����������
Unit :: Unit(){
    unit_name = "";
    res_name = "";
    coord = {0, 0};
    num = 0;
    need.clear();
    needNum.clear();
}

// ���������� - ���������� ��������� ������
Unit :: ~Unit(){
    unit_name = "";
    res_name = "";
    coord = {0, 0};
    num = 0;
    need.clear();
    needNum.clear();
}

// ����������� ��������� ���������
Unit & Unit :: operator = (const Unit &tmp){
    if (this != &tmp){             // ���� this == &tmp, �� ��� �� �� ������, ������ ������ ������ �� ���� (����������������)
        unit_name = tmp.unit_name; // ����� ��������������� ��� ����
        coord = tmp.coord;
        res_name = tmp.res_name;
        num = tmp.num;
        need = tmp.need;
        needNum = tmp.needNum;
    }
    return *this;
}

// ����������� ����������� - �������� ���������� tmp � this
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

// ����������� ��������� ����� �� ������
istream & operator >> (istream &stream, Unit &tmp){
    // ��������� �������� �����
    getline(stream, tmp.unit_name); // ��������� ������
    if (tmp.unit_name == ""){       // ���� ��� ��������� ������ (������� ������), �� ��������� ��� ���
        if (!getline(stream, tmp.unit_name)){ // ���� �� ������ �������, �� ������ ����� - ���������� ����������
            return stream;
        }
    }

    // ��������� ���������� �����
    double x, y;
    if (!(stream >> x >> y)){ // ���� �� ������ �������, �� ������ ����� - ���������� ����������
        return stream;
    }
    tmp.coord = {x, y};

    //  ��������� �������� �����
    getline(stream, tmp.res_name);
    if (tmp.res_name == ""){
        if (!getline(stream, tmp.res_name)){ // ���� �� ������ �������, �� ������ ����� - ���������� ����������
            return stream;
        }
    }

    // ��������� ���������� ������������ ��������
    if (!(stream >> tmp.num)){
        return stream;
    }

    // ��������� ���������� ����������� ��������
    int n = 0;
    if (!(stream >> n)){
        return stream;
    }

    // ��������� �������� ����������� ��������
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
        tmp.need.push_back(x); // ��������� ��������� ������ � ������
        tmp.needNum.push_back(y);
    }
    return stream;
}

// ����������� ��������� ������ � �����
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

// ����������� ��������� ������
bool Unit :: operator < (const Unit &tmp){
    // ���������� �� �����������
    if (coord != tmp.coord){
        return (coord < tmp.coord);
    }

    // ���������� �� ����� �����
    return (unit_name < tmp.unit_name);
}

// ����������� ��������� ��������
bool Unit :: operator == (const Unit &tmp){
    return (unit_name == tmp.unit_name && coord == tmp.coord);
}

// ����������� ��������� ������
bool Unit :: operator > (const Unit &tmp){
    return !(*this < tmp || *this == tmp);
}

// ������� ���������� � �������
double sqr(double a){
    return a * a;
}

// ������� �������� ���������� �� ����� a �� ����� b
double dist(pair <double, double> a, pair <double, double> b){
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

// ������� ��������
bool Unit :: check(string nm, pair <double, double> c, double d){
    bool f1 = (unit_name == nm || nm == "*");
    bool f2 = (dist(coord, c) <= d);
    return (f1 & f2);
}

// ���������� ��������, ������� ����� ���������� ���� ����
double Unit :: howManyUnits(vector <string> res_have, vector <double> res_num){
    // �������� ������� ������� ������� �� ����� � ������� �������������� �������
    map <string, double> res_h;
    for (int i = 0; i < (int)res_have.size(); ++i){
        res_h[res_have[i]] += res_num[i];
    }

    // �������� ������� ������� ������� ��� ����� � ������� �������������� �������
    map <string, double> res_n;
    for (int i = 0; i < (int)need.size(); ++i){
        res_n[need[i]] += needNum[i];
    }

    // ������ ����������� ���������� ��������, ������� �����, ����� ���, ��� ����
    double minimum = res_have.size();
    for (int i = 0; i < (int)need.size(); ++i){
        minimum = min(minimum, res_h[need[i]] / res_n[need[i]]);
    }

    // ������ �����
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
