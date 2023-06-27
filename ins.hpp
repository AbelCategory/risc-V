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
    if(Z.full()) return;
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
        if(Y.full()) return;
        ROB_dat x(s, s.rd, pc);
        RS_dat y; y.busy = 0;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!r.busy[rs1]) y.vj = r[rs1];
        else if(Z[r.a[rs1]].sta) y.vj = Z[r.a[rs1]].val;
        else y.busy = 1, y.qj = r.a[rs1];
        if(!r.busy[rs2]) y.vk = r[rs2];
        else if(Z[r.a[rs2]].sta) y.vk = Z[r.a[rs2]].val;
        else y.busy = 1, y.qk = r.a[rs2];
        y.en = Z.push(x);
        Y.push(y);
        pc += 4;
    }
    else if(s.op == B){
        if(Y.full()) return;
        ROB_dat x(s, 0, pc);
        RS_dat y; y.busy = 0;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!r.busy[rs1]) y.vj = r[rs1];
        else if(Z[r.a[rs1]].sta) y.vj = Z[r.a[rs1]].val;
        else y.busy = 1, y.qj = r.a[rs1];
        if(!r.busy[rs2]) y.vk = r[rs2];
        else if(Z[r.a[rs2]].sta) y.vk = Z[r.a[rs2]].val;
        else y.busy = 1, y.qk = r.a[rs2];
        bool t = Br.gue(pc); x.val = t;
        x.des = t;
        y.en = Z.push(x);
        Y.push(y);
        if(t) pc += 4;
        else pc += s.im;
    }
    else if(s.op == S){
        if(X.full()) return;
         ROB_dat x(s, 0, pc);
        LS_dat y; y.sta = 2;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!r.busy[rs1]) y.vj = r[rs1];
        else if(Z[r.a[rs1]].sta) y.vj = Z[r.a[rs1]].val;
        else y.sta = 1, y.qj = r.a[rs1];
        if(!r.busy[rs2]) y.vk = r[rs2];
        else if(Z[r.a[rs2]].sta) y.vk = Z[r.a[rs2]].val;
        else y.sta = 1, y.qk = r.a[rs2];
        y.en = Z.push(x);
        X.push(y);
    }
    else if(s.t == 0b0000011){
        if(X.full()) return;
        ROB_dat x(s, s.rd, pc);
        LS_dat y; y.sta = 2;
        int rs = s.rs1;
        y.qj = y.qk = -1; y.s = s;
        if(!r.busy[rs]) y.vj = r[rs];
        else if(Z[r.a[rs]].sta) y.vj = Z[r.a[rs]].val;
        else y.sta = 1, y.qj = r.a[rs];
        y.en = Z.push(x);
        X.push(y);
    }
    else if(s.opt == JALR){
        ROB_dat x(s, s.rd, pc);
        x.val = pc + 4;
        int rs = s.rs1;
        Z.push(x);
        if(!r.busy[rs]) pc += r[rs];
        else if(Z[r.a[rs]].sta) pc += Z[r.a[rs]].val;
        else{
            ok = 0;
            imm = s.im;
            ps = r.a[rs];
        }
    }
    else{
        if(X.full()) return;
        ROB_dat x(s, 0, pc);
        RS_dat y; y.busy = 0;
        int rs = s.rs1;
        y.qj = y.qk = -1; y.s = s; y.vk = s.im;
        if(!r.busy[rs]) y.vj = r[rs];
        else if(Z[r.a[rs]].sta) y.vj = Z[r.a[rs]].val;
        else y.busy = 1, y.qj = r.a[rs];
        y.en = Z.push(x);
        Y.push(y);
    }
}

#endif