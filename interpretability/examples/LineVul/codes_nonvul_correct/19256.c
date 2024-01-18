// commit message qemu@1ea879e558 (target=0, prob=0.35101283, correct=True): Make audio violate POSIX less
/*0   */ static int qpa_init_in (HWVoiceIn *hw, audsettings_t *as)                       // (6) 0.04492
/*2   */ {                                                                               // (28) 0.001953
/*4   */     int error;                                                                  // (26) 0.01172
/*6   */     static pa_sample_spec ss;                                                   // (18) 0.02148
/*8   */     audsettings_t obt_as = *as;                                                 // (9) 0.0293
/*10  */     PAVoiceIn *pa = (PAVoiceIn *) hw;                                           // (8) 0.0332
/*14  */     ss.format = audfmt_to_pa (as->fmt, as->endianness);                         // (5) 0.05078
/*16  */     ss.channels = as->nchannels;                                                // (11) 0.02734
/*18  */     ss.rate = as->freq;                                                         // (16) 0.02344
/*22  */     obt_as.fmt = pa_to_audfmt (ss.format, &obt_as.endianness);                  // (1) 0.06445
/*26  */     pa->s = pa_simple_new (                                                     // (14) 0.02539
/*28  */         conf.server,                                                            // (20) 0.02148
/*30  */         "qemu",                                                                 // (17) 0.02344
/*32  */         PA_STREAM_RECORD,                                                       // (10) 0.0293
/*34  */         conf.source,                                                            // (21) 0.02148
/*36  */         "pcm.capture",                                                          // (13) 0.02734
/*38  */         &ss,                                                                    // (23) 0.01953
/*40  */         NULL,                   /* channel map */                               // (3) 0.06055
/*42  */         NULL,                   /* buffering attributes */                      // (2) 0.0625
/*44  */         &error                                                                  // (24) 0.01758
/*46  */         );                                                                      // (25) 0.01562
/*48  */     if (!pa->s) {                                                               // (22) 0.01953
/*50  */         qpa_logerr (error, "pa_simple_new for capture failed\n");               // (4) 0.05273
/*52  */         goto fail1;                                                             // (19) 0.02148
/*54  */     }                                                                           // (27) 0.007812
/*58  */     audio_pcm_init_info (&hw->info, &obt_as);                                   // (7) 0.04297
/*60  */     hw->samples = conf.samples;                                                 // (12) 0.02734
/*62  */     pa->pcm_buf = audio_calloc (AUDIO_FUNC, hw->samples, 1 << hw->info.shift);  // (0) 0.07031
/*64  */     if (!pa->pcm_buf) {                                                         // (15) 0.02539
/*66  */         dolog ("Could not allocate buffer (%d bytes)\n",                        // 0.0
/*68  */                hw->samples << hw->info.shift);                                  // 0.0
/*70  */         goto fail2;                                                             // 0.0
/*72  */     }                                                                           // 0.0
/*76  */     if (audio_pt_init (&pa->pt, qpa_thread_in, hw, AUDIO_CAP, AUDIO_FUNC)) {    // 0.0
/*78  */         goto fail3;                                                             // 0.0
/*80  */     }                                                                           // 0.0
/*84  */     return 0;                                                                   // 0.0
/*88  */  fail3:                                                                         // 0.0
/*90  */     free (pa->pcm_buf);                                                         // 0.0
/*92  */     pa->pcm_buf = NULL;                                                         // 0.0
/*94  */  fail2:                                                                         // 0.0
/*96  */     pa_simple_free (pa->s);                                                     // 0.0
/*98  */     pa->s = NULL;                                                               // 0.0
/*100 */  fail1:                                                                         // 0.0
/*102 */     return -1;                                                                  // 0.0
/*104 */ }                                                                               // 0.0
