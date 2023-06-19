#include "analizador.h"
#include "ui_analizador.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stack>
#include <list>
#include <QFileDialog>
#include <QMessageBox>
using namespace std;

int matriz [20][33]{
    {1,2,3,506,506,2,1,105,106,107,108,128,13,14,9,12,11,10,15,17,19,129,130,121,122,119,120,124,123,506,0,0,0},
    {1,2,2,2,100,2,1,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
    {2,2,2,2,101,2,2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
    {102,102,3,102,4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
    {500,500,5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500},
    {103,103,5,103,103,6,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
    {501,501,8,501,501,501,501,7,7,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
    {502,502,8,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
    {104,104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
    {109,109,109,109,109,109,109,109,109,109,109,109,109,109,110,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109},
    {111,111,111,111,111,111,111,111,111,111,111,111,111,111,112,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111},
    {113,113,113,113,113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
    {116,116,116,116,116,116,116,116,116,116,116,116,116,116,115,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
    {503,503,503,503,503,503,503,503,503,503,503,503,117,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
    {504,504,504,504,504,504,504,504,504,504,504,504,504,118,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
    {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,505,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
    {507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,125,507,507,507,507,507,507,507,507,507,507,507,507,507,507},
    {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,17,17,17,17,17,17,17,17,17,17,17,17,17},
    {126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,17,126,126,126,126,126,126,126,126,126,126,126,126,126},
    {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,127,19,19}

};

int predictiva [36][42]{
    {0,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600},
    {601,601,2,601,601,2,1,601,601,601,601,601,601,601,601,601,601,601,601,2,601,2,2,601,601,2,2,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601},
    {602,602,3,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602},
    {603,603,603,603,603,603,603,5,603,4,603,603,5,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603},
    {604,604,604,604,604,604,604,604,604,604,604,7,6,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604},
    {605,605,605,605,605,605,605,9,605,605,605,605,8,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605},
    {606,606,606,606,606,606,606,606,606,606,606,606,606,10,11,12,13,14,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606},
    {607,607,15,607,607,16,607,607,607,607,607,607,607,607,607,607,607,607,607,15,16,15,15,16,607,15,15,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607},
    {608,608,17,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,18,608,19,20,608,608,21,22,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608},
    {609,609,23,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609},
    {610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,24,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610},
    {611,611,611,611,611,26,611,611,611,611,611,611,611,611,611,611,611,611,611,611,25,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611},
    {612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,27,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612},
    {613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,28,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613},
    {614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,29,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614},
    {615,615,615,31,615,615,615,615,615,615,615,615,30,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615,615},
    {616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,32,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616},
    {617,617,617,34,617,617,617,617,617,617,617,617,33,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617,617},
    {618,618,35,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618},
    {619,619,619,37,619,619,619,619,37,36,619,37,37,619,619,619,619,619,37,619,619,619,619,619,619,619,619,37,37,37,37,37,37,37,37,37,37,619,619,619,619,619},
    {620,620,620,620,620,620,620,620,620,38,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620},
    {621,621,621,621,621,621,621,621,621,621,621,40,39,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621},
    {622,41,41,622,622,622,622,622,622,622,41,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,41,622,622,622,622,622,622,622,41,41,41,41,622},
    {623,623,623,43,623,623,623,623,43,623,623,43,43,623,623,623,623,623,623,623,623,623,623,623,623,623,623,42,623,623,623,623,623,623,623,623,623,623,623,623,623,623},
    {624,44,44,624,624,624,624,624,624,624,44,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,624,44,624,624,624,624,624,624,624,44,44,44,44,624},
    {625,625,625,46,625,625,625,625,46,625,625,46,46,625,625,625,625,625,625,625,625,625,625,625,625,625,625,46,45,625,625,625,625,625,625,625,625,625,625,625,625,625},
    {626,48,48,626,626,626,626,626,626,626,48,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,47,626,626,626,626,626,626,626,48,48,48,48,626},
    {627,49,49,627,627,627,627,627,627,627,49,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,49,49,49,49,627},
    {628,628,628,51,628,628,628,628,51,628,628,51,51,628,628,628,628,628,50,628,628,628,628,628,628,628,628,51,51,50,50,50,628,628,628,628,628,628,628,628,628,628},
    {629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,52,629,629,629,629,629,629,629,629,629,629,53,54,55,629,629,629,629,629,629,629,629,629,629},
    {630,57,57,630,630,630,630,630,630,630,57,630,630,630,630,630,630,630,56,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,57,57,57,57,630},
    {631,58,58,631,631,631,631,631,631,631,58,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,58,58,58,58,631},
    {632,632,632,61,632,632,632,632,61,632,632,61,61,632,632,632,632,632,61,632,632,632,632,632,632,632,632,61,61,61,61,61,59,60,632,632,632,632,632,632,632,632},
    {633,62,62,633,633,633,633,633,633,633,62,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,62,62,62,62,633},
    {634,634,634,66,634,634,634,634,66,634,634,66,66,634,634,634,634,634,66,634,634,634,634,634,634,634,634,66,66,66,66,66,66,66,63,64,65,634,634,634,634,634},
    {635,73,67,635,635,635,635,635,635,635,68,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,635,69,70,71,72,635}

};

string producciones[74]={"130 7 1 129 120 101 119 class","1 123 6 as 5 2 def","","3 101","122 4 102 121","","4 102 124","","5 2 124","","int",
    "float","char","bool","string","7 123 8","","9","10","12","13","14","16","22 109 18","130 11 7 129 120 22 119 if","7 else",
    "","130 7 129 120 22 119 while","enddo 120 22 119 dowhile 7 do","120 15 101 119 output","15 101 124","","120 17 22 119 input",
    "17 22 124","","19 101","20","","122 21 22 121","21 22 124","","23 24","22 118","","25 26","24 117","","27 116","27",
    "28 31","31 29","","109 109","109 116","30 111","30 113","109","","32 33","31 105","31 106","","34 35","33 107","33 108",
    "33 128","","18","102","103","104","125","126","120 22 119",
};

string reservadas[16]={"class","int","float","char","string","bool","if","else","do","dowhile","enddo","while","input","output","def","as"};
char minusculas[25]={'a','b','c','d','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char may[25]={'A','B','C','D','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
stack<string>pila;
list <string> lista;

string le,pal;
std::string cadToken;
std::string cadError;
std::string cadSintaxis;
int edo,rel,longi,inicio,final;
char car;


int relaciona(char car){

    for(int j=0;j<25;j++){
        if(car==minusculas[j]){
            return 0;
        }else if(car==may[j]){
            return 1;
        }
    }

    int i=car-'0';
    if (i>=0 && i<=9){
        return 2;
    }

    switch (car){
        case '_':
            return 3;
            break;
        case '.':
            return 4;
            break;
        case 'E':
            return 5;
            break;
        case 'e':
            return 6;
            break;
        case '+':
            return 7;
            break;
        case '-':
            return 8;
            break;
        case '*':
            return 9;
            break;
        case '/':
            return 10;
            break;
        case '%':
            return 11;
            break;
        case '&':
            return 12;
            break;
        case '|':
            return 13;
            break;
        case '=':
            return 14;
            break;
        case '!':
            return 15;
            break;
        case '>':
            return 16;
            break;
        case '<':
            return 17;
            break;
        case '\'':
            return 18;
            break;
        case '"':
            return 19;
            break;
        case '#':
            return 20;
            break;
        case '{':
            return 21;
            break;
        case '}':
            return 22;
            break;
        case '[':
            return 23;
            break;
        case ']':
            return 24;
            break;
        case '(':
            return 25;
            break;
        case ')':
            return 26;
            break;
        case ',':
            return 27;
            break;
        case ';':
            return 28;
            break;
        case '\n':
            return 30;
            break;
        case '\t':
            return 31;
            break;
        case '\b':
            return 32;
            break;
        default:
            return 29;
            break;
    }
}

void Token(int e, string c, int i, int f){
    if(i==f){
        f++;
    }
    bool flag=false;
    switch(e){
        case 100:
            pal= c.substr(i, f-i);
            for(int j=0;j<sizeof reservadas /sizeof reservadas[0] ;j++){
                if(pal==reservadas[j]){
                    flag=true;
                }
            }
            if(flag){
                cadToken = cadToken+c.substr(i, f-i);
                cadToken=cadToken+"  >>Palabra reservada\n";
                lista.push_back(pal);
                break;
            }else{
                cadToken = cadToken+c.substr(i, f-i);
                cadToken=cadToken+"  >>Identificador\n";
                lista.push_back("101");
                break;
            }
        case 101:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Identificador\n";
            lista.push_back("101");
            break;
        case 102:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Entero\n";
            lista.push_back("102");
            break;
        case 103:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Reales\n";
            lista.push_back("103");
            break;
        case 104:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Notación cientifica\n";
            lista.push_back("104");
            break;
        case 105:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Suma\n";
            lista.push_back("105");
            break;
        case 106:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Resta\n";
            lista.push_back("106");
            break;
        case 107:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Multiplicación\n";
            lista.push_back("107");
            break;
        case 108:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>División\n";
            lista.push_back("108");
            break;
        case 109:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Asignación\n";
            lista.push_back("109");
            break;
        case 110:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Igual\n";
            lista.push_back("109");
            lista.push_back("109");
            break;
        case 111:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Menor\n";
            lista.push_back("111");
            break;
        case 112:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Menor igual\n";
            lista.push_back("111");
            lista.push_back("109");
            break;
        case 113:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Mayor\n";
            lista.push_back("113");
            break;
        case 114:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Mayor igual\n";
            lista.push_back("113");
            lista.push_back("109");
            break;
        case 115:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Diferente\n";
            lista.push_back("116");
            lista.push_back("109");
            break;           
        case 116:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Not\n";
            lista.push_back("116");
            break;
        case 117:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>And\n";
            lista.push_back("117");
            break;
        case 118:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Or\n";
            lista.push_back("118");

            break;
        case 119:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Parentesis que abre\n";
            lista.push_back("119");
            break;
        case 120:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Parentesis que cierra\n";
            lista.push_back("120");
            break;
        case 121:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Corchete que abre\n";
            lista.push_back("121");
            break;
        case 122:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Corchete que cierra\n";
            lista.push_back("122");
            break;
        case 123:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Punto y coma\n";
            lista.push_back("123");
            break;
        case 124:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Coma\n";
            lista.push_back("124");
            break;
        case 125:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Cte caracter\n";
            lista.push_back("125");
            break;
        case 126:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Cte String\n";
            lista.push_back("126");
            break;
        case 127:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Comentario de linea\n";
            lista.push_back("127");
            break;
        case 128:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Modulo\n";
            lista.push_back("128");
            break;
        case 129:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Llave que abre\n";
            lista.push_back("129");
            break;
        case 130:
            cadToken = cadToken+c.substr(i, f-i);
            cadToken=cadToken+"  >>Llave que cierra\n";
            lista.push_back("130");
            break;

    }
}

void PosError(int e, string c, int i, int f){
    if(i==f){
        f++;
    }
    switch(e){
        case 500:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 500>>Se esperaba un digito después del punto\n";
            break;
        case 501:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 501>>Se esperaba un digito despues del exponente\n";
            break;
        case 502:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 502>>Se esperaba un digito después del signo\n";
            break;
        case 503:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 503>>Se esperaba un & después del signo &\n";
            break;
        case 504:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 504>>Se esperaba un | después del signo |\n";
            break;
        case 505:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 505>>Se esperaba un caracter entre las comillas simples\n";
            break;
        /*case 506:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+"  <<Error 506>>No se esperaban valores después del delimitador\n";
            break;*/
        case 507:
            cadError = cadError+c.substr(i, f-i);
            cadError=cadError+" <<Error 507>>Se esperaba una comilla simple que cierre\n";
            break;

    }
}
int relacionaSint(string l){
    map<string, int> diccionario;
    diccionario["class"]=0;
    diccionario["119"]=1;
    diccionario["101"]=2;
    diccionario["120"]=3;
    diccionario["129"]=4;
    diccionario["130"]=5;
    diccionario["def"]=6;
    diccionario["as"]=7;
    diccionario["123"]=8;
    diccionario["121"]=9;
    diccionario["102"]=10;
    diccionario["122"]=11;
    diccionario["124"]=12;
    diccionario["int"]=13;
    diccionario["float"]=14;
    diccionario["char"]=15;
    diccionario["bool"]=16;
    diccionario["string"]=17;
    diccionario["109"]=18;
    diccionario["if"]=19;
    diccionario["else"]=20;
    diccionario["while"]=21;
    diccionario["do"]=22;
    diccionario["dowhile"]=23;
    diccionario["enddo"]=24;
    diccionario["output"]=25;
    diccionario["input"]=26;
    diccionario["118"]=27;
    diccionario["117"]=28;
    diccionario["116"]=29;
    diccionario["111"]=30;
    diccionario["113"]=31;
    diccionario["105"]=32;
    diccionario["106"]=33;
    diccionario["107"]=34;
    diccionario["108"]=35;
    diccionario["128"]=36;
    diccionario["103"]=37;
    diccionario["104"]=38;
    diccionario["125"]=39;
    diccionario["126"]=40;
    diccionario["$"]=41;

    if(diccionario.find(l)!=diccionario.end()){
        return diccionario[l];          
    }
    return 41;

}

string imprimir(stack<string> pi){
    string a="",c="";
    while (!pi.empty()) {
        a=pi.top()+" "+a;
        pi.pop();
    }
    cout<<a<<endl;
    c=c+a;
    return c;
}
void imprimirLista(){
    string a="";
    for (const auto& elemento : lista) {
        std::cout << elemento << " ";
    }
    std::cout << std::endl;
}
void agregarPila(int prod){
    string a = producciones[prod];
    string b ="";
    if(!a.empty()){
        for(int x=0; x<a.length();x++){
            char c=a[x];
            if(c==' '){
                pila.push(b);
                b="";
            }else{
                b=b+c;
            }
        }
        pila.push(b);
    }   
}

void vaciar(){
    while(!pila.empty()){
        pila.pop();
    }
    lista.clear();
}

void errorSint(int prod){
    cadSintaxis=cadSintaxis+"<<Error de sinatiz>>\nConsulta el apartado de errores para saber más sobre el error\n";
    switch (prod) {

        case 600:
            cadError=cadError+" <<Error 600>>El programa debe iniciar con la palabra reservada 'class'\n";
            break;
        case 601:
            cadError=cadError+" <<Error 601>>Error en la declaración, caracter no válido\n";
            break;
        case 602:
            cadError=cadError+" <<Error 602>>Error en el desarrollo de la declaración, se espera un 'as' o coma\n";
            break;
        case 603:
            cadError=cadError+" <<Error 603>>Tipo de dato inválido\n";
            break;
        case 604:
            cadError=cadError+" <<Error 604>>Se espera identidicador\n";
            break;
        case 605:
            cadError=cadError+" <<Error 605>>Se espera 'as' o corchete que abre\n";
            break;
        case 606:
            cadError=cadError+" <<Error 606>>Se espera corchete\n";
            break;
        case 607:
            cadError=cadError+" <<Error 607>>Error en la continuación de la constante entera\n";
            break;
        case 608:
            cadError=cadError+" <<Error 608>>Elemento no deseado en el estatuto\n";
            break;
        case 609:
            cadError=cadError+" <<Error 609>>Error al iniciar estatuto\n";
            break;
        case 610:
            cadError=cadError+" <<Error 610>>Se espera identificador\n";
            break;
        case 611:
            cadError=cadError+" <<Error 611>>Error en la asignación\n";
            break;
        case 612:
            cadError=cadError+" <<Error 612>>Se espera corchete\n";
            break;
        case 613:
            cadError=cadError+" <<Error 613>>Se espera corchete de cierre o coma\n";
            break;
        case 614:
            cadError=cadError+" <<Error 614>>Error en la expresión, caracter inválido\n";
            break;
        case 615:
            cadError=cadError+" <<Error 615>>Error en la declaración, se espera paréntesis de cierre, coma o disyunción\n";
            break;
        case 616:
            cadError=cadError+" <<Error 616>>Elemento no válido en la expresión\n";
            break;
        case 617:
            cadError=cadError+" <<Error 617>>Elemento no válido en la expresión\n";
            break;
        case 618:
            cadError=cadError+" <<Error 618>>Elemento no válido en la expresión\n";
            break;
        case 619:
            cadError=cadError+" <<Error 619>>Elemento no válido en la expresión\n";
            break;
        case 620:
            cadError=cadError+" <<Error 620>>Elemento no válido en la expresión\n";
            break;
        case 621:
            cadError=cadError+" <<Error 621>>Se espera símbolo de comparación, coma o paréntesis o corchete de cierre\n";
            break;
        case 622:
            cadError=cadError+" <<Error 622>>Se espera identificador, constante o paréntesis de cierre\n";
            break;
        case 623:
            cadError=cadError+" <<Error 623>>Elemento no válido en la expresión\n";
            break;
        case 624:
            cadError=cadError+" <<Error 624>>Se espera suma o resta\n";
            break;
        case 625:
            cadError=cadError+" <<Error 625>>Se espera identificador, constante o paréntesis de apertura\n";
            break;
        case 626:
            cadError=cadError+" <<Error 626>>Elemento no válido en la expresión\n";
            break;
        case 627:
            cadError=cadError+" <<Error 627>>Se espera multiplicación, división o módulo\n";
            break;
        case 628:
            cadError=cadError+" <<Error 628>>Se espera identificador, constante o paréntesis de apertura\n";
            break;
        case 629:
            cadError=cadError+" <<Error 629>>Se espera operador relacional\n";
            break;
        case 630:
            cadError=cadError+" <<Error 630>>Se espera identificador, constante, paréntesis de apertura o '='\n";
            break;
        case 631:
            cadError=cadError+" <<Error 631>>Se espera if\n";
            break;
        case 632:
            cadError=cadError+" <<Error 632>>Se espera else o llave de cierre\n";
            break;
        case 633:
            cadError=cadError+" <<Error 633>>Se espera while\n";
            break;
        case 634:
            cadError=cadError+" <<Error 634>>Se espera do\n";
            break;
        case 635:
            cadError=cadError+" <<Error 635>>Se espera 'output'\n";
            break;
        default:
            break;
    }


}

string sintatico(){    
    string con="",c="",pi="";
    pila.push("$");
    pila.push("0");
    lista.push_back("$");
    list<string>::iterator iter=lista.begin();
    string li= *iter;
    int prod=0;
    while(lista.size()>0){
        cout<<pila.top()+" | "+li<<endl;
        if((li=="$")&&(pila.top()=="$")){
            con=con+"La sintaxis está correcta: \nPila de ejecución:\n";
            break;
        }else{
            if(pila.top()==li){
                pila.pop();
                lista.pop_front();
                iter=lista.begin();
                li=*iter;
            }else{
                int col=relacionaSint(li);
                prod=predictiva[stoi(pila.top())][col];
                if((pila.top()=="122")&&(li=="124")){
                    prod=6;
                }
                if(prod<600){
                    pila.pop();
                    agregarPila(prod);

                }else{
                    errorSint(prod);
                    break;
                }

            }

        }
        c = imprimir(pila);
        pi=pi+c+"\n";
        imprimirLista();
    }
    con=con+pi;
    return con;
}



void analizar(QString cadena){
    inicio=0;
    final=0;
    cadToken="";
    cadError="";

    std::string cad=cadena.toStdString();
    // Eliminar los saltos de línea
    cad.erase(std::remove(cad.begin(), cad.end(), '\n'), cad.end());
    // Eliminar las tabulaciones
    cad.erase(std::remove(cad.begin(), cad.end(), '\t'), cad.end());

    int longi=cad.length();
    for(int x=0; x<longi+1;x++){        
        car=cad[x];
        rel=relaciona(car);
        edo=matriz[edo][rel];
        final=x;
        if (edo>=100 && edo<=130){
            Token(edo,cad,inicio,final);
            inicio=final+1;
            edo=0;

        }else if (edo>=500 && edo<=507){
            PosError(edo,cad,inicio,final);
            inicio=final+1;
            edo=0;
        }

    }

}



Analizador::Analizador(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Analizador)
{
    ui->setupUi(this);
}

Analizador::~Analizador()
{
    delete ui;
}

void Analizador::on_btnAbrir_clicked()
{
    QFile arch;
    QTextStream io;
    QString nombre;
    nombre = QFileDialog::getOpenFileName(this, "Abrir");
    arch.setFileName(nombre);
    arch.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    ui->txtTexto->setPlainText(io.readAll());
    arch.close();
}


void Analizador::on_btnGuardar_clicked()
{
    QFile arch;
    QTextStream io;
    QString nombre;
    nombre = QFileDialog::getSaveFileName(this, "Guardar");
    arch.setFileName(nombre);
    arch.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    io << ui->txtTexto->toPlainText();
    arch.flush();
    arch.close();
}


void Analizador::on_btnLimpiar_clicked()
{
    ui->txtTexto->setPlainText("");
    ui->txtToken->setPlainText("");
    ui->txtErrores->setPlainText("");
    ui->txtSintaxis->setPlainText("");
    vaciar();

}


void Analizador::on_btnAnalizar_clicked()
{
    if(ui->txtTexto->toPlainText().isEmpty()){
        QMessageBox::critical(this,"Error","No hay texto que analizar");
        return;
    }else{
        vaciar();
        QString a=ui->txtTexto->toPlainText();
        cadSintaxis="";
        analizar(a);
        cadSintaxis=sintatico();
        ui->txtToken->setPlainText(QString::fromStdString(cadToken));
        ui->txtErrores->setPlainText(QString::fromStdString(cadError));
        ui->txtSintaxis->setPlainText(QString::fromStdString(cadSintaxis));
    }
}

