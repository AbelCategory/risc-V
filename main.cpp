#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"

int cnt = 0;

int main(){
    freopen("testcases/array_test1.data","r",stdin);
    M.init();
    while(1){
        ++cnt;
        std::cerr << "time_cur: " << std::dec << cnt << std::endl;
        std::cerr << "ROB_cur:" << Z.l << ", " << Z.a[Z.l].pc << std::endl;
        std::cerr << Y.sz << std::endl;
        commit();
        execute();
        decode();
        fetch_ins();
        broadcast();
        next_cur();
        if(!sk) std::cerr << "pc: " << std::hex << pc << std::endl;
        // if(cnt == 100) break;
    }
    return 0;
}