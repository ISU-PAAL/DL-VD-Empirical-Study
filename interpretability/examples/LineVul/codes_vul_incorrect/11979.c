// commit message FFmpeg@5c720657c2 (target=1, prob=0.4143972, correct=False): mov: always check avio_read return value
/*0  */ static int mov_read_ftyp(MOVContext *c, AVIOContext *pb, MOVAtom atom)                // (5) 0.05078
/*2  */ {                                                                                     // (25) 0.001953
/*4  */     uint32_t minor_ver;                                                               // (22) 0.02148
/*6  */     int comp_brand_size;                                                              // (23) 0.01953
/*8  */     char minor_ver_str[11]; /* 32 bit integer -> 10 digits + null */                  // (8) 0.04297
/*10 */     char* comp_brands_str;                                                            // (20) 0.02344
/*12 */     uint8_t type[5] = {0};                                                            // (13) 0.0293
/*16 */     avio_read(pb, type, 4);                                                           // (17) 0.02734
/*18 */     if (strcmp(type, "qt  "))                                                         // (14) 0.0293
/*20 */         c->isom = 1;                                                                  // (18) 0.02734
/*22 */     av_log(c->fc, AV_LOG_DEBUG, "ISO: File Type Major Brand: %.4s\n",(char *)&type);  // (0) 0.07422
/*24 */     av_dict_set(&c->fc->metadata, "major_brand", type, 0);                            // (6) 0.04688
/*26 */     minor_ver = avio_rb32(pb); /* minor version */                                    // (9) 0.03711
/*28 */     snprintf(minor_ver_str, sizeof(minor_ver_str), "%"PRIu32"", minor_ver);           // (1) 0.06641
/*30 */     av_dict_set(&c->fc->metadata, "minor_version", minor_ver_str, 0);                 // (3) 0.05664
/*34 */     comp_brand_size = atom.size - 8;                                                  // (15) 0.0293
/*36 */     if (comp_brand_size < 0)                                                          // (19) 0.02539
/*38 */         return AVERROR_INVALIDDATA;                                                   // (11) 0.0332
/*40 */     comp_brands_str = av_malloc(comp_brand_size + 1); /* Add null terminator */       // (4) 0.05664
/*42 */     if (!comp_brands_str)                                                             // (21) 0.02344
/*44 */         return AVERROR(ENOMEM);                                                       // (12) 0.03125
/*46 */     avio_read(pb, comp_brands_str, comp_brand_size);                                  // (7) 0.04492
/*48 */     comp_brands_str[comp_brand_size] = 0;                                             // (10) 0.03711
/*50 */     av_dict_set(&c->fc->metadata, "compatible_brands", comp_brands_str, 0);           // (2) 0.05859
/*52 */     av_freep(&comp_brands_str);                                                       // (16) 0.0293
/*56 */     return 0;                                                                         // (24) 0.01172
/*58 */ }                                                                                     // 0.0
