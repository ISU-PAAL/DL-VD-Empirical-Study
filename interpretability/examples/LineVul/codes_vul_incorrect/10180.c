// commit message qemu@338c25b692 (target=1, prob=0.38605028, correct=False): spapr: Fix integer overflow during migration (TCG)
/*0   */ static int htab_save_later_pass(QEMUFile *f, sPAPREnvironment *spapr,                       // (6) 0.05664
/*2   */                                 int64_t max_ns)                                             // (0) 0.07617
/*4   */ {                                                                                           // (24) 0.001953
/*6   */     bool final = max_ns < 0;                                                                // (20) 0.02344
/*8   */     int htabslots = HTAB_SIZE(spapr) / HASH_PTE_SIZE_64;                                    // (5) 0.05859
/*10  */     int examined = 0, sent = 0;                                                             // (21) 0.02344
/*12  */     int index = spapr->htab_save_index;                                                     // (9) 0.0332
/*14  */     int64_t starttime = qemu_clock_get_ns(QEMU_CLOCK_REALTIME);                             // (4) 0.06055
/*18  */     assert(!spapr->htab_first_pass);                                                        // (8) 0.0332
/*22  */     do {                                                                                    // (23) 0.009766
/*24  */         int chunkstart, invalidstart;                                                       // (14) 0.02734
/*28  */         /* Consume non-dirty HPTEs */                                                       // (10) 0.0332
/*30  */         while ((index < htabslots)                                                          // (11) 0.03125
/*32  */                && !HPTE_DIRTY(HPTE(spapr->htab, index))) {                                  // (1) 0.06836
/*34  */             index++;                                                                        // (16) 0.02539
/*36  */             examined++;                                                                     // (15) 0.02539
/*38  */         }                                                                                   // (22) 0.01562
/*42  */         chunkstart = index;                                                                 // (19) 0.02344
/*44  */         /* Consume valid dirty HPTEs */                                                     // (12) 0.03125
/*46  */         while ((index < htabslots)                                                          // (13) 0.03125
/*48  */                && HPTE_DIRTY(HPTE(spapr->htab, index))                                      // (3) 0.06445
/*50  */                && HPTE_VALID(HPTE(spapr->htab, index))) {                                   // (2) 0.06641
/*52  */             CLEAN_HPTE(HPTE(spapr->htab, index));                                           // (7) 0.05664
/*54  */             index++;                                                                        // (18) 0.02539
/*56  */             examined++;                                                                     // (17) 0.02539
/*58  */         }                                                                                   // 0.0
/*62  */         invalidstart = index;                                                               // 0.0
/*64  */         /* Consume invalid dirty HPTEs */                                                   // 0.0
/*66  */         while ((index < htabslots)                                                          // 0.0
/*68  */                && HPTE_DIRTY(HPTE(spapr->htab, index))                                      // 0.0
/*70  */                && !HPTE_VALID(HPTE(spapr->htab, index))) {                                  // 0.0
/*72  */             CLEAN_HPTE(HPTE(spapr->htab, index));                                           // 0.0
/*74  */             index++;                                                                        // 0.0
/*76  */             examined++;                                                                     // 0.0
/*78  */         }                                                                                   // 0.0
/*82  */         if (index > chunkstart) {                                                           // 0.0
/*84  */             int n_valid = invalidstart - chunkstart;                                        // 0.0
/*86  */             int n_invalid = index - invalidstart;                                           // 0.0
/*90  */             qemu_put_be32(f, chunkstart);                                                   // 0.0
/*92  */             qemu_put_be16(f, n_valid);                                                      // 0.0
/*94  */             qemu_put_be16(f, n_invalid);                                                    // 0.0
/*96  */             qemu_put_buffer(f, HPTE(spapr->htab, chunkstart),                               // 0.0
/*98  */                             HASH_PTE_SIZE_64 * n_valid);                                    // 0.0
/*100 */             sent += index - chunkstart;                                                     // 0.0
/*104 */             if (!final && (qemu_clock_get_ns(QEMU_CLOCK_REALTIME) - starttime) > max_ns) {  // 0.0
/*106 */                 break;                                                                      // 0.0
/*108 */             }                                                                               // 0.0
/*110 */         }                                                                                   // 0.0
/*114 */         if (examined >= htabslots) {                                                        // 0.0
/*116 */             break;                                                                          // 0.0
/*118 */         }                                                                                   // 0.0
/*122 */         if (index >= htabslots) {                                                           // 0.0
/*124 */             assert(index == htabslots);                                                     // 0.0
/*126 */             index = 0;                                                                      // 0.0
/*128 */         }                                                                                   // 0.0
/*130 */     } while ((examined < htabslots) && (!qemu_file_rate_limit(f) || final));                // 0.0
/*134 */     if (index >= htabslots) {                                                               // 0.0
/*136 */         assert(index == htabslots);                                                         // 0.0
/*138 */         index = 0;                                                                          // 0.0
/*140 */     }                                                                                       // 0.0
/*144 */     spapr->htab_save_index = index;                                                         // 0.0
/*148 */     return (examined >= htabslots) && (sent == 0) ? 1 : 0;                                  // 0.0
/*150 */ }                                                                                           // 0.0
