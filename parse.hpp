#ifndef __parse__
#define __parse__

#include "def.hpp"

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

typedef u32 = unsigned;

u32 get_type(u32 x){
    u32 t = x & 127;
    if(t == LUI || t == AUIPC) return U;
    if(t == JAL) return J;
    if(t == JALR || t == 0b0000011) return I;
    if(t == 0b0100011) return S;
    if(t == 0b0110011) return R;
}

u32 get_imm(u32 op, u32 x){
    switch(op){
        case I: return get_num(x, 20, 31);
        case S: return get_num(x, 7, 11) | get_num(x, 5, 11) << 5;
        case B: return get_num(x, 8, 11) << 1 | get_num(x, 25, 30) << 5 | get_num(x, 7, 7) << 11 | get_num(x, 31, 31) << ;
        case U: return get_num();
        case 
        case R: return 0;
    }
}

struct ins{
    u32 opt;
    u32 rs1, rs2;
    u32 im; u32 op;
    ins(){opt = rs1 = rs2 = im = op = 0;}
    ins(u32 x){
        op = get_type(x);
        im = get_imm(op, x);
        if(t != U || t != J) 
    }
};
#endif