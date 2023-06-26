#ifndef __instruction__
#define __instruction__

#include "def.hpp"
#include "tomasulo.hpp"

static bool ok = 1;
static int imm = 0, ps = 0;
void fetch_ins(){
    if(!ok){
        if(Z[ps].sta){
            pc += Z[ps].val;
            ok = 1;
        }
        return;
    }
    ins s(pc, M.get_ins(pc));
    if(s.op == U){
        ROB_dat x(s, s.rd, pc);
        x.sta = 1;
        if(s.opt == LUI) x.val = s.im;
        else x.val = s.im + pc;
        Z.push(x);
        pc += 4;
    }
    else if(s.op == J){
        ROB_dat x(s, s.rd, pc);
        x.val = pc + 4;
        x.sta = 1;
        Z.push(x);
        pc += s.im;
    }
    else if(s.op == R){
        
    }
    else if(s.op == B){
        ROB_dat x(s, 0, pc);
        RS_dat y; y.busy = 0;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!f[rs1].busy) y.vj = r[rs1];
        else if(Z[f[rs1].pos].sta) y.vj = Z[f[rs1].pos].val;
        else y.busy = 1, y.qj = f[rs1].pos;
        if(!f[rs2].busy) y.vk = r[rs2];
        else if(Z[f[rs2].pos].sta) y.vk = Z[f[rs2].pos].val;
        else y.busy = 1, y.qk = f[rs2].pos;
        y.en = Z.push(x);
        Y.push(y);
    }
    else if(s.op == S){
        ROB_dat x(s, 0, pc);
        LS_dat y; y.sta = 2;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!f[rs1].busy) y.vj = r[rs1];
        else if(Z[f[rs1].pos].sta) y.vj = Z[f[rs1].pos].val;
        else y.sta = 1, y.qj = f[rs1].pos;
        if(!f[rs2].busy) y.vk = r[rs2];
        else if(Z[f[rs2].pos].sta) y.vk = Z[f[rs2].pos].val;
        else y.sta = 1, y.qk = f[rs2].pos;
        y.en = Z.push(x);
        X.push(y);
    }
    else if(s.t == 0b0000011){
        ROB_dat x(s, s.rd, pc);
        x.val = pc + 4;
        int rs = s.rs1;
        Z.push(x);
        if(!f[rs].busy) pc += r[rs];
        else if(Z[f[rs].pos].sta) pc += Z[f[rs].pos].val;
        else{
            ok = 0;
            imm = s.im;
            ps = f[rs].pos;
        }
    }
    else if(s.opt == JALR){
        ok = 0;
    }
    else{

    }
}

inline void reok(u32 pos){
    ok = 1; pc = pos;
}

#endif