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
    ROB_dat a[len];
    int l, sz;
    ROB(){l = sz = 0;}
    bool full(){return sz == len;}
    inline void pop(){
        l = (l + 1) % len; --sz;
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
    int push(ROB_dat &r){
        ++sz; int p = (l + sz - 1) % len;
        a[p] = r; a[p].en = p;
        if(r.s.op != S &&r.s.op != B){
            f[r.s.rd].busy = 1;
            f[r.s.rd].pos = p;
        }
        return p;
    }
    void mod(CDB c){
        a[c.en].sta = 1;
        a[c.en].val = c.val;
        if(a[c.en].s.op == B || a[c.en].s.opt == JAL || a[c.en].s.opt == AUI){
            a[c.en].dpc = c.pc;
            if(a[c.en].s.op != B) reok(c.pc);
        }
    }
    inline ROB_dat& operator [](int x){
        return a[x];
    }
};

#endif