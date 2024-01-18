// commit message qemu@e3f5ec2b5e (target=0, prob=0.31490457, correct=True): net: pass VLANClientState* as first arg to receive handlers
/*0   */ static void pcnet_receive(void *opaque, const uint8_t *buf, size_t size)        // (3) 0.05078
/*2   */ {                                                                               // (26) 0.001953
/*4   */     PCNetState *s = opaque;                                                     // (19) 0.02148
/*6   */     int is_padr = 0, is_bcast = 0, is_ladr = 0;                                 // (7) 0.04883
/*8   */     uint8_t buf1[60];                                                           // (17) 0.02344
/*10  */     int remaining;                                                              // (23) 0.01172
/*12  */     int crc_err = 0;                                                            // (20) 0.02148
/*16  */     if (CSR_DRX(s) || CSR_STOP(s) || CSR_SPND(s) || !size)                      // (0) 0.06836
/*18  */         return;                                                                 // (21) 0.01758
/*22  */ #ifdef PCNET_DEBUG                                                              // (22) 0.01367
/*24  */     printf("pcnet_receive size=%d\n", size);                                    // (10) 0.03711
/*26  */ #endif                                                                          // (25) 0.003906
/*30  */     /* if too small buffer, then expand it */                                   // (15) 0.02539
/*32  */     if (size < MIN_BUF_SIZE) {                                                  // (14) 0.0293
/*34  */         memcpy(buf1, buf, size);                                                // (11) 0.03516
/*36  */         memset(buf1 + size, 0, MIN_BUF_SIZE - size);                            // (6) 0.05078
/*38  */         buf = buf1;                                                             // (18) 0.02344
/*40  */         size = MIN_BUF_SIZE;                                                    // (13) 0.03125
/*42  */     }                                                                           // (24) 0.007812
/*46  */     if (CSR_PROM(s)                                                             // (16) 0.02539
/*48  */         || (is_padr=padr_match(s, buf, size))                                   // (8) 0.04883
/*50  */         || (is_bcast=padr_bcast(s, buf, size))                                  // (4) 0.05078
/*52  */         || (is_ladr=ladr_match(s, buf, size))) {                                // (5) 0.05078
/*56  */         pcnet_rdte_poll(s);                                                     // (12) 0.0332
/*60  */         if (!(CSR_CRST(s) & 0x8000) && s->rdra) {                               // (1) 0.05859
/*62  */             struct pcnet_RMD rmd;                                               // (9) 0.03906
/*64  */             int rcvrc = CSR_RCVRC(s)-1,i;                                       // (2) 0.05664
/*66  */             target_phys_addr_t nrda;                                            // 0.0
/*68  */             for (i = CSR_RCVRL(s)-1; i > 0; i--, rcvrc--) {                     // 0.0
/*70  */                 if (rcvrc <= 1)                                                 // 0.0
/*72  */                     rcvrc = CSR_RCVRL(s);                                       // 0.0
/*74  */                 nrda = s->rdra +                                                // 0.0
/*76  */                     (CSR_RCVRL(s) - rcvrc) *                                    // 0.0
/*78  */                     (BCR_SWSTYLE(s) ? 16 : 8 );                                 // 0.0
/*80  */                 RMDLOAD(&rmd, nrda);                                            // 0.0
/*82  */                 if (GET_FIELD(rmd.status, RMDS, OWN)) {                         // 0.0
/*84  */ #ifdef PCNET_DEBUG_RMD                                                          // 0.0
/*86  */                     printf("pcnet - scan buffer: RCVRC=%d PREV_RCVRC=%d\n",     // 0.0
/*88  */                                 rcvrc, CSR_RCVRC(s));                           // 0.0
/*90  */ #endif                                                                          // 0.0
/*92  */                     CSR_RCVRC(s) = rcvrc;                                       // 0.0
/*94  */                     pcnet_rdte_poll(s);                                         // 0.0
/*96  */                     break;                                                      // 0.0
/*98  */                 }                                                               // 0.0
/*100 */             }                                                                   // 0.0
/*102 */         }                                                                       // 0.0
/*106 */         if (!(CSR_CRST(s) & 0x8000)) {                                          // 0.0
/*108 */ #ifdef PCNET_DEBUG_RMD                                                          // 0.0
/*110 */             printf("pcnet - no buffer: RCVRC=%d\n", CSR_RCVRC(s));              // 0.0
/*112 */ #endif                                                                          // 0.0
/*114 */             s->csr[0] |= 0x1000; /* Set MISS flag */                            // 0.0
/*116 */             CSR_MISSC(s)++;                                                     // 0.0
/*118 */         } else {                                                                // 0.0
/*120 */             uint8_t *src = s->buffer;                                           // 0.0
/*122 */             target_phys_addr_t crda = CSR_CRDA(s);                              // 0.0
/*124 */             struct pcnet_RMD rmd;                                               // 0.0
/*126 */             int pktcount = 0;                                                   // 0.0
/*130 */             if (!s->looptest) {                                                 // 0.0
/*132 */                 memcpy(src, buf, size);                                         // 0.0
/*134 */                 /* no need to compute the CRC */                                // 0.0
/*136 */                 src[size] = 0;                                                  // 0.0
/*138 */                 src[size + 1] = 0;                                              // 0.0
/*140 */                 src[size + 2] = 0;                                              // 0.0
/*142 */                 src[size + 3] = 0;                                              // 0.0
/*144 */                 size += 4;                                                      // 0.0
/*146 */             } else if (s->looptest == PCNET_LOOPTEST_CRC ||                     // 0.0
/*148 */                        !CSR_DXMTFCS(s) || size < MIN_BUF_SIZE+4) {              // 0.0
/*150 */                 uint32_t fcs = ~0;                                              // 0.0
/*152 */                 uint8_t *p = src;                                               // 0.0
/*156 */                 while (p != &src[size])                                         // 0.0
/*158 */                     CRC(fcs, *p++);                                             // 0.0
/*160 */                 *(uint32_t *)p = htonl(fcs);                                    // 0.0
/*162 */                 size += 4;                                                      // 0.0
/*164 */             } else {                                                            // 0.0
/*166 */                 uint32_t fcs = ~0;                                              // 0.0
/*168 */                 uint8_t *p = src;                                               // 0.0
/*172 */                 while (p != &src[size-4])                                       // 0.0
/*174 */                     CRC(fcs, *p++);                                             // 0.0
/*176 */                 crc_err = (*(uint32_t *)p != htonl(fcs));                       // 0.0
/*178 */             }                                                                   // 0.0
/*182 */ #ifdef PCNET_DEBUG_MATCH                                                        // 0.0
/*184 */             PRINT_PKTHDR(buf);                                                  // 0.0
/*186 */ #endif                                                                          // 0.0
/*190 */             RMDLOAD(&rmd, PHYSADDR(s,crda));                                    // 0.0
/*192 */             /*if (!CSR_LAPPEN(s))*/                                             // 0.0
/*194 */                 SET_FIELD(&rmd.status, RMDS, STP, 1);                           // 0.0
/*198 */ #define PCNET_RECV_STORE() do {                                 \               // 0.0
/*200 */     int count = MIN(4096 - GET_FIELD(rmd.buf_length, RMDL, BCNT),remaining); \  // 0.0
/*202 */     target_phys_addr_t rbadr = PHYSADDR(s, rmd.rbadr);          \               // 0.0
/*204 */     s->phys_mem_write(s->dma_opaque, rbadr, src, count, CSR_BSWP(s)); \         // 0.0
/*206 */     src += count; remaining -= count;                           \               // 0.0
/*208 */     SET_FIELD(&rmd.status, RMDS, OWN, 0);                       \               // 0.0
/*210 */     RMDSTORE(&rmd, PHYSADDR(s,crda));                           \               // 0.0
/*212 */     pktcount++;                                                 \               // 0.0
/*214 */ } while (0)                                                                     // 0.0
/*218 */             remaining = size;                                                   // 0.0
/*220 */             PCNET_RECV_STORE();                                                 // 0.0
/*222 */             if ((remaining > 0) && CSR_NRDA(s)) {                               // 0.0
/*224 */                 target_phys_addr_t nrda = CSR_NRDA(s);                          // 0.0
/*226 */ #ifdef PCNET_DEBUG_RMD                                                          // 0.0
/*228 */                 PRINT_RMD(&rmd);                                                // 0.0
/*230 */ #endif                                                                          // 0.0
/*232 */                 RMDLOAD(&rmd, PHYSADDR(s,nrda));                                // 0.0
/*234 */                 if (GET_FIELD(rmd.status, RMDS, OWN)) {                         // 0.0
/*236 */                     crda = nrda;                                                // 0.0
/*238 */                     PCNET_RECV_STORE();                                         // 0.0
/*240 */ #ifdef PCNET_DEBUG_RMD                                                          // 0.0
/*242 */                     PRINT_RMD(&rmd);                                            // 0.0
/*244 */ #endif                                                                          // 0.0
/*246 */                     if ((remaining > 0) && (nrda=CSR_NNRD(s))) {                // 0.0
/*248 */                         RMDLOAD(&rmd, PHYSADDR(s,nrda));                        // 0.0
/*250 */                         if (GET_FIELD(rmd.status, RMDS, OWN)) {                 // 0.0
/*252 */                             crda = nrda;                                        // 0.0
/*254 */                             PCNET_RECV_STORE();                                 // 0.0
/*256 */                         }                                                       // 0.0
/*258 */                     }                                                           // 0.0
/*260 */                 }                                                               // 0.0
/*262 */             }                                                                   // 0.0
/*266 */ #undef PCNET_RECV_STORE                                                         // 0.0
/*270 */             RMDLOAD(&rmd, PHYSADDR(s,crda));                                    // 0.0
/*272 */             if (remaining == 0) {                                               // 0.0
/*274 */                 SET_FIELD(&rmd.msg_length, RMDM, MCNT, size);                   // 0.0
/*276 */                 SET_FIELD(&rmd.status, RMDS, ENP, 1);                           // 0.0
/*278 */                 SET_FIELD(&rmd.status, RMDS, PAM, !CSR_PROM(s) && is_padr);     // 0.0
/*280 */                 SET_FIELD(&rmd.status, RMDS, LFAM, !CSR_PROM(s) && is_ladr);    // 0.0
/*282 */                 SET_FIELD(&rmd.status, RMDS, BAM, !CSR_PROM(s) && is_bcast);    // 0.0
/*284 */                 if (crc_err) {                                                  // 0.0
/*286 */                     SET_FIELD(&rmd.status, RMDS, CRC, 1);                       // 0.0
/*288 */                     SET_FIELD(&rmd.status, RMDS, ERR, 1);                       // 0.0
/*290 */                 }                                                               // 0.0
/*292 */             } else {                                                            // 0.0
/*294 */                 SET_FIELD(&rmd.status, RMDS, OFLO, 1);                          // 0.0
/*296 */                 SET_FIELD(&rmd.status, RMDS, BUFF, 1);                          // 0.0
/*298 */                 SET_FIELD(&rmd.status, RMDS, ERR, 1);                           // 0.0
/*300 */             }                                                                   // 0.0
/*302 */             RMDSTORE(&rmd, PHYSADDR(s,crda));                                   // 0.0
/*304 */             s->csr[0] |= 0x0400;                                                // 0.0
/*308 */ #ifdef PCNET_DEBUG                                                              // 0.0
/*310 */             printf("RCVRC=%d CRDA=0x%08x BLKS=%d\n",                            // 0.0
/*312 */                 CSR_RCVRC(s), PHYSADDR(s,CSR_CRDA(s)), pktcount);               // 0.0
/*314 */ #endif                                                                          // 0.0
/*316 */ #ifdef PCNET_DEBUG_RMD                                                          // 0.0
/*318 */             PRINT_RMD(&rmd);                                                    // 0.0
/*320 */ #endif                                                                          // 0.0
/*324 */             while (pktcount--) {                                                // 0.0
/*326 */                 if (CSR_RCVRC(s) <= 1)                                          // 0.0
/*328 */                     CSR_RCVRC(s) = CSR_RCVRL(s);                                // 0.0
/*330 */                 else                                                            // 0.0
/*332 */                     CSR_RCVRC(s)--;                                             // 0.0
/*334 */             }                                                                   // 0.0
/*338 */             pcnet_rdte_poll(s);                                                 // 0.0
/*342 */         }                                                                       // 0.0
/*344 */     }                                                                           // 0.0
/*348 */     pcnet_poll(s);                                                              // 0.0
/*350 */     pcnet_update_irq(s);                                                        // 0.0
/*352 */ }                                                                               // 0.0
