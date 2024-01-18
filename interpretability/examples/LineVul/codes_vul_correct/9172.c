// commit message qemu@0f888bfadd (target=1, prob=0.99912065, correct=True): spapr_vty: lookup should only return valid VTY objects
/*0  */ VIOsPAPRDevice *vty_lookup(sPAPRMachineState *spapr, target_ulong reg)  // (0) 0.1303
/*1  */ {                                                                       // (11) 0.004202
/*2  */     VIOsPAPRDevice *sdev;                                               // (7) 0.05882
/*3  */     sdev = spapr_vio_find_by_reg(spapr->vio_bus, reg);                  // (1) 0.1261
/*4  */     if (!sdev && reg == 0) {                                            // (9) 0.05462
/*5  */         /* Hack for kernel early debug, which always specifies reg==0.  // (5) 0.08824
/*6  */          * We search all VIO devices, and grab the vty with the lowest  // (3) 0.1008
/*7  */          * reg.  This attempts to mimic existing PowerVM behaviour      // (6) 0.08403
/*8  */          * (early debug does work there, despite having no vty with     // (4) 0.09244
/*9  */          * reg==0. */                                                   // (8) 0.05882
/*10 */         return spapr_vty_get_default(spapr->vio_bus);                   // (2) 0.1176
/*11 */     return sdev;                                                        // (10) 0.02941
