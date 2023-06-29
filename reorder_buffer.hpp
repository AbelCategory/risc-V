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
    ROB_dat():en(0), sta(0), des(0), val(0), pc(0), dpc(0),s(){}
    ROB_dat(ins _s, u32 d, u32 p):en(0), s(_s), sta(0), des(d), pc(p), val(0), dpc(0){}
};

struct ROB{
    static const int len = 32;
    ROB_dat a[len], b[len];
    int l, sz, nl, nsz;
    ROB(){l = sz = nl = nsz = 0;}
    bool full(){return sz == len;}
    bool empty(){return sz == 0;}
    inline void clear(){
        for(int i = 0; i < len; ++i)
            b[i] = ROB_dat();
        nl = nsz = 0;
    }
    inline void pop(){
        nl = (nl + 1) % len; --nsz;
    }
    void next_cur(){
        if(is_br) clear();
        for(int i = 0; i < len; ++i)
            a[i] = b[i];
        l = nl; sz = nsz;
    }
    inline ROB_dat top(){return a[l];}
    // inline void clear(){
    //     l = sz = 0;
    //     for(int i = 0; i < len; ++i) a[i].sta = 0;
    // }
    int push(ROB_dat &x){
        ++nsz; int p = (nl + nsz - 1) % len;
        b[p] = x; b[p].en = p;
        if(x.s.op != S &&x.s.op != B) r.upd(x.s.rd, p);
        return p;
    }
    inline ROB_dat& operator [](int x){
        return a[x];
    }
}Z;

#endif