#ifndef __instruction__
#define __instruction__

#include "def.hpp"
#include "tomasulo.hpp"

static bool ok = 1, nok = 1;
static int sk = 1, nsk = 1;
static int imm = 0, ps = 0;
static int npc = 0, nxt = 0, en = 0, nc = 0, stu = 0, nz = 0, nstu = 0, nnxt = 0;
ins __s, s;
void fetch_ins(){
    if(ok){
        if(stu) return;
        // pc = npc;
        __s = ins(npc, M.get_ins(npc));
        nc = npc + 4;
    }
    else{
        if(Z[ps].sta){
            nnxt = imm + Z[ps].val;
            nok = 1; Z.b[en].sta = 1;
        }
        nsk = 1;
    }
}
void decode(){
    if(!ok) return;
    if(sk){nsk = 0; return;}
    if(Z.full()){nstu = 1; return;}
    pc = s.pc;
    // std::cerr << pc << std::endl;
    // if(pc > 0x1300) exit(0);
    if(s.op == 233){
        ROB_dat x(s, 0, pc); x.sta = 1;
        Z.push(x);
        return;
    }
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
        if(Y.full()) {nstu = 1; return;}
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
        if(Y.full()) {nstu = 1; return;}
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
        bool t = Br.gue(pc);
        x.des = t; x.dpc = pc;
        y.en = Z.push(x);
        Y.push(y);
        // if(t) pc += 4;
        // else pc += s.im;
        if(t) nxt = pc + s.im, nsk = 1;
    }
    else if(s.op == S){
        if(X.full()){nstu = 1; return;}
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
        if(X.full()){nstu = 1; return;}
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
        nsk = 1; x.sta = 1;
        if(!r.busy[rs]) nxt = r[rs] + s.im;
        else if(Z[r.a[rs]].sta) nxt = Z[r.a[rs]].val + s.im;
        else{
            nok = 0; x.sta = 0;
            imm = s.im;
            ps = r.a[rs];
        }
        en = Z.push(x);
    }
    else{
        if(Y.full()){nstu = 1; return;}
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
    nstu = 0;
}

void next_cur(){
    X.next_cur();
    Y.next_cur();
    Z.next_cur();
    r.next_cur();
    if(!ok && nok) nxt = nnxt;
    if(is_br) nok = 1, nstu = 0, nsk = 1, nxt = nz;
    if(!nstu){
        if(nsk) npc = nxt;
        else npc = nc;
        s = __s;
    } stu = nstu;
    nstu = 0;
    ok = nok; sk = nsk;
    is_br = 0;
}

int branch_cnt, ac_cnt;

int cnt_clock = 0;

void commit(){
    // static int tt_cnt = 0;
    ROB_dat t = Z.top();
    if(!Z.empty() && t.sta){
        // std::cout << std::hex << t.pc << std::endl;
        Z.pop();
        if(t.s.op == 233){
            printf("%u\n", (r[10])&255u);
            std::cerr << "time_clock: " << cnt_clock << std::endl;
            std::cerr << "right_branch: " << ac_cnt << ", total_branch: " << branch_cnt << std::endl;
            std::cerr << "accuray: " << ac_cnt / double(branch_cnt) * 100 << "%" << std::endl;
            exit(0);
        }
        else if(t.s.op == B){
            Br.upd(t.pc, t.val);
            ++ branch_cnt;
            if(t.val != t.des){
                nz = t.dpc;
                is_br = 1;
            }
            else ++ac_cnt;
        }
        else if(t.s.op == S){
            // if(t.s.pc == 0x1054){
            //     ++tt_cnt;
            //     std::cerr << tt_cnt << std::endl;
            // }
            X.commit(t.en);
        }
        else{
            // r[a[l].des] = a[l].val;
            r.mod(t.des, t.en, t.val);
            // if(f[a[l].des].pos == a[l].en) f[a[l].des].busy = 0;
        }
        // for(int i = 0; i < 32; ++i) std::cout << std::dec << r.s[i] << " "; std::cout << std::endl;
    }
}

#endif