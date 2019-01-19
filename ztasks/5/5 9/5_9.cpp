#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
 
void getline1(ifstream &in, string& s) {
    getline(in, s);
    if (s[s.length()-1] == '\r')
        s = s.erase(s.length()-1, 1);
}

// разрзаем файл на два файла
void CutFile(ifstream &in, ofstream &tmp1, ofstream &tmp2) {
    string s1 = "", s2;
    bool what_tmp = true; // true == write to tmp1, false == write to tmp2
    bool tmp1started = false, tmp2started = false; // записано ли что-то в tmp
    //(чтобы не было лишней новой строки)

    do {
        // чтобы не было новой строки в конце файлов
        getline1(in, s2);
        if (s2 > s1) {
            if (what_tmp) {
                if (tmp1started) tmp1 << endl;
                else tmp1started = true;
                tmp1 << s2;
            }
            else {
                if (tmp2started) tmp2 << endl;
                else tmp2started = true;
                tmp2 << s2;
            }
        }
        else {
            what_tmp = (what_tmp) ? false : true;
            if (what_tmp) {
                if (tmp1started) {
                    tmp1 << endl << "***" << endl;
                }
                else tmp1started = true;
                tmp1 << s2;
            }
            else {
                if (tmp2started) {
                    tmp2 << endl << "***" << endl;
                }
                else tmp2started = true;
                tmp2 << s2;
            }
        }
        s1 = s2;
    } while (!in.eof());
}

bool isSorted(ifstream &in) {
    string s1 = "", s2;
    bool sorted = true;
    do {
        getline1(in, s2);
        //cout << s2 << endl;
        if (s2 < s1) {
            sorted = false;
            break;
        }
        s1 = s2;
    } while (!in.eof());

    return sorted;
}

// сливаем два файла в один
void MergeFiles(ifstream &out1, ifstream &out2, ofstream &in) {
    string s1 = "";
    string s2 = "";
    //string stars = "***";
    string s;
    while(!out1.eof() && !out2.eof()) {
        //На начальном этапе
        if (s1 == "" && s2 == "") {
            getline1(out1, s1);
            getline1(out2, s2);
        }
        //На этапе окончания одного из блоков строк
        if (s1 == "***" && s2 != "***") {
            //cout << "s1 = " << s1 << "  s2 = " << s2 << endl;
            while (s2 != "***" && !out2.eof()) {
                in << s2 << endl;
                getline1(out2, s2);
                //cout << s2 << endl;
            }
            //if (out2.eof()) in << s2 << endl;
            getline1(out1, s1);
            getline1(out2, s2);
            //cout << "s1 == ***" << endl;
            continue;
        }
        else if (s1 != "***" && s2 == "***") {
            while (s1 != "***" && !out1.eof()) {
                in << s1 << endl;
                getline1(out1, s1);
            }
            getline1(out1, s1);
            getline1(out2, s2);
            //cout << "s2 == ***" << endl;
            continue;
        }
        else if (s1 == "***" && s2 == "***") {
            getline1(out1, s1);
            getline1(out2, s2);
            //cout << "s1 and s2 == ***" << endl;
            continue;
        }
        //Запись отсортированных блоков в файл
        if (s1 == s2) {
            in << s1 << endl;
            in << s2 << endl;
            getline1(out1, s1);
            getline1(out2, s2);
        }
        else if (s1 > s2) {
            in << s2 << endl;
            getline1(out2, s2);
        }
        else if (s1 < s2) {
            in << s1 << endl;
            getline1(out1, s1);
        }
    }
    if (out1.eof() && !out2.eof()) {
        s = s2;
        while (!out2.eof()) {
            if (s == "***") getline1(out2, s);
            if (s < s1)
                in << s << endl;
            if (s > s1) {
                in << s1 << endl << s << endl;
                while (!out1.eof()) {
                    getline1(out2, s);
                    if (s == "***") continue;
                    in << s << endl;
                }
                break;
            }
            getline1(out2, s);
        }
    }

    else if (!out1.eof() && out2.eof()) {
        //cout << "s1 = " << s1 << "  s2 = " << s2 << endl;
        s = s1;
        while (!out1.eof()) {
            if (s == "***") getline1(out1, s);
            if (s < s2)
                in << s << endl;
            if (s > s2) {
                in << s2 << endl << s << endl;
                while (!out1.eof()) {
                    getline1(out1, s);
                    if (s == "***") continue;
                    in << s << endl;
                }
                break;
            }
            getline1(out1, s);
        }
    }
}


void printFile(ifstream &in, string name) {
    string s;

    cout << endl << name << endl;
    while (!in.eof()) {
        getline1(in, s);
        cout << s << endl;
    }
    cout << endl;
}


int main() {
    ifstream in_in; ofstream in_out;
    ifstream tmp1_in; ofstream tmp1_out;
    ifstream tmp2_in; ofstream tmp2_out;
    in_in.open("in.txt", ios::in);
    tmp1_out.open("tmp1.txt", ios::out);
    tmp2_out.open("tmp2.txt", ios::out);

    while (!isSorted(in_in)) {
        in_in.seekg(0); tmp1_out.seekp(0); tmp2_out.seekp(0);
        CutFile(in_in, tmp1_out, tmp2_out);
        in_in.close(); tmp1_out.close(); tmp2_out.close();
        
        in_out.open("in.txt", ios::out);
        tmp1_in.open("tmp1.txt", ios::in);
        tmp2_in.open("tmp2.txt", ios::in);
        MergeFiles(tmp1_in, tmp2_in, in_out);
        in_out.close(); tmp1_in.close(); tmp2_in.close();
        
        // удаляем лишние пустые строки в конце in (появились после MergeFiles)
        in_in.open("in.txt", ios::in);
        vector<string> vs;
        string str;
        while (getline(in_in, str))
            vs.push_back(str);
        in_in.close();
        in_out.open("in.txt", ios::out);
        for (int i = 0; i < vs.size(); i++) {
            if (i != 0)
                in_out << endl;
            in_out << vs[i];
        }
        in_out.close();
        in_in.open("in.txt", ios::in);
        tmp1_out.open("tmp1.txt", ios::out);
        tmp2_out.open("tmp2.txt", ios::out);
        cout << "run" << endl;
    }

    cout << "done" << endl;
    return 0;
}
