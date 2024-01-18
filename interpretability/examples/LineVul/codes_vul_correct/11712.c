// commit message FFmpeg@e048a9cab1 (target=1, prob=0.99910575, correct=True): Do not crash for illegal sample size, fixes issue 2502.
/*0   */ static int pcm_decode_frame(AVCodecContext *avctx,                                                 // (9) 0.03525
/*1   */                             void *data, int *data_size,                                            // (0) 0.07225
/*2   */                             AVPacket *avpkt)                                                       // (1) 0.06835
/*3   */ {                                                                                                  // (25) 0.001953
/*4   */     const uint8_t *buf = avpkt->data;                                                              // (11) 0.0332
/*5   */     int buf_size = avpkt->size;                                                                    // (17) 0.02734
/*6   */     PCMDecode *s = avctx->priv_data;                                                               // (10) 0.03321
/*7   */     int sample_size, c, n, i;                                                                      // (18) 0.02734
/*8   */     short *samples;                                                                                // (22) 0.01562
/*9   */     const uint8_t *src, *src8, *src2[MAX_CHANNELS];                                                // (7) 0.04882
/*10  */     uint8_t *dstu8;                                                                                // (19) 0.02539
/*11  */     int16_t *dst_int16_t;                                                                          // (13) 0.03124
/*12  */     int32_t *dst_int32_t;                                                                          // (14) 0.03124
/*13  */     int64_t *dst_int64_t;                                                                          // (16) 0.03124
/*14  */     uint16_t *dst_uint16_t;                                                                        // (12) 0.03124
/*15  */     uint32_t *dst_uint32_t;                                                                        // (15) 0.03124
/*16  */     samples = data;                                                                                // (24) 0.01367
/*17  */     src = buf;                                                                                     // (23) 0.01367
/*18  */     if (avctx->sample_fmt!=avctx->codec->sample_fmts[0]) {                                         // (4) 0.05468
/*19  */         av_log(avctx, AV_LOG_ERROR, "invalid sample_fmt\n");                                       // (3) 0.05858
/*20  */         return -1;                                                                                 // (21) 0.02148
/*21  */     if(avctx->channels <= 0 || avctx->channels > MAX_CHANNELS){                                    // (8) 0.04882
/*22  */         av_log(avctx, AV_LOG_ERROR, "PCM channels out of bounds\n");                               // (2) 0.05858
/*23  */         return -1;                                                                                 // (20) 0.02148
/*24  */     sample_size = av_get_bits_per_sample(avctx->codec_id)/8;                                       // (6) 0.05273
/*25  */     /* av_get_bits_per_sample returns 0 for CODEC_ID_PCM_DVD */                                    // (5) 0.05277
/*26  */     if (CODEC_ID_PCM_DVD == avctx->codec_id)                                                       // 0.0
/*27  */         /* 2 samples are interleaved per block in PCM_DVD */                                       // 0.0
/*28  */         sample_size = avctx->bits_per_coded_sample * 2 / 8;                                        // 0.0
/*29  */     else if (avctx->codec_id == CODEC_ID_PCM_LXF)                                                  // 0.0
/*30  */         /* we process 40-bit blocks per channel for LXF */                                         // 0.0
/*31  */         sample_size = 5;                                                                           // 0.0
/*32  */     n = avctx->channels * sample_size;                                                             // 0.0
/*33  */     if(n && buf_size % n){                                                                         // 0.0
/*34  */         if (buf_size < n) {                                                                        // 0.0
/*35  */             av_log(avctx, AV_LOG_ERROR, "invalid PCM packet\n");                                   // 0.0
/*36  */             return -1;                                                                             // 0.0
/*37  */         }else                                                                                      // 0.0
/*38  */             buf_size -= buf_size % n;                                                              // 0.0
/*39  */     buf_size= FFMIN(buf_size, *data_size/2);                                                       // 0.0
/*40  */     *data_size=0;                                                                                  // 0.0
/*41  */     n = buf_size/sample_size;                                                                      // 0.0
/*42  */     switch(avctx->codec->id) {                                                                     // 0.0
/*43  */     case CODEC_ID_PCM_U32LE:                                                                       // 0.0
/*44  */         DECODE(uint32_t, le32, src, samples, n, 0, 0x80000000)                                     // 0.0
/*45  */         break;                                                                                     // 0.0
/*46  */     case CODEC_ID_PCM_U32BE:                                                                       // 0.0
/*47  */         DECODE(uint32_t, be32, src, samples, n, 0, 0x80000000)                                     // 0.0
/*48  */         break;                                                                                     // 0.0
/*49  */     case CODEC_ID_PCM_S24LE:                                                                       // 0.0
/*50  */         DECODE(int32_t, le24, src, samples, n, 8, 0)                                               // 0.0
/*51  */         break;                                                                                     // 0.0
/*52  */     case CODEC_ID_PCM_S24BE:                                                                       // 0.0
/*53  */         DECODE(int32_t, be24, src, samples, n, 8, 0)                                               // 0.0
/*54  */         break;                                                                                     // 0.0
/*55  */     case CODEC_ID_PCM_U24LE:                                                                       // 0.0
/*56  */         DECODE(uint32_t, le24, src, samples, n, 8, 0x800000)                                       // 0.0
/*57  */         break;                                                                                     // 0.0
/*58  */     case CODEC_ID_PCM_U24BE:                                                                       // 0.0
/*59  */         DECODE(uint32_t, be24, src, samples, n, 8, 0x800000)                                       // 0.0
/*60  */         break;                                                                                     // 0.0
/*61  */     case CODEC_ID_PCM_S24DAUD:                                                                     // 0.0
/*62  */         for(;n>0;n--) {                                                                            // 0.0
/*63  */           uint32_t v = bytestream_get_be24(&src);                                                  // 0.0
/*64  */           v >>= 4; // sync flags are here                                                          // 0.0
/*65  */           *samples++ = av_reverse[(v >> 8) & 0xff] +                                               // 0.0
/*66  */                        (av_reverse[v & 0xff] << 8);                                                // 0.0
/*67  */         break;                                                                                     // 0.0
/*68  */     case CODEC_ID_PCM_S16LE_PLANAR:                                                                // 0.0
/*69  */         n /= avctx->channels;                                                                      // 0.0
/*70  */         for(c=0;c<avctx->channels;c++)                                                             // 0.0
/*71  */             src2[c] = &src[c*n*2];                                                                 // 0.0
/*72  */         for(;n>0;n--)                                                                              // 0.0
/*73  */             for(c=0;c<avctx->channels;c++)                                                         // 0.0
/*74  */                 *samples++ = bytestream_get_le16(&src2[c]);                                        // 0.0
/*75  */         src = src2[avctx->channels-1];                                                             // 0.0
/*76  */         break;                                                                                     // 0.0
/*77  */     case CODEC_ID_PCM_U16LE:                                                                       // 0.0
/*78  */         DECODE(uint16_t, le16, src, samples, n, 0, 0x8000)                                         // 0.0
/*79  */         break;                                                                                     // 0.0
/*80  */     case CODEC_ID_PCM_U16BE:                                                                       // 0.0
/*81  */         DECODE(uint16_t, be16, src, samples, n, 0, 0x8000)                                         // 0.0
/*82  */         break;                                                                                     // 0.0
/*83  */     case CODEC_ID_PCM_S8:                                                                          // 0.0
/*84  */         dstu8= (uint8_t*)samples;                                                                  // 0.0
/*85  */         for(;n>0;n--) {                                                                            // 0.0
/*86  */             *dstu8++ = *src++ + 128;                                                               // 0.0
/*87  */         samples= (short*)dstu8;                                                                    // 0.0
/*88  */         break;                                                                                     // 0.0
/*89  */ #if HAVE_BIGENDIAN                                                                                 // 0.0
/*90  */     case CODEC_ID_PCM_F64LE:                                                                       // 0.0
/*91  */         DECODE(int64_t, le64, src, samples, n, 0, 0)                                               // 0.0
/*92  */         break;                                                                                     // 0.0
/*93  */     case CODEC_ID_PCM_S32LE:                                                                       // 0.0
/*94  */     case CODEC_ID_PCM_F32LE:                                                                       // 0.0
/*95  */         DECODE(int32_t, le32, src, samples, n, 0, 0)                                               // 0.0
/*96  */         break;                                                                                     // 0.0
/*97  */     case CODEC_ID_PCM_S16LE:                                                                       // 0.0
/*98  */         DECODE(int16_t, le16, src, samples, n, 0, 0)                                               // 0.0
/*99  */         break;                                                                                     // 0.0
/*100 */     case CODEC_ID_PCM_F64BE:                                                                       // 0.0
/*101 */     case CODEC_ID_PCM_F32BE:                                                                       // 0.0
/*102 */     case CODEC_ID_PCM_S32BE:                                                                       // 0.0
/*103 */     case CODEC_ID_PCM_S16BE:                                                                       // 0.0
/*104 */ #else                                                                                              // 0.0
/*105 */     case CODEC_ID_PCM_F64BE:                                                                       // 0.0
/*106 */         DECODE(int64_t, be64, src, samples, n, 0, 0)                                               // 0.0
/*107 */         break;                                                                                     // 0.0
/*108 */     case CODEC_ID_PCM_F32BE:                                                                       // 0.0
/*109 */     case CODEC_ID_PCM_S32BE:                                                                       // 0.0
/*110 */         DECODE(int32_t, be32, src, samples, n, 0, 0)                                               // 0.0
/*111 */         break;                                                                                     // 0.0
/*112 */     case CODEC_ID_PCM_S16BE:                                                                       // 0.0
/*113 */         DECODE(int16_t, be16, src, samples, n, 0, 0)                                               // 0.0
/*114 */         break;                                                                                     // 0.0
/*115 */     case CODEC_ID_PCM_F64LE:                                                                       // 0.0
/*116 */     case CODEC_ID_PCM_F32LE:                                                                       // 0.0
/*117 */     case CODEC_ID_PCM_S32LE:                                                                       // 0.0
/*118 */     case CODEC_ID_PCM_S16LE:                                                                       // 0.0
/*119 */ #endif /* HAVE_BIGENDIAN */                                                                        // 0.0
/*120 */     case CODEC_ID_PCM_U8:                                                                          // 0.0
/*121 */         memcpy(samples, src, n*sample_size);                                                       // 0.0
/*122 */         src += n*sample_size;                                                                      // 0.0
/*123 */         samples = (short*)((uint8_t*)data + n*sample_size);                                        // 0.0
/*124 */         break;                                                                                     // 0.0
/*125 */     case CODEC_ID_PCM_ZORK:                                                                        // 0.0
/*126 */         for(;n>0;n--) {                                                                            // 0.0
/*127 */             int x= *src++;                                                                         // 0.0
/*128 */             if(x&128) x-= 128;                                                                     // 0.0
/*129 */             else      x = -x;                                                                      // 0.0
/*130 */             *samples++ = x << 8;                                                                   // 0.0
/*131 */         break;                                                                                     // 0.0
/*132 */     case CODEC_ID_PCM_ALAW:                                                                        // 0.0
/*133 */     case CODEC_ID_PCM_MULAW:                                                                       // 0.0
/*134 */         for(;n>0;n--) {                                                                            // 0.0
/*135 */             *samples++ = s->table[*src++];                                                         // 0.0
/*136 */         break;                                                                                     // 0.0
/*137 */     case CODEC_ID_PCM_DVD:                                                                         // 0.0
/*138 */         dst_int32_t = data;                                                                        // 0.0
/*139 */         n /= avctx->channels;                                                                      // 0.0
/*140 */         switch (avctx->bits_per_coded_sample) {                                                    // 0.0
/*141 */         case 20:                                                                                   // 0.0
/*142 */             while (n--) {                                                                          // 0.0
/*143 */                 c = avctx->channels;                                                               // 0.0
/*144 */                 src8 = src + 4*c;                                                                  // 0.0
/*145 */                 while (c--) {                                                                      // 0.0
/*146 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8   &0xf0) << 8);   // 0.0
/*147 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++ &0x0f) << 12);  // 0.0
/*148 */                 src = src8;                                                                        // 0.0
/*149 */             break;                                                                                 // 0.0
/*150 */         case 24:                                                                                   // 0.0
/*151 */             while (n--) {                                                                          // 0.0
/*152 */                 c = avctx->channels;                                                               // 0.0
/*153 */                 src8 = src + 4*c;                                                                  // 0.0
/*154 */                 while (c--) {                                                                      // 0.0
/*155 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++) << 8);         // 0.0
/*156 */                     *dst_int32_t++ = (bytestream_get_be16(&src) << 16) + ((*src8++) << 8);         // 0.0
/*157 */                 src = src8;                                                                        // 0.0
/*158 */             break;                                                                                 // 0.0
/*159 */         default:                                                                                   // 0.0
/*160 */             av_log(avctx, AV_LOG_ERROR, "PCM DVD unsupported sample depth\n");                     // 0.0
/*161 */             return -1;                                                                             // 0.0
/*162 */             break;                                                                                 // 0.0
/*163 */         samples = (short *) dst_int32_t;                                                           // 0.0
/*164 */         break;                                                                                     // 0.0
/*165 */     case CODEC_ID_PCM_LXF:                                                                         // 0.0
/*166 */         dst_int32_t = data;                                                                        // 0.0
/*167 */         n /= avctx->channels;                                                                      // 0.0
/*168 */         //unpack and de-planerize                                                                  // 0.0
/*169 */         for (i = 0; i < n; i++) {                                                                  // 0.0
/*170 */             for (c = 0, src8 = src + i*5; c < avctx->channels; c++, src8 += n*5) {                 // 0.0
/*171 */                 //extract low 20 bits and expand to 32 bits                                        // 0.0
/*172 */                 *dst_int32_t++ = (src8[2] << 28) | (src8[1] << 20) | (src8[0] << 12) |             // 0.0
/*173 */                                  ((src8[2] & 0xF) << 8) | src8[1];                                 // 0.0
/*174 */             for (c = 0, src8 = src + i*5; c < avctx->channels; c++, src8 += n*5) {                 // 0.0
/*175 */                 //extract high 20 bits and expand to 32 bits                                       // 0.0
/*176 */                 *dst_int32_t++ = (src8[4] << 24) | (src8[3] << 16) |                               // 0.0
/*177 */                                  ((src8[2] & 0xF0) << 8) | (src8[4] << 4) | (src8[3] >> 4);        // 0.0
/*178 */         src += n * avctx->channels * 5;                                                            // 0.0
/*179 */         samples = (short *) dst_int32_t;                                                           // 0.0
/*180 */         break;                                                                                     // 0.0
/*181 */     default:                                                                                       // 0.0
/*182 */         return -1;                                                                                 // 0.0
/*183 */     *data_size = (uint8_t *)samples - (uint8_t *)data;                                             // 0.0
/*184 */     return src - buf;                                                                              // 0.0
