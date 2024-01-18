// commit message FFmpeg@b04665ac02 (target=0, prob=0.37428907, correct=True): Make ffmpeg print in the error message the exact line of a preset file containing an invalid syntax.
/*0   */ static int opt_preset(const char *opt, const char *arg)                                                                   // (11) 0.0332
/*2   */ {                                                                                                                         // (19) 0.001953
/*4   */     FILE *f=NULL;                                                                                                         // (15) 0.01758
/*6   */     char filename[1000], tmp[1000], tmp2[1000], line[1000];                                                               // (9) 0.04102
/*8   */     int i;                                                                                                                // (17) 0.01172
/*10  */     const char *base[3]= { getenv("HOME"),                                                                                // (13) 0.03125
/*12  */                            "/usr/local/share",                                                                            // (4) 0.06445
/*14  */                            "/usr/share",                                                                                  // (6) 0.06055
/*16  */                          };                                                                                               // (7) 0.04883
/*20  */     for(i=!base[0]; i<3 && !f; i++){                                                                                      // (8) 0.04297
/*22  */         snprintf(filename, sizeof(filename), "%s/%sffmpeg/%s.ffpreset", base[i], i ? "" : ".", arg);                      // (2) 0.08398
/*24  */         f= fopen(filename, "r");                                                                                          // (12) 0.0332
/*26  */         if(!f){                                                                                                           // (14) 0.02344
/*28  */             char *codec_name= *opt == 'v' ? video_codec_name :                                                            // (5) 0.0625
/*30  */                               *opt == 'a' ? audio_codec_name :                                                            // (3) 0.08398
/*32  */                                             subtitle_codec_name;                                                          // (1) 0.09766
/*34  */             snprintf(filename, sizeof(filename), "%s/%sffmpeg/%s-%s.ffpreset", base[i],  i ? "" : ".", codec_name, arg);  // (0) 0.1074
/*36  */             f= fopen(filename, "r");                                                                                      // (10) 0.04102
/*38  */         }                                                                                                                 // (16) 0.01562
/*40  */     }                                                                                                                     // (18) 0.007812
/*42  */     if(!f && ((arg[0]=='.' && arg[1]=='/') || arg[0]=='/' ||                                                              // 0.0
/*44  */               is_dos_path(arg))){                                                                                         // 0.0
/*46  */         snprintf(filename, sizeof(filename), arg);                                                                        // 0.0
/*48  */         f= fopen(filename, "r");                                                                                          // 0.0
/*50  */     }                                                                                                                     // 0.0
/*54  */     if(!f){                                                                                                               // 0.0
/*56  */         fprintf(stderr, "File for preset '%s' not found\n", arg);                                                         // 0.0
/*58  */         av_exit(1);                                                                                                       // 0.0
/*60  */     }                                                                                                                     // 0.0
/*64  */     while(!feof(f)){                                                                                                      // 0.0
/*66  */         int e= fscanf(f, "%999[^\n]\n", line) - 1;                                                                        // 0.0
/*68  */         if(line[0] == '#' && !e)                                                                                          // 0.0
/*70  */             continue;                                                                                                     // 0.0
/*72  */         e|= sscanf(line, "%999[^=]=%999[^\n]\n", tmp, tmp2) - 2;                                                          // 0.0
/*74  */         if(e){                                                                                                            // 0.0
/*76  */             fprintf(stderr, "%s: Preset file invalid\n", filename);                                                       // 0.0
/*78  */             av_exit(1);                                                                                                   // 0.0
/*80  */         }                                                                                                                 // 0.0
/*82  */         if(!strcmp(tmp, "acodec")){                                                                                       // 0.0
/*84  */             opt_audio_codec(tmp2);                                                                                        // 0.0
/*86  */         }else if(!strcmp(tmp, "vcodec")){                                                                                 // 0.0
/*88  */             opt_video_codec(tmp2);                                                                                        // 0.0
/*90  */         }else if(!strcmp(tmp, "scodec")){                                                                                 // 0.0
/*92  */             opt_subtitle_codec(tmp2);                                                                                     // 0.0
/*94  */         }else if(opt_default(tmp, tmp2) < 0){                                                                             // 0.0
/*96  */             fprintf(stderr, "%s: Invalid option or argument: %s=%s\n", filename, tmp, tmp2);                              // 0.0
/*98  */             av_exit(1);                                                                                                   // 0.0
/*100 */         }                                                                                                                 // 0.0
/*102 */     }                                                                                                                     // 0.0
/*106 */     fclose(f);                                                                                                            // 0.0
/*110 */     return 0;                                                                                                             // 0.0
/*112 */ }                                                                                                                         // 0.0
