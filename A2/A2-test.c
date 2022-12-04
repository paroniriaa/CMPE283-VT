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

    eax = 0x4FFFFFFC;
    __cpuid(&eax, &ebx, &ecx, &edx);
    printf("CPUID(0x4FFFFFFC), Total exit counter = %u \n", eax);

    eax = 0x4FFFFFFD;
    __cpuid(&eax, &ebx, &ecx, &edx);
    cycle_time = (unsigned long long) ebx << 32 | ecx;
    printf("CPUID(0x4FFFFFFD), Total exit cycles = %llu \n", cycle_time);
}