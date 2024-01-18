// commit message qemu@6e6e55f5c2 (target=0, prob=0.1322787, correct=True): qemu-img: Check for backing image if specified during create
/*0   */ static void QEMU_NORETURN help(void)                                                                // (15) 0.02539
/*2   */ {                                                                                                   // (22) 0.001953
/*4   */     const char *help_msg =                                                                          // (19) 0.01953
/*6   */            QEMU_IMG_VERSION                                                                         // (11) 0.03516
/*8   */            "usage: qemu-img [standard options] command [command options]\n"                         // (6) 0.05859
/*10  */            "QEMU disk image utility\n"                                                              // (9) 0.03906
/*12  */            "\n"                                                                                     // (18) 0.02539
/*14  */            "    '-h', '--help'       display this help and exit\n"                                  // (3) 0.07031
/*16  */            "    '-V', '--version'    output version information and exit\n"                         // (4) 0.06445
/*18  */            "    '-T', '--trace'      [[enable=]<pattern>][,events=<file>][,file=<file>]\n"          // (0) 0.09766
/*20  */            "                         specify tracing options\n"                                     // (1) 0.08008
/*22  */            "\n"                                                                                     // (17) 0.02539
/*24  */            "Command syntax:\n"                                                                      // (12) 0.03125
/*26  */ #define DEF(option, callback, arg_string)        \                                                  // (8) 0.03906
/*28  */            "  " arg_string "\n"                                                                     // (10) 0.03711
/*30  */ #include "qemu-img-cmds.h"                                                                          // (14) 0.02734
/*32  */ #undef DEF                                                                                          // (21) 0.007813
/*34  */ #undef GEN_DOCS                                                                                     // (20) 0.01367
/*36  */            "\n"                                                                                     // (16) 0.02539
/*38  */            "Command parameters:\n"                                                                  // (13) 0.03125
/*40  */            "  'filename' is a disk image filename\n"                                                // (7) 0.04492
/*42  */            "  'objectdef' is a QEMU user creatable object definition. See the qemu(1)\n"            // (2) 0.07227
/*44  */            "    manual page for a description of the object properties. The most common\n"          // (5) 0.05859
/*46  */            "    object type is a 'secret', which is used to supply passwords and/or\n"              // 0.0
/*48  */            "    encryption keys.\n"                                                                 // 0.0
/*50  */            "  'fmt' is the disk image format. It is guessed automatically in most cases\n"          // 0.0
/*52  */            "  'cache' is the cache mode used to write the output disk image, the valid\n"           // 0.0
/*54  */            "    options are: 'none', 'writeback' (default, except for convert), 'writethrough',\n"  // 0.0
/*56  */            "    'directsync' and 'unsafe' (default for convert)\n"                                  // 0.0
/*58  */            "  'src_cache' is the cache mode used to read input disk images, the valid\n"            // 0.0
/*60  */            "    options are the same as for the 'cache' option\n"                                   // 0.0
/*62  */            "  'size' is the disk image size in bytes. Optional suffixes\n"                          // 0.0
/*64  */            "    'k' or 'K' (kilobyte, 1024), 'M' (megabyte, 1024k), 'G' (gigabyte, 1024M),\n"       // 0.0
/*66  */            "    'T' (terabyte, 1024G), 'P' (petabyte, 1024T) and 'E' (exabyte, 1024P)  are\n"       // 0.0
/*68  */            "    supported. 'b' is ignored.\n"                                                       // 0.0
/*70  */            "  'output_filename' is the destination disk image filename\n"                           // 0.0
/*72  */            "  'output_fmt' is the destination format\n"                                             // 0.0
/*74  */            "  'options' is a comma separated list of format specific options in a\n"                // 0.0
/*76  */            "    name=value format. Use -o ? for an overview of the options supported by the\n"      // 0.0
/*78  */            "    used format\n"                                                                      // 0.0
/*80  */            "  'snapshot_param' is param used for internal snapshot, format\n"                       // 0.0
/*82  */            "    is 'snapshot.id=[ID],snapshot.name=[NAME]', or\n"                                   // 0.0
/*84  */            "    '[ID_OR_NAME]'\n"                                                                   // 0.0
/*86  */            "  'snapshot_id_or_name' is deprecated, use 'snapshot_param'\n"                          // 0.0
/*88  */            "    instead\n"                                                                          // 0.0
/*90  */            "  '-c' indicates that target image must be compressed (qcow format only)\n"             // 0.0
/*92  */            "  '-u' enables unsafe rebasing. It is assumed that old and new backing file\n"          // 0.0
/*94  */            "       match exactly. The image doesn't need a working backing file before\n"           // 0.0
/*96  */            "       rebasing in this case (useful for renaming the backing file)\n"                  // 0.0
/*98  */            "  '-h' with or without a command shows this help and lists the supported formats\n"     // 0.0
/*100 */            "  '-p' show progress of command (only certain commands)\n"                              // 0.0
/*102 */            "  '-q' use Quiet mode - do not print any output (except errors)\n"                      // 0.0
/*104 */            "  '-S' indicates the consecutive number of bytes (defaults to 4k) that must\n"          // 0.0
/*106 */            "       contain only zeros for qemu-img to create a sparse image during\n"               // 0.0
/*108 */            "       conversion. If the number of bytes is 0, the source will not be scanned for\n"   // 0.0
/*110 */            "       unallocated or zero sectors, and the destination image will always be\n"         // 0.0
/*112 */            "       fully allocated\n"                                                               // 0.0
/*114 */            "  '--output' takes the format in which the output must be done (human or json)\n"       // 0.0
/*116 */            "  '-n' skips the target volume creation (useful if the volume is created\n"             // 0.0
/*118 */            "       prior to running qemu-img)\n"                                                    // 0.0
/*120 */            "\n"                                                                                     // 0.0
/*122 */            "Parameters to check subcommand:\n"                                                      // 0.0
/*124 */            "  '-r' tries to repair any inconsistencies that are found during the check.\n"          // 0.0
/*126 */            "       '-r leaks' repairs only cluster leaks, whereas '-r all' fixes all\n"             // 0.0
/*128 */            "       kinds of errors, with a higher risk of choosing the wrong fix or\n"              // 0.0
/*130 */            "       hiding corruption that has already occurred.\n"                                  // 0.0
/*132 */            "\n"                                                                                     // 0.0
/*134 */            "Parameters to convert subcommand:\n"                                                    // 0.0
/*136 */            "  '-m' specifies how many coroutines work in parallel during the convert\n"             // 0.0
/*138 */            "       process (defaults to 8)\n"                                                       // 0.0
/*140 */            "  '-W' allow to write to the target out of order rather than sequential\n"              // 0.0
/*142 */            "\n"                                                                                     // 0.0
/*144 */            "Parameters to snapshot subcommand:\n"                                                   // 0.0
/*146 */            "  'snapshot' is the name of the snapshot to create, apply or delete\n"                  // 0.0
/*148 */            "  '-a' applies a snapshot (revert disk to saved state)\n"                               // 0.0
/*150 */            "  '-c' creates a snapshot\n"                                                            // 0.0
/*152 */            "  '-d' deletes a snapshot\n"                                                            // 0.0
/*154 */            "  '-l' lists all snapshots in the given image\n"                                        // 0.0
/*156 */            "\n"                                                                                     // 0.0
/*158 */            "Parameters to compare subcommand:\n"                                                    // 0.0
/*160 */            "  '-f' first image format\n"                                                            // 0.0
/*162 */            "  '-F' second image format\n"                                                           // 0.0
/*164 */            "  '-s' run in Strict mode - fail on different image size or sector allocation\n"        // 0.0
/*166 */            "\n"                                                                                     // 0.0
/*168 */            "Parameters to dd subcommand:\n"                                                         // 0.0
/*170 */            "  'bs=BYTES' read and write up to BYTES bytes at a time "                               // 0.0
/*172 */            "(default: 512)\n"                                                                       // 0.0
/*174 */            "  'count=N' copy only N input blocks\n"                                                 // 0.0
/*176 */            "  'if=FILE' read from FILE\n"                                                           // 0.0
/*178 */            "  'of=FILE' write to FILE\n"                                                            // 0.0
/*180 */            "  'skip=N' skip N bs-sized blocks at the start of input\n";                             // 0.0
/*184 */     printf("%s\nSupported formats:", help_msg);                                                     // 0.0
/*186 */     bdrv_iterate_format(format_print, NULL);                                                        // 0.0
/*188 */     printf("\n");                                                                                   // 0.0
/*190 */     exit(EXIT_SUCCESS);                                                                             // 0.0
/*192 */ }                                                                                                   // 0.0
