#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"

int cnt = 0;

int main(){
    // freopen("sample/sample.data","r",stdin);
    // freopen("log.txt","w",stdout);
    M.init();
    while(1){
        ++cnt;
        // std::cout << "time_cur: " << std::dec << cnt << std::endl;
        // std::cout << "ROB_cur:" << Z.l << ", " << std::hex << Z.a[Z.l].pc << std::endl;
        // std::cerr << std::dec << Y.sz << std::endl;
        commit();
        execute();
        decode();
        fetch_ins();
        broadcast();
        next_cur();
        // if(!sk) std::cout << "pc: " << std::hex << pc << std::endl;
        // if(cnt == 100) break;
    }
    return 0;
}