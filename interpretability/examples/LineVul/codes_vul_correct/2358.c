// commit message FFmpeg@0ecca7a49f (target=1, prob=0.5044104, correct=True): various security fixes and precautionary checks
/*0   */ static int vqa_decode_init(AVCodecContext *avctx)                                                         // (8) 0.03526
/*2   */ {                                                                                                         // (26) 0.001953
/*4   */     VqaContext *s = (VqaContext *)avctx->priv_data;                                                       // (5) 0.04101
/*6   */     unsigned char *vqa_header;                                                                            // (23) 0.02148
/*8   */     int i, j, codebook_index;;                                                                            // (20) 0.02539
/*12  */     s->avctx = avctx;                                                                                     // (24) 0.02148
/*14  */     avctx->pix_fmt = PIX_FMT_PAL8;                                                                        // (4) 0.04296
/*16  */     avctx->has_b_frames = 0;                                                                              // (17) 0.02734
/*18  */     dsputil_init(&s->dsp, avctx);                                                                         // (9) 0.03516
/*22  */     /* make sure the extradata made it */                                                                 // (22) 0.02343
/*24  */     if (s->avctx->extradata_size != VQA_HEADER_SIZE) {                                                    // (2) 0.05077
/*26  */         av_log(s->avctx, AV_LOG_ERROR, "  VQA video: expected extradata size of %d\n", VQA_HEADER_SIZE);  // (0) 0.09377
/*32  */     /* load up the VQA parameters from the header */                                                      // (16) 0.02929
/*34  */     vqa_header = (unsigned char *)s->avctx->extradata;                                                    // (6) 0.04101
/*36  */     s->vqa_version = vqa_header[0];                                                                       // (13) 0.0332
/*38  */     s->width = LE_16(&vqa_header[6]);                                                                     // (12) 0.03515
/*40  */     s->height = LE_16(&vqa_header[8]);                                                                    // (11) 0.03515
/*46  */     s->vector_width = vqa_header[10];                                                                     // (14) 0.03125
/*48  */     s->vector_height = vqa_header[11];                                                                    // (15) 0.03124
/*50  */     s->partial_count = s->partial_countdown = vqa_header[13];                                             // (3) 0.04493
/*54  */     /* the vector dimensions have to meet very stringent requirements */                                  // (18) 0.02734
/*56  */     if ((s->vector_width != 4) ||                                                                         // (19) 0.02734
/*58  */         ((s->vector_height != 2) && (s->vector_height != 4))) {                                           // (1) 0.05272
/*60  */         /* return without further initialization */                                                       // (21) 0.02539
/*66  */     /* allocate codebooks */                                                                              // (25) 0.01562
/*68  */     s->codebook_size = MAX_CODEBOOK_SIZE;                                                                 // (10) 0.03515
/*70  */     s->codebook = av_malloc(s->codebook_size);                                                            // (7) 0.03905
/*72  */     s->next_codebook_buffer = av_malloc(s->codebook_size);                                                // 0.0
/*76  */     /* initialize the solid-color vectors */                                                              // 0.0
/*78  */     if (s->vector_height == 4) {                                                                          // 0.0
/*80  */         codebook_index = 0xFF00 * 16;                                                                     // 0.0
/*82  */         for (i = 0; i < 256; i++)                                                                         // 0.0
/*84  */             for (j = 0; j < 16; j++)                                                                      // 0.0
/*86  */                 s->codebook[codebook_index++] = i;                                                        // 0.0
/*88  */     } else {                                                                                              // 0.0
/*90  */         codebook_index = 0xF00 * 8;                                                                       // 0.0
/*92  */         for (i = 0; i < 256; i++)                                                                         // 0.0
/*94  */             for (j = 0; j < 8; j++)                                                                       // 0.0
/*96  */                 s->codebook[codebook_index++] = i;                                                        // 0.0
/*99  */     s->next_codebook_buffer_index = 0;                                                                    // 0.0
/*103 */     /* allocate decode buffer */                                                                          // 0.0
/*105 */     s->decode_buffer_size = (s->width / s->vector_width) *                                                // 0.0
/*107 */         (s->height / s->vector_height) * 2;                                                               // 0.0
/*109 */     s->decode_buffer = av_malloc(s->decode_buffer_size);                                                  // 0.0
/*113 */     s->frame.data[0] = NULL;                                                                              // 0.0
/*117 */     return 0;                                                                                             // 0.0
