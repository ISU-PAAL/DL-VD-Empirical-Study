// commit message qemu@35b6e94ba5 (target=0, prob=0.10760884, correct=True): s390: avoid always-true comparison in s390_pci_generate_fid()
/*0  */ static uint32_t s390_pci_generate_fid(Error **errp)  // (1) 0.1063
/*2  */ {                                                    // (13) 0.004831
/*4  */     uint32_t fid = 0;                                // (7) 0.05314
/*8  */     while (fid <= ZPCI_MAX_FID) {                    // (4) 0.08696
/*10 */         if (!s390_pci_find_dev_by_fid(fid)) {        // (0) 0.1353
/*12 */             return fid;                              // (5) 0.06763
/*14 */         }                                            // (9) 0.03865
/*18 */         if (fid == ZPCI_MAX_FID) {                   // (2) 0.1063
/*20 */             break;                                   // (6) 0.0628
/*22 */         }                                            // (10) 0.03865
/*26 */         fid++;                                       // (8) 0.04348
/*28 */     }                                                // (12) 0.01932
/*32 */     error_setg(errp, "no free fid could be found");  // (3) 0.09179
/*34 */     return 0;                                        // (11) 0.02899
/*36 */ }                                                    // (14) 0.004831
