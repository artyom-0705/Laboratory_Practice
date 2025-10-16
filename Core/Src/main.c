#include <stdint.h>

int main(void){
    *(uint32_t*)(0x40023800 + 0x30UL)|= 0x02UL;

    while(1){

    }
}