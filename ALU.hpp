#ifndef __ALU__
#define __ALU__

#include "parser.hpp"

inline void R_ALU(u32 rs1, u32 rs2, ins &s, u32 &rd){
    switch(s.opt){
        case ADD : rd = rs1 + rs2; break;
        case SUB : rd = rs1 - rs2; break;
        case SLL : rd = rs1 << rs2; break;
        case SLT : rd = int(rs1) < int(rs2); break;
        case SLTU: rd = rs1 < rs2; break;
        case XOR : rd = rs1 ^ rs2; break;
        case SRL : rd = rs1 >> rs2; break;
        case SRA : rd = int(rs1) >> rs2; break;
        case OR  : rd = rs1 | rs2; break;
        case AND : rd = rs1 & rs2; break;
    }
}

inline void I_ALU(u32 rs1, u32 im, ins &s, u32 &rd){
    if(s.opt == JALR){
        u32 t = pc + 4;
        pc = (rs1 + sext_12(rs1));
        rd = t;
        return;
    }
    switch(s.opt){
        case ADDI : rd = rs1 + im; break;
        case SLTI : rd = int(rs1) < int(sext_12(im)); break;
        case SLTIU: rd = rs1 < im; break;
        case XORI : rd = rs1 ^ im; break;
        case ORI  : rd = rs1 | im; break;
        case ANDI : rd = rs1 & im; break;
        case SLLI : rd = rs1 << im; break;
        case SRLI : rd = rs1 >> im; break;
        case SRAI : rd = int(rs1) >> im; break;
    }
}

inline void B_ALU(u32 rs1, u32 rs2, u32 im, ins &s, u32 &rd, u32 &pc){
    switch(s.opt){
        case BEQ : (rs1 == rs2) && (rd = 1, pc += im); break;
        case BNE : (rs1 != rs2) && (rd = 1, pc += im); break;
        case BLT : (int(rs1) < int(rs2)) && (rd = 1, pc += im); break;
        case BGE : (int(rs1) >= int(rs2)) && (rd = 1, pc += im); break;
        case BLTU: (rs1 < rs2) && (rd = 1, pc += im); break;
        case BGEU: (rs1 >= rs2) && (rd = 1, pc += im); break;
    }
}

inline void J_exe(u32 &rd, u32 im, ins &s, u32 &pc){
    rd = pc + 4;
    pc += sext_21(im);
}

inline void U_exe(u32 &rd, u32 im, ins &s, const u32 &pc){
    switch(s.opt){
        case LUI: rd = im << 12; break;
        case AUI: rd = pc + (im << 12); break;
    }
}

struct ALU{
    bool busy;
    ins s;
};

struct ins_sta{
    bool busy, st;
    
};

#endif