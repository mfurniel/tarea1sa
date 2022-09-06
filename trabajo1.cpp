#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

int main(int argc, const char* argv[]){

    string nombreArchivo = "prueba.txt";
    ifstream archivo(nombreArchivo);
    string linea;

    int aux =0;    
    vector <string> w;
    while (getline(archivo, linea)){
        w.push_back(linea); 
    };
    for (auto it=w.begin(); it!= w.end(); it++){
        cout << *it << endl;
    };

    int N=3;
    int M=4;

    // for (int i = 0; i < 4; i++)
    // {
    //     cout<<alfap['A']<<endl;
    // }
      
    char wordfinal[M];
   
    int iteracion=0;

    do
    {
        
        vector<pair<int,char>> alfap;
        alfap.push_back(pair<int,char>(0,'A'));
        alfap.push_back(pair<int,char>(0,'G'));
        alfap.push_back(pair<int,char>(0,'C'));
        alfap.push_back(pair<int,char>(0,'T'));
        alfap[0].first = 0;
        alfap[1].first = 0;
        alfap[2].first = 0;
        alfap[3].first = 0;

       
        for (int i = 0; i < N; i++)
        {
            if (w[i][iteracion]=='A')
            {
                alfap[0].first++;
            }
            if (w[i][iteracion]=='G')
            {
                alfap[1].first++;
            }
             if (w[i][iteracion]=='C')
            {
                alfap[2].first++;
            }
             if (w[i][iteracion]=='T')
            {
                alfap[3].first++;
            }
        }
    
        sort(alfap.begin(), alfap.end());

        wordfinal[iteracion]=alfap[0].second;
        
        
        // if (peso0==peso1)
        // {
        //     wordfinal[iteracion]=alfabeto[0];
        // }else if (peso0<peso1)
        // {
        //      wordfinal[iteracion]=alfabeto[0];
        // } else{
        //      wordfinal[iteracion]=alfabeto[1];
        // }

        iteracion++;

    } while (iteracion < M);
    
    cout<<wordfinal<<endl;
    
}

