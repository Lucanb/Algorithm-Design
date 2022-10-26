#include<iostream>
 using namespace std;

 int p[101];
 void PrecalculKMP(string patt)
 {
     int len = patt.size();
     p[0] = 0;

     for (int i = 1; i < len; i++)
     {
         int j = p[i - 1];
         
         while (j != 0 && patt[i] != patt[j])
             j = p[j-1];

         if (patt[i] == patt[j])
             j++;

         p[i] = j;
     }
 }
 void KMP(string patt, string txt)
 {
     int sw = 0;
     int Pattlen = patt.size();
     int txtlen = txt.size();

     if (Pattlen > txtlen)
     {
         cout << -1;
         return;
     }

     int j = 0;
     for (int i = 0; i < txtlen-Pattlen; i++)
     {
         while (j != 0 && txt[i] != patt[j])
             j = p[j-1];

         if (patt[j] == txt[i])
             j++;

         if (j == Pattlen)
         {
             sw = 1;
             cout << "Apare la pozitia :" << i - Pattlen + 1 << '\n';
         }
     }
     if (sw == 0)
         cout << -1;
 }

 int main() {
  
     string patt="aba";
     string txt="maeraba";
     PrecalculKMP(patt);
     KMP(patt, txt);
 }
