// commit message FFmpeg@39e0accb7a (target=1, prob=0.43877965, correct=False): vf_remove_logo: domt access vf->next->query_format() directly but use the API. This fixes a crash
/*0  */ static unsigned int find_best(struct vf_instance *vf){                                         // (2) 0.129
/*2  */   int is_format_okay = vf->next->query_format(vf->next, IMGFMT_YV12);                          // (1) 0.25
/*4  */   if ((is_format_okay & VFCAP_CSP_SUPPORTED_BY_HW) || (is_format_okay & VFCAP_CSP_SUPPORTED))  // (0) 0.371
/*6  */     return IMGFMT_YV12;                                                                        // (3) 0.09677
/*8  */   else                                                                                         // (5) 0.01613
/*10 */     return 0;                                                                                  // (4) 0.04839
/*12 */ }                                                                                              // (6) 0.008065
