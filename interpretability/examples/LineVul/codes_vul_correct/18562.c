// commit message qemu@b6b75a99da (target=1, prob=0.99918896, correct=True): qcow2-bitmap: fix bitmap_free
/*0 */ static void bitmap_free(Qcow2Bitmap *bm)  // (0) 0.3659
/*1 */ {                                         // (3) 0.02439
/*2 */     g_free(bm->name);                     // (1) 0.2683
/*3 */     g_free(bm);                           // (2) 0.2195
