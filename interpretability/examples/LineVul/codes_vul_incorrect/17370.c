// commit message qemu@5706db1deb (target=1, prob=0.24399252, correct=False): audio: expose drv_opaque to init_out and init_in
/*0  */ static int no_init_in (HWVoiceIn *hw, struct audsettings *as)  // (0) 0.3088
/*2  */ {                                                              // (4) 0.01471
/*4  */     audio_pcm_init_info (&hw->info, as);                       // (1) 0.2647
/*6  */     hw->samples = 1024;                                        // (2) 0.1618
/*8  */     return 0;                                                  // (3) 0.08824
/*10 */ }                                                              // (5) 0.01471
