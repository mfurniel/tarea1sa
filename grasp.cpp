#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "fun.h"

using namespace std;
vector<vector<char>> mortalkombat(vector<vector<char>> winersactual);

vector<char> pGreedy(const string &nombreArchivo, const string &threshold,
                     const string &nivelDeDeterminismo) {
    // cout << nombreArchivo << "\t" << threshold << "\t" << nivelDeDeterminismo
        //  << endl;
    vector<pair<int, string>> newEmpates;
    empates = move(newEmpates);
    // vector<string> w;
    leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    tiempo = 0.0;  // resetear tiempo

    start = (double)clock();

    int iteracion = 0;

    do {
        if (rand() % 100 <= alpha) {
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
            for (int i = 0; i < N; i++) {
                // cout << i << " " << N << endl;
                if (w[i][iteracion] == 'A') {
                    alfap[0].first++;
                }
                if (w[i][iteracion] == 'G') {
                    alfap[1].first++;
                }
                if (w[i][iteracion] == 'C') {
                    alfap[2].first++;
                }
                if (w[i][iteracion] == 'T') {
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

            if (alfap[0].first == alfap[3].first) {
                // cout<<"empate3 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 4].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 4; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[2].first) {
                // cout<<"empate2 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 3].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 3; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[1].first) {
                // cout<<"empate1 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 2].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 2; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else {
                wordfinal.push_back(alfap[0].second);
            }

            iteracion++;
        } else {
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

    for (int i = 0; i < N; i++) {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++) {
            if (wordfinal[j] != w[i][j]) {
                dif++;
            }
        }
        if (dif >= th) {
            p++;
        }
    }
    f_i = p;
    // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;

    cout << p << '\t' << tiempo << endl;
    // cout << p << endl;
    return wordfinal;
}

bool localSearch2(vector<char> &wordfinal) {
    // cout<<"test1"<<endl;
    // calcula fitness final
    int fitnessWordfinal = 0;
    fitnessWordfinal = fitness(wordfinal);

    // cout<<"test2"<<endl;
    int largo = empates.size();
    // en cuantas columnas hubo empate
    for (int i = 0; i < largo; i++) {
        int columna = empates[i].first;
        // cout<<empates[i].first<<endl; |
        // cout<<"test3: largo"<<largo<<endl;
        // cout<<"test3.5: columna"<<columna<<endl;
        vector<char> vecino = wordfinal;
        // for (int i = 0; i < wordfinal.size(); i++) {
        //     cout<<vecino[i];
        // }
        // cout<<endl;
        for (int k = 0; k < empates[i].second.size(); k++) {
            // empates.first es la columna y second son los caracteres

            vecino[columna] = empates[i].second[k];
            vecino[empates[rand() % empates.size()].first] =
                empates[rand() % empates.size()].second[rand() % 4];
            // vecino[empates.size()-k]=empates[rand()%empates.size()].second[k];

            // vecino[empates[rand()%empates.size()].first]=empates[rand()%empates.size()].second[rand()%4];
            // vecino[rand()%M]=genes[rand()%4];

            // cout<<"test4"<<endl;
            // cout<<empates[i].second[k]<<endl;
            // vecino[columna]=empates[i].second[k];
            int fitnessVecino = 0;
            // cout<<"test5"<<endl;
            // calcular fitness de wordfinal y vecino y comparar
            fitnessVecino = fitness(vecino);
            if (fitnessVecino >= fitnessWordfinal) {
                wordfinal = vecino;
                if (fitnessVecino > fitnessWordfinal) {
                    cout << fitnessWordfinal << "\t";
                    return true;
                }
                fitnessWordfinal = fitnessVecino;
                // cout << "uh?" << endl;
            }
        }
    }

    return false;
}

void mutacion(vector<char> &mijo, const float mutation_rate){
    for(int i=0; i<M; i++){
        if (rand()%101 <= mutation_rate){
            //mutar
            char antiguo = mijo[i];
            while (antiguo== mijo[i]){
                mijo[i]= genes[rand()%4];
            }   
        }
    }
}





int main(int argc, const char *argv[]) {
    map<string, string> param;
    param["-i"] = "100-300-001.txt";
    param["-t"] = "90";
    param["-th"] = "0.80";
    param["-det"] = "1";

    for (int i = 1; i < argc - 1; i += 2) {
        param[argv[i]] = argv[i + 1];
    }

    signal(SIGCHLD, sig_handler);

    srand(time(NULL));
    vector<char> wordfinal;
    alarm(stoi(param["-t"]));
    wordfinal = pGreedy(param["-i"], param["-th"], param["-det"]);

    // while (true) {
    //     localSearch2(wordfinal);
    // }

    // while (true) {
    //     clock_t start = clock();
    //     if (localSearch2(wordfinal)) {
    //         // tiempo = tiempo ;
    //         cout << tiempo / (double)CLOCKS_PER_SEC << endl;
    //         // tiempo= 0.0;
    //     } else {
    //         tiempo += ((double)clock() - start);
    //     }
    // }


      for (int i = 0; i < 32; i++)
        {
            // wordfinal = pGreedy("100-600-001.txt", "0.75", "0.5");
            wordfinal = pGreedy(param["-i"], param["-th"], param["-det"]);
            lapobla.push_back(wordfinal);
            // cout<<"i: "<<i<<"   ";
            // for (int i = 0; i < 10; i++)
            // {
            //       cout<<wordfinal[i];
            // }
            // cout<<"     "<<fitness(wordfinal)<<endl;
          
        }

    
       padres=mortalkombat(lapobla);
       padres.push_back(lapobla[random()%32]);




        cout<<"-------1--------"<<endl;
        // for (int i = 0; i < 3; i++)
        // {
        //     padres.push_back(lapobla[i]);
        // }
        // cout<<"-------2--------"<<endl;
        // cout<<fitness(lapobla[1])<<endl;
        //  cout<<fitness(padres[2])<<endl;

        // for (int i = 0; i < 20; i++)
        // {
        //     // cout<<"-------3--------"<<i<<endl;
        //      if (fitness(lapobla[i])<fitness(padres[2]))
        //     {
        //         padres[2]=lapobla[i];
        //     }

        //     if (fitness(lapobla[i])>fitness(padres[0]))
        //     {
        //         padres[0]=lapobla[i];
        //         continue;
        //     }

        //     if (fitness(lapobla[i])>fitness(padres[1]))
        //     {
        //         padres[1]=lapobla[i];
        //         continue;
        //     }
            
        // }

        cout<<"---------------"<<endl;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                  cout<<padres[i][j];
             }
             cout<<"     fit: "<<fitness(padres[i])<<endl;
        }
        
        vector<vector<char>> hijos;





}

 vector<vector<char>> mortalkombat(vector<vector<char>> winersactual){
    vector<vector<char>> winersfuturo; 
    if (winersactual.size()==2) {
        return winersactual;
    }  
    for (int i = 0; i < winersactual.size(); i=i+2)  {          
            if (fitness(winersactual[i])>fitness(winersactual[i+1]))  {
               
                winersfuturo.push_back(winersactual[i]);
            }else{
              
                winersfuturo.push_back(winersactual[i+1]);
            } 
        }
        winersactual=winersfuturo;
        return mortalkombat(winersactual);

}
