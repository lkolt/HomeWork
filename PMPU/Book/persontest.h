#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;


/**
 * Функция isString проверяет наличие в строке букв или цифр.
 * @param s - строка, в которой проверяют.
 * @return 0 - в строке не содержатся буквы или цифры.
 * @return 1 - в строке содержаться буквы или цифры.
 * @return 2 - в строке содержаться другие символы
 **/
int isString(string s);

/**
 * Функция toInt переводит число из строки tmp в число *num
 * @param tmp - строка, в которой должно содержаться число
 * @param num - ссылка на число, в которое надо перевести
 * @return 0 - успешный перевод
 * @return 1 - перевод окончился с ошибкой
 **/
bool toInt(int *num, string tmp);

/**
 * Функция getlineString считывает из потока stream одну строку, содержащую пробелы, буквы и цифры
 * @param stream - поток ввода
 * @param s - ссылка на строку, в которую считывают
 * @return 0 - считывание произведено корректно
 * @return 1,2 - считывание окончилось с ошибкой
 **/
int getlineString(istream &stream, string *s);

/**
 * Функция readString считывает из потока stream одну строку, содержащую буквы и цифры
 * @param stream - поток ввода
 * @param s - ссылка на строку, в которую считывают
 * @return 0 - считывание произведено корректно
 * @return 1,2 - считывание окончилось с ошибкой
 **/
int readString(istream &stream, string *s);

/**
 * Функция readInt считывает из потока stream одно число
 * @param stream - поток ввода
 * @param num - ссылка на число, в которое считывают
 * return 0 - считывание произведено корректно
 * return 1,2 - считывание окончилось с ошибкой
 **/
int readInt(istream &stream, int *num);

struct Test{
    string name;
    int num;
    vector <int> scores;

    /**
     * Переопределение оператора = для класса Test
     * @param tmp - this = tmp
     **/
    Test & operator = (const Test &tmp);

    /**
     * Переопределение конструктора копирования для класса Test
     * @param tmp - this = tmp
     **/
    Test (const Test &tmp);

    /**
     * Переопределение конструктора для класса Test
     * @param tmp - this = tmp
     **/
    Test ();

    /**
     * Переопределение оператора << для ostream и элемента типа Test
     * @param stream - поток вывода
     * @param temp - переменная типа Test
     **/
    friend ostream& operator << (ostream &stream, Test &temp);

    /**
     * Переопределение оператора >> для istream и элемента типа Test
     * @param stream - поток ввода
     * @param tmp - переменная типа Test
     **/
    friend istream& operator >> (istream &stream, Test &tmp);

    /**
     * Переопределение оператора < для класса Test
     * @param tmp - this = tmp
     **/
    bool operator < (const Test &tmp);

    /**
     * Переопределение оператора == для класса Test
     * @param tmp - this = tmp
     **/
    bool operator == (const Test &tmp);

    /**
     * Переопределение оператора > для класса Test
     * @param tmp - this = tmp
     **/
    bool operator > (const Test &tmp);

    /**
     * Функция read считывает значения для полей структуры из потока stream
     * @param work = 1, если работа происходит с интерфейсом пользователя.
     * @param work = 0, если работа происходит с файлом.
     * @param stream - поток ввода, из которого считываются данные.
     * @return 0 - успешный ввод.
     * @return 1-4 - ввод закончился с ошибкой
     **/
    int read(bool work = 1, istream &stream = cin);

    /**
     * Функция write выводит поля структуры в поток stream
     * @param work = 1, если работа происходит с интерфейсом пользователя.
     * @param work = 0, если работа происходит с файлом.
     * @param stream - поток вывода, в который выводятся данные.
     **/
    void write(bool work = 1, ostream &stream = cout);

    /**
     * Функция compare сравнивает this с cmp
     * @param cmp - переменная типа Test
     * @return 1 - cmp > this.
     * @return 0 - cmp = this
     * @return -1 - cmp < this
     **/
    int compare(Test cmp);

    /**
     * Функция check проверяет подходит ли this под условия ch
     * @param ch - переменная типа Test, которая содержит в себе условия для сравнения
     * @return 1 - Переменная this подходит по условия ch.
     * @return 0 - Переменная this не подходит по условия ch.
     **/
    bool check(Test ch);

    /**
     * Функция getProperty возвращает взвешенную сумму с весами из v
     * @param v - вектор, который содержит в себе веса
     **/
    int getProperty(vector <int> v);
};

struct list_test{ // 1-linked list
    Test val;
    list_test *next;
};

class List{
    private:
        list_test *head;
        list_test *last;
    public:

        /**
         * Функция add добавляет в конец списка this элемент a типа Test
         * @param a - переменная типа Test
         **/
        void add(Test a);

        /**
         * Переопределение оператора = для класса List
         * @param tmp - this = tmp
         **/
        List & operator = (const List &tmp);

        /**
         * Переопределение оператора << для ostream и элемента типа List
         * @param stream - поток вывода
         * @param temp - переменная типа List
         **/
        friend ostream& operator << (ostream &stream, List &temp);

        /**
         * Переопределение оператора >> для istream и элемента типа List
         * @param stream - поток ввода
         * @param tmp - переменная типа List
         **/
        friend istream& operator >> (istream &stream, List &tmp);

        /**
         * Функция sort_list сортирует список this с помощью компоратора Test::compare. Реализована сортировка merge sort
         **/
        void sort_list();

        /**
         * Функция addSort добавляет в список this елемент a типа Test так, чтобы отсортированность this не изменилась
         * @param nw - переменная типа Test
         **/
        void addSort(Test nw);

        /**
         * Функция addList добавляет в конец списка this список sec
         * @param sec - список типа List
         **/
        void addList(List sec);

        /**
         * Функция write выводит все элементы списка this, которые подходят под условие tmp в поток вывода
         * @param tmp - переменная типа Test
         **/
        void write(Test tmp);

        /**
         * Функция getBallList для данного теста выдает список наборов баллов по убыванию частоты встречаемости набора баллов
         * @param t - номер теста
         **/
        vector <vector <int> > getBallList(int t);

        /**
         * Функция remove_out удаляет все элементы списка из this, которые подходят под условие tmp
         * @param tmp - переменная типа Test
         **/
        void remove_out(Test tmp);

        /**
         * Функция Clear очищает помять, которую использует список this и обнуляет его.
         **/
        void Clear();

        /**
         * Конструктор класса List
         **/
        List();

        /**
         * Деструктор класса List
         **/
        ~List();
};

/**
 * Функция getCondition считывает условия из потока ввода
 * @param nw - переменная типа Test, в которую считывают условия
 * @return 0 - успешное считывание
 * @return 1-5 - ошибка при считывании
 **/
int getCondition(Test *nw);
