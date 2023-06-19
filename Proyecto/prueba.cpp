#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

ifstream doc;
string cad,le;

void analizar(){
    ifstream doc("Analisis.txt");
    while(getline(doc,le)){
        cad=cad+le+"\n";              
    }
    cout<<cad<<endl;
    doc.close();
}

int main(){
    analizar();
    return 0;
}