// commit message qemu@4a1418e07b (target=0, prob=0.0706203, correct=True): Unbreak large mem support by removing kqemu
/*0  */ static void kqemu_record_flush(void)                      // (5) 0.07143
/*2  */ {                                                         // (11) 0.005495
/*4  */     PCRecord *r, *r_next;                                 // (6) 0.07143
/*6  */     int h;                                                // (9) 0.03297
/*10 */     for(h = 0; h < PC_REC_HASH_SIZE; h++) {               // (1) 0.1264
/*12 */         for(r = pc_rec_hash[h]; r != NULL; r = r_next) {  // (0) 0.1648
/*14 */             r_next = r->next;                             // (2) 0.1044
/*16 */             free(r);                                      // (4) 0.08242
/*18 */         }                                                 // (8) 0.04396
/*20 */         pc_rec_hash[h] = NULL;                            // (3) 0.0989
/*22 */     }                                                     // (10) 0.02198
/*24 */     nb_pc_records = 0;                                    // (7) 0.07143
/*26 */ }                                                         // (12) 0.005495
