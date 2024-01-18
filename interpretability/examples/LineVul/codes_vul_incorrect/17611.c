// commit message qemu@b2caa3b82e (target=1, prob=0.17590198, correct=False): net/eth: fix incorrect check of iov_to_buf() return value
/*0   */ _eth_get_rss_ex_src_addr(const struct iovec *pkt, int pkt_frags,                 // (6) 0.05664
/*2   */                         size_t dsthdr_offset,                                    // (4) 0.0625
/*4   */                         struct ip6_ext_hdr *ext_hdr,                             // (1) 0.07227
/*6   */                         struct in6_address *src_addr)                            // (3) 0.06445
/*8   */ {                                                                                // (19) 0.001954
/*10  */     size_t bytes_left = (ext_hdr->ip6r_len + 1) * 8 - sizeof(*ext_hdr);          // (2) 0.06641
/*12  */     struct ip6_option_hdr opthdr;                                                // (14) 0.0293
/*14  */     size_t opt_offset = dsthdr_offset + sizeof(*ext_hdr);                        // (9) 0.04492
/*18  */     while (bytes_left > sizeof(opthdr)) {                                        // (13) 0.03125
/*20  */         size_t input_size = iov_size(pkt, pkt_frags);                            // (8) 0.05469
/*22  */         size_t bytes_read, optlen;                                               // (12) 0.0332
/*26  */         if (input_size < opt_offset) {                                           // (11) 0.03516
/*28  */             return false;                                                        // (16) 0.02734
/*30  */         }                                                                        // (17) 0.01562
/*34  */         bytes_read = iov_to_buf(pkt, pkt_frags, opt_offset,                      // (5) 0.06055
/*36  */                                 &opthdr, sizeof(opthdr));                        // (0) 0.08203
/*40  */         if (bytes_read != sizeof(opthdr)) {                                      // (10) 0.03906
/*42  */             return false;                                                        // (15) 0.02734
/*44  */         }                                                                        // (18) 0.01562
/*48  */         optlen = (opthdr.type == IP6_OPT_PAD1) ? 1                               // (7) 0.05664
/*50  */                                                : (opthdr.len + sizeof(opthdr));  // 0.0
/*54  */         if (optlen > bytes_left) {                                               // 0.0
/*56  */             return false;                                                        // 0.0
/*58  */         }                                                                        // 0.0
/*62  */         if (opthdr.type == IP6_OPT_HOME) {                                       // 0.0
/*64  */             size_t input_size = iov_size(pkt, pkt_frags);                        // 0.0
/*68  */             if (input_size < opt_offset + sizeof(opthdr)) {                      // 0.0
/*70  */                 return false;                                                    // 0.0
/*72  */             }                                                                    // 0.0
/*76  */             bytes_read = iov_to_buf(pkt, pkt_frags,                              // 0.0
/*78  */                                     opt_offset + sizeof(opthdr),                 // 0.0
/*80  */                                     src_addr, sizeof(*src_addr));                // 0.0
/*84  */             return bytes_read == sizeof(src_addr);                               // 0.0
/*86  */         }                                                                        // 0.0
/*90  */         opt_offset += optlen;                                                    // 0.0
/*92  */         bytes_left -= optlen;                                                    // 0.0
/*94  */     }                                                                            // 0.0
/*98  */     return false;                                                                // 0.0
/*100 */ }                                                                                // 0.0
