# Virtualization-Technologies

## CMPE 283 Virtualization Technologies Assignments

---

### Assignment 1: Discovering VMX Features

This assignment (A1) is to create a Linux kernel module that will query various MSRs to determine virtualization features available in your CPU. This module will report (via the system message log) the features it discovers.

At a high level, you will need to perform the following:

* Configure a Linux machine, either VM based or on real hardware. (You may use any Linux distribution you wish, but I prefer Ubuntu 22.04 LTS)

* Download and build the Linux kernel source code

* Create a new kernel module with the assignment functionality

* Load (insert) the new module

* Verify proper output in the system message log

Note: The assignment 1 instructions are specific to Intel brand CPUs. If you are using an AMD brand CPU (or another type of CPU such as an ARM64 or Apple M1/M2), you will need to do this assignment in Google Cloud (GCP).

Go to [A1](A1/) directory and read the corresponding README.md file to gain more info.

---

### Assignment 2: Instrumentation Via Hyper-call (Add New CPUID Emulation Features in KVM)

This assignment (A2) is to modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested:

* For CPUID leaf node %eax=0x4FFFFFFC:
    * Return the total number of exits (all types) in %eax

* For CPUID leaf node %eax=0x4FFFFFFD:
    * Return the high 32 bits of the total time spent processing all exits in %ebx
    * Return the low 32 bits of the total time spent processing all exits in %ecx
        * %ebx and %ecx return values are measured in processor cycles, across all VCPUs

At a high level, you will need to perform the following:
* Start with your assignment 1 environment
* Modify the kernel code with the assignment(s) functionality:
    * Determine where to place the measurement code (for exit counts and # cycles)
    * Create new CPUID leaf 0x4FFFFFFD, 0x4FFFFFFC
        * Report back information as described above
* Create a user-mode program that performs various CPUID instructions required to test your
  assignment
    * Pro-tip: This can be achieved on ubuntu by installing the ‘cpuid’ package
    * Run this user mode program in the inner VM
        * There is no need to insmod anything like assignment 1 did
* Verify proper output

Go to [A2](A2/) directory and read the corresponding README.md file to gain more info.
