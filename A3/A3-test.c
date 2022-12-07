#include <stdio.h>
#include <sys/types.h>


static inline void
__cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx,
unsigned int *edx)
{
    asm volatile("cpuid"
    : "=a" (*eax),"=b" (*ebx),"=c" (*ecx),"=d" (*edx)
    : "0" (*eax), "1" (*ebx), "2" (*ecx), "3" (*edx));
}

int
main(int argc, char **argv)
{
    unsigned int eax, ebx, ecx, edx;
    unsigned long long cycle_time;
    unsigned int ecx_copy;
    int i;
    bool valid;
    
    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFC)-----\n\n");
    eax = 0x4FFFFFFC;
    __cpuid(&eax, &ebx, &ecx, &edx);
    printf("CPUID(0x4FFFFFFC), Total Exit Counter = %u \n", eax);

    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFD)-----\n\n");
    eax = 0x4FFFFFFD;
    __cpuid(&eax, &ebx, &ecx, &edx);
    cycle_time = (unsigned long long) ebx << 32 | ecx;
    printf("CPUID(0x4FFFFFFD), Total Exit Cycles = %llu \n", cycle_time);

    /*
    For CPUID(0x4FFFFFFE) and CPUID(0x4FFFFFFF)
    test range [-1, 70] to include 3 cases:
        1. ecx in valid range -> 0~34, 36~37, 39~41, 43~69
        2. ecx in invalid range(not defined in SDM) -> 35, 38, 42   
        3. ecx in invalid range(not enabled in KVM) -> -1, 70
        Note: above indexs referenced from textbook Combined Volume Set of Intel® 64 and IA-32 Architectures Software Developers Manuals 
        with version 09/30/2022    
    */

    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFE)-----\n\n");
    for(i = -1; i < 71; i++) {
        eax = 0x4FFFFFFE;
        ecx = i;
        ecx_copy = ecx;
        ((i == 35) || (i == 38) || (i == 42) || (i < 0) || (i > 69)) ? valid = false : valid = true;
        __cpuid(&eax, &ebx, &ecx, &edx);
        if (valid) {
            printf("CPUID(0x4FFFFFFE), Valid Exit Type %u, Exit Count = %u \n", ecx_copy, eax);       
        } else {
            printf("CPUID(0x4FFFFFFE), Invalid Exit Type %u, EAX = %u EBX = %u ECX = %u EDX = %u \n", ecx_copy, eax, ebx, ecx, edx);       
        }
    }

    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFF)-----\n\n");
    for(i = -1; i < 71; i++) {
        eax = 0x4FFFFFFF;
        ecx = i;
        ecx_copy = ecx;
        ((i == 35) || (i == 38) || (i == 42) || (i < 0) || (i > 69)) ? valid = false : valid = true;
        __cpuid(&eax, &ebx, &ecx, &edx);
        if (valid) {
            cycle_time = (unsigned long long) ebx << 32 | ecx;    
            printf("CPUID(0x4FFFFFFF), Valid Exit Type %u, Exit Cycles = %llu \n", ecx_copy, cycle_time);       
        } else {
            printf("CPUID(0x4FFFFFFF), Invalid Exit Type %u, EAX = %u EBX = %u ECX = %u EDX = %u \n", ecx_copy, eax, ebx, ecx, edx);       
        }
    }

}