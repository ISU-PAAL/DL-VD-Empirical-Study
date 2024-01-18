// commit message qemu@d044be3714 (target=0, prob=0.06865801, correct=True): hw/ac97: Make a bunch of mixer registers read only
/*0  */ static void mixer_reset (AC97LinkState *s)                              // (16) 0.02539
/*2  */ {                                                                       // (20) 0.001953
/*4  */     uint8_t active[LAST_INDEX];                                         // (14) 0.0293
/*8  */     dolog ("mixer_reset\n");                                            // (17) 0.02539
/*10 */     memset (s->mixer_data, 0, sizeof (s->mixer_data));                  // (12) 0.04687
/*12 */     memset (active, 0, sizeof (active));                                // (15) 0.02734
/*14 */     mixer_store (s, AC97_Reset                   , 0x0000); /* 6940 */  // (0) 0.08008
/*16 */     mixer_store (s, AC97_Master_Volume_Mono_Mute , 0x8000);             // (11) 0.05078
/*18 */     mixer_store (s, AC97_PC_BEEP_Volume_Mute     , 0x0000);             // (6) 0.05859
/*22 */     mixer_store (s, AC97_Phone_Volume_Mute       , 0x8008);             // (7) 0.05859
/*24 */     mixer_store (s, AC97_Mic_Volume_Mute         , 0x8008);             // (5) 0.0625
/*26 */     mixer_store (s, AC97_CD_Volume_Mute          , 0x8808);             // (3) 0.06445
/*28 */     mixer_store (s, AC97_Aux_Volume_Mute         , 0x8808);             // (4) 0.06445
/*30 */     mixer_store (s, AC97_Record_Gain_Mic_Mute    , 0x8000);             // (8) 0.05664
/*32 */     mixer_store (s, AC97_General_Purpose         , 0x0000);             // (9) 0.05664
/*34 */     mixer_store (s, AC97_3D_Control              , 0x0000);             // (2) 0.06641
/*36 */     mixer_store (s, AC97_Powerdown_Ctrl_Stat     , 0x000f);             // (10) 0.05469
/*40 */     /*                                                                  // (19) 0.007812
/*42 */      * Sigmatel 9700 (STAC9700)                                         // (13) 0.03125
/*44 */      */                                                                 // (18) 0.009766
/*46 */     mixer_store (s, AC97_Vendor_ID1              , 0x8384);             // (1) 0.07031
/*48 */     mixer_store (s, AC97_Vendor_ID2              , 0x7600); /* 7608 */  // 0.0
/*52 */     mixer_store (s, AC97_Extended_Audio_ID       , 0x0809);             // 0.0
/*54 */     mixer_store (s, AC97_Extended_Audio_Ctrl_Stat, 0x0009);             // 0.0
/*56 */     mixer_store (s, AC97_PCM_Front_DAC_Rate      , 0xbb80);             // 0.0
/*58 */     mixer_store (s, AC97_PCM_Surround_DAC_Rate   , 0xbb80);             // 0.0
/*60 */     mixer_store (s, AC97_PCM_LFE_DAC_Rate        , 0xbb80);             // 0.0
/*62 */     mixer_store (s, AC97_PCM_LR_ADC_Rate         , 0xbb80);             // 0.0
/*64 */     mixer_store (s, AC97_MIC_ADC_Rate            , 0xbb80);             // 0.0
/*68 */     record_select (s, 0);                                               // 0.0
/*70 */     set_volume (s, AC97_Master_Volume_Mute, 0x8000);                    // 0.0
/*72 */     set_volume (s, AC97_PCM_Out_Volume_Mute, 0x8808);                   // 0.0
/*74 */     set_volume (s, AC97_Line_In_Volume_Mute, 0x8808);                   // 0.0
/*78 */     reset_voices (s, active);                                           // 0.0
/*80 */ }                                                                       // 0.0
