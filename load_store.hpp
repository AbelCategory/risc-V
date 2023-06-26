#ifndef __load_store__
#define __load_store__

#include "memory.hpp"
#include "tomasulo.hpp"

struct LS_dat{
    ins s; int sta, ti;
    u32 vj, vk, en, des;
    int qj, qk;
    LS_dat():qj(0), qk(0), vj(0), vk(0), ti(0), en(0), sta(0), des(0){}
};

static const int len = 32;

struct LS{
    LS_dat a[len];
    int l, sz;
    LS(){}
    struct ex{
        int ti, pos;
    }Lo,St;
    void pop(){
        if(sz) l++, sz--;
    }
    void push(LS_dat &x){
        int p = (l + sz) % len;
        ++sz; a[p] = x;
    }
    void mod(CDB &cur){
        for(int i = 0; i < len; ++i) if(a[i].sta == 1){
            if(a[i].qj == cur.en){
                a[i].qj = -1;
                a[i].vj = cur.val;
            }
            if(a[i].s.op == S){
                if(a[i].qk == cur.en) a[i].qk = -1, a[i].vk = cur.val;
                if(a[i].qj == -1 && a[i].qk == -1) a[i].sta = 2;
            }
            else if(a[i].qj == -1) a[i].sta = 2;
        }
    }
    void exe(){
        
    }
    void reset(){
        
    }
};

#endif