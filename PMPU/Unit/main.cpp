#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "unit.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian"); // русский язык в консоли
    List *lst = new List();
    while (true){
        string command;
        cin >> command;
        if (command == "help"){
            cout << "help - вывести на экран список команд" << endl
                 << "clear - очистить список" << endl
                 << "load <filename> - добавить список из файла" << endl
                 << "save <filename> - сохранить список в файле" << endl
                 << "sort - отсортировать список" << endl
                 << "add - добавить элемент" << endl
                 << "addList <filename> - добавить в текущий список новый список из файла" << endl
                 << "find <условия> - вывести на экран элементы, удовлетворяющие условиям" << endl
                 << "delete <условия> - удалить элементы, удовлетворяющие условиям" << endl
                 << "exit - завершить работу и выйти" << endl
                 << "resources - вывести на экран, сколько ресурсов нужно для создания имеющихся юнитов и сколько они производят" << endl;
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
            ifstream stream(file);                              // открываем файл
            if (stream.is_open()){                              // проверяем смогли ли мы открыть файл
                streambuf *newBuffer = stream.rdbuf();          // сохраняем старый поток ввода
                streambuf *curBuffer = cin.rdbuf(newBuffer);    // перенаправляем поток ввода в файл
                lst->~List();
                lst = new List();
                cin >> *lst;                                    // считываем
                cin.rdbuf(curBuffer);                           // перенаправляем поток ввода обратно
                stream.close();                                 // закрываем файл
            } else {
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
            }
            continue;
        }

        if (command == "addList"){
            char file[256];
            cin >> file;
            ifstream stream(file);                              // открываем файл
            if (stream.is_open()){                              // проверяем смогли ли мы открыть файл
                streambuf *newBuffer = stream.rdbuf();          // сохраняем старый поток ввода
                streambuf *curBuffer = cin.rdbuf(newBuffer);    // перенаправляем поток ввода в файл
                List *newList = new List();
                cin >> *newList;                                // считываем
                lst->addList(*newList);
                cin.rdbuf(curBuffer);                           // перенаправляем поток ввода обратно
                stream.close();                                 // закрываем файл
            } else {
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
            }
            continue;
        }

        if (command == "save"){
            char file[256];
            cin >> file;
            ofstream stream(file);                           // открываем файл
            streambuf *newBuffer = stream.rdbuf();           // сохраняем старый поток вывода
            streambuf *curBuffer = cout.rdbuf(newBuffer);    // перенаправляем поток вывода в файл
            cout << *lst;                                    // выводим
            cout.rdbuf(curBuffer);                           // перенаправляем поток вывода обратно
            stream.close();                                  // закрываем файл
            continue;
        }

        if (command == "sort"){
            lst->sort_();
            continue;
        }

        if (command == "add"){
            while (true){
                cout << "Введите новый элемент в следующем формате:" << endl
                     << "Название юнита - одна строчка" << endl
                     << "Координаты юнита - два вещественных числа" << endl
                     << "Название ресурса - одна строчка" << endl
                     << "Сколько ресурса он производит - одно вещественное число" << endl
                     << "Количество требуемых ресурсов - одно целое число N" << endl
                     << "Требуемые ресурсы - 2 * N строчек, по одному названию в строке и по одному числу в следующей строке" << endl;
                Unit nw;
                if (!(cin >> nw)){ // если мы не смогли считать
                    cin.clear();   // сбросим поток ввода, чтобы можно было дальше считывать
                    cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
                    break;
                }
                lst->add(nw);
                cout << "Хотите ввести еще одно? Напишите Yes/No" << endl;
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
            cout << "Введите условия в следующем формате: " << endl
                 << "Название юнита - одна строка" << endl
                 << "Координата - два вещественных числа" << endl
                 << "Максимальное расстояние до точки - одно вещественное число" << endl;
            string nm;
            getline(cin, nm);
            if (nm == ""){
                getline(cin, nm);
            }
            pair <double, double> c;
            if (!(cin >> c.first >> c.second)){
                cin.clear();
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
                continue;
            }
            double d;
            if (!(cin >> d)){
                cin.clear();
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
                continue;
            }
            int cnt = lst->write(nm, c, d);
            if (cnt == 0){
                cout << "Нет подходящих элементов" << endl;
            }
            continue;
        }

        if (command == "delete"){
            cout << "Введите условия в следующем формате: " << endl
                 << "Название юнита - одна строка" << endl
                 << "Координата - два вещественных числа" << endl
                 << "Максимальное расстояние до точки - одно вещественное число" << endl;
            string nm;
            getline(cin, nm);
            if (nm == ""){
                getline(cin, nm);
            }
            pair <double, double> c;
            if (!(cin >> c.first >> c.second)){
                cin.clear();
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
                continue;
            }
            double d;
            if (!(cin >> d)){
                cin.clear();
                cout << "НЕПРАВИЛЬНЫЙ ВВОД" << endl;
                continue;
            }
            int cnt = lst->remove_(nm, c, d);
            cout << "Количество удаленных элементов: " << cnt << endl;
            continue;
        }

        if (command  == "exit"){
            lst->~List();
            return 0;
        }

        if (command == "resources"){
            vector <pair <string, double> > need = lst->resourcesNeed();
            cout << "Необходимые ресурсы и их количество: " << endl;
            for (int i = 0; i < (int)need.size(); i++){
                cout << need[i].first << endl;
                cout << need[i].second << endl;
            }

            vector <pair <string, double> > prod = lst->resourcesProduce();
            cout << "Производимые ресурсы и их количество: " << endl;
            for (int i = 0; i < (int)prod.size(); i++){
                cout << prod[i].first << endl;
                cout << prod[i].second << endl;
            }

            continue;
        }

        cout << "Неизвестная команда" << endl;
    }
    return 0;
}
