// commit message qemu@9be385980d (target=0, prob=0.09393848, correct=True): coccinelle: Remove unnecessary variables for function return value
/*0  */ static int64_t qemu_archipelago_getlength(BlockDriverState *bs)  // (0) 0.2588
/*2  */ {                                                                // (5) 0.01176
/*4  */     int64_t ret;                                                 // (3) 0.1059
/*6  */     BDRVArchipelagoState *s = bs->opaque;                        // (1) 0.2235
/*10 */     ret = archipelago_volume_info(s);                            // (2) 0.1765
/*12 */     return ret;                                                  // (4) 0.07059
/*14 */ }                                                                // (6) 0.01176
