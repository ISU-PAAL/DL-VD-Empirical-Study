// commit message qemu@ae261c86aa (target=0, prob=0.6135298, correct=False): VMDK: fix coding style
/*0  */ static int vmdk_parent_open(BlockDriverState *bs)                              // (7) 0.04678
/*2  */ {                                                                              // (18) 0.002924
/*4  */     char *p_name;                                                              // (14) 0.02632
/*6  */     char desc[DESC_SIZE + 1];                                                  // (11) 0.03801
/*8  */     BDRVVmdkState *s = bs->opaque;                                             // (6) 0.05556
/*12 */     desc[DESC_SIZE] = '\0';                                                    // (8) 0.04386
/*14 */     if (bdrv_pread(bs->file, s->desc_offset, desc, DESC_SIZE) != DESC_SIZE) {  // (0) 0.1023
/*16 */         return -1;                                                             // (13) 0.03216
/*18 */     }                                                                          // (16) 0.0117
/*22 */     if ((p_name = strstr(desc,"parentFileNameHint")) != NULL) {                // (4) 0.07018
/*24 */         char *end_name;                                                        // (12) 0.03801
/*28 */         p_name += sizeof("parentFileNameHint") + 1;                            // (5) 0.06433
/*30 */         if ((end_name = strchr(p_name,'\"')) == NULL)                          // (3) 0.07895
/*32 */             return -1;                                                         // (9) 0.04386
/*34 */         if ((end_name - p_name) > sizeof (bs->backing_file) - 1)               // (2) 0.08772
/*36 */             return -1;                                                         // (10) 0.04386
/*40 */         pstrcpy(bs->backing_file, end_name - p_name + 1, p_name);              // (1) 0.09649
/*42 */     }                                                                          // (17) 0.0117
/*46 */     return 0;                                                                  // (15) 0.01754
/*48 */ }                                                                              // (19) 0.002924
