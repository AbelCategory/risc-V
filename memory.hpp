#ifndef __memory_1__
#define __memory_1__

#include <iostream>
#include <cstring>
#include <string>
#include "def.hpp"
#include "parser.hpp"

const static int N = 100010;

inline u32 ge(char x){return x > 64 ? x - 55 : x - 48;}

struct Mem{
    u32 a[N];
    Mem(){memset(a, 0, sizeof(a));}
    inline u32 lb(u32 x){
        u32 cur = a[x];
        return sext_8(cur);
    }
    inline u32 lh(u32 x){
        u32 cur = a[x] | (a[x + 1] << 8);
        return sext_16(cur);
    }
    inline u32 lw(u32 x){
        u32 cur = a[x] | (a[x + 1] << 8) | (a[x + 2] << 16) | (a[x + 3] << 24);
        return cur;
    }
    inline u32 lbu(u32 x){
        return a[x];
    }
    inline u32 lhu(u32 x){
        return a[x] | a[x + 1] << 8;
    }
    inline void sb(u32 x, u32 t){
        a[x] = t & 0xff;
    }
    inline void sh(u32 x, u32 t){
        a[x] = t & 0xff;
        a[x + 1] = (t >> 8) & 0xff;
    }
    inline void sw(u32 x, u32 t){
        a[x] = t & 0xff;
        a[x + 1] = (t >> 8) & 0xff;
        a[x + 2] = (t >> 16) & 0xff;
        a[x + 3] = t >> 24;
    }
    void init(){
        u32 pc = 0;
        std::string s;
        while(std::cin >> s){
            if(s[0] == '@'){
                pc = 0;
                for(int i = 1; i <= 8; ++i)
                    pc = (pc << 4) | ge(s[i]);
            }
            else a[pc] = ge(s[0]) | ge(s[1]) << 4;
        }
    }
    inline u32 get_ins(u32 x){
        return lw(x);
    }
}M;

#endif
