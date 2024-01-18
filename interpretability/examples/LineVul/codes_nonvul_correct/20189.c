// commit message qemu@550830f935 (target=0, prob=0.010463486, correct=True): block: delete cow block driver
/*0  */ static int cow_probe(const uint8_t *buf, int buf_size, const char *filename)  // (2) 0.1553
/*2  */ {                                                                             // (8) 0.006211
/*4  */     const struct cow_header_v2 *cow_header = (const void *)buf;               // (3) 0.1366
/*8  */     if (buf_size >= sizeof(struct cow_header_v2) &&                           // (4) 0.1242
/*10 */         be32_to_cpu(cow_header->magic) == COW_MAGIC &&                        // (0) 0.1677
/*12 */         be32_to_cpu(cow_header->version) == COW_VERSION)                      // (1) 0.1615
/*14 */         return 100;                                                           // (5) 0.06211
/*16 */     else                                                                      // (7) 0.02484
/*18 */         return 0;                                                             // (6) 0.06211
/*20 */ }                                                                             // (9) 0.006211
