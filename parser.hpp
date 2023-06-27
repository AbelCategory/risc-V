#ifndef __parser__
#define __parser__

#include "def.hpp"
#include "memory.hpp"

#define LUI  0b0110111
#define AUI  0b0010111
#define JAL  0b1101111
#define JALR 0b1100111
#define BEQ  0b000
#define BNE  0b001
#define BLT  0b100
#define BGE  0b101
#define BLTU 0b110
#define BGEU 0b111
#define LB   0b000
#define LH   0b001
#define LW   0b010
#define LBU  0b100
#define LHU  0b101
#define SB   0b000
#define SH   0b001
#define SW   0b010
#define ADDI 0b000
#define SLTI 0b010
#define SLTIU 0b011
#define XORI 0b100
#define ORI  0b110
#define ANDI 0b111
#define SLLI 0b001
#define SRLI 0b0101
#define SRAI 0b1101
#define ADD  0b0000
#define SUB  0b1000
#define SLL  0b001
#define SLT  0b010
#define SLTU 0b011
#define XOR  0b100
#define SRL  0b0101
#define SRA  0b1101
#define OR   0b110
#define AND  0b111

#define R 0b000
#define I 0b001
#define S 0b010
#define B 0b011
#define U 0b100
#define J 0b101

u32 get_type(u32 x){
    u32 t = x & 127;
    if(t == LUI || t == AUI) return U;
    if(t == JAL) return J;
    if(t == JALR || t == 0b0000011) return I;
    if(t == 0b0100011) return S;
    if(t == 0b0110011) return R;
}

u32 get_imm(u32 op, u32 x){
    switch(op){
        case I: return get_num(x, 20, 31);
        case S: return get_num(x, 7, 11) | get_num(x, 5, 11) << 5;
        case B: return get_num(x, 8, 11) << 1 | get_num(x, 25, 30) << 5 | get_num(x, 7, 7) << 11 | get_num(x, 31, 31) << 12;
        case U: return get_num(x, 12, 31) << 12;
        case J: return get_num(x, 21, 30) << 1 | get_num(x, 20, 20) << 11 | get_num(x, 12, 19) << 12 | get_num(x, 31, 31) << 20;
        case R: return 0;
    }
}

struct ins{
    u32 opt, t, pc;
    u32 rs1, rs2, rd;
    u32 im; u32 op;
    ins(){opt = t = pc = rs1 = rs2 = rd = im = op = 0;}
    ins(u32 p, u32 x){
        if(x == 0x0ff00513){
            op = 233;
            return;
        }
        op = get_type(x); pc = p;
        if(op == U || op == J) rs1 = rs2 = 0;
        else{
            rs1 = get_num(x, 15, 19);
            if(op == I) rs2 = 0;
            else rs2 = get_num(x, 20, 24);
        }
        t = x & 127;
        if(op == U || op == J) opt = t;
        else if(op == I){
            if(t == JALR) opt = JALR;
            else opt = get_num(x, 27, 30) | get_num(x, 12, 14);
        }
        if(op != B && op != S) rd = get_num(x, 7, 11);
        else if(op == B || op == S) opt = get_num(x, 12, 14);
        else if(op == R) opt = get_num(x, 27, 30) | get_num(x, 12, 14);
        if(op == I && (opt == SLLI || opt == SRLI || opt == SRAI)) im = get_num(x, 20, 24);
        else im = get_imm(op, x);
    }
};

static const int len = 16;
/*struct Ins{
    ins a[len];
    u32 l = 0, sz = 0;
    bool ok;
    Ins(){ok = 1; memset(a, 0, sizeof(a));}
    bool full(){return sz == len;}
    inline void get_next(){
        if(!ok || full()) return;
        ++sz; int p = (l + sz - 1) % len;
        a[p] = ins(pc, M.get_ins(pc));
        if(a[p].op == U) ok = 0;
        else pc += 4;
    }
    inline void pop(){
        sz--; l = (l + 1) % len;
    }
    inline void clear(u32 &pos){
        l = sz = 0; ok = 1; pc = pos;
    }
    inline void reok(u32 &pos){
        ok = 1; pc = pos;
    }
};*/


#endif