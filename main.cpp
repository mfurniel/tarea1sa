#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <vector>

int main(){


    std::string w[3];

    w[0] = "0101";
    w[1] = "0111";
    w[2] = "0011";

    char alfabeto[2];
    alfabeto[0] = '0';
    alfabeto[1] = '1';

    int t = 3; // 0 <= t <= m (m=4)
    int m = 4;
    int n = 3;

    int ps; // valor funcion objetivo

    char wordfinal[m];
   
    int iteracion=0;

    do
    {

        int peso0 = 0;
        int peso1 = 0;

        for (int i = 0; i < n; i++)
        {
            if (w[i][iteracion]==alfabeto[0])
            {
                peso0++;
            }
            if (w[i][iteracion]==alfabeto[1])
            {
                peso1++;
            }
        }
    
        if (peso0==peso1)
        {
            wordfinal[iteracion]=alfabeto[0];
        }else if (peso0<peso1)
        {
             wordfinal[iteracion]=alfabeto[0];
        } else{
             wordfinal[iteracion]=alfabeto[1];
        }

        iteracion++;

    } while (iteracion <= n);
    
   
    std::cout<<wordfinal<<std::endl;




    return 0;
}