#ifndef __tomasulo__
#define __tomasulo__

#include "reorder_buffer.hpp"
#include "load_store.hpp"
#include "reservation_station.hpp"
#include "parser.hpp"

LS X;
RS Y;
ROB Z;

void execute(){
    X.exe();
    Y.exe();
}

void broadcast(){
    X.upd();
    Y.upd();
}

void next_cur(){
    X.next_cur();
    Y.next_cur();
    Z.next_cur();
    r.next_cur();
}


struct Tomasulo{
    LS X;
    RS Y;
    ROB Z;
    
};
#endif