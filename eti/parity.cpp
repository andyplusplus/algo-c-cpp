/*
  compute the parity of a very large number, p45
 */
#include <cassert>
#include <iostream>


int parity1(unsigned long x){
        int result = 0;
        while(x){
                result ^= (x & 1);
                x >>= 1;
        }
        return result;
}

int main(){
        assert(parity1(1) == 1);
        assert(parity1(3) == 0);
}
