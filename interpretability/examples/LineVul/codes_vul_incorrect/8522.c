// commit message qemu@d6b6abc51d (target=1, prob=0.40113765, correct=False): fw_cfg: fix memory corruption when all fw_cfg slots are used
/*0   */ void fw_cfg_add_file_callback(FWCfgState *s,  const char *filename,               // (6) 0.04883
/*2   */                               FWCfgCallback select_cb,                            // (3) 0.07227
/*4   */                               FWCfgWriteCallback write_cb,                        // (2) 0.07422
/*6   */                               void *callback_opaque,                              // (4) 0.07031
/*8   */                               void *data, size_t len, bool read_only)             // (0) 0.08398
/*10  */ {                                                                                 // (23) 0.001953
/*12  */     int i, index, count;                                                          // (15) 0.01953
/*14  */     size_t dsize;                                                                 // (18) 0.01758
/*16  */     MachineClass *mc = MACHINE_GET_CLASS(qdev_get_machine());                     // (7) 0.04492
/*18  */     int order = 0;                                                                // (20) 0.01563
/*22  */     if (!s->files) {                                                              // (16) 0.01953
/*24  */         dsize = sizeof(uint32_t) + sizeof(FWCfgFile) * fw_cfg_file_slots(s);      // (1) 0.07422
/*26  */         s->files = g_malloc0(dsize);                                              // (10) 0.03906
/*28  */         fw_cfg_add_bytes(s, FW_CFG_FILE_DIR, s->files, dsize);                    // (5) 0.06641
/*30  */     }                                                                             // (22) 0.007812
/*34  */     count = be32_to_cpu(s->files->count);                                         // (12) 0.03516
/*36  */     assert(count < fw_cfg_file_slots(s));                                         // (11) 0.03711
/*40  */     /* Find the insertion point. */                                               // (17) 0.01953
/*42  */     if (mc->legacy_fw_cfg_order) {                                                // (14) 0.0332
/*44  */         /*                                                                        // (21) 0.01562
/*46  */          * Sort by order. For files with the same order, we keep them             // (8) 0.04492
/*48  */          * in the sequence in which they were added.                              // (13) 0.03516
/*50  */          */                                                                       // (19) 0.01758
/*52  */         order = get_fw_cfg_order(s, filename);                                    // (9) 0.04102
/*54  */         for (index = count;                                                       // 0.0
/*56  */              index > 0 && order < s->entry_order[index - 1];                      // 0.0
/*58  */              index--);                                                            // 0.0
/*60  */     } else {                                                                      // 0.0
/*62  */         /* Sort by file name. */                                                  // 0.0
/*64  */         for (index = count;                                                       // 0.0
/*66  */              index > 0 && strcmp(filename, s->files->f[index - 1].name) < 0;      // 0.0
/*68  */              index--);                                                            // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     /*                                                                            // 0.0
/*76  */      * Move all the entries from the index point and after down one               // 0.0
/*78  */      * to create a slot for the new entry.  Because calculations are              // 0.0
/*80  */      * being done with the index, make it so that "i" is the current              // 0.0
/*82  */      * index and "i - 1" is the one being copied from, thus the                   // 0.0
/*84  */      * unusual start and end in the for statement.                                // 0.0
/*86  */      */                                                                           // 0.0
/*88  */     for (i = count + 1; i > index; i--) {                                         // 0.0
/*90  */         s->files->f[i] = s->files->f[i - 1];                                      // 0.0
/*92  */         s->files->f[i].select = cpu_to_be16(FW_CFG_FILE_FIRST + i);               // 0.0
/*94  */         s->entries[0][FW_CFG_FILE_FIRST + i] =                                    // 0.0
/*96  */             s->entries[0][FW_CFG_FILE_FIRST + i - 1];                             // 0.0
/*98  */         s->entry_order[i] = s->entry_order[i - 1];                                // 0.0
/*100 */     }                                                                             // 0.0
/*104 */     memset(&s->files->f[index], 0, sizeof(FWCfgFile));                            // 0.0
/*106 */     memset(&s->entries[0][FW_CFG_FILE_FIRST + index], 0, sizeof(FWCfgEntry));     // 0.0
/*110 */     pstrcpy(s->files->f[index].name, sizeof(s->files->f[index].name), filename);  // 0.0
/*112 */     for (i = 0; i <= count; i++) {                                                // 0.0
/*114 */         if (i != index &&                                                         // 0.0
/*116 */             strcmp(s->files->f[index].name, s->files->f[i].name) == 0) {          // 0.0
/*118 */             error_report("duplicate fw_cfg file name: %s",                        // 0.0
/*120 */                          s->files->f[index].name);                                // 0.0
/*122 */             exit(1);                                                              // 0.0
/*124 */         }                                                                         // 0.0
/*126 */     }                                                                             // 0.0
/*130 */     fw_cfg_add_bytes_callback(s, FW_CFG_FILE_FIRST + index,                       // 0.0
/*132 */                               select_cb, write_cb,                                // 0.0
/*134 */                               callback_opaque, data, len,                         // 0.0
/*136 */                               read_only);                                         // 0.0
/*140 */     s->files->f[index].size   = cpu_to_be32(len);                                 // 0.0
/*142 */     s->files->f[index].select = cpu_to_be16(FW_CFG_FILE_FIRST + index);           // 0.0
/*144 */     s->entry_order[index] = order;                                                // 0.0
/*146 */     trace_fw_cfg_add_file(s, index, s->files->f[index].name, len);                // 0.0
/*150 */     s->files->count = cpu_to_be32(count+1);                                       // 0.0
/*152 */ }                                                                                 // 0.0
