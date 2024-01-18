// commit message FFmpeg@7ed47e9729 (target=1, prob=0.999074, correct=True): avformat/smacker: fix integer overflow with pts_inc
/*0   */ static int smacker_read_header(AVFormatContext *s)                                                               // (3) 0.05451
/*1   */ {                                                                                                                // (26) 0.001744
/*2   */     AVIOContext *pb = s->pb;                                                                                     // (15) 0.02873
/*3   */     SmackerContext *smk = s->priv_data;                                                                          // (6) 0.03854
/*4   */     AVStream *st, *ast[7];                                                                                       // (9) 0.03288
/*5   */     int i, ret;                                                                                                  // (25) 0.01981
/*6   */     int tbase;                                                                                                   // (1) 0.06844
/*7   */     /* read and check header */                                                                                  // (16) 0.02698
/*8   */     smk->magic = avio_rl32(pb);                                                                                  // (17) 0.02667
/*9   */     if (smk->magic != MKTAG('S', 'M', 'K', '2') && smk->magic != MKTAG('S', 'M', 'K', '4'))                      // (0) 0.07423
/*10  */     smk->width = avio_rl32(pb);                                                                                  // (19) 0.02622
/*11  */     smk->height = avio_rl32(pb);                                                                                 // (20) 0.02622
/*12  */     smk->frames = avio_rl32(pb);                                                                                 // (18) 0.02657
/*13  */     smk->pts_inc = (int32_t)avio_rl32(pb);                                                                       // (5) 0.04396
/*14  */     smk->flags = avio_rl32(pb);                                                                                  // (21) 0.02604
/*15  */     if(smk->flags & SMACKER_FLAG_RING_FRAME)                                                                     // (8) 0.03694
/*16  */         smk->frames++;                                                                                           // (24) 0.01992
/*17  */     for(i = 0; i < 7; i++)                                                                                       // (22) 0.02446
/*18  */         smk->audio[i] = avio_rl32(pb);                                                                           // (7) 0.0381
/*19  */     smk->treesize = avio_rl32(pb);                                                                               // (12) 0.02969
/*20  */     if(smk->treesize >= UINT_MAX/4){ // smk->treesize + 16 must not overflow (this check is probably redundant)  // (2) 0.06419
/*21  */         av_log(s, AV_LOG_ERROR, "treesize too large\n");                                                         // (4) 0.04844
/*22  */ //FIXME remove extradata "rebuilding"                                                                            // (23) 0.0232
/*23  */     smk->mmap_size = avio_rl32(pb);                                                                              // (11) 0.03171
/*24  */     smk->mclr_size = avio_rl32(pb);                                                                              // (10) 0.03281
/*25  */     smk->full_size = avio_rl32(pb);                                                                              // (14) 0.02931
/*26  */     smk->type_size = avio_rl32(pb);                                                                              // (13) 0.02933
/*27  */     for(i = 0; i < 7; i++) {                                                                                     // 0.0
/*28  */         smk->rates[i]  = avio_rl24(pb);                                                                          // 0.0
/*29  */         smk->aflags[i] = avio_r8(pb);                                                                            // 0.0
/*30  */     smk->pad = avio_rl32(pb);                                                                                    // 0.0
/*31  */     /* setup data */                                                                                             // 0.0
/*32  */     if(smk->frames > 0xFFFFFF) {                                                                                 // 0.0
/*33  */         av_log(s, AV_LOG_ERROR, "Too many frames: %"PRIu32"\n", smk->frames);                                    // 0.0
/*34  */     smk->frm_size = av_malloc_array(smk->frames, sizeof(*smk->frm_size));                                        // 0.0
/*35  */     smk->frm_flags = av_malloc(smk->frames);                                                                     // 0.0
/*36  */     if (!smk->frm_size || !smk->frm_flags) {                                                                     // 0.0
/*37  */         av_freep(&smk->frm_size);                                                                                // 0.0
/*38  */         av_freep(&smk->frm_flags);                                                                               // 0.0
/*39  */         return AVERROR(ENOMEM);                                                                                  // 0.0
/*40  */     smk->is_ver4 = (smk->magic != MKTAG('S', 'M', 'K', '2'));                                                    // 0.0
/*41  */     /* read frame info */                                                                                        // 0.0
/*42  */     for(i = 0; i < smk->frames; i++) {                                                                           // 0.0
/*43  */         smk->frm_size[i] = avio_rl32(pb);                                                                        // 0.0
/*44  */     for(i = 0; i < smk->frames; i++) {                                                                           // 0.0
/*45  */         smk->frm_flags[i] = avio_r8(pb);                                                                         // 0.0
/*46  */     /* init video codec */                                                                                       // 0.0
/*47  */     st = avformat_new_stream(s, NULL);                                                                           // 0.0
/*48  */     if (!st)                                                                                                     // 0.0
/*49  */         return AVERROR(ENOMEM);                                                                                  // 0.0
/*50  */     smk->videoindex = st->index;                                                                                 // 0.0
/*51  */     st->codec->width = smk->width;                                                                               // 0.0
/*52  */     st->codec->height = smk->height;                                                                             // 0.0
/*53  */     st->codec->pix_fmt = AV_PIX_FMT_PAL8;                                                                        // 0.0
/*54  */     st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                                  // 0.0
/*55  */     st->codec->codec_id = AV_CODEC_ID_SMACKVIDEO;                                                                // 0.0
/*56  */     st->codec->codec_tag = smk->magic;                                                                           // 0.0
/*57  */     /* Smacker uses 100000 as internal timebase */                                                               // 0.0
/*58  */     if(smk->pts_inc < 0)                                                                                         // 0.0
/*59  */         smk->pts_inc = -smk->pts_inc;                                                                            // 0.0
/*60  */     else                                                                                                         // 0.0
/*61  */         smk->pts_inc *= 100;                                                                                     // 0.0
/*62  */     tbase = 100000;                                                                                              // 0.0
/*63  */     av_reduce(&tbase, &smk->pts_inc, tbase, smk->pts_inc, (1UL<<31)-1);                                          // 0.0
/*64  */     avpriv_set_pts_info(st, 33, smk->pts_inc, tbase);                                                            // 0.0
/*65  */     st->duration = smk->frames;                                                                                  // 0.0
/*66  */     /* handle possible audio streams */                                                                          // 0.0
/*67  */     for(i = 0; i < 7; i++) {                                                                                     // 0.0
/*68  */         smk->indexes[i] = -1;                                                                                    // 0.0
/*69  */         if (smk->rates[i]) {                                                                                     // 0.0
/*70  */             ast[i] = avformat_new_stream(s, NULL);                                                               // 0.0
/*71  */             if (!ast[i])                                                                                         // 0.0
/*72  */                 return AVERROR(ENOMEM);                                                                          // 0.0
/*73  */             smk->indexes[i] = ast[i]->index;                                                                     // 0.0
/*74  */             ast[i]->codec->codec_type = AVMEDIA_TYPE_AUDIO;                                                      // 0.0
/*75  */             if (smk->aflags[i] & SMK_AUD_BINKAUD) {                                                              // 0.0
/*76  */                 ast[i]->codec->codec_id = AV_CODEC_ID_BINKAUDIO_RDFT;                                            // 0.0
/*77  */             } else if (smk->aflags[i] & SMK_AUD_USEDCT) {                                                        // 0.0
/*78  */                 ast[i]->codec->codec_id = AV_CODEC_ID_BINKAUDIO_DCT;                                             // 0.0
/*79  */             } else if (smk->aflags[i] & SMK_AUD_PACKED){                                                         // 0.0
/*80  */                 ast[i]->codec->codec_id = AV_CODEC_ID_SMACKAUDIO;                                                // 0.0
/*81  */                 ast[i]->codec->codec_tag = MKTAG('S', 'M', 'K', 'A');                                            // 0.0
/*82  */             } else {                                                                                             // 0.0
/*83  */                 ast[i]->codec->codec_id = AV_CODEC_ID_PCM_U8;                                                    // 0.0
/*84  */             if (smk->aflags[i] & SMK_AUD_STEREO) {                                                               // 0.0
/*85  */                 ast[i]->codec->channels       = 2;                                                               // 0.0
/*86  */                 ast[i]->codec->channel_layout = AV_CH_LAYOUT_STEREO;                                             // 0.0
/*87  */             } else {                                                                                             // 0.0
/*88  */                 ast[i]->codec->channels       = 1;                                                               // 0.0
/*89  */                 ast[i]->codec->channel_layout = AV_CH_LAYOUT_MONO;                                               // 0.0
/*90  */             ast[i]->codec->sample_rate = smk->rates[i];                                                          // 0.0
/*91  */             ast[i]->codec->bits_per_coded_sample = (smk->aflags[i] & SMK_AUD_16BITS) ? 16 : 8;                   // 0.0
/*92  */             if(ast[i]->codec->bits_per_coded_sample == 16 && ast[i]->codec->codec_id == AV_CODEC_ID_PCM_U8)      // 0.0
/*93  */                 ast[i]->codec->codec_id = AV_CODEC_ID_PCM_S16LE;                                                 // 0.0
/*94  */             avpriv_set_pts_info(ast[i], 64, 1, ast[i]->codec->sample_rate                                        // 0.0
/*95  */                     * ast[i]->codec->channels * ast[i]->codec->bits_per_coded_sample / 8);                       // 0.0
/*96  */     /* load trees to extradata, they will be unpacked by decoder */                                              // 0.0
/*97  */     if(ff_alloc_extradata(st->codec, smk->treesize + 16)){                                                       // 0.0
/*98  */         av_log(s, AV_LOG_ERROR,                                                                                  // 0.0
/*99  */                "Cannot allocate %"PRIu32" bytes of extradata\n",                                                 // 0.0
/*100 */                smk->treesize + 16);                                                                              // 0.0
/*101 */         av_freep(&smk->frm_size);                                                                                // 0.0
/*102 */         av_freep(&smk->frm_flags);                                                                               // 0.0
/*103 */         return AVERROR(ENOMEM);                                                                                  // 0.0
/*104 */     ret = avio_read(pb, st->codec->extradata + 16, st->codec->extradata_size - 16);                              // 0.0
/*105 */     if(ret != st->codec->extradata_size - 16){                                                                   // 0.0
/*106 */         av_freep(&smk->frm_size);                                                                                // 0.0
/*107 */         av_freep(&smk->frm_flags);                                                                               // 0.0
/*108 */         return AVERROR(EIO);                                                                                     // 0.0
/*109 */     ((int32_t*)st->codec->extradata)[0] = av_le2ne32(smk->mmap_size);                                            // 0.0
/*110 */     ((int32_t*)st->codec->extradata)[1] = av_le2ne32(smk->mclr_size);                                            // 0.0
/*111 */     ((int32_t*)st->codec->extradata)[2] = av_le2ne32(smk->full_size);                                            // 0.0
/*112 */     ((int32_t*)st->codec->extradata)[3] = av_le2ne32(smk->type_size);                                            // 0.0
/*113 */     smk->curstream = -1;                                                                                         // 0.0
/*114 */     smk->nextpos = avio_tell(pb);                                                                                // 0.0
/*115 */     return 0;                                                                                                    // 0.0
