// commit message FFmpeg@138568e9da (target=0, prob=0.4727752, correct=True): downgrade mov negative ctts log message to warning, patch by Art Clarke, aclarke at vlideshow dot com
/*0  */ static int mov_read_ctts(MOVContext *c, ByteIOContext *pb, MOV_atom_t atom)         // (2) 0.05469
/*2  */ {                                                                                   // (25) 0.001953
/*4  */     AVStream *st = c->fc->streams[c->fc->nb_streams-1];                             // (5) 0.05078
/*6  */     MOVStreamContext *sc = st->priv_data;                                           // (13) 0.0293
/*8  */     unsigned int i, entries;                                                        // (23) 0.01758
/*12 */     get_byte(pb); /* version */                                                     // (17) 0.02344
/*14 */     get_be24(pb); /* flags */                                                       // (15) 0.02539
/*16 */     entries = get_be32(pb);                                                         // (18) 0.02344
/*18 */     if(entries >= UINT_MAX / sizeof(MOV_stts_t))                                    // (6) 0.04492
/*20 */         return -1;                                                                  // (22) 0.02148
/*24 */     sc->ctts_count = entries;                                                       // (20) 0.02344
/*26 */     sc->ctts_data = av_malloc(entries * sizeof(MOV_stts_t));                        // (4) 0.05469
/*28 */     if (!sc->ctts_data)                                                             // (19) 0.02344
/*30 */         return -1;                                                                  // (21) 0.02148
/*32 */     dprintf(c->fc, "track[%i].ctts.entries = %i\n", c->fc->nb_streams-1, entries);  // (0) 0.07812
/*36 */     for(i=0; i<entries; i++) {                                                      // (12) 0.0332
/*38 */         int count    =get_be32(pb);                                                 // (9) 0.03906
/*40 */         int duration =get_be32(pb);                                                 // (11) 0.0332
/*44 */         if (duration < 0) {                                                         // (14) 0.02734
/*46 */             av_log(c->fc, AV_LOG_ERROR, "negative ctts, ignoring\n");               // (1) 0.06836
/*48 */             sc->ctts_count = 0;                                                     // (10) 0.03906
/*50 */             url_fskip(pb, 8 * (entries - i - 1));                                   // (3) 0.05469
/*52 */             break;                                                                  // (16) 0.02539
/*54 */         }                                                                           // (24) 0.01562
/*56 */         sc->ctts_data[i].count   = count;                                           // (7) 0.04297
/*58 */         sc->ctts_data[i].duration= duration;                                        // (8) 0.03906
/*62 */         sc->time_rate= ff_gcd(sc->time_rate, duration);                             // 0.0
/*64 */     }                                                                               // 0.0
/*66 */     return 0;                                                                       // 0.0
/*68 */ }                                                                                   // 0.0
