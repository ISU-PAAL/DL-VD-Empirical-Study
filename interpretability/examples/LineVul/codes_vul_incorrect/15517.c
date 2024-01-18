// commit message qemu@5f706fdc16 (target=1, prob=0.015795134, correct=False): s390x/arch_dump: use proper note name and note size
/*0  */ int s390_cpu_write_elf64_note(WriteCoreDumpFunction f, CPUState *cs,    // (2) 0.2083
/*2  */                               int cpuid, void *opaque)                  // (0) 0.3167
/*4  */ {                                                                       // (4) 0.008333
/*6  */     S390CPU *cpu = S390_CPU(cs);                                        // (3) 0.1333
/*8  */     return s390x_write_all_elf64_notes("CORE", f, cpu, cpuid, opaque);  // (1) 0.2417
/*10 */ }                                                                       // (5) 0.008333
