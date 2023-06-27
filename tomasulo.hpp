#ifndef __tomasulo__
#define __tomasulo__

#include "reorder_buffer.hpp"
#include "load_store.hpp"
#include "reservation_station.hpp"
#include "parser.hpp"

LS X;
RS Y;

void execute(){
    X.exe();
    Y.exe();
}

void broadcast(){
    for(int i = 0; i < sze; ++i){
        X.upd(c[i]);
        Y.upd(c[i]);
    }
    sze = 0;
}

void next_cur(){
    X.next_cur();
    Y.next_cur();
    Z.next_cur();
    r.next_cur();
}

void commit(){
    ROB_dat t = Z.top();
    if(!Z.empty() && t.sta){
        if(t.s.op == 233){
            printf("%u\n", (r[10])&255u);
            exit(0);
        }
        else if(t.s.op == B){
            Br.upd(t.pc, t.val);
            if(t.val != t.des){
                Z.clear();
                X.reset();
                Y.reset();
            }
        }
        else if(t.s.op == S){
            X.commit(t.en);
        }
        else{
            // r[a[l].des] = a[l].val;
            r.mod(t.des, t.en, t.val);
            // if(f[a[l].des].pos == a[l].en) f[a[l].des].busy = 0;
        }
        Z.pop();
    }
}

#endif