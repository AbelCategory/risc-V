#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int main(){
    unsigned x = -2;
    int y = -2;
    vector<int> a{3,0};
    for(auto &x:a) cout << x << " "; cout << endl;
    cout << (x>>1) << " " << (y>>1) <<endl;
    return 0;
}