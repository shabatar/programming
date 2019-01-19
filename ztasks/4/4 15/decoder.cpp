#include <iostream>
#include <stdlib.h>  
#include <stdio.h>
#include <fstream>
#include <math.h>
using namespace std;

char enc_char( char el ) {
    char table[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                      'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
                      'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
                      'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'}; 
    int i;
    for (i=0; i<64; ++i) {
        if (table[i] == el) {
            return (char)(i);
        }
    }
}

void decode(char in[4], char out[3])
{
    int i;
	if (in[2] == '=') {
		in[2]= 0;
		in[3]= 0;
	}
	if (in[3] == '=') {
		in[3]= 0;
	}
    for(i=0; i<4; ++i) { in[i] = enc_char(in[i]);}
   	out[0] = ((in[0])<< 2) + ((in[1])>> 4);
	out[1] = ((in[1])<< 4) + ((in[2])>> 2);
	out[2] = ((in[2])<< 6) + (in[3]); 
}

int main() {
	fstream fs, out;
    fs.open("in.txt");
    out.open("out.txt",ios_base::out | ios_base::trunc);
    if(!fs.is_open() || !out.is_open()) {
        cout << "Error." << endl;
        return 0;
    }
    bool eofile = false;
    int replace = 0;
    while(!eofile) {
	    char c;
	   	char buf[4];
	   	for (int i=0; i<4; ++i) 
        {
            fs.get(c);
            if (fs.eof()) {
                eofile = true; 
                break; }
            buf[i]  = c;
        }
        char out1[3];
        decode(buf,out1);
        out.put(out1[0]);
        out.put(out1[1]);
        out.put(out1[2]);
    }
    fs.close();
    out.close();
}