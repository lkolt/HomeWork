#include <iostream>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "persontest.h"

using namespace std;

int main()
{
    List ls;
    while (true){

        string com;
        cin >> com;
        if (com == "help"){
            cout << "List of available commands:\n";
            cout << "help - write list of available commands\n";
            cout << "list - write current list\n";
            cout << "clear - clear the list\n";
            cout << "load <filename> - load list from file\n";
            cout << "save <filename> - save list to file\n";
            cout << "add - add new element to list\n";
            cout << "sort - sort list\n";
            cout << "find <conditions> - find tests\n";
            cout << "delete <conditions> - delete tests\n";
            cout << "testinfo <number> - find all set of balls in test <number>\n";
            cout << "exit - safe exit\n";
            cout << "cls - clear screen\n";
            continue;
        } else if (com == "list"){
            Test tmp;
            tmp.name = "*";
            tmp.num = -1;
            tmp.scores.clear();
            ls.write(tmp);
            continue;
        } else if (com == "clear"){
            ls.Clear();
            cout << "Done" << endl;
            continue;
        } else if (com == "load"){
            static char filename[256];
            cin >> filename;
            ifstream ifs(filename);                          // use <fstream> for read from file
            if (!ifs.is_open()) {
                cout << "INCORRECT INPUT!\n";
            } else {
                streambuf* our_buffer = cin.rdbuf(ifs.rdbuf());  // redirect stream to file
                cin >> ls;
                cin.rdbuf(our_buffer);                           // redirect stream back to stdin
                ifs.close();
                cout << "Done" << endl;
            }
            continue;
        } else if (com == "save"){
            static char filename[256];
            cin >> filename;
            ofstream ofs(filename);                           // use <fstream> for read from file
            streambuf* our_buffer = cout.rdbuf(ofs.rdbuf());  // redirect stream to file
            cout << ls;
            cout.rdbuf(our_buffer);                           // redirect stream back to stdin
            ofs.close();
            cout << "Done" << endl;
            continue;
        } else if (com == "add"){
            Test nw;
            while (true){
                if (!nw.read()){
                    ls.add(nw);
                } else {
                    cout << "INCORRECT INPUT!" << endl;
                    break;
                }
                cout << "Add one more? Y/N\n";
                string wk;
                cin >> wk;
                if (wk == "N"){
                    break;
                } else if (wk != "Y"){
                    cout << "INCORRECT INPUT!\n";
                    break;
                }
            }
            continue;
        } else if (com == "sort"){
            ls.sort_list();
            cout << "Done" << endl;
            continue;
        } else if (com == "find"){
            Test tmp;
            if (!getCondition(&tmp)){
                ls.write(tmp);
            } else {
                cout << "INCORRECT INPUT!" << endl;
            }
            continue;
        } else if (com == "delete"){
            Test tmp;
            if (!getCondition(&tmp)){
                ls.remove_out(tmp);
                cout << "Done" << endl;
            } else {
                cout << "INCORRECT INPUT!" << endl;
            }
            continue;
        } else if (com == "testinfo"){
            int num;
            if (readInt(cin, &num)){
                cout << "INCORRECT INPUT!" << endl;
            } else {
                vector <vector <int> > wr = ls.getBallList(num);
                for (int i = 0; i < (int)wr.size(); i++){
                    for (int j = 0; j < (int)wr[i].size(); j++){
                        cout << wr[i][j] << " ";
                    }
                    cout << endl;
                }
            }
            continue;
        } else if (com == "exit"){
            return 0;
        } else if (com == "cls"){
            system ("cls");
            continue;
        }
        cout << "Don't understand command." << endl;
    }
    return 0;
}
