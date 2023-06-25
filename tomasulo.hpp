#ifndef __tomasulo__
#define __tomasulo__

#include "reorder_buffer.hpp"
#include "load_store.hpp"
#include "reservation_station.hpp"
#include "parser.hpp"

struct bus{
    ROB r;
    LS X;
    RS Y;
    Ins Q;
    void fetch(){
        Q.get_next();
    }
    void run(){
        
    }
};


#endif