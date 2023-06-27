#ifndef __ReOB__
#define __ReOB__

#include "parser.hpp"
#include "def.hpp"
#include "tomasulo.hpp"
#include "ins.hpp"

struct ROB_dat{
    u32 en;
    ins s;
    bool sta;
    u32 des, val, pc, dpc;
    ROB_dat():en(0), sta(0), des(0), val(0), pc(0), dpc(0){}
    ROB_dat(ins _s, u32 d, u32 p):en(0), s(_s), sta(0), des(d), pc(p), val(0), dpc(0){}
};

static const int len = 32;

struct ROB{
    ROB_dat a[len], b[len];
    int l, sz, nl, nsz;
    ROB(){l = sz = nl = nsz = 0;}
    bool full(){return sz == len;}
    inline void pop(){
        nl = (nl + 1) % len; --nsz;
    }
    void next_cur(){
        for(int i = 0; i < len; ++i)
            a[i] = b[i];
        l = nl; sz = nsz;
    }
    inline ROB_dat top(){return a[l];}
    inline void clear(){
        for(int i = 0; i < len; ++i)
            a[i] = ROB_dat();
        l = sz = 0;
    }
    inline void clear(){
        l = sz = 0;
        for(int i = 0; i < len; ++i) a[i].sta = 0;
    }
    int push(ROB_dat &x){
        ++nsz; int p = (nl + nsz - 1) % len;
        b[p] = x; b[p].en = p;
        if(x.s.op != S &&x.s.op != B) r.upd(x.s.rd, p);
        return p;
    }
    inline ROB_dat& operator [](int x){
        return a[x];
    }
    inline void commit(){
        if(sz && a[l].sta){
            if(a[l].s.op == 233){
                printf("%u\n", (r[10])&255u);
                exit(0);
            }
            else if(a[l].s.op == B){
                Br.upd(a[l].pc, a[l].val);
                if(a[l].val != a[l].des){
                    clear();
                    X.reset();
                    Y.reset();
                }
            }
            else if(a[l].s.op == S){
                X.commit(l);
            }
            else{
                // r[a[l].des] = a[l].val;
                r.mod(a[l].des, a[l].en, a[l].val);
                // if(f[a[l].des].pos == a[l].en) f[a[l].des].busy = 0;
            }
            pop();
        }
    }
};

#endif