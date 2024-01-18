// commit message qemu@92dcc234ec (target=0, prob=0.16976376, correct=True): Add support for cancelling of a TPM command
/*0  */ static int tpm_passthrough_unix_tx_bufs(int tpm_fd,                          // (10) 0.04492
/*2  */                                         const uint8_t *in, uint32_t in_len,  // (0) 0.1074
/*4  */                                         uint8_t *out, uint32_t out_len)      // (1) 0.1055
/*6  */ {                                                                            // (19) 0.001953
/*8  */     int ret;                                                                 // (17) 0.01172
/*12 */     ret = tpm_passthrough_unix_write(tpm_fd, in, in_len);                    // (7) 0.05469
/*14 */     if (ret != in_len) {                                                     // (13) 0.02344
/*16 */         error_report("tpm_passthrough: error while transmitting data "       // (11) 0.04492
/*18 */                      "to TPM: %s (%i)\n",                                    // (3) 0.0625
/*20 */                      strerror(errno), errno);                                // (5) 0.05859
/*22 */         goto err_exit;                                                       // (14) 0.02344
/*24 */     }                                                                        // (18) 0.007812
/*28 */     ret = tpm_passthrough_unix_read(tpm_fd, out, out_len);                   // (8) 0.05469
/*30 */     if (ret < 0) {                                                           // (16) 0.01953
/*32 */         error_report("tpm_passthrough: error while reading data from "       // (9) 0.04688
/*34 */                      "TPM: %s (%i)\n",                                       // (4) 0.06055
/*36 */                      strerror(errno), errno);                                // (6) 0.05859
/*38 */     } else if (ret < sizeof(struct tpm_resp_hdr) ||                          // (12) 0.04102
/*40 */                tpm_passthrough_get_size_from_buffer(out) != ret) {           // (2) 0.06836
/*42 */         ret = -1;                                                            // (15) 0.02344
/*44 */         error_report("tpm_passthrough: received invalid response "           // 0.0
/*46 */                      "packet from TPM\n");                                   // 0.0
/*48 */     }                                                                        // 0.0
/*52 */ err_exit:                                                                    // 0.0
/*54 */     if (ret < 0) {                                                           // 0.0
/*56 */         tpm_write_fatal_error_response(out, out_len);                        // 0.0
/*58 */     }                                                                        // 0.0
/*62 */     return ret;                                                              // 0.0
/*64 */ }                                                                            // 0.0
