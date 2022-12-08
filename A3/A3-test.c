#include <stdio.h>
#include <sys/types.h>

unsigned int type_exit_counter[75];
unsigned long long type_cycle_time[75];

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
    
    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFC)-----\n\n");
    eax = 0x4FFFFFFC;
    __cpuid(&eax, &ebx, &ecx, &edx);
    printf("CPUID(0x4FFFFFFC), All Type Total Exit Counter = %u \n", eax);
    printf("EAX = %u  EBX = %u ECX = %u EDX = %u \n", eax, ebx, ecx, edx);   


    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFD)-----\n\n");
    eax = 0x4FFFFFFD;
    __cpuid(&eax, &ebx, &ecx, &edx);
    cycle_time = (unsigned long long) ebx << 32 | ecx;
    printf("CPUID(0x4FFFFFFD), All Type Total Exit Cycles = %llu \n", cycle_time);
    printf("EAX = %u  EBX = %u ECX = %u EDX = %u \n", eax, ebx, ecx, edx);

    /*
    For CPUID(0x4FFFFFFE) and CPUID(0x4FFFFFFF)
    test range [0, 74] to include 3 cases:
        The 1st invalid range for %ecx(not defined in SDM):
            -> N<0, N>69, 35, 38, 42
        The 2nd invalid range for %ecx(not enabled in KVM):
            -> 5, 6, 11, 17, 65, 66, 69
        The valid range for %ecx(defined in SDM and enabled in KVM):
            -> 0~4, 7~10, 12~16, 18~34, 36~37, 39~41, 43~64, 67~68
        Note: above indexs referenced from textbook Combined Volume Set of Intel® 64 and IA-32 Architectures Software Developers Manuals 
        with version 09/30/2022 and vmx.h with last commit in 06/08/2022.
    */

    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFE)-----\n\n");
    for (i = 0; i < 75; i++) {
        eax = 0x4FFFFFFE;
        ecx = i;
        ecx_copy = ecx;
        __cpuid(&eax, &ebx, &ecx, &edx);
        printf("CPUID(0x4FFFFFFE), Type %u Total Exit Counter = %u \n", ecx_copy, eax);
        printf("EAX = %u  EBX = %u ECX = %u EDX = %u \n", eax, ebx, ecx, edx);
        type_exit_counter[i] = eax;
    }

    printf("\n-----Test Leaf Node CPUID(0x4FFFFFFF)-----\n\n");
    for (i = 0; i < 75; i++) {
        eax = 0x4FFFFFFF;
        ecx = i;
        ecx_copy = ecx;
        __cpuid(&eax, &ebx, &ecx, &edx);
        cycle_time = (unsigned long long) ebx << 32 | ecx;
        printf("CPUID(0x4FFFFFFF), Type %u Total Exit Cycles = %llu \n", ecx_copy, cycle_time);
        printf("EAX = %u  EBX = %u ECX = %u EDX = %u \n", eax, ebx, ecx, edx);
        type_cycle_time[i] = cycle_time;
    }

    printf("\n-----Statics Overview For Each Basic Exit-----\n\n");
    printf("Exit Type %-3s Exit Counter %-3s Exit Cycles %-5s Cycles/Exit \n", " ", " ", " ");
    for (i = 0; i < 75; i++) {
        printf("%-13d %-16u %-17llu %-17llu \n", i, type_exit_counter[i], type_cycle_time[i], type_exit_counter[i] != 0 ? (type_cycle_time[i]/type_exit_counter[i]) : 0);
    }

}