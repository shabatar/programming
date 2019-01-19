#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
using namespace std;

void encode( char in[3],  char out[4] )
{
    out[0] = (in[0]&0xfc) >> 2;
    out[1] = ((in[0]&0x03) << 4)+((in[1] & 0xf0) >> 4);
    out[2] = ((in[1]&0x0f) << 2)+((in[2] & 0xc0) >> 6);
    out[3] = in[2]&0x3f; 
}

int main() {
    fstream fs, out;
    fs.open("in.txt");
    out.open("out.txt",ios_base::out | ios_base::trunc);
    char table[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
                      'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
                      'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
                      'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};      
    bool eofile = false; 
    int replace = 0; 
    while (!eofile) {
        char c = 0;
        char buf[3];
        for (int i=0; i<3; ++i) {
            fs.get(c);
            if (fs.eof()) {
                eofile = true;
                if (i==0) break;
                if (i==1) {
                    buf[i] = 0;
                    buf[i+1] = 0;
                    replace = 2;
                    break; }
                if (i==2) {
                    buf[i] = 0;
                    replace = 1;
                    break; }
            }
            buf[i]=c;
        }
        if (eofile && replace == 0) break;
        char out1[4];
        encode(buf,out1);
        char encoded[4];
        for (int i=0;i<4;i++) encoded[i] = table[out1[i]];
        if (replace == 1)
            encoded[3] = '=';
        else if (replace == 2) {
            encoded[2] = '=';
            encoded[3] = '='; }
        out.put(encoded[0]);
        out.put(encoded[1]);
        out.put(encoded[2]);
        out.put(encoded[3]);
    }
    fs.close();
    out.close();
    return 0;
}