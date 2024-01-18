// commit message FFmpeg@568e18b15e (target=1, prob=0.9989936, correct=True): integer overflows, heap corruption possible arbitrary code execution cannot be ruled out in some cases precautionary checks
/*0  */ static void read_sgi_header(ByteIOContext *f, SGIInfo *info)  // (1) 0.06364
/*1  */ {                                                             // (19) 0.00303
/*2  */     info->magic = (unsigned short) get_be16(f);               // (11) 0.05455
/*3  */     info->rle = get_byte(f);                                  // (14) 0.04242
/*4  */     info->bytes_per_channel = get_byte(f);                    // (12) 0.05152
/*5  */     info->dimension = (unsigned short)get_be16(f);            // (10) 0.05455
/*6  */     info->xsize = (unsigned short) get_be16(f);               // (4) 0.05758
/*7  */     info->ysize = (unsigned short) get_be16(f);               // (5) 0.05758
/*8  */     info->zsize = (unsigned short) get_be16(f);               // (6) 0.05758
/*9  */ #ifdef DEBUG                                                  // (17) 0.01212
/*10 */     printf("sgi header fields:\n");                           // (15) 0.03636
/*11 */     printf("  magic: %d\n", info->magic);                     // (13) 0.05152
/*12 */     printf("    rle: %d\n", info->rle);                       // (2) 0.06364
/*13 */     printf("    bpc: %d\n", info->bytes_per_channel);         // (0) 0.07273
/*14 */     printf("    dim: %d\n", info->dimension);                 // (3) 0.05758
/*15 */     printf("  xsize: %d\n", info->xsize);                     // (7) 0.05758
/*16 */     printf("  ysize: %d\n", info->ysize);                     // (8) 0.05758
/*17 */     printf("  zsize: %d\n", info->zsize);                     // (9) 0.05758
/*18 */ #endif                                                        // (18) 0.006061
/*19 */     return;                                                   // (16) 0.01515
/*20 */ }                                                             // (20) 0.00303
