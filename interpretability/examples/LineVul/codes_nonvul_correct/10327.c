// commit message qemu@1b27d7a1e8 (target=0, prob=0.2634542, correct=True): hw/ivshmem.c don't check for negative values on unsigned data types
/*0  */ static void ivshmem_io_writel(void *opaque, target_phys_addr_t addr,            // (5) 0.04883
/*2  */                                                             uint32_t val)       // (0) 0.127
/*4  */ {                                                                               // (24) 0.001953
/*6  */     IVShmemState *s = opaque;                                                   // (19) 0.02344
/*10 */     uint64_t write_one = 1;                                                     // (12) 0.02539
/*12 */     uint16_t dest = val >> 16;                                                  // (13) 0.02539
/*14 */     uint16_t vector = val & 0xff;                                               // (11) 0.02734
/*18 */     addr &= 0xfc;                                                               // (21) 0.01953
/*22 */     IVSHMEM_DPRINTF("writing to addr " TARGET_FMT_plx "\n", addr);              // (3) 0.05859
/*24 */     switch (addr)                                                               // (22) 0.01367
/*26 */     {                                                                           // (23) 0.007812
/*28 */         case INTRMASK:                                                          // (14) 0.02539
/*30 */             ivshmem_IntrMask_write(s, val);                                     // (6) 0.04883
/*32 */             break;                                                              // (15) 0.02539
/*36 */         case INTRSTATUS:                                                        // (16) 0.02539
/*38 */             ivshmem_IntrStatus_write(s, val);                                   // (7) 0.04883
/*40 */             break;                                                              // (17) 0.02539
/*44 */         case DOORBELL:                                                          // (18) 0.02539
/*46 */             /* check that dest VM ID is reasonable */                           // (8) 0.03906
/*48 */             if ((dest < 0) || (dest > s->max_peer)) {                           // (4) 0.05469
/*50 */                 IVSHMEM_DPRINTF("Invalid destination VM ID (%d)\n", dest);      // (1) 0.07031
/*52 */                 break;                                                          // (10) 0.0332
/*54 */             }                                                                   // (20) 0.02344
/*58 */             /* check doorbell range */                                          // (9) 0.0332
/*60 */             if ((vector >= 0) && (vector < s->peers[dest].nb_eventfds)) {       // (2) 0.06836
/*62 */                 IVSHMEM_DPRINTF("Writing %" PRId64 " to VM %d on vector %d\n",  // 0.0
/*64 */                                                     write_one, dest, vector);   // 0.0
/*66 */                 if (write(s->peers[dest].eventfds[vector],                      // 0.0
/*68 */                                                     &(write_one), 8) != 8) {    // 0.0
/*70 */                     IVSHMEM_DPRINTF("error writing to eventfd\n");              // 0.0
/*72 */                 }                                                               // 0.0
/*74 */             }                                                                   // 0.0
/*76 */             break;                                                              // 0.0
/*78 */         default:                                                                // 0.0
/*80 */             IVSHMEM_DPRINTF("Invalid VM Doorbell VM %d\n", dest);               // 0.0
/*82 */     }                                                                           // 0.0
/*84 */ }                                                                               // 0.0
