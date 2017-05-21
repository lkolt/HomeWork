#include <iostream>
#include "unit.h"

using namespace std;

// �����������
List :: List(){ // �������� ���� ����� ������� ��������
    value = Unit();
    nxt = NULL;
    isEmpty = true;
}

// ����������� � ��������� ������
List :: List(Unit val, List* next, bool em){ // �������� ���� ����� ������ ��������
    value = val;
    nxt = next;
    isEmpty = em;
}

// ����������
List :: ~List(){
    while (nxt != NULL){    // ��������� �� ���� ��������� ������
        List *cur = nxt;
        nxt = nxt->nxt;
        cur->nxt = NULL;
        delete(cur);
    }
}

// ����������� ��������� ���������
List & List :: operator = (const List &cpy){
    if (this == &cpy){ // ����������������
        return *this;
    }
    value = cpy.value;     //
    nxt = new List();      // ��������� 1 �������
    isEmpty = cpy.isEmpty; // �������� �� 2 ��-�� ����, ��� cpy - ��� ���������


    List *cur = this->nxt; // ������� �� 2, ��������� ��������� ����
    List *last = this;     // last - ������������� �������
    List *tmp = cpy.nxt;

    while (tmp != NULL){

        *cur = *tmp;           //
        List *nw = new List(); // ��������� ������� �������
        cur->nxt = nw;         //

        last = cur;            //
        cur = nw;              // �������� � ���������� ��������
        tmp = tmp->nxt;        //
    }

    last->nxt = NULL;
    return *this;
}

// ���������� �����������
List :: List(const List &cpy){

    value = cpy.value;     //
    nxt = new List();      // ��������� 1 �������
    isEmpty = cpy.isEmpty; // �������� �� 2 ��-�� ����, ��� cpy - ��� ���������


    List *cur = this->nxt; // ������� �� 2, ��������� ��������� ����
    List *last = this;     // last - ������������� �������
    List *tmp = cpy.nxt;

    while (tmp != NULL){

        *cur = *tmp;           //
        List *nw = new List(); // ��������� ������� �������
        cur->nxt = nw;         //

        last = cur;            //
        cur = nw;              // �������� � ���������� ��������
        tmp = tmp->nxt;        //
    }

    last->nxt = NULL;
}

// ����������� ��������� ���������� �� ������
istream & operator >> (istream &stream, List &tmp){
    List *cur = &tmp;
    List *last = cur;
    while (stream >> cur->value){         // ������� ������� ������� �������
        List *nw = new List();            // ���� ����������, �� �������� ����� �������
        cur->isEmpty = false;
        cur->nxt = nw;
        last = cur;
        cur = nw;
    }

    if (last == cur){                    // ���� �� ����������, �� ��������� ����������
        cur->isEmpty = true;             // ���� �� ������ �� �������, �� ������, ��� ������ ������
    } else {
        last->nxt = NULL;
    }
    return stream;
}

// ����������� �������� ������ � �����
ostream & operator << (ostream &stream, List &tmp){
    if (tmp.isEmpty){     // ���� ������ ������, �� ������ �������� �� ����
        return stream;
    }

    List *cur = &tmp;     // ����� ������� ��� �������� �� �������
    while (cur != NULL){
        stream << cur->value;
        cur = cur->nxt;
    }

    return stream;
}

// ���������� � ����� ������
void List :: add(Unit val){
    if (isEmpty){    // ���� ������ ������, �� �������� ��� 1 ������� �������� ���������
        value = val;
        nxt = NULL;
        isEmpty = false;
        return;
    }

    List *cur = this;          // ����� ������ �� ����� ������
    while (cur->nxt != NULL){
        cur = cur->nxt;
    }

    List *nw = new List(val, NULL, false);  // � ������� ���� ������� � �����
    cur->nxt = nw;
}

// ���������� ������ ���������
void List :: sort_(){
    if (isEmpty){
        return;
    }

    bool isSorted = false;
    while (!isSorted){                         // ���� ������ �� ������������
        isSorted = true;
        List *cur = this;
        List *next = cur->nxt;

        while (next != NULL){                  // ����� �� ����� ������
            if (cur->value > next->value){     // �������� �������� 2 �������� ��������
                swap(cur->value, next->value);
                isSorted = false;
            }

            cur = cur->nxt;
            next = next->nxt;
        }
    }
}

// ���������� � ������ � ����������� ������� ����������
void List :: addSort(Unit val){
    if (isEmpty){              // ���� ������ ������, �� ������� ������� �� 1 �����
        value = val;
        nxt = NULL;
        isEmpty = false;
        return;
    }

    if (val < value){                              // ���� ������ ������� ������ ��������, �� ������� ������ ������
        List *sec = new List(value, nxt, isEmpty); // �������� ������ �������
        List *nw = new List(val, sec, false);      // �������� ������ �������
        *this = *nw;                               // ������������ ������ �������
        return;
    }

    List *cur = this;                // ��������� �� ������
    while (cur->nxt != NULL){
        if (val < cur->nxt->value){  // ������ ��� ������ ������ �������
            break;
        }
        cur = cur->nxt;
    }

    List *nw = new List(val, cur->nxt, false);  // ������� ��� ����
    cur->nxt = nw;
}

// ������� 2 ������
void List :: addList(List next){
    if (next.isEmpty){ // ���� 2 ������ ������, �� ������ ������ �� ����
        return;
    }

    if (isEmpty){      // ���� ��� ������ ������, �� ������ ������, ��� ��� ������ - ��� ������ ������
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
    while (cur->nxt != NULL){ // ������ �� ����� ������ ������
        cur = cur->nxt;
    }
    List *nw = new List(next); // ��������� ������ ������
    cur->nxt = nw;             // ������� � ��� ������ ����� ������
}

// ������� ��� ��������, ������� �������� ��� �������
int List :: write(string nm, pair <double, double> c, double d){
    if (isEmpty){ // ���� ������ ������, �� ������ ������ �� ����
        return 0;
    }

    List *cur = this;
    int cnt = 0;
    while (cur != NULL){                 // ��������� �� ������
        if (cur->value.check(nm, c, d)){ // ������ �������� � ���� ����, �� �������
            cout << cur->value;
            cout << endl;
            cnt++;
        }
        cur = cur->nxt;
    }
    return cnt;
}

// ������� ��� ��������, ������� �������� ��� �������
int List :: remove_(string nm, pair <double, double> c, double d){
    if (isEmpty){ // ���� ������ ������, �� ������ ������� �� �� �����
        return 0;
    }

    int cnt = 0;
    while (nxt != NULL && value.check(nm, c, d)){ // ���� ������ ������� �������� ��� �������, ������� ���
        List *next = nxt;
        value = nxt->value;
        nxt = nxt->nxt;
        next->nxt = NULL;
        delete(next);
        next = NULL;
        cnt++;
    }

    if (value.check(nm, c, d)){                   // ���� ������� ���, �� �������, ��� ������ ������
        isEmpty = true;
        cnt++;
        return cnt;
    }

    List *last = this;
    List *cur = nxt;
    while (cur != NULL){                          // ��������� �� ����� ������
        if (cur->value.check(nm, c, d)){          // ���� ����, ������
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

// ������� �������� ����� ��� ��������� ������
vector <pair <string, double> > List :: resourcesNeed(){
    vector <pair <string, double> > need;
    if (isEmpty){  // ���� ������ ������, �� ������ �� ����
        need.clear();
        return need;
    }

    List *cur = this;
    while (cur != NULL){              // ��������� �� ������
        vector <string> h = cur->value.getNeed(); // ������� ���, ��� ����
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
    if (isEmpty){ // ���� ������ ������, �� ������ �� ����������
        prod.clear();
        return prod;
    }

    List *cur = this;

    while (cur != NULL){            // ������� �� ����� ������
        double res = cur->value.getNum(); // ������� ���, ��� ����
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
