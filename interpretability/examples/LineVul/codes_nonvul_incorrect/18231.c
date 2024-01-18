// commit message qemu@4a1418e07b (target=0, prob=0.5551846, correct=False): Unbreak large mem support by removing kqemu
/*0  */ void kqemu_record_dump(void)                                   // (16) 0.02344
/*2  */ {                                                              // (29) 0.001953
/*4  */     PCRecord **pr, *r;                                         // (17) 0.02148
/*6  */     int i, h;                                                  // (20) 0.01562
/*8  */     FILE *f;                                                   // (23) 0.01367
/*10 */     int64_t total, sum;                                        // (18) 0.02148
/*14 */     pr = malloc(sizeof(PCRecord *) * nb_pc_records);           // (4) 0.04492
/*16 */     i = 0;                                                     // (24) 0.01367
/*18 */     total = 0;                                                 // (25) 0.01367
/*20 */     for(h = 0; h < PC_REC_HASH_SIZE; h++) {                    // (5) 0.04492
/*22 */         for(r = pc_rec_hash[h]; r != NULL; r = r->next) {      // (2) 0.05859
/*24 */             pr[i++] = r;                                       // (10) 0.03711
/*26 */             total += r->count;                                 // (13) 0.0332
/*28 */         }                                                      // (21) 0.01562
/*30 */     }                                                          // (27) 0.007812
/*32 */     qsort(pr, nb_pc_records, sizeof(PCRecord *), pc_rec_cmp);  // (3) 0.05469
/*36 */     f = fopen("/tmp/kqemu.stats", "w");                        // (7) 0.04102
/*38 */     if (!f) {                                                  // (22) 0.01562
/*40 */         perror("/tmp/kqemu.stats");                            // (9) 0.03906
/*42 */         exit(1);                                               // (19) 0.02148
/*44 */     }                                                          // (28) 0.007812
/*46 */     fprintf(f, "total: %" PRId64 "\n", total);                 // (8) 0.04102
/*48 */     sum = 0;                                                   // (26) 0.01367
/*50 */     for(i = 0; i < nb_pc_records; i++) {                       // (6) 0.04297
/*52 */         r = pr[i];                                             // (14) 0.02539
/*54 */         sum += r->count;                                       // (15) 0.02539
/*56 */         fprintf(f, "%08lx: %" PRId64 " %0.2f%% %0.2f%%\n",     // (0) 0.07422
/*58 */                 r->pc,                                         // (11) 0.03711
/*60 */                 r->count,                                      // (12) 0.03711
/*62 */                 (double)r->count / (double)total * 100.0,      // (1) 0.06055
/*64 */                 (double)sum / (double)total * 100.0);          // 0.0
/*66 */     }                                                          // 0.0
/*68 */     fclose(f);                                                 // 0.0
/*70 */     free(pr);                                                  // 0.0
/*74 */     kqemu_record_flush();                                      // 0.0
/*76 */ }                                                              // 0.0
