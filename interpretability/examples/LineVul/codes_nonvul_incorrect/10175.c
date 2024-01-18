// commit message FFmpeg@02055b6d40 (target=0, prob=0.6804334, correct=False): vorbisdec: check memory allocations
/*0   */ static int vorbis_parse_setup_hdr_codebooks(vorbis_context *vc)                                                                                                         // (11) 0.04492
/*2   */ {                                                                                                                                                                       // (21) 0.001953
/*4   */     unsigned cb;                                                                                                                                                        // (20) 0.01367
/*6   */     uint8_t  *tmp_vlc_bits;                                                                                                                                             // (15) 0.03125
/*8   */     uint32_t *tmp_vlc_codes;                                                                                                                                            // (17) 0.0293
/*10  */     GetBitContext *gb = &vc->gb;                                                                                                                                        // (18) 0.02734
/*12  */     uint16_t *codebook_multiplicands;                                                                                                                                   // (16) 0.0293
/*14  */     int ret = 0;                                                                                                                                                        // (19) 0.01562
/*18  */     vc->codebook_count = get_bits(gb, 8) + 1;                                                                                                                           // (13) 0.04297
/*22  */     av_dlog(NULL, " Codebooks: %d \n", vc->codebook_count);                                                                                                             // (6) 0.05273
/*26  */     vc->codebooks = av_mallocz(vc->codebook_count * sizeof(*vc->codebooks));                                                                                            // (4) 0.05664
/*28  */     tmp_vlc_bits  = av_mallocz(V_MAX_VLCS * sizeof(*tmp_vlc_bits));                                                                                                     // (1) 0.06445
/*30  */     tmp_vlc_codes = av_mallocz(V_MAX_VLCS * sizeof(*tmp_vlc_codes));                                                                                                    // (2) 0.0625
/*32  */     codebook_multiplicands = av_malloc(V_MAX_VLCS * sizeof(*codebook_multiplicands));                                                                                   // (3) 0.06055
/*36  */     for (cb = 0; cb < vc->codebook_count; ++cb) {                                                                                                                       // (10) 0.04688
/*38  */         vorbis_codebook *codebook_setup = &vc->codebooks[cb];                                                                                                           // (5) 0.05273
/*40  */         unsigned ordered, t, entries, used_entries = 0;                                                                                                                 // (14) 0.04102
/*44  */         av_dlog(NULL, " %u. Codebook\n", cb);                                                                                                                           // (8) 0.05078
/*48  */         if (get_bits(gb, 24) != 0x564342) {                                                                                                                             // (9) 0.04883
/*50  */             av_log(vc->avctx, AV_LOG_ERROR,                                                                                                                             // (7) 0.05078
/*52  */                    " %u. Codebook setup data corrupt.\n", cb);                                                                                                          // (0) 0.06641
/*54  */             ret = AVERROR_INVALIDDATA;                                                                                                                                  // (12) 0.04297
/*56  */             goto error;                                                                                                                                                 // 0.0
/*58  */         }                                                                                                                                                               // 0.0
/*62  */         codebook_setup->dimensions=get_bits(gb, 16);                                                                                                                    // 0.0
/*64  */         if (codebook_setup->dimensions > 16 || codebook_setup->dimensions == 0) {                                                                                       // 0.0
/*66  */             av_log(vc->avctx, AV_LOG_ERROR,                                                                                                                             // 0.0
/*68  */                    " %u. Codebook's dimension is invalid (%d).\n",                                                                                                      // 0.0
/*70  */                    cb, codebook_setup->dimensions);                                                                                                                     // 0.0
/*72  */             ret = AVERROR_INVALIDDATA;                                                                                                                                  // 0.0
/*74  */             goto error;                                                                                                                                                 // 0.0
/*76  */         }                                                                                                                                                               // 0.0
/*78  */         entries = get_bits(gb, 24);                                                                                                                                     // 0.0
/*80  */         if (entries > V_MAX_VLCS) {                                                                                                                                     // 0.0
/*82  */             av_log(vc->avctx, AV_LOG_ERROR,                                                                                                                             // 0.0
/*84  */                    " %u. Codebook has too many entries (%u).\n",                                                                                                        // 0.0
/*86  */                    cb, entries);                                                                                                                                        // 0.0
/*88  */             ret = AVERROR_INVALIDDATA;                                                                                                                                  // 0.0
/*90  */             goto error;                                                                                                                                                 // 0.0
/*92  */         }                                                                                                                                                               // 0.0
/*96  */         ordered = get_bits1(gb);                                                                                                                                        // 0.0
/*100 */         av_dlog(NULL, " codebook_dimensions %d, codebook_entries %u\n",                                                                                                 // 0.0
/*102 */                 codebook_setup->dimensions, entries);                                                                                                                   // 0.0
/*106 */         if (!ordered) {                                                                                                                                                 // 0.0
/*108 */             unsigned ce, flag;                                                                                                                                          // 0.0
/*110 */             unsigned sparse = get_bits1(gb);                                                                                                                            // 0.0
/*114 */             av_dlog(NULL, " not ordered \n");                                                                                                                           // 0.0
/*118 */             if (sparse) {                                                                                                                                               // 0.0
/*120 */                 av_dlog(NULL, " sparse \n");                                                                                                                            // 0.0
/*124 */                 used_entries = 0;                                                                                                                                       // 0.0
/*126 */                 for (ce = 0; ce < entries; ++ce) {                                                                                                                      // 0.0
/*128 */                     flag = get_bits1(gb);                                                                                                                               // 0.0
/*130 */                     if (flag) {                                                                                                                                         // 0.0
/*132 */                         tmp_vlc_bits[ce] = get_bits(gb, 5) + 1;                                                                                                         // 0.0
/*134 */                         ++used_entries;                                                                                                                                 // 0.0
/*136 */                     } else                                                                                                                                              // 0.0
/*138 */                         tmp_vlc_bits[ce] = 0;                                                                                                                           // 0.0
/*140 */                 }                                                                                                                                                       // 0.0
/*142 */             } else {                                                                                                                                                    // 0.0
/*144 */                 av_dlog(NULL, " not sparse \n");                                                                                                                        // 0.0
/*148 */                 used_entries = entries;                                                                                                                                 // 0.0
/*150 */                 for (ce = 0; ce < entries; ++ce)                                                                                                                        // 0.0
/*152 */                     tmp_vlc_bits[ce] = get_bits(gb, 5) + 1;                                                                                                             // 0.0
/*154 */             }                                                                                                                                                           // 0.0
/*156 */         } else {                                                                                                                                                        // 0.0
/*158 */             unsigned current_entry  = 0;                                                                                                                                // 0.0
/*160 */             unsigned current_length = get_bits(gb, 5) + 1;                                                                                                              // 0.0
/*164 */             av_dlog(NULL, " ordered, current length: %u\n", current_length);  //FIXME                                                                                   // 0.0
/*168 */             used_entries = entries;                                                                                                                                     // 0.0
/*170 */             for (; current_entry < used_entries && current_length <= 32; ++current_length) {                                                                            // 0.0
/*172 */                 unsigned i, number;                                                                                                                                     // 0.0
/*176 */                 av_dlog(NULL, " number bits: %u ", ilog(entries - current_entry));                                                                                      // 0.0
/*180 */                 number = get_bits(gb, ilog(entries - current_entry));                                                                                                   // 0.0
/*184 */                 av_dlog(NULL, " number: %u\n", number);                                                                                                                 // 0.0
/*188 */                 for (i = current_entry; i < number+current_entry; ++i)                                                                                                  // 0.0
/*190 */                     if (i < used_entries)                                                                                                                               // 0.0
/*192 */                         tmp_vlc_bits[i] = current_length;                                                                                                               // 0.0
/*196 */                 current_entry+=number;                                                                                                                                  // 0.0
/*198 */             }                                                                                                                                                           // 0.0
/*200 */             if (current_entry>used_entries) {                                                                                                                           // 0.0
/*202 */                 av_log(vc->avctx, AV_LOG_ERROR, " More codelengths than codes in codebook. \n");                                                                        // 0.0
/*204 */                 ret = AVERROR_INVALIDDATA;                                                                                                                              // 0.0
/*206 */                 goto error;                                                                                                                                             // 0.0
/*208 */             }                                                                                                                                                           // 0.0
/*210 */         }                                                                                                                                                               // 0.0
/*214 */         codebook_setup->lookup_type = get_bits(gb, 4);                                                                                                                  // 0.0
/*218 */         av_dlog(NULL, " lookup type: %d : %s \n", codebook_setup->lookup_type,                                                                                          // 0.0
/*220 */                 codebook_setup->lookup_type ? "vq" : "no lookup");                                                                                                      // 0.0
/*224 */ // If the codebook is used for (inverse) VQ, calculate codevectors.                                                                                                     // 0.0
/*228 */         if (codebook_setup->lookup_type == 1) {                                                                                                                         // 0.0
/*230 */             unsigned i, j, k;                                                                                                                                           // 0.0
/*232 */             unsigned codebook_lookup_values = ff_vorbis_nth_root(entries, codebook_setup->dimensions);                                                                  // 0.0
/*236 */             float codebook_minimum_value = vorbisfloat2float(get_bits_long(gb, 32));                                                                                    // 0.0
/*238 */             float codebook_delta_value   = vorbisfloat2float(get_bits_long(gb, 32));                                                                                    // 0.0
/*240 */             unsigned codebook_value_bits = get_bits(gb, 4) + 1;                                                                                                         // 0.0
/*242 */             unsigned codebook_sequence_p = get_bits1(gb);                                                                                                               // 0.0
/*246 */             av_dlog(NULL, " We expect %d numbers for building the codevectors. \n",                                                                                     // 0.0
/*248 */                     codebook_lookup_values);                                                                                                                            // 0.0
/*250 */             av_dlog(NULL, "  delta %f minmum %f \n",                                                                                                                    // 0.0
/*252 */                     codebook_delta_value, codebook_minimum_value);                                                                                                      // 0.0
/*256 */             for (i = 0; i < codebook_lookup_values; ++i) {                                                                                                              // 0.0
/*258 */                 codebook_multiplicands[i] = get_bits(gb, codebook_value_bits);                                                                                          // 0.0
/*262 */                 av_dlog(NULL, " multiplicands*delta+minmum : %e \n",                                                                                                    // 0.0
/*264 */                         (float)codebook_multiplicands[i] * codebook_delta_value + codebook_minimum_value);                                                              // 0.0
/*266 */                 av_dlog(NULL, " multiplicand %u\n", codebook_multiplicands[i]);                                                                                         // 0.0
/*268 */             }                                                                                                                                                           // 0.0
/*272 */ // Weed out unused vlcs and build codevector vector                                                                                                                     // 0.0
/*274 */             codebook_setup->codevectors = used_entries ? av_mallocz(used_entries *                                                                                      // 0.0
/*276 */                                                                     codebook_setup->dimensions *                                                                        // 0.0
/*278 */                                                                     sizeof(*codebook_setup->codevectors))                                                               // 0.0
/*280 */                                                        : NULL;                                                                                                          // 0.0
/*282 */             for (j = 0, i = 0; i < entries; ++i) {                                                                                                                      // 0.0
/*284 */                 unsigned dim = codebook_setup->dimensions;                                                                                                              // 0.0
/*288 */                 if (tmp_vlc_bits[i]) {                                                                                                                                  // 0.0
/*290 */                     float last = 0.0;                                                                                                                                   // 0.0
/*292 */                     unsigned lookup_offset = i;                                                                                                                         // 0.0
/*296 */                     av_dlog(vc->avctx, "Lookup offset %u ,", i);                                                                                                        // 0.0
/*300 */                     for (k = 0; k < dim; ++k) {                                                                                                                         // 0.0
/*302 */                         unsigned multiplicand_offset = lookup_offset % codebook_lookup_values;                                                                          // 0.0
/*304 */                         codebook_setup->codevectors[j * dim + k] = codebook_multiplicands[multiplicand_offset] * codebook_delta_value + codebook_minimum_value + last;  // 0.0
/*306 */                         if (codebook_sequence_p)                                                                                                                        // 0.0
/*308 */                             last = codebook_setup->codevectors[j * dim + k];                                                                                            // 0.0
/*310 */                         lookup_offset/=codebook_lookup_values;                                                                                                          // 0.0
/*312 */                     }                                                                                                                                                   // 0.0
/*314 */                     tmp_vlc_bits[j] = tmp_vlc_bits[i];                                                                                                                  // 0.0
/*318 */                     av_dlog(vc->avctx, "real lookup offset %u, vector: ", j);                                                                                           // 0.0
/*320 */                     for (k = 0; k < dim; ++k)                                                                                                                           // 0.0
/*322 */                         av_dlog(vc->avctx, " %f ",                                                                                                                      // 0.0
/*324 */                                 codebook_setup->codevectors[j * dim + k]);                                                                                              // 0.0
/*326 */                     av_dlog(vc->avctx, "\n");                                                                                                                           // 0.0
/*330 */                     ++j;                                                                                                                                                // 0.0
/*332 */                 }                                                                                                                                                       // 0.0
/*334 */             }                                                                                                                                                           // 0.0
/*336 */             if (j != used_entries) {                                                                                                                                    // 0.0
/*338 */                 av_log(vc->avctx, AV_LOG_ERROR, "Bug in codevector vector building code. \n");                                                                          // 0.0
/*340 */                 ret = AVERROR_INVALIDDATA;                                                                                                                              // 0.0
/*342 */                 goto error;                                                                                                                                             // 0.0
/*344 */             }                                                                                                                                                           // 0.0
/*346 */             entries = used_entries;                                                                                                                                     // 0.0
/*348 */         } else if (codebook_setup->lookup_type >= 2) {                                                                                                                  // 0.0
/*350 */             av_log(vc->avctx, AV_LOG_ERROR, "Codebook lookup type not supported. \n");                                                                                  // 0.0
/*352 */             ret = AVERROR_INVALIDDATA;                                                                                                                                  // 0.0
/*354 */             goto error;                                                                                                                                                 // 0.0
/*356 */         }                                                                                                                                                               // 0.0
/*360 */ // Initialize VLC table                                                                                                                                                 // 0.0
/*362 */         if (ff_vorbis_len2vlc(tmp_vlc_bits, tmp_vlc_codes, entries)) {                                                                                                  // 0.0
/*364 */             av_log(vc->avctx, AV_LOG_ERROR, " Invalid code lengths while generating vlcs. \n");                                                                         // 0.0
/*366 */             ret = AVERROR_INVALIDDATA;                                                                                                                                  // 0.0
/*368 */             goto error;                                                                                                                                                 // 0.0
/*370 */         }                                                                                                                                                               // 0.0
/*372 */         codebook_setup->maxdepth = 0;                                                                                                                                   // 0.0
/*374 */         for (t = 0; t < entries; ++t)                                                                                                                                   // 0.0
/*376 */             if (tmp_vlc_bits[t] >= codebook_setup->maxdepth)                                                                                                            // 0.0
/*378 */                 codebook_setup->maxdepth = tmp_vlc_bits[t];                                                                                                             // 0.0
/*382 */         if (codebook_setup->maxdepth > 3 * V_NB_BITS)                                                                                                                   // 0.0
/*384 */             codebook_setup->nb_bits = V_NB_BITS2;                                                                                                                       // 0.0
/*386 */         else                                                                                                                                                            // 0.0
/*388 */             codebook_setup->nb_bits = V_NB_BITS;                                                                                                                        // 0.0
/*392 */         codebook_setup->maxdepth = (codebook_setup->maxdepth+codebook_setup->nb_bits - 1) / codebook_setup->nb_bits;                                                    // 0.0
/*396 */         if ((ret = init_vlc(&codebook_setup->vlc, codebook_setup->nb_bits,                                                                                              // 0.0
/*398 */                             entries, tmp_vlc_bits, sizeof(*tmp_vlc_bits),                                                                                               // 0.0
/*400 */                             sizeof(*tmp_vlc_bits), tmp_vlc_codes,                                                                                                       // 0.0
/*402 */                             sizeof(*tmp_vlc_codes), sizeof(*tmp_vlc_codes),                                                                                             // 0.0
/*404 */                             INIT_VLC_LE))) {                                                                                                                            // 0.0
/*406 */             av_log(vc->avctx, AV_LOG_ERROR, " Error generating vlc tables. \n");                                                                                        // 0.0
/*408 */             goto error;                                                                                                                                                 // 0.0
/*410 */         }                                                                                                                                                               // 0.0
/*412 */     }                                                                                                                                                                   // 0.0
/*416 */     av_free(tmp_vlc_bits);                                                                                                                                              // 0.0
/*418 */     av_free(tmp_vlc_codes);                                                                                                                                             // 0.0
/*420 */     av_free(codebook_multiplicands);                                                                                                                                    // 0.0
/*422 */     return 0;                                                                                                                                                           // 0.0
/*426 */ // Error:                                                                                                                                                               // 0.0
/*428 */ error:                                                                                                                                                                  // 0.0
/*430 */     av_free(tmp_vlc_bits);                                                                                                                                              // 0.0
/*432 */     av_free(tmp_vlc_codes);                                                                                                                                             // 0.0
/*434 */     av_free(codebook_multiplicands);                                                                                                                                    // 0.0
/*436 */     return ret;                                                                                                                                                         // 0.0
/*438 */ }                                                                                                                                                                       // 0.0
