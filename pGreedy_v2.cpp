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

using namespace std;

int N, M, th, alpha;

ifstream leerArchivo(const string &nombreArchivo, const string &threshold, vector<string> &w, const string &nivelDeDeterminismo)
{

    string directorio = "dataset/";
    directorio += nombreArchivo;
    // cout << directorio << endl;
    ifstream archivo(directorio);

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

void ffmsp(const string &nombreArchivo, const string &threshold, const string &nivelDeDeterminismo)
{
    vector<string> w;
    leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    double tiempo = 0.0;

    start = (double)clock();

    int iteracion = 0;
    vector<char> genes = {'A', 'C', 'G', 'T'};

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
                wordfinal.push_back(alfap[rand() % 4].second);
            }
            else if (alfap[0].first == alfap[2].first)
            {
                wordfinal.push_back(alfap[rand() % 3].second);
            }
            else if (alfap[0].first == alfap[1].first)
            {
                wordfinal.push_back(alfap[rand() % 2].second);
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

    // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;

    cout << p << '\t' << tiempo << endl;
    // cout << p << endl;
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));

    string stringAux = "100-300-00";
    vector<string> threshold{"0.75", "0.80", "0.85"};
    for (auto it = threshold.begin(); it != threshold.end(); it++)
    {
        cout << "---" << *it << "---" << endl;
        for (int k = 1; k < 10; k++)
        {
            cout << k << "\t";
            string nombreArchivo = stringAux + to_string(k);
            nombreArchivo += ".txt";
            ffmsp(nombreArchivo, *it, "0.90");
        }
        cout << 10 << "\t";
        ffmsp("100-300-010.txt", *it, "0.90");
        cout << endl;
    }

    // ifstream archivo;

    // if (argc == 5)
    // {
    //     archivo = leerArchivo(argv[2], argv[4]);
    // }
    // else
    // {
    //     archivo = leerArchivo("100-600-010.txt", "0.75");
    // }

    // cout << "termine de leer" << endl;
}
