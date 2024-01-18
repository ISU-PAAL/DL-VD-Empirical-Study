// commit message qemu@894e02804c (target=1, prob=0.42698252, correct=False): nbd/server: Add helper functions for parsing option payload
/*0  */ static int nbd_reject_length(NBDClient *client, bool fatal, Error **errp)    // (6) 0.07317
/*2  */ {                                                                            // (15) 0.003049
/*4  */     int ret;                                                                 // (11) 0.01829
/*8  */     assert(client->optlen);                                                  // (10) 0.03049
/*10 */     if (nbd_drop(client->ioc, client->optlen, errp) < 0) {                   // (4) 0.08232
/*12 */         return -EIO;                                                         // (9) 0.03659
/*14 */     }                                                                        // (13) 0.0122
/*16 */     ret = nbd_negotiate_send_rep_err(client, NBD_REP_ERR_INVALID, errp,      // (2) 0.1067
/*18 */                                      "option '%s' should have zero length",  // (1) 0.1433
/*20 */                                      nbd_opt_lookup(client->opt));           // (0) 0.1463
/*22 */     if (fatal && !ret) {                                                     // (8) 0.03659
/*24 */         error_setg(errp, "option '%s' should have zero length",              // (5) 0.07927
/*26 */                    nbd_opt_lookup(client->opt));                             // (3) 0.09146
/*28 */         return -EINVAL;                                                      // (7) 0.03963
/*30 */     }                                                                        // (14) 0.0122
/*32 */     return ret;                                                              // (12) 0.01829
/*34 */ }                                                                            // (16) 0.003049
