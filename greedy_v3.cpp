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

int N, M, th;

ifstream leerArchivo(const string &nombreArchivo, const string &threshold, vector<string> &w)
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

    return archivo;
}

void ffmsp(const string &nombreArchivo, const string &threshold)
{
    vector<string> w;
    leerArchivo(nombreArchivo, threshold, w);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    double tiempo = 0.0;

    start = (double)clock();

    int iteracion = 0;

    do
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
    if (argc == 5)
    {
        ffmsp(argv[2], argv[4]);
    }

}
