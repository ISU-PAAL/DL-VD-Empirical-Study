// commit message FFmpeg@c5be6192f0 (target=1, prob=0.26301697, correct=False): cmdutils: avoid using cpp directives within printf macro arguments
/*0   */ int show_license(void *optctx, const char *opt, const char *arg)                       // (5) 0.03906
/*2   */ {                                                                                      // (29) 0.001953
/*4   */     printf(                                                                            // (28) 0.009766
/*6   */ #if CONFIG_NONFREE                                                                     // (23) 0.01367
/*8   */     "This version of %s has nonfree parts compiled in.\n"                              // (11) 0.03711
/*10  */     "Therefore it is not legally redistributable.\n",                                  // (16) 0.03125
/*12  */     program_name                                                                       // (24) 0.01172
/*14  */ #elif CONFIG_GPLV3                                                                     // (21) 0.01758
/*16  */     "%s is free software; you can redistribute it and/or modify\n"                     // (3) 0.04102
/*18  */     "it under the terms of the GNU General Public License as published by\n"           // (6) 0.03906
/*20  */     "the Free Software Foundation; either version 3 of the License, or\n"              // (8) 0.03906
/*22  */     "(at your option) any later version.\n"                                            // (19) 0.0293
/*24  */     "\n"                                                                               // (26) 0.01172
/*26  */     "%s is distributed in the hope that it will be useful,\n"                          // (14) 0.03711
/*28  */     "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"                 // (13) 0.03711
/*30  */     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"                  // (2) 0.05078
/*32  */     "GNU General Public License for more details.\n"                                   // (17) 0.03125
/*34  */     "\n"                                                                               // (27) 0.01172
/*36  */     "You should have received a copy of the GNU General Public License\n"              // (12) 0.03711
/*38  */     "along with %s.  If not, see <http://www.gnu.org/licenses/>.\n",                   // (0) 0.05859
/*40  */     program_name, program_name, program_name                                           // (20) 0.02734
/*42  */ #elif CONFIG_GPL                                                                       // (22) 0.01367
/*44  */     "%s is free software; you can redistribute it and/or modify\n"                     // (4) 0.04102
/*46  */     "it under the terms of the GNU General Public License as published by\n"           // (7) 0.03906
/*48  */     "the Free Software Foundation; either version 2 of the License, or\n"              // (9) 0.03906
/*50  */     "(at your option) any later version.\n"                                            // (18) 0.0293
/*52  */     "\n"                                                                               // (25) 0.01172
/*54  */     "%s is distributed in the hope that it will be useful,\n"                          // (15) 0.03711
/*56  */     "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"                 // (10) 0.03711
/*58  */     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"                  // (1) 0.05078
/*60  */     "GNU General Public License for more details.\n"                                   // 0.0
/*62  */     "\n"                                                                               // 0.0
/*64  */     "You should have received a copy of the GNU General Public License\n"              // 0.0
/*66  */     "along with %s; if not, write to the Free Software\n"                              // 0.0
/*68  */     "Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA\n",  // 0.0
/*70  */     program_name, program_name, program_name                                           // 0.0
/*72  */ #elif CONFIG_LGPLV3                                                                    // 0.0
/*74  */     "%s is free software; you can redistribute it and/or modify\n"                     // 0.0
/*76  */     "it under the terms of the GNU Lesser General Public License as published by\n"    // 0.0
/*78  */     "the Free Software Foundation; either version 3 of the License, or\n"              // 0.0
/*80  */     "(at your option) any later version.\n"                                            // 0.0
/*82  */     "\n"                                                                               // 0.0
/*84  */     "%s is distributed in the hope that it will be useful,\n"                          // 0.0
/*86  */     "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"                 // 0.0
/*88  */     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"                  // 0.0
/*90  */     "GNU Lesser General Public License for more details.\n"                            // 0.0
/*92  */     "\n"                                                                               // 0.0
/*94  */     "You should have received a copy of the GNU Lesser General Public License\n"       // 0.0
/*96  */     "along with %s.  If not, see <http://www.gnu.org/licenses/>.\n",                   // 0.0
/*98  */     program_name, program_name, program_name                                           // 0.0
/*100 */ #else                                                                                  // 0.0
/*102 */     "%s is free software; you can redistribute it and/or\n"                            // 0.0
/*104 */     "modify it under the terms of the GNU Lesser General Public\n"                     // 0.0
/*106 */     "License as published by the Free Software Foundation; either\n"                   // 0.0
/*108 */     "version 2.1 of the License, or (at your option) any later version.\n"             // 0.0
/*110 */     "\n"                                                                               // 0.0
/*112 */     "%s is distributed in the hope that it will be useful,\n"                          // 0.0
/*114 */     "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"                 // 0.0
/*116 */     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n"              // 0.0
/*118 */     "Lesser General Public License for more details.\n"                                // 0.0
/*120 */     "\n"                                                                               // 0.0
/*122 */     "You should have received a copy of the GNU Lesser General Public\n"               // 0.0
/*124 */     "License along with %s; if not, write to the Free Software\n"                      // 0.0
/*126 */     "Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA\n",  // 0.0
/*128 */     program_name, program_name, program_name                                           // 0.0
/*130 */ #endif                                                                                 // 0.0
/*132 */     );                                                                                 // 0.0
/*136 */     return 0;                                                                          // 0.0
/*138 */ }                                                                                      // 0.0
