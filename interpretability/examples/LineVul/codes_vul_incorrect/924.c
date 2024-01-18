// commit message qemu@a9f8ad8f2a (target=1, prob=0.37461075, correct=False): Add SLOF-based partition firmware for pSeries machine, allowing more boot options
/*0  */ static void register_core_rtas(void)                                   // (3) 0.1068
/*2  */ {                                                                      // (5) 0.009709
/*4  */     spapr_rtas_register("display-character", rtas_display_character);  // (1) 0.233
/*6  */     spapr_rtas_register("get-time-of-day", rtas_get_time_of_day);      // (0) 0.3107
/*8  */     spapr_rtas_register("power-off", rtas_power_off);                  // (2) 0.233
/*13 */ }                                                                      // (4) 0.009709
