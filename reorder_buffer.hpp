#ifndef __ReOB__
#define __ReOB__

#include "parser.hpp"
#include "def.hpp"
#include "tomasulo.hpp"

struct ROB_dat{
    u32 en;
    ins s;
    bool sta;
    u32 des, val, pc, dpc;
    ROB_dat():en(0), sta(0), des(0), val(0), pc(0), dpc(0){}
    ROB_dat(u32 e, ins _s, int st = 0, u32 d, u32 p):en(e), s(_s), sta(st), des(d), pc(p), val(0), dpc(0){}
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
        l = sz = 0;
        for(int i = 0; i < len; ++i) a[i].sta = 0;
    }
    int push(ins &s){
        ++sz; int p = (l + sz - 1) % len;
        a[p] = ROB_dat(p, s, 0, s.rd, s.pc);
        return p;
    }
    void commit(CDB c, bus &b){
        a[c.en].sta = 1;
        a[c.en].val = c.val;
        if(a[c.en].s.op == B || a[c.en].s.opt == JAL || a[c.en].s.opt == AUI){
            a[c.en].dpc = c.pc;
            if(a[c.en].s.op != B) b.Q.reok(c.pc);
        }
    }
};

#endif