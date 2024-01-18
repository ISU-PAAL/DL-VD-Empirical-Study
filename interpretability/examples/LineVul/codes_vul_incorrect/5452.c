// commit message FFmpeg@9a3f10695a (target=1, prob=0.49679586, correct=False): ra144enc: zero the reflection coeffs if the filter is unstable
/*0   */ static int ra144_encode_frame(AVCodecContext *avctx, uint8_t *frame,              // (6) 0.04883
/*2   */                               int buf_size, void *data)                           // (2) 0.07421
/*4   */ {                                                                                 // (24) 0.001958
/*6   */     static const uint8_t sizes[LPC_ORDER] = {64, 32, 32, 16, 16, 8, 8, 8, 8, 4};  // (1) 0.07617
/*8   */     static const uint8_t bit_sizes[LPC_ORDER] = {6, 5, 5, 4, 4, 3, 3, 3, 3, 2};   // (0) 0.08203
/*10  */     RA144Context *ractx;                                                          // (17) 0.01953
/*12  */     PutBitContext pb;                                                             // (20) 0.01758
/*14  */     int32_t lpc_data[NBLOCKS * BLOCKSIZE];                                        // (11) 0.04101
/*16  */     int32_t lpc_coefs[LPC_ORDER][MAX_LPC_ORDER];                                  // (4) 0.05468
/*18  */     int shift[LPC_ORDER];                                                         // (16) 0.02345
/*20  */     int16_t block_coefs[NBLOCKS][LPC_ORDER];                                      // (8) 0.04687
/*22  */     int lpc_refl[LPC_ORDER];    /**< reflection coefficients of the frame */      // (5) 0.05273
/*24  */     unsigned int refl_rms[NBLOCKS]; /**< RMS of the reflection coefficients */    // (7) 0.04883
/*26  */     int energy = 0;                                                               // (21) 0.01562
/*28  */     int i, idx;                                                                   // (19) 0.01758
/*32  */     if (buf_size < FRAMESIZE) {                                                   // (14) 0.02734
/*34  */         av_log(avctx, AV_LOG_ERROR, "output buffer too small\n");                 // (3) 0.05468
/*36  */         return 0;                                                                 // (18) 0.01953
/*38  */     }                                                                             // (23) 0.007812
/*40  */     ractx = avctx->priv_data;                                                     // (15) 0.02734
/*44  */     /**                                                                           // (22) 0.007814
/*46  */      * Since the LPC coefficients are calculated on a frame centered over the     // (13) 0.03516
/*48  */      * fourth subframe, to encode a given frame, data from the next frame is      // (9) 0.04102
/*50  */      * needed. In each call to this function, the previous frame (whose data are  // (10) 0.04101
/*52  */      * saved in the encoder context) is encoded, and data from the current frame  // (12) 0.04101
/*54  */      * are saved in the encoder context to be used in the next function call.     // 0.0
/*56  */      */                                                                           // 0.0
/*58  */     for (i = 0; i < (2 * BLOCKSIZE + BLOCKSIZE / 2); i++) {                       // 0.0
/*60  */         lpc_data[i] = ractx->curr_block[BLOCKSIZE + BLOCKSIZE / 2 + i];           // 0.0
/*62  */         energy += (lpc_data[i] * lpc_data[i]) >> 4;                               // 0.0
/*64  */     }                                                                             // 0.0
/*66  */     for (i = 2 * BLOCKSIZE + BLOCKSIZE / 2; i < NBLOCKS * BLOCKSIZE; i++) {       // 0.0
/*68  */         lpc_data[i] = *((int16_t *)data + i - 2 * BLOCKSIZE - BLOCKSIZE / 2) >>   // 0.0
/*70  */                       2;                                                          // 0.0
/*72  */         energy += (lpc_data[i] * lpc_data[i]) >> 4;                               // 0.0
/*74  */     }                                                                             // 0.0
/*76  */     energy = ff_energy_tab[quantize(ff_t_sqrt(energy >> 5) >> 10, ff_energy_tab,  // 0.0
/*78  */                                     32)];                                         // 0.0
/*82  */     ff_lpc_calc_coefs(&ractx->lpc_ctx, lpc_data, NBLOCKS * BLOCKSIZE, LPC_ORDER,  // 0.0
/*84  */                       LPC_ORDER, 16, lpc_coefs, shift, FF_LPC_TYPE_LEVINSON,      // 0.0
/*86  */                       0, ORDER_METHOD_EST, 12, 0);                                // 0.0
/*88  */     for (i = 0; i < LPC_ORDER; i++)                                               // 0.0
/*90  */         block_coefs[NBLOCKS - 1][i] = -(lpc_coefs[LPC_ORDER - 1][i] <<            // 0.0
/*92  */                                         (12 - shift[LPC_ORDER - 1]));             // 0.0
/*96  */     /**                                                                           // 0.0
/*98  */      * TODO: apply perceptual weighting of the input speech through bandwidth     // 0.0
/*100 */      * expansion of the LPC filter.                                               // 0.0
/*102 */      */                                                                           // 0.0
/*106 */     if (ff_eval_refl(lpc_refl, block_coefs[NBLOCKS - 1], avctx)) {                // 0.0
/*108 */         /**                                                                       // 0.0
/*110 */          * The filter is unstable: use the coefficients of the previous frame.    // 0.0
/*112 */          */                                                                       // 0.0
/*114 */         ff_int_to_int16(block_coefs[NBLOCKS - 1], ractx->lpc_coef[1]);            // 0.0
/*116 */         ff_eval_refl(lpc_refl, block_coefs[NBLOCKS - 1], avctx);                  // 0.0
/*118 */     }                                                                             // 0.0
/*120 */     init_put_bits(&pb, frame, buf_size);                                          // 0.0
/*122 */     for (i = 0; i < LPC_ORDER; i++) {                                             // 0.0
/*124 */         idx = quantize(lpc_refl[i], ff_lpc_refl_cb[i], sizes[i]);                 // 0.0
/*126 */         put_bits(&pb, bit_sizes[i], idx);                                         // 0.0
/*128 */         lpc_refl[i] = ff_lpc_refl_cb[i][idx];                                     // 0.0
/*130 */     }                                                                             // 0.0
/*132 */     ractx->lpc_refl_rms[0] = ff_rms(lpc_refl);                                    // 0.0
/*134 */     ff_eval_coefs(ractx->lpc_coef[0], lpc_refl);                                  // 0.0
/*136 */     refl_rms[0] = ff_interp(ractx, block_coefs[0], 1, 1, ractx->old_energy);      // 0.0
/*138 */     refl_rms[1] = ff_interp(ractx, block_coefs[1], 2,                             // 0.0
/*140 */                             energy <= ractx->old_energy,                          // 0.0
/*142 */                             ff_t_sqrt(energy * ractx->old_energy) >> 12);         // 0.0
/*144 */     refl_rms[2] = ff_interp(ractx, block_coefs[2], 3, 0, energy);                 // 0.0
/*146 */     refl_rms[3] = ff_rescale_rms(ractx->lpc_refl_rms[0], energy);                 // 0.0
/*148 */     ff_int_to_int16(block_coefs[NBLOCKS - 1], ractx->lpc_coef[0]);                // 0.0
/*150 */     put_bits(&pb, 5, quantize(energy, ff_energy_tab, 32));                        // 0.0
/*152 */     for (i = 0; i < NBLOCKS; i++)                                                 // 0.0
/*154 */         ra144_encode_subblock(ractx, ractx->curr_block + i * BLOCKSIZE,           // 0.0
/*156 */                               block_coefs[i], refl_rms[i], &pb);                  // 0.0
/*158 */     flush_put_bits(&pb);                                                          // 0.0
/*160 */     ractx->old_energy = energy;                                                   // 0.0
/*162 */     ractx->lpc_refl_rms[1] = ractx->lpc_refl_rms[0];                              // 0.0
/*164 */     FFSWAP(unsigned int *, ractx->lpc_coef[0], ractx->lpc_coef[1]);               // 0.0
/*166 */     for (i = 0; i < NBLOCKS * BLOCKSIZE; i++)                                     // 0.0
/*168 */         ractx->curr_block[i] = *((int16_t *)data + i) >> 2;                       // 0.0
/*170 */     return FRAMESIZE;                                                             // 0.0
/*172 */ }                                                                                 // 0.0
