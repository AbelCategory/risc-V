#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"

int main(){
    freopen("sample.data","r",stdin);
    M.init();
    while(1){
        commit();
        execute();
        fetch_ins();
        broadcast();
        next_cur();
    }
    return 0;
}