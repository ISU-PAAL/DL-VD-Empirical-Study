// commit message qemu@f53a829bb9 (target=0, prob=0.63083935, correct=False): nbd: Drop BDS backpointer
/*0  */ static void nbd_close(BlockDriverState *bs)  // (3) 0.1646
/*2  */ {                                            // (4) 0.01266
/*4  */     BDRVNBDState *s = bs->opaque;            // (1) 0.2278
/*8  */     qemu_opts_del(s->socket_opts);           // (0) 0.2405
/*10 */     nbd_client_session_close(&s->client);    // (2) 0.2025
/*12 */ }                                            // (5) 0.01266
