// commit message qemu@5fe79386ba (target=0, prob=0.0070788106, correct=True): nvdimm acpi: initialize the resource used by NVDIMM ACPI
/*0  */ static bool pc_machine_get_nvdimm(Object *obj, Error **errp)  // (0) 0.3387
/*2  */ {                                                             // (3) 0.01613
/*4  */     PCMachineState *pcms = PC_MACHINE(obj);                   // (1) 0.2903
/*8  */     return pcms->nvdimm;                                      // (2) 0.1774
/*10 */ }                                                             // (4) 0.01613
