#ifndef __reservation__
#define __reservation__

#include "ALU.hpp"
#include "reorder_buffer.hpp"

struct RS_dat{
    int busy;
    ins s;
    u32 vj, vk, en; int qj, qk;
    RS_dat():busy(-1),qj(0),qk(0),vj(0),vk(0), en(0),s(){}
};


struct RS{
    static const int len = 32;
    RS_dat a[len], b[len];
    int sz = 0, nsz = 0;
    RS(){}
    bool full(){return len == sz;}
    void next_cur(){
        if(is_br) nsz = 0;
        for(int i = 0; i < len; ++i)
            a[i] = b[i];
        sz = nsz;
    }
    void push(RS_dat y){
        for(int i = 0; i < len; ++i)
            if(a[i].busy == -1){
                b[i] = y; ++nsz;
                break;
            }
    }
    void exe(){
        int cnt = 0;
        for(int i = 0; i < len; ++i) if(a[i].busy == 0){
            if(a[i].s.pc == 4248){
                std::cerr << "??";
            }
            ROB_dat &cur = Z.b[a[i].en];
            switch(a[i].s.op){
                case R: R_ALU(a[i].vj, a[i].vk, a[i].s, cur.val); break;
                case I: I_ALU(a[i].vj, a[i].vk, a[i].s, cur.val); break;
                case B: B_ALU(a[i].vj, a[i].vk, a[i].s.im, a[i].s, cur.val, cur.dpc); break;
            }
            c[sze ++] = (CDB){a[i].en, cur.pc, cur.val};
            b[i].busy = -1; cur.sta = 1;
            --nsz;
        }
    }
    void upd(CDB c){
        int cnt = 0;
        for(int i = 0; i < len; ++i) if(a[i].busy == 1){
            if(b[i].qj != -1 && b[i].qj == c.en){
                b[i].qj = -1;
                b[i].vj = c.val;
            }
            if(b[i].qk != -1 && b[i].qk == c.en){
                b[i].qk = -1;
                b[i].vk = c.val;
            }
            if(b[i].qj == -1 && b[i].qk == -1) b[i].busy = 0;
        }
    }
    void reset(){
        for(int i = 0; i < len; ++i) b[i] = RS_dat();
        nsz = 0;
    }
};

#endif