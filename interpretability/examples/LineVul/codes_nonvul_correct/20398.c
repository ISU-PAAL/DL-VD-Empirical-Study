// commit message qemu@f53a829bb9 (target=0, prob=0.056644246, correct=True): nbd: Drop BDS backpointer
/*0  */ static int nbd_co_flush(BlockDriverState *bs)        // (2) 0.2344
/*2  */ {                                                    // (3) 0.01563
/*4  */     BDRVNBDState *s = bs->opaque;                    // (1) 0.2813
/*8  */     return nbd_client_session_co_flush(&s->client);  // (0) 0.2969
/*10 */ }                                                    // (4) 0.01562
