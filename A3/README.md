### Assignment 3: Instrumentation Via Hyper-call II (Add New CPUID Emulation Features in KVM)

This assignment (A2) is to modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested:

* For CPUID leaf node %eax=0x4FFFFFFE:
  * Return the number of exits for the exit number provided (on input) in %ecx
    * This value should be returned in %eax

* For CPUID leaf node %eax=0x4FFFFFFF:
  * Return the time spent processing the exit number provided (on input) in %ecx
    * Return the high 32 bits of the total time spent for that exit in %ebx
    * Return the low 32 bits of the total time spent for that exit in %ecx

At a high level, you will need to perform the following:

* Start with your assignment 2 environment
* Modify the kernel code with the assignment(s) functionality:
  * Determine where to place the measurement code (for exit counts and # cycles)
  * Create new CPUID leafs 0x4FFFFFFE, 0x4FFFFFFF
    * Report back information as described above
* Create a user-mode program that performs various CPUID instructions required to test your
assignment
  * Pro-tip: This can be achieved on ubuntu by installing the ‘cpuid’ package
  * Run this user mode program in the inner VM
    * There is no need to insmod anything like assignment 1 did
* Verify proper output

Refer to [A3 Instruction](source/283_Assignment2-3_F22.pdf) for detailed info and instructions in this assignment, and refer to my [A3 log-book](A3-log-book.txt) if you are blocked and needed help.

### A3 Result Demonstration

(check out [A3 screenshots](screenshots/) for more)

TBD...
