#ifndef __reservation__
#define __reservation__

#include "ALU.hpp"

struct RS_dat{
    bool busy;
    ins s;
    u32 qj, qk, vj, vk;
    RS_dat():busy(0),qj(0),qk(0),vj(0),vk(0){}
};

struct RS{
    
};

#endif