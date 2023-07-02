#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"
#include <functional>
#include <random>

int main(){
    freopen("testcases/bulgarian.data","r",stdin);
    // freopen("log.txt","w",stdout);
    M.init();
    std::function<void()> f[4]={commit, execute, decode, fetch_ins};
    while(1){
        ++cnt_clock;
        // std::cout << "time_cur: " << std::dec << cnt_clock << std::endl;
        // std::cout << "ROB_cur:" << Z.l << ", " << std::hex << Z.a[Z.l].pc << std::endl;
        // std::cerr << std::dec << Y.sz << std::endl;
        // if(pc == 0x10e0){
        //     std::cerr << "!!!" << std::endl;
        // }
        random_shuffle(f+0, f+4);
        f[0]();
        f[1]();
        f[3]();
        f[2]();
        broadcast();
        // if(!sk) std::cout << "pc: " << std::hex << pc << std::endl;
        next_cur();
        // if(cnt == 664) break;
    }
    return 0;
}