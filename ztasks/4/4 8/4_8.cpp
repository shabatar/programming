#include <iostream>
#include <fstream>
using namespace std;

void c_comment(fstream& in, fstream& out) {
    char c, next;

    in.get(c);
    in.get(next);
    while (c != '*' || next != '/') {
        c = next;
        in.get(next);
    }
}

void cpp_comment(fstream& in, fstream& out) {
    char c;
    bool full_line = false; // занимает ли комментарий всю строку

    in.unget();
    in.unget();
    in.unget();
    in.get(c);
    if (c == '\n') full_line = true;

    in.get(c);
    while (c != '\n')
        in.get(c);
    
    if (!full_line) out.put('\n');
}

void findComments(char c, fstream& in, fstream& out) {
    char next;
    if (c == '/') {
        in.get(next);
        if (next == '*')
            c_comment(in, out);
        else if (next == '/')
            cpp_comment(in, out);
        else {
            out.put(c);
            out.put(next);
        }
    }
    else
        out.put(c);
}


int main(int argc, char *argv[])
{
    fstream in(argv[1], ios_base::in);
    fstream out(argv[2], ios_base::out);

    if (!in.is_open()) {
        cout << "Can't open file." << endl;
        return 1;
    }
    
    char c;
    while ((in.get(c)) && !in.eof()) {
        findComments(c, in, out);
    }

    in.close();
    out.close();
    return 0;
}
