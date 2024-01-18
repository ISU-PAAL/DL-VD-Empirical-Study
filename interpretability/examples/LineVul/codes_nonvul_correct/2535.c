// commit message qemu@1f8431f42d (target=0, prob=0.010722853, correct=True): q35: Check propery to determine if iommu is set
/*0 */ bool machine_iommu(MachineState *machine)  // (0) 0.375
/*2 */ {                                          // (2) 0.03125
/*4 */     return machine->iommu;                 // (1) 0.3125
/*6 */ }                                          // (3) 0.03125
