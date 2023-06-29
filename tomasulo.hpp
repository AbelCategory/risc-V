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

#endif