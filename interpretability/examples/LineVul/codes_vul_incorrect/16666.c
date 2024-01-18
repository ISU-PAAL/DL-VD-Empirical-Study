// commit message qemu@a38648290e (target=1, prob=0.4777765, correct=False): cpu_ioreq_pio, cpu_ioreq_move: introduce read_phys_req_item, write_phys_req_item
/*0  */ static void cpu_ioreq_pio(ioreq_t *req)                               // (10) 0.03711
/*2  */ {                                                                     // (22) 0.001953
/*4  */     int i, sign;                                                      // (20) 0.01562
/*8  */     sign = req->df ? -1 : 1;                                          // (16) 0.02734
/*12 */     if (req->dir == IOREQ_READ) {                                     // (15) 0.03125
/*14 */         if (!req->data_is_ptr) {                                      // (12) 0.03516
/*16 */             req->data = do_inp(req->addr, req->size);                 // (3) 0.05469
/*18 */         } else {                                                      // (18) 0.01953
/*20 */             uint32_t tmp;                                             // (14) 0.0332
/*24 */             for (i = 0; i < req->count; i++) {                        // (5) 0.05078
/*26 */                 tmp = do_inp(req->addr, req->size);                   // (2) 0.05859
/*28 */                 cpu_physical_memory_write(                            // (7) 0.04492
/*30 */                         req->data + (sign * i * (int64_t)req->size),  // (0) 0.08203
/*32 */                         (uint8_t *) &tmp, req->size);                 // (1) 0.07031
/*34 */             }                                                         // (17) 0.02344
/*36 */         }                                                             // (21) 0.01562
/*38 */     } else if (req->dir == IOREQ_WRITE) {                             // (11) 0.03711
/*40 */         if (!req->data_is_ptr) {                                      // (13) 0.03516
/*42 */             do_outp(req->addr, req->size, req->data);                 // (4) 0.05469
/*44 */         } else {                                                      // (19) 0.01953
/*46 */             for (i = 0; i < req->count; i++) {                        // (6) 0.05078
/*48 */                 uint32_t tmp = 0;                                     // (8) 0.04492
/*52 */                 cpu_physical_memory_read(                             // (9) 0.04492
/*54 */                         req->data + (sign * i * (int64_t)req->size),  // 0.0
/*56 */                         (uint8_t*) &tmp, req->size);                  // 0.0
/*58 */                 do_outp(req->addr, req->size, tmp);                   // 0.0
/*60 */             }                                                         // 0.0
/*62 */         }                                                             // 0.0
/*64 */     }                                                                 // 0.0
/*66 */ }                                                                     // 0.0
