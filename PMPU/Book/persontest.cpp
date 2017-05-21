#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <map>
#include <cstdlib>
#include "persontest.h"

using namespace std;

int isString(string s){
    if (s == ""){
        return 0;
    }
    if (s == "*"){
        return 1;
    }
    bool isSpace = 1;
    for (int i = 0; i < (int)s.size(); i++){
        if (!(isalnum(s[i]) || s[i] == ' ')){
            return 2;
        }
        if (s[i] != ' '){
            isSpace = 0;
        }
    }
    return !isSpace;
}

bool toInt(int *num, string tmp){
    *num = 0;
    for (int i = 0; i < (int)tmp.size(); i++){
        if (!(isdigit(tmp[i]))){
            return 1;
        }
        *num = (*num) * 10 + tmp[i] - '0';
    }
    return 0;
}

int getlineString(istream &stream, string *s){
    *s = "";
    while (true){
        if (isString(*s) == 2){
            return 2;
        }
        if (isString(*s) == 1){
            return 0;
        }
        if (!getline(stream, *s)){
            return 1;
        }
    }
}

int readString(istream &stream, string *s){
    *s = "";
    while (true){
        if (isString(*s) == 2){
            return 2;
        }
        if (isString(*s) == 1){
            return 0;
        }
        if (!(stream >> *s)){
            return 1;
        }
    }
}

int readInt(istream &stream, int *num){
    string tmp = "";
    if (readString(stream, &tmp)){
        return 1;
    }
    if (toInt(num, tmp)){
        return 2;
    }
    return 0;
}

Test & Test::operator = (const Test &tmp){
        if (this == &tmp){
            return *this;
        }
        name = tmp.name;
        num = tmp.num;
        scores = tmp.scores;
        return *this;
    }

Test::Test(const Test &tmp){
        name = tmp.name;
        num = tmp.num;
        scores.clear();
        for (int i = 0; i < (int)tmp.scores.size(); i++){
            scores.push_back(tmp.scores[i]);
        }
    }

Test::Test(){
        name = "";
        num = 0;
        scores.clear();
    }

int Test::read(bool work, istream &stream){    // work == 1 - work with user and keyboard, work == 0 - work with file
        if (work){
            cout << "Enter name:\n";
        }
        if (getlineString(stream, &name)){
            return 1;
        }

        if (work){
            cout << "Enter test number:\n";
        }
        if (readInt(stream, &num)){
            return 2;
        }

        if (work){
            cout << "Enter number of attributes:\n";
        }
        int n = 0;
        if (readInt(stream, &n)){
            return 3;
        }

        if (work){
            cout << "Enter scores:\n";
        }
        scores.clear();
        for (int i = 0; i < n; i++){
            int x = 0;
            if(readInt(stream, &x)){
                return 4;
            }
            scores.push_back(x);
        }

        return 0; // we successfully read from file
    }

istream& operator >> (istream &stream, Test &temp){
        temp.read(0, stream);
        return stream;
    }

void Test::write(bool work, ostream &stream){
        if (work) stream << "***TEST***\n";
        if (work) stream << "Name: ";
        stream << name << endl;
        if (work) stream << "Test number: ";
        stream << num << endl;
        if (work) stream << "Number of attributes: ";
        stream << scores.size() << endl;
        if (work) stream << "Scores: ";
        for (int i = 0; i < (int)scores.size(); i++){
            stream << scores[i] << " ";
        }
        stream << endl;
    }

ostream& operator << (ostream &stream, Test &temp){
        temp.write(0, stream);
        return stream;
    }

int Test::compare(Test cmp){
        if (cmp.name != name){
            cout << "kek " << (cmp.name > name) << " kok ";
            return ((cmp.name > name) ? 1 : -1);
        }
        if (cmp.num != num){
            return ((cmp.num > num) ? 1 : -1);
        }
        return 0;
    }

bool Test::operator < (const Test &tmp){
        return (compare(tmp) == -1 ? 1 : 0);
    }

bool Test::operator == (const Test &tmp){
        return (compare(tmp) == 0 ? 1 : 0);
    }

bool Test::operator > (const Test &tmp){
        return !(*this == tmp || *this < tmp);
    }


bool Test::check(Test ch){
        bool f1 = (ch.name == name || ch.name == "*");
        bool f2 = (ch.num == num || ch.num == -1);
        bool f3 = ((ch.scores.size() == 0) || (ch.scores.size() == 2 * scores.size()));
        for (int i = 0; i < (int)scores.size(); i++){
            if ((int)ch.scores.size() <= i * 2)
                break;
            f3 &= (ch.scores[i] <= scores[i] && scores[i] <= ch.scores[i + scores.size()]);
        }
        return (f1 && f2 && f3);
    }

int Test::getProperty(vector <int> v){
        int sum = 0;
        for (int i = 0; i < (int)scores.size(); i++)
            sum += v[i] * scores[i];
        return sum;
    }

void free_list(list_test *tmp){ // free memory of list
    while (tmp != NULL){
        list_test *nw = tmp->next;
        delete tmp;
        tmp = nw;
    }
    return;
}

void List::add(Test a){
            if (head == NULL){
                head = new list_test;
                head->next = NULL;
                head->val = a;
                last = head;
                return;
            }
            list_test *nw = new list_test;
            last->next = nw;
            last = nw;
            last->next = NULL;
            last->val = a;
            return;
        }

List & List::operator = (const List &tmp){
            if (this == &tmp){
                return *this;
            }
            free_list(head);
            head = NULL;
            last = NULL;
            if (tmp.head == NULL){
                return *this;
            }
            add(tmp.head->val);
            list_test *nw = tmp.head->next;
            while (nw != NULL){
                add(nw->val);
                nw = nw->next;
            }
            return *this;
        }

ostream& operator << (ostream &stream, List &temp){
            list_test *tmp = temp.head;
            while (tmp != NULL){
                tmp->val.write(0, stream);
                tmp = tmp->next;
            }
            return stream;
        }

istream& operator >> (istream &stream, List &tmp){
            Test nw;
            while (!nw.read(0, stream)){
                tmp.add(nw);
            }
            return stream;
        }

void List::sort_list(){
            if (head == last){
                return;
            }
            int cnt = 0;
            list_test *tmp = head;
            while (tmp != NULL){
                cnt++;
                tmp = tmp->next;
            }
            tmp = head;
            int cntl = 1;
            while (cntl < cnt / 2){
                cntl++;
                tmp = tmp->next;
            }
            list_test *rhead = tmp->next;
            list_test *rlast = last;
            tmp->next = NULL;
            last = tmp;
            (*this).sort_list();
            list_test *lhead = head;
            head = rhead;
            last = rlast;
            (*this).sort_list();
            list_test *lc = lhead;
            list_test *rc = head;
            List Buf;
            int cur = 0;
            while (cur < cnt){
                if (lc == NULL){
                    Buf.add(rc->val);
                    rc = rc->next;
                    cur++;
                    continue;
                }
                if (rc == NULL){
                    Buf.add(lc->val);
                    lc = lc->next;
                    cur++;
                    continue;
                }
                cout << lc->val.name << " check " << rc->val.name << " return " << lc->val.compare(rc->val) << endl;
                if (lc->val.compare(rc->val) == -1){
                    Buf.add(rc->val);
                    rc = rc->next;
                    cur++;
                    continue;
                } else {
                    Buf.add(lc->val);
                    lc = lc->next;
                    cur++;
                    continue;
                }
            }
            free_list(lhead);
            (*this) = Buf;
            return;
        }

void List::addSort(Test nw){
            list_test *cur = head;
            if (cur == NULL){
                add(nw);
                return;
            }
            if (cur->val.compare(nw) == 1){
                list_test *tmp = new list_test;
                tmp->val = nw;
                tmp->next = head;
                head = tmp;
                return;
            }
            while ((cur->next != NULL) && (nw.compare(cur->next->val) == 1)){
                cur = cur->next;
            }
            list_test *tmp = new list_test;
            tmp->val = nw;
            tmp->next = cur->next;
            cur->next = tmp;
            if (tmp->next == NULL){
                last = tmp;
            }
            return;
        }

void List::addList(List sec){
            list_test *cur = sec.head;
            while (cur != NULL){
                add(cur->val);
                cur = cur->next;
            }
            return;
        }

void List::write(Test tmp){
            list_test *cur = head;
            while (cur != NULL){
                if (cur->val.check(tmp)){
                    cur->val.write();
                }
                cur = cur->next;
            }
            return;
        }

vector <vector <int> > List::getBallList(int t){
            list_test *cur = head;
            map <vector <int>, int> balls;
            while (cur != NULL){
                if (cur->val.num == t){
                    balls[cur->val.scores]++;
                }
                cur = cur->next;
            }
            map <vector <int>, int>::iterator beg = balls.begin();
            vector <pair<int, vector <int> > > srt;
            for (; beg != balls.end(); beg++){
                srt.push_back(make_pair((*beg).second, (*beg).first));
            }
            sort(srt.begin(), srt.end());
            reverse(srt.begin(), srt.end());

            vector <vector <int> > ans;
            for (int i = 0; i < (int)srt.size(); i++){
                ans.push_back(srt[i].second);
            }
            return ans;
        }

void List::remove_out(Test tmp){
            list_test *cur = head;
            while (cur != NULL && cur->val.check(tmp)){
                head = cur->next;
                delete cur;
                cur = head;
            }
            if (cur == NULL){
                last = NULL;
                return;
            }
            while (cur->next != NULL){
                if (cur->next->val.check(tmp)){
                    list_test *nw = cur->next;
                    cur->next = nw->next;
                    if (last == nw){
                        last = cur;
                    }
                    delete nw;
                } else {
                    cur = cur->next;
                }
            }
            return;
        }

void List::Clear(){
            free_list(head);
            head = NULL;
            last = NULL;
        }

List::List(){  // constructor
            head = NULL;
            last = NULL;
        }

List::~List(){ // destructor
            free_list(head);
        }

int getCondition(Test *nw){
    cout << "Enter name:\n";
    if (getlineString(cin, &(nw->name))){
        return 1;
    }

    cout << "Enter test number:\n";
    if (readInt(cin, &(nw->num))){
        return 2;
    }

    cout << "Enter number of attributes:\n";
    int n = 0;
    if (readInt(cin, &(n))){
        return 3;
    }

    cout << "Enter lower bounds of scores:\n";
    for (int i = 0; i < n; i++){
        int x = 0;
        if (readInt(cin, &x)){
            return 4;
        }
        nw->scores.push_back(x);
    }

    cout << "Enter upper bounds of scores:\n";
    for (int i = 0; i < n; i++){
        int x = 0;
        if (readInt(cin, &x)){
            return 5;
        }
        nw->scores.push_back(x);
    }

    return 0; // we successfully read from file
}
