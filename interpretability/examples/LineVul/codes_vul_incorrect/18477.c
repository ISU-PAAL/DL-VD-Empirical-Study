// commit message qemu@ef4c9fc854 (target=1, prob=0.42987487, correct=False): trace: remove the TraceEventID and TraceEventVCPUID enums
/*0  */ int trace_record_start(TraceBufferRecord *rec, TraceEventID event, size_t datasize)  // (6) 0.04883
/*2  */ {                                                                                    // (22) 0.001953
/*4  */     unsigned int idx, rec_off, old_idx, new_idx;                                     // (9) 0.04297
/*6  */     uint32_t rec_len = sizeof(TraceRecord) + datasize;                               // (10) 0.04102
/*8  */     uint64_t event_u64 = event;                                                      // (17) 0.02734
/*10 */     uint64_t timestamp_ns = get_clock();                                             // (15) 0.0293
/*14 */     do {                                                                             // (21) 0.009766
/*16 */         old_idx = g_atomic_int_get(&trace_idx);                                      // (7) 0.04883
/*18 */         smp_rmb();                                                                   // (18) 0.02539
/*20 */         new_idx = old_idx + rec_len;                                                 // (11) 0.04102
/*24 */         if (new_idx - writeout_idx > TRACE_BUF_LEN) {                                // (3) 0.05859
/*26 */             /* Trace Buffer Full, Event dropped ! */                                 // (12) 0.03906
/*28 */             g_atomic_int_inc(&dropped_events);                                       // (8) 0.04687
/*30 */             return -ENOSPC;                                                          // (14) 0.0332
/*32 */         }                                                                            // (20) 0.01562
/*34 */     } while (!g_atomic_int_compare_and_exchange(&trace_idx, old_idx, new_idx));      // (0) 0.06836
/*38 */     idx = old_idx % TRACE_BUF_LEN;                                                   // (13) 0.03906
/*42 */     rec_off = idx;                                                                   // (19) 0.01953
/*44 */     rec_off = write_to_buffer(rec_off, &event_u64, sizeof(event_u64));               // (2) 0.05859
/*46 */     rec_off = write_to_buffer(rec_off, &timestamp_ns, sizeof(timestamp_ns));         // (1) 0.05859
/*48 */     rec_off = write_to_buffer(rec_off, &rec_len, sizeof(rec_len));                   // (5) 0.05469
/*50 */     rec_off = write_to_buffer(rec_off, &trace_pid, sizeof(trace_pid));               // (4) 0.05469
/*54 */     rec->tbuf_idx = idx;                                                             // (16) 0.02734
/*56 */     rec->rec_off  = (idx + sizeof(TraceRecord)) % TRACE_BUF_LEN;                     // 0.0
/*58 */     return 0;                                                                        // 0.0
/*60 */ }                                                                                    // 0.0
