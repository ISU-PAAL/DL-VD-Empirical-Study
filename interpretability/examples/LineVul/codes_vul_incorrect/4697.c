// commit message qemu@4652b8f3e1 (target=1, prob=0.3626945, correct=False): qcow2: add support for LUKS encryption format
/*0   */ static int perform_cow(BlockDriverState *bs, QCowL2Meta *m)                     // (10) 0.03906
/*2   */ {                                                                               // (28) 0.001954
/*4   */     BDRVQcow2State *s = bs->opaque;                                             // (11) 0.03717
/*6   */     Qcow2COWRegion *start = &m->cow_start;                                      // (12) 0.03711
/*8   */     Qcow2COWRegion *end = &m->cow_end;                                          // (13) 0.03711
/*10  */     unsigned buffer_size;                                                       // (22) 0.01562
/*12  */     unsigned data_bytes = end->offset - (start->offset + start->nb_bytes);      // (5) 0.04492
/*14  */     bool merge_reads;                                                           // (23) 0.01562
/*16  */     uint8_t *start_buffer, *end_buffer;                                         // (16) 0.0332
/*18  */     QEMUIOVector qiov;                                                          // (19) 0.02148
/*20  */     int ret;                                                                    // (25) 0.01172
/*24  */     assert(start->nb_bytes <= UINT_MAX - end->nb_bytes);                        // (8) 0.04297
/*26  */     assert(start->nb_bytes + end->nb_bytes <= UINT_MAX - data_bytes);           // (2) 0.05078
/*28  */     assert(start->offset + start->nb_bytes <= end->offset);                     // (15) 0.03711
/*30  */     assert(!m->data_qiov || m->data_qiov->size == data_bytes);                  // (1) 0.05078
/*34  */     if (start->nb_bytes == 0 && end->nb_bytes == 0) {                           // (7) 0.04297
/*36  */         return 0;                                                               // (21) 0.01953
/*38  */     }                                                                           // (27) 0.007812
/*42  */     /* If we have to read both the start and end COW regions and the            // (14) 0.03711
/*44  */      * middle region is not too large then perform just one read                // (17) 0.03125
/*46  */      * operation */                                                             // (24) 0.01367
/*48  */     merge_reads = start->nb_bytes && end->nb_bytes && data_bytes <= 16384;      // (3) 0.05078
/*50  */     if (merge_reads) {                                                          // (20) 0.02148
/*52  */         buffer_size = start->nb_bytes + data_bytes + end->nb_bytes;             // (0) 0.05273
/*54  */     } else {                                                                    // (26) 0.01172
/*56  */         /* If we have to do two reads, add some padding in the middle           // (6) 0.04297
/*58  */          * if necessary to make sure that the end region is optimally           // (9) 0.04101
/*60  */          * aligned. */                                                          // (18) 0.02344
/*62  */         size_t align = bdrv_opt_mem_align(bs);                                  // (4) 0.04687
/*64  */         assert(align > 0 && align <= UINT_MAX);                                 // 0.0
/*66  */         assert(QEMU_ALIGN_UP(start->nb_bytes, align) <=                         // 0.0
/*68  */                UINT_MAX - end->nb_bytes);                                       // 0.0
/*70  */         buffer_size = QEMU_ALIGN_UP(start->nb_bytes, align) + end->nb_bytes;    // 0.0
/*72  */     }                                                                           // 0.0
/*76  */     /* Reserve a buffer large enough to store all the data that we're           // 0.0
/*78  */      * going to read */                                                         // 0.0
/*80  */     start_buffer = qemu_try_blockalign(bs, buffer_size);                        // 0.0
/*82  */     if (start_buffer == NULL) {                                                 // 0.0
/*84  */         return -ENOMEM;                                                         // 0.0
/*86  */     }                                                                           // 0.0
/*88  */     /* The part of the buffer where the end region is located */                // 0.0
/*90  */     end_buffer = start_buffer + buffer_size - end->nb_bytes;                    // 0.0
/*94  */     qemu_iovec_init(&qiov, 2 + (m->data_qiov ? m->data_qiov->niov : 0));        // 0.0
/*98  */     qemu_co_mutex_unlock(&s->lock);                                             // 0.0
/*100 */     /* First we read the existing data from both COW regions. We                // 0.0
/*102 */      * either read the whole region in one go, or the start and end             // 0.0
/*104 */      * regions separately. */                                                   // 0.0
/*106 */     if (merge_reads) {                                                          // 0.0
/*108 */         qemu_iovec_add(&qiov, start_buffer, buffer_size);                       // 0.0
/*110 */         ret = do_perform_cow_read(bs, m->offset, start->offset, &qiov);         // 0.0
/*112 */     } else {                                                                    // 0.0
/*114 */         qemu_iovec_add(&qiov, start_buffer, start->nb_bytes);                   // 0.0
/*116 */         ret = do_perform_cow_read(bs, m->offset, start->offset, &qiov);         // 0.0
/*118 */         if (ret < 0) {                                                          // 0.0
/*120 */             goto fail;                                                          // 0.0
/*122 */         }                                                                       // 0.0
/*126 */         qemu_iovec_reset(&qiov);                                                // 0.0
/*128 */         qemu_iovec_add(&qiov, end_buffer, end->nb_bytes);                       // 0.0
/*130 */         ret = do_perform_cow_read(bs, m->offset, end->offset, &qiov);           // 0.0
/*132 */     }                                                                           // 0.0
/*134 */     if (ret < 0) {                                                              // 0.0
/*136 */         goto fail;                                                              // 0.0
/*138 */     }                                                                           // 0.0
/*142 */     /* Encrypt the data if necessary before writing it */                       // 0.0
/*144 */     if (bs->encrypted) {                                                        // 0.0
/*146 */         if (!do_perform_cow_encrypt(bs, m->offset, start->offset,               // 0.0
/*148 */                                     start_buffer, start->nb_bytes) ||           // 0.0
/*150 */             !do_perform_cow_encrypt(bs, m->offset, end->offset,                 // 0.0
/*152 */                                     end_buffer, end->nb_bytes)) {               // 0.0
/*154 */             ret = -EIO;                                                         // 0.0
/*156 */             goto fail;                                                          // 0.0
/*158 */         }                                                                       // 0.0
/*160 */     }                                                                           // 0.0
/*164 */     /* And now we can write everything. If we have the guest data we            // 0.0
/*166 */      * can write everything in one single operation */                          // 0.0
/*168 */     if (m->data_qiov) {                                                         // 0.0
/*170 */         qemu_iovec_reset(&qiov);                                                // 0.0
/*172 */         if (start->nb_bytes) {                                                  // 0.0
/*174 */             qemu_iovec_add(&qiov, start_buffer, start->nb_bytes);               // 0.0
/*176 */         }                                                                       // 0.0
/*178 */         qemu_iovec_concat(&qiov, m->data_qiov, 0, data_bytes);                  // 0.0
/*180 */         if (end->nb_bytes) {                                                    // 0.0
/*182 */             qemu_iovec_add(&qiov, end_buffer, end->nb_bytes);                   // 0.0
/*184 */         }                                                                       // 0.0
/*186 */         /* NOTE: we have a write_aio blkdebug event here followed by            // 0.0
/*188 */          * a cow_write one in do_perform_cow_write(), but there's only          // 0.0
/*190 */          * one single I/O operation */                                          // 0.0
/*192 */         BLKDBG_EVENT(bs->file, BLKDBG_WRITE_AIO);                               // 0.0
/*194 */         ret = do_perform_cow_write(bs, m->alloc_offset, start->offset, &qiov);  // 0.0
/*196 */     } else {                                                                    // 0.0
/*198 */         /* If there's no guest data then write both COW regions separately */   // 0.0
/*200 */         qemu_iovec_reset(&qiov);                                                // 0.0
/*202 */         qemu_iovec_add(&qiov, start_buffer, start->nb_bytes);                   // 0.0
/*204 */         ret = do_perform_cow_write(bs, m->alloc_offset, start->offset, &qiov);  // 0.0
/*206 */         if (ret < 0) {                                                          // 0.0
/*208 */             goto fail;                                                          // 0.0
/*210 */         }                                                                       // 0.0
/*214 */         qemu_iovec_reset(&qiov);                                                // 0.0
/*216 */         qemu_iovec_add(&qiov, end_buffer, end->nb_bytes);                       // 0.0
/*218 */         ret = do_perform_cow_write(bs, m->alloc_offset, end->offset, &qiov);    // 0.0
/*220 */     }                                                                           // 0.0
/*224 */ fail:                                                                           // 0.0
/*226 */     qemu_co_mutex_lock(&s->lock);                                               // 0.0
/*230 */     /*                                                                          // 0.0
/*232 */      * Before we update the L2 table to actually point to the new cluster, we   // 0.0
/*234 */      * need to be sure that the refcounts have been increased and COW was       // 0.0
/*236 */      * handled.                                                                 // 0.0
/*238 */      */                                                                         // 0.0
/*240 */     if (ret == 0) {                                                             // 0.0
/*242 */         qcow2_cache_depends_on_flush(s->l2_table_cache);                        // 0.0
/*244 */     }                                                                           // 0.0
/*248 */     qemu_vfree(start_buffer);                                                   // 0.0
/*250 */     qemu_iovec_destroy(&qiov);                                                  // 0.0
/*252 */     return ret;                                                                 // 0.0
/*254 */ }                                                                               // 0.0
