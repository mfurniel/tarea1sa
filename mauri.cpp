#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>

#include <unistd.h>
#include <signal.h>

using namespace std;

int N, M, th, alpha;
vector<string> w;
vector<pair<int,string>> empates;
vector<char> genes = {'A', 'C', 'G', 'T'};
int f_i;
double tiempo = 0.0;

int fitness(vector<char> word){
    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++)
    {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++)
        {

            if (word[j] != w[i][j])
            {
                dif++;
            }
        }
        if (dif >= th)
        {
            p++;
        }
    }
    return p;
}

void sig_handler(int sig) {
    if (sig == SIGALRM) {
        printf("llega senal de fin hijo\n");
        exit(0);
    }
}

ifstream leerArchivo(const string &nombreArchivo, const string &threshold, vector<string> &w, const string &nivelDeDeterminismo)
{

    string directorio = "dataset/";
    directorio += nombreArchivo;
    // cout << directorio << endl;
    ifstream archivo(directorio);

    if(!archivo){
        cout << "Error al abir el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    string linea;

    while (getline(archivo, linea))
    {
        w.push_back(linea);
    }

    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    auto it = nombreArchivo.begin();
    int cont = 0; // contador de ' - '
    string s;
    while (*it != '.') // 5-4-001.txt
    {
        if (*it != '-')
        {
            s.push_back(*it);
        }
        else if (cont == 0)
        {
            N = stoi(s);
            string new_m;
            s = move(new_m);
            cont++;
        }
        else
        {
            M = stoi(s);
        }
        it++;
    }

    th = stof(threshold) * M;
    alpha = stof(nivelDeDeterminismo) * 100;

    return archivo;
}

vector<char> pGreedy(const string &nombreArchivo, const string &threshold, const string &nivelDeDeterminismo)
{
    vector<pair<int,string>> newEmpates;
    empates=move(newEmpates);
    // vector<string> w;
    leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    tiempo= 0.0;    //resetear tiempo

    start = (double)clock();

    int iteracion = 0;

    do
    {
        if (rand() % 100 <= alpha)
        {

            vector<pair<int, char>> alfap;
            alfap.push_back(pair<int, char>(0, 'A'));
            alfap.push_back(pair<int, char>(0, 'G'));
            alfap.push_back(pair<int, char>(0, 'C'));
            alfap.push_back(pair<int, char>(0, 'T'));
            alfap[0].first = 0;
            alfap[1].first = 0;
            alfap[2].first = 0;
            alfap[3].first = 0;

            //    cout<<"b"<<endl;
            for (int i = 0; i < N; i++)
            {
                // cout << i << " " << N << endl;
                if (w[i][iteracion] == 'A')
                {
                    alfap[0].first++;
                }
                if (w[i][iteracion] == 'G')
                {
                    alfap[1].first++;
                }
                if (w[i][iteracion] == 'C')
                {
                    alfap[2].first++;
                }
                if (w[i][iteracion] == 'T')
                {
                    alfap[3].first++;
                }
            }

            // cout<<"a"<<endl;
            sort(alfap.begin(), alfap.end());

            // for(size_t i = 1; i < alfap.size(); i++){

            //     if(alfap[i-1].first == alfap[i].first){
            //         wordfinal.push_back(alfap[rand()%i].second);
            //     }
            // }

            // wordfinal.push_back(alfap[0].second);

            if (alfap[0].first == alfap[3].first)
            {
                // cout<<"empate3 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 4].second);
                pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <4; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                         aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else if (alfap[0].first == alfap[2].first)
            {
                // cout<<"empate2 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 3].second);
                 pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <3; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                         aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else if (alfap[0].first == alfap[1].first)
            {
                // cout<<"empate1 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 2].second);
                pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <2; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                         aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else
            {

                wordfinal.push_back(alfap[0].second);
            }

            iteracion++;
        }
        else
        {
            wordfinal.push_back(genes[rand() % 4]);
        }

    } while (iteracion < M);

    // muestra string generado

    // for (int i = 0; i < M; i++)
    // {
    //     cout << wordfinal[i];
    // }
    // cout << endl;

    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++)
    {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++)
        {

            if (wordfinal[j] != w[i][j])
            {
                dif++;
            }
        }
        if (dif >= th)
        {
            p++;
        }
    }
    f_i=p;
    // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;

    cout << p << '\t' << tiempo << endl;
    // cout << p << endl;
    return wordfinal;
}


 void localSearch2(vector<char>& wordfinal){ 
    // cout<<"test1"<<endl;
    //calcula fitness final
    int fitnessWordfinal= 0;
    fitnessWordfinal=fitness(wordfinal);
    
    // cout<<"test2"<<endl;
    int largo= empates.size();  
    //en cuantas columnas hubo empate
    for(int i=0; i<largo; i++)  {
        int columna= empates[i].first; 
        // cout<<empates[i].first<<endl; |
        // cout<<"test3: largo"<<largo<<endl;
        // cout<<"test3.5: columna"<<columna<<endl;
        vector<char> vecino=wordfinal;         
    // for (int i = 0; i < wordfinal.size(); i++) {    
    //     cout<<vecino[i];    
    // }      
    // cout<<endl;
    for(int k=0; k<empates[i].second.size();k++){   
        //empates.first es la columna y second son los caracteres
         
         
        vecino[columna]=empates[i].second[k]; 
        vecino[empates[rand()%empates.size()].first]=empates[rand()%empates.size()].second[rand()%4];
        // vecino[empates.size()-k]=empates[rand()%empates.size()].second[k]; 

        // vecino[empates[rand()%empates.size()].first]=empates[rand()%empates.size()].second[rand()%4]; 
        // vecino[rand()%M]=genes[rand()%4];

       
        // cout<<"test4"<<endl;
        // cout<<empates[i].second[k]<<endl;
        // vecino[columna]=empates[i].second[k];
        int fitnessVecino=0;         
        // cout<<"test5"<<endl;   
//calcular fitness de wordfinal y vecino y comparar
        fitnessVecino=fitness(vecino);
             if(fitnessVecino>=fitnessWordfinal){

                 wordfinal= vecino;

                 fitnessWordfinal= fitnessVecino;

             }

         }

     }

     
//  cout<<"A"<<endl;

     
    // for (int i = 0; i < wordfinal.size(); i++) {
    //     cout<<wordfinal[i];  
    // }   
    // cout<<endl;
    cout<<fitnessWordfinal<<endl;


    //  asd=fitnessWordfinal;

}



bool localSearch(vector<char>& wordfinal){
    int mejorFitness = fitness(wordfinal);



    //  for (int i = 0; i < M; i++) {
    vector<char> aux = wordfinal;
    vector<char> aux2 = wordfinal;
    
        //   for(int j = 0; j < 4; j++){
            // aux[i]=genes[j];
            //aux[azar]=genes[azar]
            //aux[azar]=genes[azar]
            aux[rand()%M]=genes[rand()%4];  //cambia tres caracteres por otros tres elegidos al azar
            aux[rand()%M]=genes[rand()%4];
            aux[rand()%M]=genes[rand()%4];

            int fitnessAuxiliar = fitness(aux);

            if (fitnessAuxiliar==mejorFitness)
            {
                wordfinal= aux;
            }

            if (fitnessAuxiliar>mejorFitness)
            {
                if(fitnessAuxiliar!=mejorFitness){
                    cout << fitnessAuxiliar << "\t";

                }
                wordfinal= aux;
                mejorFitness= fitnessAuxiliar;
                //imprimir el mejor fitness encontrado y el tiempo que se demoro en calcularlo
                return true;
    //         }

    //    }
     }
    return false;

}

int main(int argc, const char *argv[])
{
    // ./grasp -i nombreArchivo -t tiempoMaxSec -th threashold -p nivelDeDeterminismo
    signal(SIGCHLD, sig_handler);


    srand(time(NULL));
    vector<char> wordfinal;
    if (argc == 9)  //se puede mejorar
    {
        // cout << "tiempo: " << argv[4] << endl;
        int porfavor_detente= stoi(argv[4]);
        alarm(porfavor_detente);
        //nombreArchivo, threshold, nivelDeDeterminismo
        // cout << "nombreArchivo: " << argv[2] << " threshold: " << argv[6] << " nivelDeDeterminismo: " << argv[8] << endl;
        wordfinal = pGreedy(argv[2], argv[6], argv[8]);

    }else{
        cout << "error en el formato" << endl;

        int porfavor_detente= 90;
        alarm(porfavor_detente);
        wordfinal = pGreedy("100-800-001.txt", "0.85", "1");
    }

        // for (int i = 0; i < empates.size(); i++)
        // {
        //     cout<<empates[i].first<<" "<<empates[i].second<<endl;
        // }

        //  for (int i = 0; i < wordfinal.size(); i++)
        // {
        //     cout<<wordfinal[i];
        // }
        // cout<<endl;


        while (true)
        {
            localSearch2(wordfinal);
        }
        


    // while(true){
    //     clock_t start= clock();
    //     if(localSearch(wordfinal)){
    //         // tiempo = tiempo ;
    //         cout << tiempo / (double)CLOCKS_PER_SEC << endl;
    //         // tiempo= 0.0;
    //     }
    //     else{
    //         tiempo += ((double)clock() - start);
    //     }
    // }



}
