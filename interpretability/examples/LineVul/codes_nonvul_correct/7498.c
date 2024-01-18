// commit message qemu@1ea879e558 (target=0, prob=0.33588877, correct=True): Make audio violate POSIX less
/*0   */ static int qesd_init_out (HWVoiceOut *hw, audsettings_t *as)                      // (2) 0.04688
/*2   */ {                                                                                 // (30) 0.001953
/*4   */     ESDVoiceOut *esd = (ESDVoiceOut *) hw;                                        // (8) 0.03906
/*6   */     audsettings_t obt_as = *as;                                                   // (12) 0.0293
/*8   */     int esdfmt = ESD_STREAM | ESD_PLAY;                                           // (9) 0.03711
/*10  */     int err;                                                                      // (27) 0.01172
/*12  */     sigset_t set, old_set;                                                        // (14) 0.02539
/*16  */     sigfillset (&set);                                                            // (23) 0.01953
/*20  */     esdfmt |= (as->nchannels == 2) ? ESD_STEREO : ESD_MONO;                       // (0) 0.05859
/*22  */     switch (as->fmt) {                                                            // (22) 0.02148
/*24  */     case AUD_FMT_S8:                                                              // (18) 0.02344
/*26  */     case AUD_FMT_U8:                                                              // (16) 0.02344
/*28  */         esdfmt |= ESD_BITS8;                                                      // (11) 0.03711
/*30  */         obt_as.fmt = AUD_FMT_U8;                                                  // (3) 0.04492
/*32  */         break;                                                                    // (25) 0.01758
/*36  */     case AUD_FMT_S32:                                                             // (17) 0.02344
/*38  */     case AUD_FMT_U32:                                                             // (19) 0.02344
/*40  */         dolog ("Will use 16 instead of 32 bit samples\n");                        // (7) 0.04102
/*44  */     case AUD_FMT_S16:                                                             // (20) 0.02344
/*46  */     case AUD_FMT_U16:                                                             // (21) 0.02344
/*48  */     deffmt:                                                                       // (26) 0.01367
/*50  */         esdfmt |= ESD_BITS16;                                                     // (10) 0.03711
/*52  */         obt_as.fmt = AUD_FMT_S16;                                                 // (4) 0.04492
/*54  */         break;                                                                    // (24) 0.01758
/*58  */     default:                                                                      // (28) 0.009766
/*60  */         dolog ("Internal logic error: Bad audio format %d\n", as->fmt);           // (1) 0.05273
/*62  */         goto deffmt;                                                              // (15) 0.02344
/*66  */     }                                                                             // (29) 0.007812
/*68  */     obt_as.endianness = AUDIO_HOST_ENDIANNESS;                                    // (6) 0.04297
/*72  */     audio_pcm_init_info (&hw->info, &obt_as);                                     // (5) 0.04297
/*76  */     hw->samples = conf.samples;                                                   // (13) 0.02734
/*78  */     esd->pcm_buf = audio_calloc (AUDIO_FUNC, hw->samples, 1 << hw->info.shift);   // 0.0
/*80  */     if (!esd->pcm_buf) {                                                          // 0.0
/*82  */         dolog ("Could not allocate buffer (%d bytes)\n",                          // 0.0
/*84  */                hw->samples << hw->info.shift);                                    // 0.0
/*86  */         return -1;                                                                // 0.0
/*88  */     }                                                                             // 0.0
/*92  */     esd->fd = -1;                                                                 // 0.0
/*94  */     err = pthread_sigmask (SIG_BLOCK, &set, &old_set);                            // 0.0
/*96  */     if (err) {                                                                    // 0.0
/*98  */         qesd_logerr (err, "pthread_sigmask failed\n");                            // 0.0
/*100 */         goto fail1;                                                               // 0.0
/*102 */     }                                                                             // 0.0
/*106 */     esd->fd = esd_play_stream (esdfmt, as->freq, conf.dac_host, NULL);            // 0.0
/*108 */     if (esd->fd < 0) {                                                            // 0.0
/*110 */         qesd_logerr (errno, "esd_play_stream failed\n");                          // 0.0
/*112 */         goto fail2;                                                               // 0.0
/*114 */     }                                                                             // 0.0
/*118 */     if (audio_pt_init (&esd->pt, qesd_thread_out, esd, AUDIO_CAP, AUDIO_FUNC)) {  // 0.0
/*120 */         goto fail3;                                                               // 0.0
/*122 */     }                                                                             // 0.0
/*126 */     err = pthread_sigmask (SIG_SETMASK, &old_set, NULL);                          // 0.0
/*128 */     if (err) {                                                                    // 0.0
/*130 */         qesd_logerr (err, "pthread_sigmask(restore) failed\n");                   // 0.0
/*132 */     }                                                                             // 0.0
/*136 */     return 0;                                                                     // 0.0
/*140 */  fail3:                                                                           // 0.0
/*142 */     if (close (esd->fd)) {                                                        // 0.0
/*144 */         qesd_logerr (errno, "%s: close on esd socket(%d) failed\n",               // 0.0
/*146 */                      AUDIO_FUNC, esd->fd);                                        // 0.0
/*148 */     }                                                                             // 0.0
/*150 */     esd->fd = -1;                                                                 // 0.0
/*154 */  fail2:                                                                           // 0.0
/*156 */     err = pthread_sigmask (SIG_SETMASK, &old_set, NULL);                          // 0.0
/*158 */     if (err) {                                                                    // 0.0
/*160 */         qesd_logerr (err, "pthread_sigmask(restore) failed\n");                   // 0.0
/*162 */     }                                                                             // 0.0
/*166 */  fail1:                                                                           // 0.0
/*168 */     qemu_free (esd->pcm_buf);                                                     // 0.0
/*170 */     esd->pcm_buf = NULL;                                                          // 0.0
/*172 */     return -1;                                                                    // 0.0
/*174 */ }                                                                                 // 0.0
