// commit message FFmpeg@bf252f7f6f (target=0, prob=0.5234058, correct=False): prevent reading more than container atom size, fix broken file broken_by_rev15830.MOV, fix #818
/*0  */ static int mov_read_udta_string(MOVContext *c, ByteIOContext *pb, MOVAtom atom)  // (1) 0.05469
/*2  */ {                                                                                // (27) 0.001953
/*4  */     char *str = NULL;                                                            // (23) 0.01758
/*6  */     int size;                                                                    // (24) 0.01172
/*8  */     uint16_t str_size;                                                           // (21) 0.02148
/*12 */     if (c->itunes_metadata) {                                                    // (19) 0.02539
/*14 */         int data_size = get_be32(pb);                                            // (10) 0.03711
/*16 */         int tag = get_le32(pb);                                                  // (17) 0.0332
/*18 */         if (tag == MKTAG('d','a','t','a')) {                                     // (5) 0.04688
/*20 */             get_be32(pb); // type                                                // (8) 0.03906
/*22 */             get_be32(pb); // unknown                                             // (9) 0.03906
/*24 */             str_size = data_size - 16;                                           // (6) 0.04102
/*26 */         } else return 0;                                                         // (20) 0.02344
/*28 */     } else {                                                                     // (25) 0.01172
/*30 */         str_size = get_be16(pb); // string length                                // (7) 0.04102
/*32 */         get_be16(pb); // language                                                // (18) 0.03125
/*34 */     }                                                                            // (26) 0.007812
/*36 */     switch (atom.type) {                                                         // (22) 0.01953
/*38 */     case MKTAG(0xa9,'n','a','m'):                                                // (11) 0.03516
/*40 */         str = c->fc->title; size = sizeof(c->fc->title); break;                  // (2) 0.05273
/*42 */     case MKTAG(0xa9,'A','R','T'):                                                // (12) 0.03516
/*44 */     case MKTAG(0xa9,'w','r','t'):                                                // (13) 0.03516
/*46 */         str = c->fc->author; size = sizeof(c->fc->author); break;                // (3) 0.05273
/*48 */     case MKTAG(0xa9,'c','p','y'):                                                // (14) 0.03516
/*50 */         str = c->fc->copyright; size = sizeof(c->fc->copyright); break;          // (0) 0.05664
/*52 */     case MKTAG(0xa9,'c','m','t'):                                                // (15) 0.03516
/*54 */     case MKTAG(0xa9,'i','n','f'):                                                // (16) 0.03516
/*56 */         str = c->fc->comment; size = sizeof(c->fc->comment); break;              // (4) 0.05273
/*58 */     case MKTAG(0xa9,'a','l','b'):                                                // 0.0
/*60 */         str = c->fc->album; size = sizeof(c->fc->album); break;                  // 0.0
/*62 */     }                                                                            // 0.0
/*64 */     if (!str)                                                                    // 0.0
/*66 */         return 0;                                                                // 0.0
/*68 */     get_buffer(pb, str, FFMIN(size, str_size));                                  // 0.0
/*70 */     dprintf(c->fc, "%.4s %s\n", (char*)&atom.type, str);                         // 0.0
/*72 */     return 0;                                                                    // 0.0
/*74 */ }                                                                                // 0.0
