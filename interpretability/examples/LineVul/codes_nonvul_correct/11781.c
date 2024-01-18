// commit message qemu@494a8ebe71 (target=0, prob=0.005291118, correct=True): 9pfs: rename virtio-9p-proxy.{c,h} to 9p-proxy.{c,h}
/*0 */ static off_t proxy_telldir(FsContext *ctx, V9fsFidOpenState *fs)  // (0) 0.5333
/*2 */ {                                                                 // (2) 0.02222
/*4 */     return telldir(fs->dir);                                      // (1) 0.2444
/*6 */ }                                                                 // (3) 0.02222
