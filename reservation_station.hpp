#ifndef __reservation__
#define __reservation__

#include "ALU.hpp"

struct RS_dat{
    bool busy;
    ins s;
    u32 qj, qk, vj, vk, en;
    RS_dat():busy(0),qj(0),qk(0),vj(0),vk(0), en(0){}
};

static const int len = 16;

struct RS{
    RS_dat a[len];
    RS(){}
    void push(RS_dat y){
        
    }
    void exe(){

    }
    
};

#endif