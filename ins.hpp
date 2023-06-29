#ifndef __instruction__
#define __instruction__

#include "def.hpp"
#include "tomasulo.hpp"

static bool ok = 1, nok = 1;
static bool sk = 1, nsk = 1;
static int imm = 0, ps = 0;
int npc = 0, nxt = 0;
ins __s, s;
void fetch_ins(){
    if(ok){
        pc = npc;
        __s = ins(npc, M.get_ins(npc));
        if(!nsk) nxt = npc + 4;
    }
    else{
        if(Z[ps].sta){
            nxt = imm + Z[ps].val;
            nok = 1;
        }
        nsk = 1;
    }
}
void decode(){
    if(!ok || sk){nsk = 0; return;}
    if(Z.full()){nxt = pc; return;}
    if(s.op == U){
        ROB_dat x(s, s.rd, pc);
        x.sta = 1;
        if(s.opt == LUI) x.val = s.im;
        else x.val = s.im + pc;
        Z.push(x);
    }
    else if(s.op == J){
        ROB_dat x(s, s.rd, pc);
        x.val = pc + 4;
        x.sta = 1;
        Z.push(x);
        nxt = pc + s.im; nsk = 1;
    }
    else if(s.op == R){
        if(Y.full()) {nxt = pc; return;}
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
    }
    else if(s.op == B){
        if(Y.full()) {nxt = pc; return;}
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
        // if(t) pc += 4;
        // else pc += s.im;
        if(t) nxt = pc + s.im, nsk = 1;
    }
    else if(s.op == S){
        if(X.full()){nxt = pc; return;}
        ROB_dat x(s, 0, pc); x.sta = 1;
        LS_dat y; y.sta = 2;
        int rs1 = s.rs1, rs2 = s.rs2;
        y.qj = y.qk = -1; y.s = s;
        if(!r.busy[rs1]) y.vj = r[rs1];
        else if(Z[r.a[rs1]].sta) y.vj = Z[r.a[rs1]].val;
        else y.sta = 1, y.qj = r.a[rs1], x.sta = 0;
        if(!r.busy[rs2]) y.vk = r[rs2];
        else if(Z[r.a[rs2]].sta) y.vk = Z[r.a[rs2]].val;
        else y.sta = 1, y.qk = r.a[rs2], x.sta = 0;
        y.en = Z.push(x);
        X.push(y);
    }
    else if(s.t == 0b0000011){
        if(X.full()){nxt = pc; return;}
        ROB_dat x(s, s.rd, pc);
        LS_dat y; y.sta = 3;
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
        nsk = 1;
        if(!r.busy[rs]) nxt = r[rs] + s.im;
        else if(Z[r.a[rs]].sta) nxt = Z[r.a[rs]].val + s.im;
        else{
            nok = 0;
            imm = s.im;
            ps = r.a[rs];
        }
    }
    else{
        if(Y.full()){nxt = pc; return;}
        ROB_dat x(s, s.rd, pc);
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

void next_cur(){
    X.next_cur();
    Y.next_cur();
    Z.next_cur();
    r.next_cur();
    s = __s;
    npc = nxt;
    ok = nok; sk = nsk;
}

#endif