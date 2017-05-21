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
        // �������� �����
        string unit_name;
        // ���������� �����
        pair <double, double> coord;
        // �������� �������, ������� ���������� ����
        string res_name;
        // ������� �������� ���������� ����
        double num;
        // ����� ������� ����� � �����
        vector <string> need;

        vector <int> needNum;

    public:
        // �����������
        Unit();
        // ����������
        ~Unit();
        // �������� ������������
        Unit & operator = (const Unit &tmp);
        // ����������� �����������
        Unit(const Unit &tmp);
        // �������� �����
        friend istream & operator >> (istream &stream, Unit &tmp);
        // �������� ������
        friend ostream & operator << (ostream &stream, Unit &tmp);
        // �������� ������
        bool operator < (const Unit &tmp);
        // �������� �����
        bool operator == (const Unit &tmp);
        // �������� ������
        bool operator > (const Unit &tmp);
        // ������� ��������
        bool check(string name, pair <double, double> c, double d);
        // C������ ������ ������ ���� ����� ���������� � ���������� ���������
        double howManyUnits(vector <string> res_have, vector <double> res_num);
        // ���������� ���������� ��������� � need
        vector <string> getNeed();
        vector <int> getNeedNum();
        // ���������� ������� �������� ���������� ����
        double getNum();
        string getRes();
};

// ���������� ����� � � �������
double sqr(double a);
// ���������� �� ����� � �� ����� b
double dist(pair <double, double> a, pair <double, double> b);


class List{
    private:
        // ������� ���� Unit
        Unit value;
        // ������ �� ��������� ������� �����
        List *nxt;
        // ������ �� ����
        bool isEmpty;

    public:
        // �����������
        List();
        // ����������� � ��������� ������
        List(Unit val, List* next, bool em);
        // ���������� �����������
        List(const List &cpy);
        // ����������
        ~List();
        // ����������� ��������� ���������
        List & operator = (const List &tmp);
        // ����������� ��������� ���������� �� ������
        friend istream & operator >> (istream &stream, List &tmp);
        // ����������� �������� ������ � �����
        friend ostream & operator << (ostream &stream, List &tmp);
        // ���������� � ����� ������
        void add(Unit val);
        // ���������� ������ ���������
        void sort_();
        // ���������� � ������ � ����������� ������� ����������
        void addSort(Unit val);
        // ������� 2 ������
        void addList(List next);
        // ������� ��� ��������, ������� �������� ��� �������
        int write(string nm, pair <double, double> c, double d);
        // ������� ��� ��������, ������� �������� ��� �������
        int remove_(string nm, pair <double, double> c, double d);
        // ������� �������� ����� ��� ��������� ������
        vector <pair <string, double> > resourcesNeed();
        // ������� �������� ��������� ����� ����������
        vector <pair <string, double> > resourcesProduce();
};
