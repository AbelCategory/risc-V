#ifndef __defi__
#define __defi__

#include <cstring>

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

inline u32 sext_21(u32 x){
    return (x >> 20) ? (x | 0xffe00000) : x;
}

inline u32 get_num(u32 x, int l, int r){
    return (x &((1 << r + 1) - 1)) >> l;
}

u32 pc = 0;
// u32 r[32];
// struct reg{
//     bool busy;
//     int pos;
// }f[32];

static const int L = 32;
struct reg{
    u32 r[L], s[L];
    bool busy[L], nb[L];
    int a[L], b[L];
    void next_cur(){
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
        b[x] = p;
        nb[x] = 1;
    }
    inline void mod(int x, u32 p, u32 v){
        s[x] = v;
        nb[x] = p != a[x];
    }
}r;

struct CDB{
    u32 en, val, pc;
};

static const int siz = 4096;
struct Ba{
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