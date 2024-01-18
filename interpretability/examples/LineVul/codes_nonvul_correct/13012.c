// commit message qemu@d1048bef9d (target=0, prob=0.00771208, correct=True): -machine vmport=auto: Fix handling of VMWare ioport emulation for xen
/*0  */ static void pc_machine_set_vmport(Object *obj, bool value, Error **errp)  // (0) 0.3594
/*2  */ {                                                                         // (3) 0.01563
/*4  */     PCMachineState *pcms = PC_MACHINE(obj);                               // (1) 0.2813
/*8  */     pcms->vmport = value;                                                 // (2) 0.1719
/*10 */ }                                                                         // (4) 0.01562
