#include "def.hpp"
#include "memory.hpp"
#include "parser.hpp"
#include "ins.hpp"

int main(){
    M.init();
    while(1){
        Z.commit();
        execute();
        fetch_ins();
        broadcast();
    }
    return 0;
}