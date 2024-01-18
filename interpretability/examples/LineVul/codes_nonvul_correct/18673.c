// commit message qemu@92dcc234ec (target=0, prob=0.038219057, correct=True): Add support for cancelling of a TPM command
/*0  */ static int tpm_passthrough_unix_transfer(int tpm_fd,                     // (6) 0.0639
/*2  */                                          const TPMLocality *locty_data)  // (0) 0.1661
/*4  */ {                                                                        // (7) 0.003195
/*6  */     return tpm_passthrough_unix_tx_bufs(tpm_fd,                          // (5) 0.07668
/*8  */                                         locty_data->w_buffer.buffer,     // (1) 0.1629
/*10 */                                         locty_data->w_offset,            // (4) 0.1565
/*12 */                                         locty_data->r_buffer.buffer,     // (2) 0.1629
/*14 */                                         locty_data->r_buffer.size);      // (3) 0.1629
/*16 */ }                                                                        // (8) 0.003195
