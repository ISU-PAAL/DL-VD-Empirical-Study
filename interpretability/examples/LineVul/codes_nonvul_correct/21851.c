// commit message FFmpeg@7b46add725 (target=0, prob=0.029352466, correct=True): opus_pvq: do not compile encoding/decoding code if the encoder/decoder is disabled
/*0 */ static QUANT_FN(pvq_encode_band)                                                         // (2) 0.1364
/*2 */ {                                                                                        // (3) 0.009091
/*4 */     return quant_band_template(pvq, f, rc, band, X, Y, N, b, blocks, lowband, duration,  // (1) 0.3182
/*6 */                                lowband_out, level, gain, lowband_scratch, fill, 1);      // (0) 0.4455
/*8 */ }                                                                                        // (4) 0.009091
