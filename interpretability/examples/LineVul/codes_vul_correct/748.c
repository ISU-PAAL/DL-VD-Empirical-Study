// commit message FFmpeg@a8d702859b (target=1, prob=0.99909484, correct=True): avcodec/mlpdec: check that streamtype matches the codec
/*0   */ static int read_major_sync(MLPDecodeContext *m, GetBitContext *gb)                                                            // (7) 0.04297
/*2   */ {                                                                                                                             // (21) 0.001953
/*4   */     MLPHeaderInfo mh;                                                                                                         // (18) 0.02148
/*6   */     int substr, ret;                                                                                                          // (20) 0.01563
/*10  */     if ((ret = ff_mlp_read_major_sync(m->avctx, &mh, gb)) != 0)                                                               // (1) 0.06445
/*12  */         return ret;                                                                                                           // (19) 0.01953
/*16  */     if (mh.group1_bits == 0) {                                                                                                // (17) 0.03125
/*18  */         av_log(m->avctx, AV_LOG_ERROR, "invalid/unknown bits per sample\n");                                                  // (2) 0.06445
/*20  */         return AVERROR_INVALIDDATA;                                                                                           // (13) 0.0332
/*23  */     if (mh.group2_bits > mh.group1_bits) {                                                                                    // (8) 0.04297
/*25  */         av_log(m->avctx, AV_LOG_ERROR,                                                                                        // (9) 0.04297
/*27  */                "Channel group 2 cannot have more bits per sample than group 1.\n");                                           // (4) 0.06055
/*29  */         return AVERROR_INVALIDDATA;                                                                                           // (14) 0.0332
/*34  */     if (mh.group2_samplerate && mh.group2_samplerate != mh.group1_samplerate) {                                               // (0) 0.07031
/*36  */         av_log(m->avctx, AV_LOG_ERROR,                                                                                        // (10) 0.04297
/*38  */                "Channel groups with differing sample rates are not currently supported.\n");                                  // (5) 0.05664
/*40  */         return AVERROR_INVALIDDATA;                                                                                           // (15) 0.0332
/*45  */     if (mh.group1_samplerate == 0) {                                                                                          // (12) 0.03516
/*47  */         av_log(m->avctx, AV_LOG_ERROR, "invalid/unknown sampling rate\n");                                                    // (3) 0.0625
/*49  */         return AVERROR_INVALIDDATA;                                                                                           // (16) 0.0332
/*52  */     if (mh.group1_samplerate > MAX_SAMPLERATE) {                                                                              // (6) 0.04492
/*54  */         av_log(m->avctx, AV_LOG_ERROR,                                                                                        // (11) 0.04297
/*56  */                "Sampling rate %d is greater than the supported maximum (%d).\n",                                              // 0.0
/*58  */                mh.group1_samplerate, MAX_SAMPLERATE);                                                                         // 0.0
/*60  */         return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*63  */     if (mh.access_unit_size > MAX_BLOCKSIZE) {                                                                                // 0.0
/*65  */         av_log(m->avctx, AV_LOG_ERROR,                                                                                        // 0.0
/*67  */                "Block size %d is greater than the supported maximum (%d).\n",                                                 // 0.0
/*69  */                mh.access_unit_size, MAX_BLOCKSIZE);                                                                           // 0.0
/*71  */         return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*74  */     if (mh.access_unit_size_pow2 > MAX_BLOCKSIZE_POW2) {                                                                      // 0.0
/*76  */         av_log(m->avctx, AV_LOG_ERROR,                                                                                        // 0.0
/*78  */                "Block size pow2 %d is greater than the supported maximum (%d).\n",                                            // 0.0
/*80  */                mh.access_unit_size_pow2, MAX_BLOCKSIZE_POW2);                                                                 // 0.0
/*82  */         return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*87  */     if (mh.num_substreams == 0)                                                                                               // 0.0
/*89  */         return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*91  */     if (m->avctx->codec_id == AV_CODEC_ID_MLP && mh.num_substreams > 2) {                                                     // 0.0
/*93  */         av_log(m->avctx, AV_LOG_ERROR, "MLP only supports up to 2 substreams.\n");                                            // 0.0
/*95  */         return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*98  */     if (mh.num_substreams > MAX_SUBSTREAMS) {                                                                                 // 0.0
/*101 */                               "%d substreams (more than the "                                                                 // 0.0
/*103 */                               "maximum supported by the decoder)",                                                            // 0.0
/*105 */                               mh.num_substreams);                                                                             // 0.0
/*111 */     m->access_unit_size      = mh.access_unit_size;                                                                           // 0.0
/*113 */     m->access_unit_size_pow2 = mh.access_unit_size_pow2;                                                                      // 0.0
/*117 */     m->num_substreams        = mh.num_substreams;                                                                             // 0.0
/*119 */     m->max_decoded_substream = m->num_substreams - 1;                                                                         // 0.0
/*123 */     m->avctx->sample_rate    = mh.group1_samplerate;                                                                          // 0.0
/*125 */     m->avctx->frame_size     = mh.access_unit_size;                                                                           // 0.0
/*129 */     m->avctx->bits_per_raw_sample = mh.group1_bits;                                                                           // 0.0
/*131 */     if (mh.group1_bits > 16)                                                                                                  // 0.0
/*133 */         m->avctx->sample_fmt = AV_SAMPLE_FMT_S32;                                                                             // 0.0
/*135 */     else                                                                                                                      // 0.0
/*137 */         m->avctx->sample_fmt = AV_SAMPLE_FMT_S16;                                                                             // 0.0
/*141 */     m->params_valid = 1;                                                                                                      // 0.0
/*143 */     for (substr = 0; substr < MAX_SUBSTREAMS; substr++)                                                                       // 0.0
/*145 */         m->substream[substr].restart_seen = 0;                                                                                // 0.0
/*149 */     /* Set the layout for each substream. When there's more than one, the first                                               // 0.0
/*151 */      * substream is Stereo. Subsequent substreams' layouts are indicated in the                                               // 0.0
/*153 */      * major sync. */                                                                                                         // 0.0
/*155 */     if (m->avctx->codec_id == AV_CODEC_ID_MLP) {                                                                              // 0.0
/*163 */         if ((substr = (mh.num_substreams > 1)))                                                                               // 0.0
/*165 */             m->substream[0].ch_layout = AV_CH_LAYOUT_STEREO;                                                                  // 0.0
/*167 */         m->substream[substr].ch_layout = mh.channel_layout_mlp;                                                               // 0.0
/*169 */     } else {                                                                                                                  // 0.0
/*177 */         if ((substr = (mh.num_substreams > 1)))                                                                               // 0.0
/*179 */             m->substream[0].ch_layout = AV_CH_LAYOUT_STEREO;                                                                  // 0.0
/*181 */         if (mh.num_substreams > 2)                                                                                            // 0.0
/*183 */             if (mh.channel_layout_thd_stream2)                                                                                // 0.0
/*185 */                 m->substream[2].ch_layout = mh.channel_layout_thd_stream2;                                                    // 0.0
/*187 */             else                                                                                                              // 0.0
/*189 */                 m->substream[2].ch_layout = mh.channel_layout_thd_stream1;                                                    // 0.0
/*191 */         m->substream[substr].ch_layout = mh.channel_layout_thd_stream1;                                                       // 0.0
/*195 */         if (m->avctx->channels<=2 && m->substream[substr].ch_layout == AV_CH_LAYOUT_MONO && m->max_decoded_substream == 1) {  // 0.0
/*197 */             av_log(m->avctx, AV_LOG_DEBUG, "Mono stream with 2 substreams, ignoring 2nd\n");                                  // 0.0
/*199 */             m->max_decoded_substream = 0;                                                                                     // 0.0
/*201 */             if (m->avctx->channels==2)                                                                                        // 0.0
/*203 */                 m->avctx->channel_layout = AV_CH_LAYOUT_STEREO;                                                               // 0.0
/*209 */     m->needs_reordering = mh.channel_arrangement >= 18 && mh.channel_arrangement <= 20;                                       // 0.0
/*213 */     return 0;                                                                                                                 // 0.0
