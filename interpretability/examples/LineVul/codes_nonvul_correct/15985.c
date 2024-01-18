// commit message qemu@8f3a73bc57 (target=0, prob=0.021099944, correct=True): block: Add blk_dev_has_tray()
/*0  */ bool blk_dev_is_tray_open(BlockBackend *blk)                 // (2) 0.2
/*2  */ {                                                            // (5) 0.01
/*4  */     if (blk->dev_ops && blk->dev_ops->is_tray_open) {        // (1) 0.27
/*6  */         return blk->dev_ops->is_tray_open(blk->dev_opaque);  // (0) 0.3
/*8  */     }                                                        // (4) 0.04
/*10 */     return false;                                            // (3) 0.06
/*12 */ }                                                            // (6) 0.01
