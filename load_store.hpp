#ifndef __load_store__
#define __load_store__

#include "memory.hpp"
#include "tomasulo.hpp"

struct LS_dat{
    ins s; int sta, ti;
    u32 vj, vk, en;
    int qj, qk;
    LS_dat():qj(0), qk(0), vj(0), vk(0), ti(0), en(0), sta(0){}
};

static const int len = 32;

struct LS{
    LS_dat a[len], b[len];
    int l, sz, nl, nsz;
    LS(){}
    struct ex{
        int ti, pos;
    }Lo,St;
    inline void next_cur(){
        l = nl; sz = nsz;
        for(int i = 0; i < len; ++i) a[i] = b[i];
    }
    inline bool full(){return sz == len;}
    void push(LS_dat &x){
        int p = (nl + nsz) % len;
        ++nsz; b[p] = x; b[p].ti = 3;
    }
    void upd(){
        for(int i = 0; i < len; ++i) if(a[i].sta == 1){
            if(b[i].qj != -1 && Z[a[i].qj].sta){
                b[i].qj = -1;
                b[i].vj = Z[a[i].qj].val;
            }
            if(b[i].s.op == S){
                if(b[i].qk != -1 && Z[b[i].qk].sta) b[i].qk = -1, b[i].vk = Z[a[i].qk].val;
                if(b[i].qj == -1 && b[i].qk == -1) b[i].sta = 2;
            }
            else if(b[i].qj == -1) b[i].sta = 3;
        }
    }
    void exe(){
        if(a[l].ti){
            --b[l].ti;
            if(!b[l].ti){
                if(b[l].s.op == I) Load_exe(b[l].vj, b[l].s.im, b[l].s, Z[b[l].en].val);
                else Store_exe(b[l].vj, b[l].vk, b[l].s, b[l].s.im);
                Z.b[b[l].en].sta = 1;
            }
        }
        else if(a[(l + 1) % len].sta == 3 && sz > 1){
            nl = (nl + 1) % len;
            --nsz;
        }
    }
    void commit(u32 en){
        for(int i = 0; i < len; ++i) if(a[i].en == en){
            b[i].sta = 3;
            break;
        }
    }
    void reset(){
        for(int i = 0; i < sz; ++i){
            int x = (l + i) % len;
            if(a[x].s.op != S && a[x].sta != 3){
                nsz = i + 1;
                break;
            }
        }
    }
};

#endif