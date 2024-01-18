// commit message FFmpeg@4dbcdfa86d (target=0, prob=0.8146457, correct=False): AVOptions: remove AVOption.offset <= 0 checks
/*0  */ static int av_set_number2(void *obj, const char *name, double num, int den, int64_t intnum, const AVOption **o_out)  // (3) 0.07617
/*2  */ {                                                                                                                    // (20) 0.001953
/*4  */     const AVOption *o = av_opt_find(obj, name, NULL, 0, 0);                                                          // (8) 0.04883
/*6  */     void *dst;                                                                                                       // (18) 0.01563
/*8  */     if (o_out)                                                                                                       // (17) 0.01758
/*10 */         *o_out= o;                                                                                                   // (15) 0.02734
/*12 */     if (!o || o->offset<=0)                                                                                          // (13) 0.02734
/*14 */         return AVERROR_OPTION_NOT_FOUND;                                                                             // (9) 0.03906
/*18 */     if (o->max*den < num*intnum || o->min*den > num*intnum) {                                                        // (7) 0.05469
/*20 */         av_log(obj, AV_LOG_ERROR, "Value %lf for parameter '%s' out of range\n", num, name);                         // (4) 0.07617
/*22 */         return AVERROR(ERANGE);                                                                                      // (11) 0.0293
/*24 */     }                                                                                                                // (19) 0.007812
/*28 */     dst= ((uint8_t*)obj) + o->offset;                                                                                // (10) 0.03516
/*32 */     switch (o->type) {                                                                                               // (16) 0.01953
/*34 */     case FF_OPT_TYPE_FLAGS:                                                                                          // (12) 0.02734
/*36 */     case FF_OPT_TYPE_INT:   *(int       *)dst= llrint(num/den)*intnum; break;                                        // (2) 0.07812
/*38 */     case FF_OPT_TYPE_INT64: *(int64_t   *)dst= llrint(num/den)*intnum; break;                                        // (5) 0.07422
/*40 */     case FF_OPT_TYPE_FLOAT: *(float     *)dst= num*intnum/den;         break;                                        // (0) 0.08398
/*42 */     case FF_OPT_TYPE_DOUBLE:*(double    *)dst= num*intnum/den;         break;                                        // (1) 0.08203
/*44 */     case FF_OPT_TYPE_RATIONAL:                                                                                       // (14) 0.02734
/*46 */         if ((int)num == num) *(AVRational*)dst= (AVRational){num*intnum, den};                                       // (6) 0.07031
/*48 */         else                 *(AVRational*)dst= av_d2q(num*intnum/den, 1<<24);                                       // 0.0
/*50 */         break;                                                                                                       // 0.0
/*52 */     default:                                                                                                         // 0.0
/*54 */         return AVERROR(EINVAL);                                                                                      // 0.0
/*56 */     }                                                                                                                // 0.0
/*58 */     return 0;                                                                                                        // 0.0
/*60 */ }                                                                                                                    // 0.0
