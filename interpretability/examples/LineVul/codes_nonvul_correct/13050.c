// commit message qemu@fdfab37dfe (target=0, prob=0.4409928, correct=True): qcow2: Make distinction between zero cluster types obvious
/*0   */ static int check_oflag_copied(BlockDriverState *bs, BdrvCheckResult *res,        // (8) 0.04688
/*2   */                               BdrvCheckMode fix)                                 // (1) 0.07031
/*4   */ {                                                                                // (22) 0.001953
/*6   */     BDRVQcow2State *s = bs->opaque;                                              // (11) 0.03711
/*8   */     uint64_t *l2_table = qemu_blockalign(bs, s->cluster_size);                   // (6) 0.05664
/*10  */     int ret;                                                                     // (21) 0.01172
/*12  */     uint64_t refcount;                                                           // (17) 0.01953
/*14  */     int i, j;                                                                    // (18) 0.01562
/*18  */     for (i = 0; i < s->l1_size; i++) {                                           // (10) 0.04102
/*20  */         uint64_t l1_entry = s->l1_table[i];                                      // (7) 0.04883
/*22  */         uint64_t l2_offset = l1_entry & L1E_OFFSET_MASK;                         // (5) 0.06055
/*24  */         bool l2_dirty = false;                                                   // (12) 0.0293
/*28  */         if (!l2_offset) {                                                        // (13) 0.0293
/*30  */             continue;                                                            // (15) 0.02539
/*32  */         }                                                                        // (19) 0.01562
/*36  */         ret = qcow2_get_refcount(bs, l2_offset >> s->cluster_bits,               // (4) 0.0625
/*38  */                                  &refcount);                                     // (2) 0.07031
/*40  */         if (ret < 0) {                                                           // (14) 0.02734
/*42  */             /* don't print message nor increment check_errors */                 // (9) 0.04297
/*44  */             continue;                                                            // (16) 0.02539
/*46  */         }                                                                        // (20) 0.01562
/*48  */         if ((refcount == 1) != ((l1_entry & QCOW_OFLAG_COPIED) != 0)) {          // (3) 0.06836
/*50  */             fprintf(stderr, "%s OFLAG_COPIED L2 cluster: l1_index=%d "           // (0) 0.07422
/*52  */                     "l1_entry=%" PRIx64 " refcount=%" PRIu64 "\n",               // 0.0
/*54  */                     fix & BDRV_FIX_ERRORS ? "Repairing" :                        // 0.0
/*56  */                                             "ERROR",                             // 0.0
/*58  */                     i, l1_entry, refcount);                                      // 0.0
/*60  */             if (fix & BDRV_FIX_ERRORS) {                                         // 0.0
/*62  */                 s->l1_table[i] = refcount == 1                                   // 0.0
/*64  */                                ? l1_entry |  QCOW_OFLAG_COPIED                   // 0.0
/*66  */                                : l1_entry & ~QCOW_OFLAG_COPIED;                  // 0.0
/*68  */                 ret = qcow2_write_l1_entry(bs, i);                               // 0.0
/*70  */                 if (ret < 0) {                                                   // 0.0
/*72  */                     res->check_errors++;                                         // 0.0
/*74  */                     goto fail;                                                   // 0.0
/*76  */                 }                                                                // 0.0
/*78  */                 res->corruptions_fixed++;                                        // 0.0
/*80  */             } else {                                                             // 0.0
/*82  */                 res->corruptions++;                                              // 0.0
/*84  */             }                                                                    // 0.0
/*86  */         }                                                                        // 0.0
/*90  */         ret = bdrv_pread(bs->file, l2_offset, l2_table,                          // 0.0
/*92  */                          s->l2_size * sizeof(uint64_t));                         // 0.0
/*94  */         if (ret < 0) {                                                           // 0.0
/*96  */             fprintf(stderr, "ERROR: Could not read L2 table: %s\n",              // 0.0
/*98  */                     strerror(-ret));                                             // 0.0
/*100 */             res->check_errors++;                                                 // 0.0
/*102 */             goto fail;                                                           // 0.0
/*104 */         }                                                                        // 0.0
/*108 */         for (j = 0; j < s->l2_size; j++) {                                       // 0.0
/*110 */             uint64_t l2_entry = be64_to_cpu(l2_table[j]);                        // 0.0
/*112 */             uint64_t data_offset = l2_entry & L2E_OFFSET_MASK;                   // 0.0
/*114 */             QCow2ClusterType cluster_type = qcow2_get_cluster_type(l2_entry);    // 0.0
/*118 */             if ((cluster_type == QCOW2_CLUSTER_NORMAL) ||                        // 0.0
/*120 */                 ((cluster_type == QCOW2_CLUSTER_ZERO) && (data_offset != 0))) {  // 0.0
/*122 */                 ret = qcow2_get_refcount(bs,                                     // 0.0
/*124 */                                          data_offset >> s->cluster_bits,         // 0.0
/*126 */                                          &refcount);                             // 0.0
/*128 */                 if (ret < 0) {                                                   // 0.0
/*130 */                     /* don't print message nor increment check_errors */         // 0.0
/*132 */                     continue;                                                    // 0.0
/*134 */                 }                                                                // 0.0
/*136 */                 if ((refcount == 1) != ((l2_entry & QCOW_OFLAG_COPIED) != 0)) {  // 0.0
/*138 */                     fprintf(stderr, "%s OFLAG_COPIED data cluster: "             // 0.0
/*140 */                             "l2_entry=%" PRIx64 " refcount=%" PRIu64 "\n",       // 0.0
/*142 */                             fix & BDRV_FIX_ERRORS ? "Repairing" :                // 0.0
/*144 */                                                     "ERROR",                     // 0.0
/*146 */                             l2_entry, refcount);                                 // 0.0
/*148 */                     if (fix & BDRV_FIX_ERRORS) {                                 // 0.0
/*150 */                         l2_table[j] = cpu_to_be64(refcount == 1                  // 0.0
/*152 */                                     ? l2_entry |  QCOW_OFLAG_COPIED              // 0.0
/*154 */                                     : l2_entry & ~QCOW_OFLAG_COPIED);            // 0.0
/*156 */                         l2_dirty = true;                                         // 0.0
/*158 */                         res->corruptions_fixed++;                                // 0.0
/*160 */                     } else {                                                     // 0.0
/*162 */                         res->corruptions++;                                      // 0.0
/*164 */                     }                                                            // 0.0
/*166 */                 }                                                                // 0.0
/*168 */             }                                                                    // 0.0
/*170 */         }                                                                        // 0.0
/*174 */         if (l2_dirty) {                                                          // 0.0
/*176 */             ret = qcow2_pre_write_overlap_check(bs, QCOW2_OL_ACTIVE_L2,          // 0.0
/*178 */                                                 l2_offset, s->cluster_size);     // 0.0
/*180 */             if (ret < 0) {                                                       // 0.0
/*182 */                 fprintf(stderr, "ERROR: Could not write L2 table; metadata "     // 0.0
/*184 */                         "overlap check failed: %s\n", strerror(-ret));           // 0.0
/*186 */                 res->check_errors++;                                             // 0.0
/*188 */                 goto fail;                                                       // 0.0
/*190 */             }                                                                    // 0.0
/*194 */             ret = bdrv_pwrite(bs->file, l2_offset, l2_table,                     // 0.0
/*196 */                               s->cluster_size);                                  // 0.0
/*198 */             if (ret < 0) {                                                       // 0.0
/*200 */                 fprintf(stderr, "ERROR: Could not write L2 table: %s\n",         // 0.0
/*202 */                         strerror(-ret));                                         // 0.0
/*204 */                 res->check_errors++;                                             // 0.0
/*206 */                 goto fail;                                                       // 0.0
/*208 */             }                                                                    // 0.0
/*210 */         }                                                                        // 0.0
/*212 */     }                                                                            // 0.0
/*216 */     ret = 0;                                                                     // 0.0
/*220 */ fail:                                                                            // 0.0
/*222 */     qemu_vfree(l2_table);                                                        // 0.0
/*224 */     return ret;                                                                  // 0.0
/*226 */ }                                                                                // 0.0
