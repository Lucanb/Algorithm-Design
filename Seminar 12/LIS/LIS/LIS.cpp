// LIS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>

int CautareBinara(std::vector<int> v,int dr,int st,int val)
{
    while (dr - st > 1)
    {
        int m = (dr + st) / 2;
            if (v[m] >= val)
                dr = v[m];
            else
                st = v[m];
    }
    return dr;
}

int LIS(std::vector<int> v)
{
    if (v.size() == 0)
        return 0;

        int length = v.size();
        std::vector<int> tail(length, 0);

        length = 1;

        tail[0] = v[0]; //Caz de Baza

        for (auto i : v)
        {
            if (v[i] < tail[0]) //Cazul 1 (il aleg pe cel mai mic);
                tail[0] = v[i];
            else
                if (v[i] > tail[length - 1])//Cazul 2 : v[i] este cel mai mare  ~ il adaug in vector
                    tail[length++] = v[i];
                else  //Cazul 3 : cautam o lista cu cel mai mare element <=v[i] si il pun pe v[i] in ea (in rest uit)
                    tail[CautareBinara(tail, -1, length - 1, v[i])] = v[i];
        }
        return length;
}

int main()
{
    std::vector<int> v{ 2, 5, 3, 7, 11, 8, 10, 13, 6 };
    std::cout << LIS(v) << '\n';
    return 0;
}

