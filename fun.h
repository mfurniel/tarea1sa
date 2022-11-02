#ifndef FUN_H
#define FUN_H

using namespace std;

int N, M, th, alpha;
vector<string> w;
vector<pair<int, string>> empates;
vector<char> genes = {'A', 'C', 'G', 'T'};
int f_i;
double tiempo = 0.0;
vector<vector<char>> lapobla;
 vector<vector<char>> padres;

void sig_handler(int sig) {
    if (sig == SIGALRM) {
        printf("llega senal de fin hijo\n");
        exit(0);
    }
}

ifstream leerArchivo(const string &nombreArchivo, const string &threshold,
                     vector<string> &w, const string &nivelDeDeterminismo) {
    string directorio = "dataset/";
    directorio += nombreArchivo;
    // cout << directorio << endl;
    ifstream archivo(directorio);

    if (!archivo) {
        cout << "Error al abir el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    string linea;

    while (getline(archivo, linea)) {
        w.push_back(linea);
    }

    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    auto it = nombreArchivo.begin();
    int cont = 0;  // contador de ' - '
    string s;
    while (*it != '.')  // 5-4-001.txt
    {
        if (*it != '-') {
            s.push_back(*it);
        } else if (cont == 0) {
            N = stoi(s);
            string new_m;
            s = move(new_m);
            cont++;
        } else {
            M = stoi(s);
        }
        it++;
    }

    th = stof(threshold) * M;
    alpha = stof(nivelDeDeterminismo) * 100;

    return archivo;
}

int fitness(vector<char> word) {
    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++) {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++) {
            if (word[j] != w[i][j]) {
                dif++;
            }
        }
        if (dif >= th) {
            p++;
        }
    }
    return p;
}

#endif
