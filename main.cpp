#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"
#include <functional>
#include <random>

int main(){
    // freopen("testcases/bulgarian.data","r",stdin);
    // freopen("log.txt","w",stdout);
    M.init();
    while(1){
        ++cnt_clock;
        // std::cout << "time_cur: " << std::dec << cnt << std::endl;
        // std::cout << "ROB_cur:" << Z.l << ", " << std::hex << Z.a[Z.l].pc << std::endl;
        // std::cerr << std::dec << Y.sz << std::endl;
        // if(pc == 0x10e0){
        //     std::cerr << "!!!" << std::endl;
        // }
        std::function<void()> f[4]={commit, execute, decode, fetch_ins};
        random_shuffle(f+1, f+3);
        f[2]();
        f[0]();
        f[1]();
        f[3]();
        broadcast();
        next_cur();
        // if(!sk) std::cout << "pc: " << std::hex << pc << std::endl;
        // if(cnt == 664) break;
    }
    return 0;
}