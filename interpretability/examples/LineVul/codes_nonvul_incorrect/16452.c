// commit message FFmpeg@c96f3750c2 (target=0, prob=0.5878582, correct=False): postprocess: Remove test for impossible condition (was: Re: postprocess.c: replace check for p==NULL with *p==0)
/*0   */ pp_mode *pp_get_mode_by_name_and_quality(const char *name, int quality)                                // (0) 0.05078
/*2   */ {                                                                                                      // (31) 0.001953
/*4   */     char temp[GET_MODE_BUFFER_SIZE];                                                                   // (14) 0.0293
/*6   */     char *p= temp;                                                                                     // (28) 0.01758
/*8   */     static const char filterDelimiters[] = ",/";                                                       // (9) 0.03125
/*10  */     static const char optionDelimiters[] = ":";                                                        // (8) 0.03125
/*12  */     struct PPMode *ppMode;                                                                             // (23) 0.02149
/*14  */     char *filterToken;                                                                                 // (29) 0.01563
/*18  */     ppMode= av_malloc(sizeof(PPMode));                                                                 // (6) 0.03516
/*22  */     ppMode->lumMode= 0;                                                                                // (22) 0.02344
/*24  */     ppMode->chromMode= 0;                                                                              // (25) 0.02148
/*26  */     ppMode->maxTmpNoise[0]= 700;                                                                       // (10) 0.03125
/*28  */     ppMode->maxTmpNoise[1]= 1500;                                                                      // (12) 0.03125
/*30  */     ppMode->maxTmpNoise[2]= 3000;                                                                      // (13) 0.03125
/*32  */     ppMode->maxAllowedY= 234;                                                                          // (18) 0.02539
/*34  */     ppMode->minAllowedY= 16;                                                                           // (19) 0.02539
/*36  */     ppMode->baseDcDiff= 256/8;                                                                         // (15) 0.0293
/*38  */     ppMode->flatnessThreshold= 56-16-1;                                                                // (7) 0.0332
/*40  */     ppMode->maxClippedThreshold= 0.01;                                                                 // (11) 0.03125
/*42  */     ppMode->error=0;                                                                                   // (27) 0.01953
/*46  */     memset(temp, 0, GET_MODE_BUFFER_SIZE);                                                             // (5) 0.03711
/*48  */     av_strlcpy(temp, name, GET_MODE_BUFFER_SIZE - 1);                                                  // (2) 0.04688
/*52  */     av_log(NULL, AV_LOG_DEBUG, "pp: %s\n", name);                                                      // (1) 0.04883
/*56  */     for(;;){                                                                                           // (30) 0.01367
/*58  */         char *filterName;                                                                              // (20) 0.02344
/*60  */         int q= 1000000; //PP_QUALITY_MAX;                                                              // (3) 0.04297
/*62  */         int chrom=-1;                                                                                  // (21) 0.02344
/*64  */         int luma=-1;                                                                                   // (17) 0.02539
/*66  */         char *option;                                                                                  // (24) 0.02148
/*68  */         char *options[OPTIONS_ARRAY_SIZE];                                                             // (4) 0.03906
/*70  */         int i;                                                                                         // (26) 0.01953
/*72  */         int filterNameOk=0;                                                                            // (16) 0.02734
/*74  */         int numOfUnknownOptions=0;                                                                     // 0.0
/*76  */         int enable=1; //does the user want us to enabled or disabled the filter                        // 0.0
/*80  */         filterToken= strtok(p, filterDelimiters);                                                      // 0.0
/*82  */         if(filterToken == NULL) break;                                                                 // 0.0
/*84  */         p+= strlen(filterToken) + 1; // p points to next filterToken                                   // 0.0
/*86  */         filterName= strtok(filterToken, optionDelimiters);                                             // 0.0
/*88  */         av_log(NULL, AV_LOG_DEBUG, "pp: %s::%s\n", filterToken, filterName);                           // 0.0
/*92  */         if(*filterName == '-'){                                                                        // 0.0
/*94  */             enable=0;                                                                                  // 0.0
/*96  */             filterName++;                                                                              // 0.0
/*98  */         }                                                                                              // 0.0
/*102 */         for(;;){ //for all options                                                                     // 0.0
/*104 */             option= strtok(NULL, optionDelimiters);                                                    // 0.0
/*106 */             if(option == NULL) break;                                                                  // 0.0
/*110 */             av_log(NULL, AV_LOG_DEBUG, "pp: option: %s\n", option);                                    // 0.0
/*112 */             if(!strcmp("autoq", option) || !strcmp("a", option)) q= quality;                           // 0.0
/*114 */             else if(!strcmp("nochrom", option) || !strcmp("y", option)) chrom=0;                       // 0.0
/*116 */             else if(!strcmp("chrom", option) || !strcmp("c", option)) chrom=1;                         // 0.0
/*118 */             else if(!strcmp("noluma", option) || !strcmp("n", option)) luma=0;                         // 0.0
/*120 */             else{                                                                                      // 0.0
/*122 */                 options[numOfUnknownOptions] = option;                                                 // 0.0
/*124 */                 numOfUnknownOptions++;                                                                 // 0.0
/*126 */             }                                                                                          // 0.0
/*128 */             if(numOfUnknownOptions >= OPTIONS_ARRAY_SIZE-1) break;                                     // 0.0
/*130 */         }                                                                                              // 0.0
/*132 */         options[numOfUnknownOptions] = NULL;                                                           // 0.0
/*136 */         /* replace stuff from the replace Table */                                                     // 0.0
/*138 */         for(i=0; replaceTable[2*i]!=NULL; i++){                                                        // 0.0
/*140 */             if(!strcmp(replaceTable[2*i], filterName)){                                                // 0.0
/*142 */                 int newlen= strlen(replaceTable[2*i + 1]);                                             // 0.0
/*144 */                 int plen;                                                                              // 0.0
/*146 */                 int spaceLeft;                                                                         // 0.0
/*150 */                 if(p==NULL) p= temp, *p=0;      //last filter                                          // 0.0
/*152 */                 else p--, *p=',';               //not last filter                                      // 0.0
/*156 */                 plen= strlen(p);                                                                       // 0.0
/*158 */                 spaceLeft= p - temp + plen;                                                            // 0.0
/*160 */                 if(spaceLeft + newlen  >= GET_MODE_BUFFER_SIZE - 1){                                   // 0.0
/*162 */                     ppMode->error++;                                                                   // 0.0
/*164 */                     break;                                                                             // 0.0
/*166 */                 }                                                                                      // 0.0
/*168 */                 memmove(p + newlen, p, plen+1);                                                        // 0.0
/*170 */                 memcpy(p, replaceTable[2*i + 1], newlen);                                              // 0.0
/*172 */                 filterNameOk=1;                                                                        // 0.0
/*174 */             }                                                                                          // 0.0
/*176 */         }                                                                                              // 0.0
/*180 */         for(i=0; filters[i].shortName!=NULL; i++){                                                     // 0.0
/*182 */             if(   !strcmp(filters[i].longName, filterName)                                             // 0.0
/*184 */                || !strcmp(filters[i].shortName, filterName)){                                          // 0.0
/*186 */                 ppMode->lumMode &= ~filters[i].mask;                                                   // 0.0
/*188 */                 ppMode->chromMode &= ~filters[i].mask;                                                 // 0.0
/*192 */                 filterNameOk=1;                                                                        // 0.0
/*194 */                 if(!enable) break; // user wants to disable it                                         // 0.0
/*198 */                 if(q >= filters[i].minLumQuality && luma)                                              // 0.0
/*200 */                     ppMode->lumMode|= filters[i].mask;                                                 // 0.0
/*202 */                 if(chrom==1 || (chrom==-1 && filters[i].chromDefault))                                 // 0.0
/*204 */                     if(q >= filters[i].minChromQuality)                                                // 0.0
/*206 */                             ppMode->chromMode|= filters[i].mask;                                       // 0.0
/*210 */                 if(filters[i].mask == LEVEL_FIX){                                                      // 0.0
/*212 */                     int o;                                                                             // 0.0
/*214 */                     ppMode->minAllowedY= 16;                                                           // 0.0
/*216 */                     ppMode->maxAllowedY= 234;                                                          // 0.0
/*218 */                     for(o=0; options[o]!=NULL; o++){                                                   // 0.0
/*220 */                         if(  !strcmp(options[o],"fullyrange")                                          // 0.0
/*222 */                            ||!strcmp(options[o],"f")){                                                 // 0.0
/*224 */                             ppMode->minAllowedY= 0;                                                    // 0.0
/*226 */                             ppMode->maxAllowedY= 255;                                                  // 0.0
/*228 */                             numOfUnknownOptions--;                                                     // 0.0
/*230 */                         }                                                                              // 0.0
/*232 */                     }                                                                                  // 0.0
/*234 */                 }                                                                                      // 0.0
/*236 */                 else if(filters[i].mask == TEMP_NOISE_FILTER)                                          // 0.0
/*238 */                 {                                                                                      // 0.0
/*240 */                     int o;                                                                             // 0.0
/*242 */                     int numOfNoises=0;                                                                 // 0.0
/*246 */                     for(o=0; options[o]!=NULL; o++){                                                   // 0.0
/*248 */                         char *tail;                                                                    // 0.0
/*250 */                         ppMode->maxTmpNoise[numOfNoises]=                                              // 0.0
/*252 */                             strtol(options[o], &tail, 0);                                              // 0.0
/*254 */                         if(tail!=options[o]){                                                          // 0.0
/*256 */                             numOfNoises++;                                                             // 0.0
/*258 */                             numOfUnknownOptions--;                                                     // 0.0
/*260 */                             if(numOfNoises >= 3) break;                                                // 0.0
/*262 */                         }                                                                              // 0.0
/*264 */                     }                                                                                  // 0.0
/*266 */                 }                                                                                      // 0.0
/*268 */                 else if(filters[i].mask == V_DEBLOCK   || filters[i].mask == H_DEBLOCK                 // 0.0
/*270 */                      || filters[i].mask == V_A_DEBLOCK || filters[i].mask == H_A_DEBLOCK){             // 0.0
/*272 */                     int o;                                                                             // 0.0
/*276 */                     for(o=0; options[o]!=NULL && o<2; o++){                                            // 0.0
/*278 */                         char *tail;                                                                    // 0.0
/*280 */                         int val= strtol(options[o], &tail, 0);                                         // 0.0
/*282 */                         if(tail==options[o]) break;                                                    // 0.0
/*286 */                         numOfUnknownOptions--;                                                         // 0.0
/*288 */                         if(o==0) ppMode->baseDcDiff= val;                                              // 0.0
/*290 */                         else ppMode->flatnessThreshold= val;                                           // 0.0
/*292 */                     }                                                                                  // 0.0
/*294 */                 }                                                                                      // 0.0
/*296 */                 else if(filters[i].mask == FORCE_QUANT){                                               // 0.0
/*298 */                     int o;                                                                             // 0.0
/*300 */                     ppMode->forcedQuant= 15;                                                           // 0.0
/*304 */                     for(o=0; options[o]!=NULL && o<1; o++){                                            // 0.0
/*306 */                         char *tail;                                                                    // 0.0
/*308 */                         int val= strtol(options[o], &tail, 0);                                         // 0.0
/*310 */                         if(tail==options[o]) break;                                                    // 0.0
/*314 */                         numOfUnknownOptions--;                                                         // 0.0
/*316 */                         ppMode->forcedQuant= val;                                                      // 0.0
/*318 */                     }                                                                                  // 0.0
/*320 */                 }                                                                                      // 0.0
/*322 */             }                                                                                          // 0.0
/*324 */         }                                                                                              // 0.0
/*326 */         if(!filterNameOk) ppMode->error++;                                                             // 0.0
/*328 */         ppMode->error += numOfUnknownOptions;                                                          // 0.0
/*330 */     }                                                                                                  // 0.0
/*334 */     av_log(NULL, AV_LOG_DEBUG, "pp: lumMode=%X, chromMode=%X\n", ppMode->lumMode, ppMode->chromMode);  // 0.0
/*336 */     if(ppMode->error){                                                                                 // 0.0
/*338 */         av_log(NULL, AV_LOG_ERROR, "%d errors in postprocess string \"%s\"\n", ppMode->error, name);   // 0.0
/*340 */         av_free(ppMode);                                                                               // 0.0
/*342 */         return NULL;                                                                                   // 0.0
/*344 */     }                                                                                                  // 0.0
/*346 */     return ppMode;                                                                                     // 0.0
/*348 */ }                                                                                                      // 0.0
