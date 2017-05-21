#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "unit.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian"); // ������� ���� � �������
    List *lst = new List();
    while (true){
        string command;
        cin >> command;
        if (command == "help"){
            cout << "help - ������� �� ����� ������ ������" << endl
                 << "clear - �������� ������" << endl
                 << "load <filename> - �������� ������ �� �����" << endl
                 << "save <filename> - ��������� ������ � �����" << endl
                 << "sort - ������������� ������" << endl
                 << "add - �������� �������" << endl
                 << "addList <filename> - �������� � ������� ������ ����� ������ �� �����" << endl
                 << "find <�������> - ������� �� ����� ��������, ��������������� ��������" << endl
                 << "delete <�������> - ������� ��������, ��������������� ��������" << endl
                 << "exit - ��������� ������ � �����" << endl
                 << "resources - ������� �� �����, ������� �������� ����� ��� �������� ��������� ������ � ������� ��� ����������" << endl;
            continue;
        }

        if (command == "clear"){
            lst->~List();
            lst = new List();
            continue;
        }

        if (command == "load"){
            char file[256];
            cin >> file;
            ifstream stream(file);                              // ��������� ����
            if (stream.is_open()){                              // ��������� ������ �� �� ������� ����
                streambuf *newBuffer = stream.rdbuf();          // ��������� ������ ����� �����
                streambuf *curBuffer = cin.rdbuf(newBuffer);    // �������������� ����� ����� � ����
                lst->~List();
                lst = new List();
                cin >> *lst;                                    // ���������
                cin.rdbuf(curBuffer);                           // �������������� ����� ����� �������
                stream.close();                                 // ��������� ����
            } else {
                cout << "������������ ����" << endl;
            }
            continue;
        }

        if (command == "addList"){
            char file[256];
            cin >> file;
            ifstream stream(file);                              // ��������� ����
            if (stream.is_open()){                              // ��������� ������ �� �� ������� ����
                streambuf *newBuffer = stream.rdbuf();          // ��������� ������ ����� �����
                streambuf *curBuffer = cin.rdbuf(newBuffer);    // �������������� ����� ����� � ����
                List *newList = new List();
                cin >> *newList;                                // ���������
                lst->addList(*newList);
                cin.rdbuf(curBuffer);                           // �������������� ����� ����� �������
                stream.close();                                 // ��������� ����
            } else {
                cout << "������������ ����" << endl;
            }
            continue;
        }

        if (command == "save"){
            char file[256];
            cin >> file;
            ofstream stream(file);                           // ��������� ����
            streambuf *newBuffer = stream.rdbuf();           // ��������� ������ ����� ������
            streambuf *curBuffer = cout.rdbuf(newBuffer);    // �������������� ����� ������ � ����
            cout << *lst;                                    // �������
            cout.rdbuf(curBuffer);                           // �������������� ����� ������ �������
            stream.close();                                  // ��������� ����
            continue;
        }

        if (command == "sort"){
            lst->sort_();
            continue;
        }

        if (command == "add"){
            while (true){
                cout << "������� ����� ������� � ��������� �������:" << endl
                     << "�������� ����� - ���� �������" << endl
                     << "���������� ����� - ��� ������������ �����" << endl
                     << "�������� ������� - ���� �������" << endl
                     << "������� ������� �� ���������� - ���� ������������ �����" << endl
                     << "���������� ��������� �������� - ���� ����� ����� N" << endl
                     << "��������� ������� - 2 * N �������, �� ������ �������� � ������ � �� ������ ����� � ��������� ������" << endl;
                Unit nw;
                if (!(cin >> nw)){ // ���� �� �� ������ �������
                    cin.clear();   // ������� ����� �����, ����� ����� ���� ������ ���������
                    cout << "������������ ����" << endl;
                    break;
                }
                lst->add(nw);
                cout << "������ ������ ��� ����? �������� Yes/No" << endl;
                string want;
                cin >> want;
                if (want == "Yes"){
                    continue;
                } else {
                    break;
                }
            }
            continue;
        }

        if (command == "find"){
            cout << "������� ������� � ��������� �������: " << endl
                 << "�������� ����� - ���� ������" << endl
                 << "���������� - ��� ������������ �����" << endl
                 << "������������ ���������� �� ����� - ���� ������������ �����" << endl;
            string nm;
            getline(cin, nm);
            if (nm == ""){
                getline(cin, nm);
            }
            pair <double, double> c;
            if (!(cin >> c.first >> c.second)){
                cin.clear();
                cout << "������������ ����" << endl;
                continue;
            }
            double d;
            if (!(cin >> d)){
                cin.clear();
                cout << "������������ ����" << endl;
                continue;
            }
            int cnt = lst->write(nm, c, d);
            if (cnt == 0){
                cout << "��� ���������� ���������" << endl;
            }
            continue;
        }

        if (command == "delete"){
            cout << "������� ������� � ��������� �������: " << endl
                 << "�������� ����� - ���� ������" << endl
                 << "���������� - ��� ������������ �����" << endl
                 << "������������ ���������� �� ����� - ���� ������������ �����" << endl;
            string nm;
            getline(cin, nm);
            if (nm == ""){
                getline(cin, nm);
            }
            pair <double, double> c;
            if (!(cin >> c.first >> c.second)){
                cin.clear();
                cout << "������������ ����" << endl;
                continue;
            }
            double d;
            if (!(cin >> d)){
                cin.clear();
                cout << "������������ ����" << endl;
                continue;
            }
            int cnt = lst->remove_(nm, c, d);
            cout << "���������� ��������� ���������: " << cnt << endl;
            continue;
        }

        if (command  == "exit"){
            lst->~List();
            return 0;
        }

        if (command == "resources"){
            vector <pair <string, double> > need = lst->resourcesNeed();
            cout << "����������� ������� � �� ����������: " << endl;
            for (int i = 0; i < (int)need.size(); i++){
                cout << need[i].first << endl;
                cout << need[i].second << endl;
            }

            vector <pair <string, double> > prod = lst->resourcesProduce();
            cout << "������������ ������� � �� ����������: " << endl;
            for (int i = 0; i < (int)prod.size(); i++){
                cout << prod[i].first << endl;
                cout << prod[i].second << endl;
            }

            continue;
        }

        cout << "����������� �������" << endl;
    }
    return 0;
}
