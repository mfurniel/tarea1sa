#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, const char* argv[]){

    
   

    // string words[100];
    
    
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

    int N=100;
    int M=300;


    map <char,int> alfap;
    alfap.insert (pair<char,int>('A',0) );
    alfap.insert (pair<char,int>('G',0) );
    alfap.insert (pair<char,int>('C',0) );
    alfap.insert (pair<char,int>('T',0) );

    // for (int i = 0; i < 4; i++)
    // {
    //     cout<<alfap['A']<<endl;
    // }
    

    char alfabeto[4];
    alfabeto[0] = 'A';
    alfabeto[1] = 'G';
    alfabeto[2] = 'C';
    alfabeto[3] = 'T';
   
    char wordfinal[M];
   
    int iteracion=0;

    do
    {
        alfap['A'] = 0;
        alfap['G'] = 0;
        alfap['C'] = 0;
        alfap['T'] = 0;

        // int peso[4];
        // peso[0] = 0;
        // peso[1] = 0;
        // peso[2] = 0;
        // peso[3] = 0;

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
    
        

        // wordfinal[iteracion]=
        
        
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

    } while (iteracion <= N);
    
    


    
}

