#ifndef __memory_1__
#define __memory_1__

#include <cstring>
#include "def.hpp"

const static int N = 100010;
struct Mem{
    u32 a[N];
    Mem(){memset(a, 0, sizeof(a));}
    inline u32 lb(int x){
        u32 cur = a[x];
        if((cur >> 7) & 1) return 0xffffff00 | cur;
        else return cur;
    }
    inline u32 lh(int x){
        u32 cur = a[x] | (a[x + 1] << 8);
        if((cur >> 15) & 1) return 0xffff0000 | cur;
        else return cur;
    }
    inline u32 lw(int x){
        u32 cur = a[x] | (a[x + 1] << 8) | (a[x + 2] << 16) | (a[x + 3] << 24);
        return cur;
    }
    inline void sb(int x, u32 t){
        a[x] = t & 0xff;
    }
    inline void sh(int x, u32 t){
        a[x] = t & 0xff;
        a[x + 1] = (t >> 8) & 0xff;
    }
    inline void sw(int x, u32 t){
        a[x] = t & 0xff;
        a[x + 1] = (t >> 8) & 0xff;
        a[x + 2] = (t >> 16) & 0xff;
        a[x + 3] = t >> 24;
    }
    void init(){
        
    }
};

#endif
