// commit message FFmpeg@5d97d9d53e (target=1, prob=0.312127, correct=False): fix checksum check (was my bug not libnut)
/*0  */ static int check_checksum(ByteIOContext *bc){                                // (4) 0.01164
/*2  */     unsigned long checksum= get_checksum(bc);                                // (3) 0.02098
/*4  */ //    return checksum != get_be32(bc);                                       // (0) 0.4737
/*8  */     av_log(NULL, AV_LOG_ERROR, "%08X %08X\n", checksum, (int)get_be32(bc));  // (2) 0.03845
/*12 */     return 0;                                                                // (1) 0.04197
/*14 */ }                                                                            // (5) 0.001723
