#ifndef __defi__
#define __defi__

using u32 = unsigned;

inline u32 get_num(u32 x, int l, int r){
    return (x &((1 << r) - 1)) >> l;
}


#endif