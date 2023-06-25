#ifndef __defi__
#define __defi__

using u32 = unsigned;
using uc = unsigned char;

inline u32 sext_8(u32 x){
    return (x >> 8) ? (x | 0xffffff00) : x;
}

inline u32 sext_16(u32 x){
    return (x >> 16) ? (x | 0xffff0000) : x;
}

inline u32 sext_12(u32 x){
    return (x >> 12) ? (x | 0xfffff000) : x;
}

inline u32 get_num(u32 x, int l, int r){
    return (x &((1 << r) - 1)) >> l;
}

u32 pc = 0;
u32 x[32];

#endif