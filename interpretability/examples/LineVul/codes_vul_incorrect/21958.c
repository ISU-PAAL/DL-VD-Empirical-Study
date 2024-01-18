// commit message qemu@cdad4bd894 (target=1, prob=0.040830232, correct=False): Change default werror semantics from "report" to "enospc"
/*0  */ BlockInterfaceErrorAction drive_get_onerror(BlockDriverState *bdrv)  // (2) 0.161
/*2  */ {                                                                    // (6) 0.008475
/*4  */     int index;                                                       // (5) 0.05085
/*8  */     for (index = 0; index < nb_drives; index++)                      // (3) 0.161
/*10 */         if (drives_table[index].bdrv == bdrv)                        // (0) 0.2034
/*12 */             return drives_table[index].onerror;                      // (1) 0.178
/*16 */     return BLOCK_ERR_REPORT;                                         // (4) 0.1102
/*18 */ }                                                                    // (7) 0.008475
