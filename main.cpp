#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"

int cnt = 0;

int main(){
    freopen("sample.data","r",stdin);
    M.init();
    while(1){
        ++cnt;
        std::cerr << "time_cur: " << cnt << std::endl;
        commit();
        execute();
        decode();
        fetch_ins();
        broadcast();
        next_cur();
        std::cerr << "pc: " << pc << std::endl;
        // if(cnt == 20) break;
    }
    return 0;
}