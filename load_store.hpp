#ifndef __load_store__
#define __load_store__

#include "memory.hpp"
#include "reorder_buffer.hpp"

struct LS_dat{
    ins s; int sta, ti;
    u32 vj, vk, en;
    int qj, qk;
    LS_dat():qj(0), qk(0), vj(0), vk(0), ti(0), en(0), sta(0){}
};


struct LS{
    static const int len = 32;
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
    void upd(CDB c){
        for(int i = 0; i < len; ++i) if(a[i].sta == 1){
            if(b[i].qj != -1 && a[i].qj == c.en){
                b[i].qj = -1;
                b[i].vj = c.val;
            }
            if(b[i].s.op == S){
                if(b[i].qk != -1 && a[i].qk == c.en) b[i].qk = -1, b[i].vk = c.val;
                if(b[i].qj == -1 && b[i].qk == -1) b[i].sta = 2;
            }
            else if(b[i].qj == -1) b[i].sta = 3;
        }
    }
    void exe(){
        if(a[l].ti){
            --b[l].ti;
            if(!b[l].ti){
                if(a[l].s.op == I){
                    Load_exe(a[l].vj, a[l].s.im, a[l].s, Z.b[a[l].en].val); 
                    c[sze ++] = (CDB){a[l].en, Z.b[a[l].en].pc, Z.b[a[l].en].val};
                }
                else Store_exe(a[l].vj, a[l].vk, a[l].s, a[l].s.im);
                Z.b[a[l].en].sta = 1;
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