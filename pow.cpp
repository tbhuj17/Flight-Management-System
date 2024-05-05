#include<iostream>
using namespace std;

int calc_pow(int p, int k)
{
    if(k == 0) return 1;
    else if(k == 1) return p;
    if(k%2 == 0) return calc_pow(p, k/2)*calc_pow(p, k/2);
    return calc_pow(p, k/2)*calc_pow(p, k/2)* calc_pow(p, 1);
}
int main()
{
    cout<<calc_pow(4, 2);
}