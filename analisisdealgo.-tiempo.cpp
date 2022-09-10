#include <iostream>
#include <map>
#include <string>
#include <time.h>
// #include <climits>
#include <math.h>
// #include <utility>
#include <vector>
#include <map>
#include <fstream>

using namespace ::std;
typedef long long ll;
ll contglobal = 0;

long long compute_hash(string key); // entrega un identificador numerico a cada string
void readFile(bool flag, int n);    // lee el archivo de entrada y se guarda la informacion en dict
ll espacio();

ll p = 2431655867, k = 15, a, b, cont1 = 0; // p= primo, cont1= numero de veces que se calculan a y b del primer nivel
vector<int> cont2(10);                      // ??? 0 0 0 0 0 0 0 0 0                      // numero de veces que se calculan a y b en el segundo nivel
map<string, ll> dict;                       // diccionario que guarda todo kmero como clave y su identificador numerico
string s;

void generarString();

struct bucket
{
    int a, b;
    std::vector<std::string> lvl2; // vector que guarda los strings del bucket
    std::vector<ll> key;
};

void hashing1(); // realiza el hashing de primer nivel, utilizando todos los kmeros de dict
void hashing2(); // realiza el hashing de segundo nivel, utilizando toos los kmeros de cada bucket
bool buscar(string kmero);

std::vector<bucket> lvl1; // vector que guarda todos los buckets

int main()
{
    srand(time(NULL));
    int rep = 3;
    clock_t start;
    ll nElementos = 1000000, moarElementos = nElementos;

    for (int i = 0; i < 7; i++) // numero de puntos
    {
        double time_generar = 0.0;
        double time_buscar = 0.0;
        ll memory = 0;
        cont1 = 0;
        vector<int> new_cont2(10);
        cont2 = move(new_cont2);

        for (int k = 0; k < rep; k++) // numero de repeticiones
        {
            // generamos la tabla
            start = (double)clock();
            readFile(false, nElementos);
            hashing1();
            hashing2();
            time_generar += ((double)clock() - start);

            // calculamos el espacio ocupado por la tabla
            memory += espacio();

            // generamos y buscamos elementos
            start = (double)clock();
            for (int j = 0; j < nElementos; j++)
            {
                generarString();
                buscar(s);
                // cout << s << endl;
                // if (buscar(s))
                // {
                //     cout << "encontre " << s << endl;
                // }
                // else
                // {
                //     cout << "no encontre " << s << endl;
                // }
            }
            time_buscar += ((double)clock() - start);
        }

        time_generar = time_generar / (double)rep / (double)CLOCKS_PER_SEC;
        time_buscar = time_buscar / (double)rep / (double)CLOCKS_PER_SEC;
        cont1 /= rep;
        memory /= rep;

        std::cout << i << "\t" << nElementos << "\t" << time_generar << "\t" << time_buscar << "\t" << cont1 << "\t" << memory << endl;
        for (k = 0; k < 10; k++)
        {
            cont2[k] /= rep;
            cout << cont2[k] << "\t";
        }
        cout << endl;
        cout << endl;

        nElementos += moarElementos;
    }
}

void readFile(bool flag, int n)
{
    ifstream input("genes");
    string s;
    char c;

    if (input.is_open())
    {
        while (s.length() < k)
        {
            input.get(c); // cin >> c;
            if (c == 'T' || c == 'A' || c == 'G' || c == 'C')
            {
                s.push_back(c);
            }
        }
        map<string, ll> new_dict;
        dict = move(new_dict);
        dict[s] = compute_hash(s);
        while (input.get(c) && dict.size() < n) // cin >> c
        {
            if (c == 'T' || c == 'A' || c == 'G' || c == 'C')
            {
                string aux(s.begin() + 1, s.end());
                s = aux;
                s.push_back(c);
                dict[s] = compute_hash(s);
            }
        }
    }
    else
    {
        cout << "No pude abrir el archivo" << endl;
    }

    if (flag) // debug
    {
        for (auto &it : dict)
        {
            if (it.second < 0)
            {
                std::cout << it.first << ": " << it.second << endl;
            }
        }
        std::cout << endl;
        std::cout << "terminé de leer" << endl;
    }
}

void hashing1()
{
    int n = dict.size();
    ll vibeCheck;
    // cont1 = 0;
    do
    {
        cont1++;
        // reset
        // cout << "reset1" << endl;
        vibeCheck = 0;
        a = rand() % p;
        do
        {
            b = rand() % p;
        } while (a == b);

        vector<bucket> new_lvl1 = vector<bucket>(dict.size()); // guardamos espacio para los todos los buckets
        lvl1 = move(new_lvl1);
        lvl1.resize(dict.size());

        ll nivel;
        for (auto &it : dict)
        {
            nivel = ((a * it.second + b) % p) % dict.size();
            // cout << "asignamos el string: " << it.first << " al nivel: " << nivel << endl;
            lvl1[nivel].lvl2.push_back(it.first);
            lvl1[nivel].key.push_back(it.second);
        }
        for (int i = 0; i < n; i++)
        {
            vibeCheck += pow(lvl1[i].lvl2.size(), 2);
        }
        // cout << "vibe: " << vibeCheck << endl;
    } while (vibeCheck >= 4 * n);
}

void hashing2()
{
    // vector<int> new_cont2(10);
    // cont2 = move(new_cont2);
    for (int i = 0; i < lvl1.size(); i++)
    {
        if (lvl1[i].lvl2.size() != 0) // si el bucket lvl1[i] no tiene elementos, se omite
        {
            bool vibeCheck = false;

            ll cont2Aux = 0; // contador que permite saber cuantas veces se calculan a y b para cada bucket
            do
            {
                // cout << "Realizando hashing2 al bucket " << i << endl;
                // reset
                // cout << "reset2" << endl;
                lvl1[i].a = rand() % p;
                do
                {
                    lvl1[i].b = rand() % p;
                } while (lvl1[i].a == lvl1[i].b);

                ll nivel;
                vector<string> new_lvl2 = vector<string>(pow(lvl1[i].lvl2.size(), 2));

                int j;
                for (j = 0; j < lvl1[i].lvl2.size(); j++)
                {
                    nivel = ((lvl1[i].a * lvl1[i].key[j] + lvl1[i].b) % p) % new_lvl2.size();
                    if (new_lvl2[nivel] == "")
                    {
                        new_lvl2[nivel] = lvl1[i].lvl2[j];
                    }
                    else
                    {
                        // colision
                        // cout << new_lvl2[nivel] << " = " << lvl1[i].lvl2[j] << " con nivel: " << nivel << endl;
                        // cout << "moir xd" << endl;
                        contglobal++;
                        cont2Aux++;
                        break;
                    }
                }

                if (j == lvl1[i].lvl2.size())
                {
                    lvl1[i].lvl2 = move(new_lvl2);
                    vibeCheck = true;
                    // cout << i << " ";
                    if (cont2Aux > 9)
                    {
                        cont2Aux = 9;
                    }
                    cont2[cont2Aux]++; // 1 0 0 0 0 0 0 0 0 0
                }
                // cout << endl;

            } while (!vibeCheck);
        }
    }
}

long long compute_hash(string key)
{
    long long keyint = 0;
    for (int i = 0; i < k; i++)
    {
        if (key[i] == 'T')
        {
            keyint += 1 * pow(4, i);
        }
        if (key[i] == 'A')
        {
            keyint += 2 * pow(4, i);
        }
        if (key[i] == 'G')
        {
            keyint += 3 * pow(4, i);
        }
        if (key[i] == 'C')
        {
            keyint += 4 * pow(4, i);
        }
    }
    // cout<<"key: "<<keyint<<endl;
    return keyint;
}

bool buscar(string kmero)
{
    ll h = compute_hash(kmero);
    ll nivel1 = ((a * h + b) % p) % dict.size();
    if (lvl1[nivel1].lvl2.size() != 0)
    {
        ll nivel2 = ((lvl1[nivel1].a * h + lvl1[nivel1].b) % p) % lvl1[nivel1].lvl2.size();
        if (lvl1[nivel1].lvl2[nivel2] == kmero)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void generarString()
{
    string new_s;
    char c;
    for (int j = 0; j < k; j++)
    {
        c = rand() % 4 + 1;
        if (c == 1)
        {
            c = 'T';
        }
        if (c == 2)
        {
            c = 'A';
        }
        if (c == 3)
        {
            c = 'G';
        }
        if (c == 4)
        {
            c = 'C';
        }
        new_s.push_back(c);
    }
    s = move(new_s);
}

ll espacio()
{
    ll memory = sizeof(lvl1);
    memory = memory * lvl1.size();
    ll mem_a = 0;
    ll mem_b = 0;
    ll mem_lvl2 = 0;
    for (int i = 0; i < lvl1.size(); i++)
    {
        mem_a = mem_a + sizeof(ll);
        mem_b = mem_b + sizeof(ll);
        for (int j = 0; j < lvl1[i].lvl2.size(); j++)
        {
            mem_lvl2 = mem_lvl2 + sizeof(string);
        }
    }
    memory = memory + mem_a + mem_b + mem_lvl2;
    return memory;
}