#ifndef __defi__
#define __defi__

#include <cstring>
#include <iostream>

using u32 = unsigned;
using uc = unsigned char;

inline u32 sext_8(u32 x){
    return (x >> 7) ? (x | 0xffffff00) : x;
}

inline u32 sext_16(u32 x){
    return (x >> 15) ? (x | 0xffff0000) : x;
}

inline u32 sext_12(u32 x){
    return (x >> 11) ? (x | 0xfffff000) : x;
}

inline u32 sext_13(u32 x){
    return (x >> 12) ? (x | 0xffffe000) : x;
}

inline u32 sext_21(u32 x){
    return (x >> 20) ? (x | 0xffe00000) : x;
}

inline u32 get_num(u32 x, u32 l, u32 r){
    x >>= l;
    return x ^ ((x >> (r - l + 1)) << (r - l + 1));
}

u32 pc = 0;
// u32 r[32];
// struct reg{
//     bool busy;
//     int pos;
// }f[32];

bool is_br = 0;

struct reg{
    static const int L = 32;
    u32 r[L], s[L];
    bool busy[L], nb[L];
    int a[L], b[L];
    void reset(){
        for(int i = 0; i < L; ++i)
            b[i] = 0, nb[i] = 0;
    }
    void next_cur(){
        if(is_br) reset();
        for(int i = 0; i < L; ++i){
            a[i] = b[i];
            r[i] = s[i];
            busy[i] = nb[i];
        }
    }
    inline u32& operator [](int x){
        return r[x];
    }
    inline void upd(int x, u32 p){
        if(x == 0) return;
        b[x] = p;
        nb[x] = 1;
    }
    inline void mod(int x, u32 p, u32 v){
        if(x == 0) return;
        s[x] = v;
        nb[x] = p != a[x];
    }
}r;

int sze = 0;
struct CDB{
    u32 en, pc, val;
}c[20];

struct Ba{
    static const int siz = 4096;
    u32 a[siz];
    Ba(){memset(a, 0, sizeof(a));}
    bool gue(u32 x){
        u32 t = x & 0x0fff;
        return a[t] > 1;
    }
    void upd(u32 x, bool ok){
        u32 t = x & 0x0fff;
        if(ok && a[t] == 2) ++a[t];
        else if(!ok && a[t] == 1) --a[t]; 
    }
}Br;

#endif