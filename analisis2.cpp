#include <iostream>
#include <map>
#include <string>
#include <time.h>
// #include <climits>
#include <math.h>
// #include <utility>
#include <vector>
#include <map>

using namespace ::std;
typedef long long ll;

long long compute_hash(string key); // entrega un identificador numerico a cada string
void readFile(bool flag, int n);    // lee el archivo de entrada y se guarda la informacion en dict

ll p = 2431655867, k = 15, a, b, cont1 = 0; // p= primo, cont1= numero de veces que se calculan a y b del primer nivel
vector<int> cont2(10);                      // numero de veces que se calculan a y b en el segundo nivel
map<string, ll> dict;                       // diccionario que guarda todo kmero como clave y su identificador numerico
string s;

string generarString();

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
    ll nElementos = 10000, moarElementos = nElementos;
    for (int i = 0; i < 15; i++)
    {
        readFile(false, nElementos);

        // generanmos la tabla
        hashing1();
        hashing2();

        // buscar
        s = generarString();
        // cout << s << endl;

        buscar(s);

        for (int j = 0; j < nElementos; j++)
        {
            s = generarString();
            // cout << s << endl;
            if (buscar(s))
            {
                cout << "encontre " << s << endl;
            }
            else
            {
                // cout << "no encontre " << s << endl;
            }
        }
        nElementos += moarElementos;
    }

    //     if (buscar("TCGTTTGGAGTTGCC"))
    // {
    //     cout << "lo encontre c:" << endl;
    // }
    // else
    // {
    //     cout << "no lo encontre :c" << endl;
    // }
}

void readFile(bool flag, int n)
{
    string s;
    char c;
    while (s.length() < k)
    {
        cin >> c;
        if (c == 'T' || c == 'A' || c == 'G' || c == 'C')
        {
            s.push_back(c);
        }
    }
    dict[s] = compute_hash(s);
    while (cin >> c && dict.size() < n)
    {
        if (c == 'T' || c == 'A' || c == 'G' || c == 'C')
        {
            string aux(s.begin() + 1, s.end());
            s = aux;
            s.push_back(c);
            dict[s] = compute_hash(s);
        }
    }

    if (flag) // debug
    {
        for (auto &it : dict)
        {
            if (it.second < 0)
            {
                cout << it.first << ": " << it.second << endl;
            }
        }
        cout << endl;
        cout << "terminé de leer" << endl;
    }
}

void hashing1()
{
    int n = dict.size();
    ll vibeCheck;
    do
    {
        // reset
        cont1++;
        vibeCheck = 0;
        a = rand() % p;
        do
        {
            b = rand() % p;
        } while (a == b);

        vector<bucket> new_lvl1 = vector<bucket>(dict.size()); // guardamos espacio para los todos los buckets
        lvl1 = move(new_lvl1);

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
                        cont2Aux++;
                        break;
                    }
                }

                if (j == lvl1[i].lvl2.size())
                {
                    lvl1[i].lvl2 = move(new_lvl2);
                    vibeCheck = true;
                    if (cont2Aux > 9)
                    {
                        cont2Aux = 9;
                    }
                    cont2[cont2Aux]++;
                }

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

string generarString()
{
    string s;
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
        s.push_back(c);
    }
    return s;
}