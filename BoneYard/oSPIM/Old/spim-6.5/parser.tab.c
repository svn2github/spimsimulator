
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	Y_EOF	257
#define	Y_NL	258
#define	Y_INT	259
#define	Y_ID	260
#define	Y_REG	261
#define	Y_FP_REG	262
#define	Y_STR	263
#define	Y_FP	264
#define	Y_ABS_D_OP	265
#define	Y_ABS_S_OP	266
#define	Y_ADDIU_OP	267
#define	Y_ADDI_OP	268
#define	Y_ADDU_OP	269
#define	Y_ADD_D_OP	270
#define	Y_ADD_OP	271
#define	Y_ADD_S_OP	272
#define	Y_ANDI_OP	273
#define	Y_AND_OP	274
#define	Y_BC0F_OP	275
#define	Y_BC0T_OP	276
#define	Y_BC1F_OP	277
#define	Y_BC1T_OP	278
#define	Y_BC2F_OP	279
#define	Y_BC2T_OP	280
#define	Y_BC3F_OP	281
#define	Y_BC3T_OP	282
#define	Y_BEQ_OP	283
#define	Y_BGEZAL_OP	284
#define	Y_BGEZ_OP	285
#define	Y_BGTZ_OP	286
#define	Y_BLEZ_OP	287
#define	Y_BLTZAL_OP	288
#define	Y_BLTZ_OP	289
#define	Y_BNE_OP	290
#define	Y_BREAK_OP	291
#define	Y_CFC0_OP	292
#define	Y_CFC1_OP	293
#define	Y_CFC2_OP	294
#define	Y_CFC3_OP	295
#define	Y_COP0_OP	296
#define	Y_COP1_OP	297
#define	Y_COP2_OP	298
#define	Y_COP3_OP	299
#define	Y_CTC0_OP	300
#define	Y_CTC1_OP	301
#define	Y_CTC2_OP	302
#define	Y_CTC3_OP	303
#define	Y_CVT_D_S_OP	304
#define	Y_CVT_D_W_OP	305
#define	Y_CVT_S_D_OP	306
#define	Y_CVT_S_W_OP	307
#define	Y_CVT_W_D_OP	308
#define	Y_CVT_W_S_OP	309
#define	Y_C_EQ_D_OP	310
#define	Y_C_EQ_S_OP	311
#define	Y_C_F_D_OP	312
#define	Y_C_F_S_OP	313
#define	Y_C_LE_D_OP	314
#define	Y_C_LE_S_OP	315
#define	Y_C_LT_D_OP	316
#define	Y_C_LT_S_OP	317
#define	Y_C_NGE_D_OP	318
#define	Y_C_NGE_S_OP	319
#define	Y_C_NGLE_D_OP	320
#define	Y_C_NGLE_S_OP	321
#define	Y_C_NGL_D_OP	322
#define	Y_C_NGL_S_OP	323
#define	Y_C_NGT_D_OP	324
#define	Y_C_NGT_S_OP	325
#define	Y_C_OLT_D_OP	326
#define	Y_C_OLT_S_OP	327
#define	Y_C_OLE_D_OP	328
#define	Y_C_OLE_S_OP	329
#define	Y_C_SEQ_D_OP	330
#define	Y_C_SEQ_S_OP	331
#define	Y_C_SF_D_OP	332
#define	Y_C_SF_S_OP	333
#define	Y_C_UEQ_D_OP	334
#define	Y_C_UEQ_S_OP	335
#define	Y_C_ULT_D_OP	336
#define	Y_C_ULT_S_OP	337
#define	Y_C_ULE_D_OP	338
#define	Y_C_ULE_S_OP	339
#define	Y_C_UN_D_OP	340
#define	Y_C_UN_S_OP	341
#define	Y_DIVU_OP	342
#define	Y_DIV_D_OP	343
#define	Y_DIV_OP	344
#define	Y_DIV_S_OP	345
#define	Y_JALR_OP	346
#define	Y_JAL_OP	347
#define	Y_JR_OP	348
#define	Y_J_OP	349
#define	Y_LBU_OP	350
#define	Y_LB_OP	351
#define	Y_LHU_OP	352
#define	Y_LH_OP	353
#define	Y_LUI_OP	354
#define	Y_LWC0_OP	355
#define	Y_LWC1_OP	356
#define	Y_LWC2_OP	357
#define	Y_LWC3_OP	358
#define	Y_LWL_OP	359
#define	Y_LWR_OP	360
#define	Y_LW_OP	361
#define	Y_MFC0_OP	362
#define	Y_MFC1_OP	363
#define	Y_MFC2_OP	364
#define	Y_MFC3_OP	365
#define	Y_MFHI_OP	366
#define	Y_MFLO_OP	367
#define	Y_MOV_D_OP	368
#define	Y_MOV_S_OP	369
#define	Y_MTC0_OP	370
#define	Y_MTC1_OP	371
#define	Y_MTC2_OP	372
#define	Y_MTC3_OP	373
#define	Y_MTHI_OP	374
#define	Y_MTLO_OP	375
#define	Y_MULTU_OP	376
#define	Y_MULT_OP	377
#define	Y_MUL_D_OP	378
#define	Y_MUL_S_OP	379
#define	Y_NEG_D_OP	380
#define	Y_NEG_S_OP	381
#define	Y_NOR_OP	382
#define	Y_ORI_OP	383
#define	Y_OR_OP	384
#define	Y_PFW_OP	385
#define	Y_RFE_OP	386
#define	Y_SB_OP	387
#define	Y_SH_OP	388
#define	Y_SLLV_OP	389
#define	Y_SLL_OP	390
#define	Y_SLTIU_OP	391
#define	Y_SLTI_OP	392
#define	Y_SLTU_OP	393
#define	Y_SLT_OP	394
#define	Y_SRAV_OP	395
#define	Y_SRA_OP	396
#define	Y_SRLV_OP	397
#define	Y_SRL_OP	398
#define	Y_SUBU_OP	399
#define	Y_SUB_D_OP	400
#define	Y_SUB_OP	401
#define	Y_SUB_S_OP	402
#define	Y_SWC0_OP	403
#define	Y_SWC1_OP	404
#define	Y_SWC2_OP	405
#define	Y_SWC3_OP	406
#define	Y_SWL_OP	407
#define	Y_SWR_OP	408
#define	Y_SW_OP	409
#define	Y_SYSCALL_OP	410
#define	Y_TLBP_OP	411
#define	Y_TLBR_OP	412
#define	Y_TLBWI_OP	413
#define	Y_TLBWR_OP	414
#define	Y_XORI_OP	415
#define	Y_XOR_OP	416
#define	Y_ABS_POP	417
#define	Y_BAL_POP	418
#define	Y_BEQZ_POP	419
#define	Y_BGEU_POP	420
#define	Y_BGE_POP	421
#define	Y_BGTU_POP	422
#define	Y_BGT_POP	423
#define	Y_BLEU_POP	424
#define	Y_BLE_POP	425
#define	Y_BLTU_POP	426
#define	Y_BLT_POP	427
#define	Y_BNEZ_POP	428
#define	Y_B_POP	429
#define	Y_LA_POP	430
#define	Y_LD_POP	431
#define	Y_LI_POP	432
#define	Y_LI_D_POP	433
#define	Y_LI_S_POP	434
#define	Y_L_D_POP	435
#define	Y_L_S_POP	436
#define	Y_MFC1_D_POP	437
#define	Y_MTC1_D_POP	438
#define	Y_MOVE_POP	439
#define	Y_MULOU_POP	440
#define	Y_MULO_POP	441
#define	Y_MUL_POP	442
#define	Y_NEGU_POP	443
#define	Y_NEG_POP	444
#define	Y_NOP_POP	445
#define	Y_NOT_POP	446
#define	Y_REMU_POP	447
#define	Y_REM_POP	448
#define	Y_ROL_POP	449
#define	Y_ROR_POP	450
#define	Y_SD_POP	451
#define	Y_SEQ_POP	452
#define	Y_SGEU_POP	453
#define	Y_SGE_POP	454
#define	Y_SGTU_POP	455
#define	Y_SGT_POP	456
#define	Y_SLEU_POP	457
#define	Y_SLE_POP	458
#define	Y_SNE_POP	459
#define	Y_S_D_POP	460
#define	Y_S_S_POP	461
#define	Y_ULHU_POP	462
#define	Y_ULH_POP	463
#define	Y_ULW_POP	464
#define	Y_USH_POP	465
#define	Y_USW_POP	466
#define	Y_ALIAS_DIR	467
#define	Y_ALIGN_DIR	468
#define	Y_ASCII_DIR	469
#define	Y_ASCIIZ_DIR	470
#define	Y_ASM0_DIR	471
#define	Y_BGNB_DIR	472
#define	Y_BYTE_DIR	473
#define	Y_COMM_DIR	474
#define	Y_DATA_DIR	475
#define	Y_DOUBLE_DIR	476
#define	Y_ENDB_DIR	477
#define	Y_ENDR_DIR	478
#define	Y_END_DIR	479
#define	Y_ENT_DIR	480
#define	Y_ERR_DIR	481
#define	Y_EXTERN_DIR	482
#define	Y_FILE_DIR	483
#define	Y_FLOAT_DIR	484
#define	Y_FMASK_DIR	485
#define	Y_FRAME_DIR	486
#define	Y_GLOBAL_DIR	487
#define	Y_HALF_DIR	488
#define	Y_K_TEXT_DIR	489
#define	Y_K_DATA_DIR	490
#define	Y_LABEL_DIR	491
#define	Y_LCOMM_DIR	492
#define	Y_LIVEREG_DIR	493
#define	Y_LOC_DIR	494
#define	Y_MASK_DIR	495
#define	Y_NOALIAS_DIR	496
#define	Y_OPTIONS_DIR	497
#define	Y_RDATA_DIR	498
#define	Y_REPEAT_DIR	499
#define	Y_SDATA_DIR	500
#define	Y_SET_DIR	501
#define	Y_SPACE_DIR	502
#define	Y_STRUCT_DIR	503
#define	Y_TEXT_DIR	504
#define	Y_VERSTAMP_DIR	505
#define	Y_VREG_DIR	506
#define	Y_WORD_DIR	507

#line 293 "parser.y"

#include <stdio.h>

#include "spim.h"
#include "spim-utils.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "sym-tbl.h"
#include "data.h"
#include "scanner.h"
#include "parser.h"


/* return (0) */
#define LINE_PARSE_DONE YYACCEPT

/* return (1) */
#define FILE_PARSE_DONE YYABORT

typedef struct ll
{
  label *head;
  struct ll *tail;
} label_list;


/* Exported Variables: */

int data_dir;			/* Non-zero means item in data segment */

int text_dir;			/* Non-zero means item in text segment */

int parse_error_occurred;  /* Non-zero => parse resulted in error */


/* Local functions: */

#ifdef __STDC__
static imm_expr *branch_offset (int n_inst);
static void check_imm_range (imm_expr*, int32, int32);
static void check_uimm_range (imm_expr*, uint32, uint32);
static void clear_labels (void);
static label_list *cons_label (label *head, label_list *tail);
static void div_inst (int op, int rd, int rs, int rt, int const_divisor);
static void mult_inst (int op, int rd, int rs, int rt);
static void nop_inst (void);
static void set_eq_inst (int op, int rd, int rs, int rt);
static void set_ge_inst (int op, int rd, int rs, int rt);
static void set_gt_inst (int op, int rd, int rs, int rt);
static void set_le_inst (int op, int rd, int rs, int rt);
static void store_word_data (int value);
static void trap_inst (void);
static void yywarn (char*);
#else
static imm_expr *branch_offset ();
static void check_imm_range();
static void check_uimm_range();
static void clear_labels ();
static label_list *cons_label ();
static void div_inst ();
static void mult_inst ();
static void nop_inst ();
static void set_eq_inst ();
static void set_ge_inst ();
static void set_gt_inst ();
static void set_le_inst ();
static void store_word_data ();
static void trap_inst ();
static void yywarn ();
#endif


/* Local variables: */

static int null_term;		/* Non-zero means string terminate by \0 */

static void (*store_op) ();	/* Function to store items in an EXPR_LST */

static label_list *this_line_labels = NULL; /* List of label for curent line */

static int noat_flag = 0;	/* Non-zero means program can use $1 */

static char *input_file_name;	/* Name of file being parsed */

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		601
#define	YYFLAG		-32768
#define	YYNTBASE	261

#define YYTRANSLATE(x) ((unsigned)(x) <= 507 ? yytranslate[x] : 355)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   256,
   257,     2,   258,     2,   259,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   254,     2,     2,
   255,   260,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
   197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
   227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
   237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
   247,   248,   249,   250,   251,   252,   253
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     9,    12,    16,    17,    21,    22,
    26,    28,    30,    32,    36,    40,    44,    48,    52,    56,
    60,    64,    68,    72,    76,    80,    84,    88,    92,    94,
    97,    99,   103,   107,   111,   115,   119,   124,   129,   133,
   138,   143,   147,   152,   156,   161,   165,   170,   175,   180,
   185,   189,   194,   199,   203,   207,   212,   217,   222,   227,
   231,   236,   241,   246,   251,   256,   261,   266,   271,   276,
   281,   286,   291,   294,   298,   302,   307,   312,   317,   322,
   327,   332,   337,   342,   347,   352,   355,   358,   362,   365,
   369,   372,   375,   379,   383,   387,   392,   396,   400,   404,
   406,   408,   410,   412,   414,   416,   418,   420,   422,   424,
   426,   428,   430,   432,   434,   436,   438,   440,   442,   444,
   446,   448,   450,   452,   454,   456,   458,   460,   462,   464,
   466,   468,   470,   472,   474,   476,   478,   480,   482,   484,
   486,   488,   490,   492,   494,   496,   498,   500,   502,   504,
   506,   508,   510,   512,   514,   516,   518,   520,   522,   524,
   526,   528,   530,   532,   534,   536,   538,   540,   542,   544,
   546,   548,   550,   552,   554,   556,   558,   560,   562,   564,
   566,   568,   570,   572,   574,   576,   578,   580,   582,   584,
   586,   588,   590,   592,   594,   596,   598,   600,   602,   604,
   606,   608,   610,   612,   614,   616,   618,   620,   622,   624,
   626,   628,   630,   632,   634,   636,   638,   640,   642,   644,
   646,   648,   650,   652,   654,   656,   658,   660,   662,   664,
   666,   668,   670,   672,   674,   676,   678,   680,   682,   684,
   686,   688,   690,   692,   694,   696,   698,   700,   702,   704,
   706,   708,   710,   712,   714,   716,   718,   720,   722,   724,
   726,   728,   730,   732,   734,   736,   738,   740,   742,   744,
   746,   748,   750,   752,   754,   756,   758,   760,   764,   767,
   768,   772,   773,   777,   779,   782,   783,   787,   791,   793,
   796,   798,   801,   802,   806,   809,   812,   814,   817,   821,
   825,   827,   831,   832,   836,   840,   845,   848,   849,   853,
   856,   860,   864,   868,   872,   876,   879,   882,   884,   887,
   889,   892,   895,   898,   901,   903,   906,   908,   911,   915,
   920,   921,   925,   926,   929,   933,   935,   940,   942,   947,
   951,   955,   959,   966,   973,   974,   977,   979,   981,   983,
   990,   992,   996,  1000,  1002,  1006,  1009,  1011,  1013,  1015,
  1017,  1019,  1021,  1023,  1025,  1027,  1029,  1031,  1033,  1035,
  1037,  1040,  1042,  1044,  1048,  1049,  1052,  1054,  1056,  1059,
  1061,  1065,  1068,  1070,  1071,  1074,  1076,  1077,  1078
};

static const short yyrhs[] = {    -1,
   262,   263,     0,   264,   265,     0,   265,     0,   353,   254,
     0,   353,   255,     5,     0,     0,   269,   266,   268,     0,
     0,   313,   267,   268,     0,   268,     0,     4,     0,     3,
     0,   270,   330,   321,     0,   271,   341,   321,     0,   272,
   330,   327,     0,   176,   330,   321,     0,   178,   330,   328,
     0,   179,   337,    10,     0,   180,   337,    10,     0,   210,
   330,   321,     0,   273,   330,   321,     0,   274,   337,   321,
     0,   275,   335,   321,     0,   276,   341,   321,     0,   212,
   335,   321,     0,   211,   335,   321,     0,   277,   338,   321,
     0,   278,     0,    37,     5,     0,   191,     0,   163,   330,
   331,     0,   190,   330,   331,     0,   189,   330,   331,     0,
   192,   330,   331,     0,   185,   330,   331,     0,   279,   330,
   331,   332,     0,   279,   330,   331,   328,     0,   279,   330,
   328,     0,   280,   330,   331,   332,     0,   280,   330,   331,
     5,     0,   280,   330,     5,     0,   281,   330,   331,   326,
     0,   281,   330,   326,     0,   282,   330,   331,   327,     0,
   282,   330,   327,     0,   283,   330,   331,     5,     0,   283,
   330,   331,   332,     0,   284,   330,   331,   332,     0,   284,
   330,   331,   328,     0,   284,   330,   328,     0,   285,   330,
   331,   332,     0,   285,   330,   331,   328,     0,   285,   330,
   328,     0,   286,   330,   331,     0,   286,   330,   331,   332,
     0,   286,   330,   331,   328,     0,   287,   330,   331,   332,
     0,   287,   330,   331,   328,     0,   292,   331,   332,     0,
   196,   330,   331,   332,     0,   195,   330,   331,   332,     0,
   196,   330,   331,   328,     0,   195,   330,   331,   328,     0,
   288,   330,   331,   332,     0,   288,   330,   331,   328,     0,
   289,   330,   331,   332,     0,   289,   330,   331,   328,     0,
   290,   330,   331,   332,     0,   290,   330,   331,   328,     0,
   291,   330,   331,   332,     0,   291,   330,   331,   328,     0,
   293,   342,     0,   294,   331,   342,     0,   295,   331,   342,
     0,   296,   331,   332,   342,     0,   296,   331,   324,   342,
     0,   297,   331,   332,   342,     0,   297,   331,   324,   342,
     0,   298,   331,   332,   342,     0,   298,   331,   324,   342,
     0,   299,   331,   332,   342,     0,   299,   331,   324,   342,
     0,   300,   331,   332,   342,     0,   300,   331,   324,   342,
     0,   301,   342,     0,   301,   331,     0,   301,   333,   331,
     0,   302,   342,     0,   303,   341,   341,     0,   304,   334,
     0,   305,   334,     0,   306,   334,   341,     0,   307,   341,
   341,     0,   308,   337,   338,     0,   309,   337,   338,   339,
     0,   310,   337,   339,     0,   311,   337,   339,     0,   312,
   338,   339,     0,    97,     0,    96,     0,    99,     0,    98,
     0,   107,     0,   105,     0,   106,     0,   177,     0,   131,
     0,   101,     0,   103,     0,   104,     0,   100,     0,   209,
     0,   208,     0,   102,     0,   182,     0,   181,     0,   133,
     0,   134,     0,   155,     0,   153,     0,   154,     0,   197,
     0,   149,     0,   151,     0,   152,     0,   150,     0,   207,
     0,   206,     0,   132,     0,   156,     0,    17,     0,    15,
     0,    20,     0,   162,     0,   130,     0,   140,     0,   139,
     0,   135,     0,   141,     0,   143,     0,    14,     0,    13,
     0,   138,     0,   137,     0,    19,     0,   129,     0,   161,
     0,   136,     0,   142,     0,   144,     0,   128,     0,   147,
     0,   145,     0,    90,     0,    88,     0,   194,     0,   193,
     0,   188,     0,   187,     0,   186,     0,   204,     0,   203,
     0,   202,     0,   201,     0,   200,     0,   199,     0,   198,
     0,   205,     0,   123,     0,   122,     0,    22,     0,    24,
     0,    26,     0,    28,     0,    21,     0,    23,     0,    25,
     0,    27,     0,    31,     0,    30,     0,    32,     0,    33,
     0,    35,     0,    34,     0,   165,     0,   174,     0,    29,
     0,    36,     0,   169,     0,   168,     0,   167,     0,   166,
     0,   173,     0,   172,     0,   171,     0,   170,     0,    95,
     0,    94,     0,    93,     0,    92,     0,   175,     0,   164,
     0,   115,     0,   114,     0,   112,     0,   113,     0,   120,
     0,   121,     0,   108,     0,   109,     0,   183,     0,   110,
     0,   111,     0,   116,     0,   117,     0,   184,     0,   118,
     0,   119,     0,    38,     0,    39,     0,    40,     0,    41,
     0,    46,     0,    47,     0,    48,     0,    49,     0,    12,
     0,    11,     0,    18,     0,    16,     0,    91,     0,    89,
     0,   125,     0,   124,     0,   148,     0,   146,     0,    50,
     0,    51,     0,    52,     0,    53,     0,    54,     0,    55,
     0,   127,     0,   126,     0,    59,     0,    87,     0,    57,
     0,    81,     0,    73,     0,    75,     0,    83,     0,    85,
     0,    79,     0,    67,     0,    77,     0,    69,     0,    63,
     0,    65,     0,    61,     0,    71,     0,    58,     0,    86,
     0,    56,     0,    80,     0,    72,     0,    74,     0,    82,
     0,    84,     0,    78,     0,    66,     0,    76,     0,    68,
     0,    62,     0,    64,     0,    60,     0,    70,     0,   213,
     7,     7,     0,   214,   347,     0,     0,   215,   314,   343,
     0,     0,   216,   315,   343,     0,   217,     0,   218,     5,
     0,     0,   219,   316,   348,     0,   220,   353,   347,     0,
   221,     0,   221,     5,     0,   236,     0,   236,     5,     0,
     0,   222,   317,   349,     0,   225,   350,     0,   223,     5,
     0,   224,     0,   226,   353,     0,   226,   353,     5,     0,
   228,   353,   347,     0,   227,     0,   229,     5,     9,     0,
     0,   230,   318,   349,     0,   231,     5,     5,     0,   232,
   336,     5,   336,     0,   233,   353,     0,     0,   234,   319,
   348,     0,   237,   353,     0,   238,   353,   347,     0,   239,
     5,     5,     0,   240,     5,     5,     0,   241,     5,     5,
     0,   242,     7,     7,     0,   243,   353,     0,   245,   347,
     0,   244,     0,   244,     5,     0,   246,     0,   246,     5,
     0,   247,   353,     0,   248,   347,     0,   249,   347,     0,
   250,     0,   250,     5,     0,   235,     0,   235,     5,     0,
   251,     5,     5,     0,   252,   336,     5,     5,     0,     0,
   253,   320,   348,     0,     0,   322,   323,     0,   256,   336,
   257,     0,   329,     0,   329,   256,   336,   257,     0,     6,
     0,     6,   256,   336,   257,     0,     6,   258,   329,     0,
   329,   258,   353,     0,     6,   259,   329,     0,     6,   258,
   329,   256,   336,   257,     0,     6,   259,   329,   256,   336,
   257,     0,     0,   325,   328,     0,   328,     0,   328,     0,
   329,     0,   256,   329,   257,   260,   260,     5,     0,   353,
     0,     6,   258,   329,     0,     6,   259,   329,     0,     5,
     0,     5,   258,     5,     0,     5,     5,     0,   336,     0,
   336,     0,   336,     0,   336,     0,   336,     0,   336,     0,
     7,     0,   340,     0,   340,     0,   340,     0,     8,     0,
     7,     0,     8,     0,   353,     0,   343,   344,     0,   344,
     0,     9,     0,     9,   254,     5,     0,     0,   346,   347,
     0,     5,     0,   353,     0,   348,   345,     0,   345,     0,
   345,   254,     5,     0,   349,    10,     0,    10,     0,     0,
   351,   352,     0,   353,     0,     0,     0,   354,     6,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   384,   384,   386,   387,   391,   402,   413,   419,   419,   425,
   425,   429,   434,   443,   459,   467,   473,   487,   493,   504,
   514,   538,   566,   581,   597,   607,   631,   649,   664,   670,
   678,   684,   694,   700,   706,   712,   718,   724,   731,   738,
   744,   750,   756,   762,   767,   773,   779,   787,   793,   799,
   817,   836,   842,   859,   876,   885,   891,   904,   909,   923,
   929,   938,   947,   959,   972,   977,   988,   993,  1005,  1010,
  1021,  1026,  1037,  1043,  1049,  1056,  1061,  1085,  1092,  1115,
  1122,  1131,  1138,  1147,  1154,  1177,  1187,  1196,  1205,  1213,
  1219,  1225,  1231,  1248,  1254,  1260,  1266,  1272,  1278,  1286,
  1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,  1297,  1298,
  1299,  1302,  1305,  1306,  1309,  1310,  1311,  1315,  1316,  1317,
  1318,  1319,  1320,  1323,  1324,  1325,  1328,  1329,  1330,  1334,
  1335,  1341,  1342,  1343,  1344,  1345,  1346,  1347,  1350,  1351,
  1352,  1355,  1356,  1357,  1358,  1361,  1362,  1363,  1366,  1367,
  1368,  1373,  1375,  1376,  1379,  1380,  1381,  1382,  1385,  1386,
  1387,  1390,  1391,  1394,  1395,  1398,  1399,  1402,  1403,  1406,
  1407,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1420,
  1421,  1422,  1423,  1424,  1425,  1428,  1429,  1432,  1433,  1436,
  1437,  1439,  1440,  1442,  1443,  1445,  1446,  1449,  1450,  1451,
  1452,  1455,  1456,  1459,  1460,  1463,  1464,  1467,  1468,  1471,
  1472,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,  1483,
  1484,  1485,  1486,  1487,  1488,  1489,  1490,  1493,  1494,  1497,
  1498,  1499,  1500,  1501,  1502,  1503,  1504,  1507,  1508,  1509,
  1510,  1511,  1512,  1515,  1516,  1519,  1520,  1521,  1522,  1523,
  1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,
  1534,  1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,
  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1555,  1557,  1562,
  1563,  1568,  1569,  1575,  1577,  1580,  1583,  1589,  1601,  1608,
  1617,  1624,  1633,  1639,  1645,  1647,  1649,  1651,  1653,  1656,
  1662,  1668,  1671,  1677,  1683,  1685,  1688,  1695,  1701,  1707,
  1718,  1725,  1728,  1730,  1732,  1734,  1736,  1742,  1749,  1758,
  1765,  1774,  1783,  1792,  1798,  1805,  1814,  1821,  1830,  1832,
  1835,  1842,  1846,  1846,  1848,  1853,  1858,  1863,  1869,  1875,
  1881,  1886,  1892,  1898,  1906,  1906,  1908,  1914,  1921,  1926,
  1931,  1936,  1942,  1950,  1952,  1955,  1964,  1966,  1968,  1970,
  1972,  1974,  1976,  1985,  1987,  1989,  1991,  1999,  2001,  2006,
  2012,  2013,  2017,  2022,  2033,  2033,  2035,  2037,  2051,  2055,
  2059,  2069,  2073,  2080,  2080,  2082,  2083,  2087,  2087
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","Y_EOF",
"Y_NL","Y_INT","Y_ID","Y_REG","Y_FP_REG","Y_STR","Y_FP","Y_ABS_D_OP","Y_ABS_S_OP",
"Y_ADDIU_OP","Y_ADDI_OP","Y_ADDU_OP","Y_ADD_D_OP","Y_ADD_OP","Y_ADD_S_OP","Y_ANDI_OP",
"Y_AND_OP","Y_BC0F_OP","Y_BC0T_OP","Y_BC1F_OP","Y_BC1T_OP","Y_BC2F_OP","Y_BC2T_OP",
"Y_BC3F_OP","Y_BC3T_OP","Y_BEQ_OP","Y_BGEZAL_OP","Y_BGEZ_OP","Y_BGTZ_OP","Y_BLEZ_OP",
"Y_BLTZAL_OP","Y_BLTZ_OP","Y_BNE_OP","Y_BREAK_OP","Y_CFC0_OP","Y_CFC1_OP","Y_CFC2_OP",
"Y_CFC3_OP","Y_COP0_OP","Y_COP1_OP","Y_COP2_OP","Y_COP3_OP","Y_CTC0_OP","Y_CTC1_OP",
"Y_CTC2_OP","Y_CTC3_OP","Y_CVT_D_S_OP","Y_CVT_D_W_OP","Y_CVT_S_D_OP","Y_CVT_S_W_OP",
"Y_CVT_W_D_OP","Y_CVT_W_S_OP","Y_C_EQ_D_OP","Y_C_EQ_S_OP","Y_C_F_D_OP","Y_C_F_S_OP",
"Y_C_LE_D_OP","Y_C_LE_S_OP","Y_C_LT_D_OP","Y_C_LT_S_OP","Y_C_NGE_D_OP","Y_C_NGE_S_OP",
"Y_C_NGLE_D_OP","Y_C_NGLE_S_OP","Y_C_NGL_D_OP","Y_C_NGL_S_OP","Y_C_NGT_D_OP",
"Y_C_NGT_S_OP","Y_C_OLT_D_OP","Y_C_OLT_S_OP","Y_C_OLE_D_OP","Y_C_OLE_S_OP","Y_C_SEQ_D_OP",
"Y_C_SEQ_S_OP","Y_C_SF_D_OP","Y_C_SF_S_OP","Y_C_UEQ_D_OP","Y_C_UEQ_S_OP","Y_C_ULT_D_OP",
"Y_C_ULT_S_OP","Y_C_ULE_D_OP","Y_C_ULE_S_OP","Y_C_UN_D_OP","Y_C_UN_S_OP","Y_DIVU_OP",
"Y_DIV_D_OP","Y_DIV_OP","Y_DIV_S_OP","Y_JALR_OP","Y_JAL_OP","Y_JR_OP","Y_J_OP",
"Y_LBU_OP","Y_LB_OP","Y_LHU_OP","Y_LH_OP","Y_LUI_OP","Y_LWC0_OP","Y_LWC1_OP",
"Y_LWC2_OP","Y_LWC3_OP","Y_LWL_OP","Y_LWR_OP","Y_LW_OP","Y_MFC0_OP","Y_MFC1_OP",
"Y_MFC2_OP","Y_MFC3_OP","Y_MFHI_OP","Y_MFLO_OP","Y_MOV_D_OP","Y_MOV_S_OP","Y_MTC0_OP",
"Y_MTC1_OP","Y_MTC2_OP","Y_MTC3_OP","Y_MTHI_OP","Y_MTLO_OP","Y_MULTU_OP","Y_MULT_OP",
"Y_MUL_D_OP","Y_MUL_S_OP","Y_NEG_D_OP","Y_NEG_S_OP","Y_NOR_OP","Y_ORI_OP","Y_OR_OP",
"Y_PFW_OP","Y_RFE_OP","Y_SB_OP","Y_SH_OP","Y_SLLV_OP","Y_SLL_OP","Y_SLTIU_OP",
"Y_SLTI_OP","Y_SLTU_OP","Y_SLT_OP","Y_SRAV_OP","Y_SRA_OP","Y_SRLV_OP","Y_SRL_OP",
"Y_SUBU_OP","Y_SUB_D_OP","Y_SUB_OP","Y_SUB_S_OP","Y_SWC0_OP","Y_SWC1_OP","Y_SWC2_OP",
"Y_SWC3_OP","Y_SWL_OP","Y_SWR_OP","Y_SW_OP","Y_SYSCALL_OP","Y_TLBP_OP","Y_TLBR_OP",
"Y_TLBWI_OP","Y_TLBWR_OP","Y_XORI_OP","Y_XOR_OP","Y_ABS_POP","Y_BAL_POP","Y_BEQZ_POP",
"Y_BGEU_POP","Y_BGE_POP","Y_BGTU_POP","Y_BGT_POP","Y_BLEU_POP","Y_BLE_POP","Y_BLTU_POP",
"Y_BLT_POP","Y_BNEZ_POP","Y_B_POP","Y_LA_POP","Y_LD_POP","Y_LI_POP","Y_LI_D_POP",
"Y_LI_S_POP","Y_L_D_POP","Y_L_S_POP","Y_MFC1_D_POP","Y_MTC1_D_POP","Y_MOVE_POP",
"Y_MULOU_POP","Y_MULO_POP","Y_MUL_POP","Y_NEGU_POP","Y_NEG_POP","Y_NOP_POP",
"Y_NOT_POP","Y_REMU_POP","Y_REM_POP","Y_ROL_POP","Y_ROR_POP","Y_SD_POP","Y_SEQ_POP",
"Y_SGEU_POP","Y_SGE_POP","Y_SGTU_POP","Y_SGT_POP","Y_SLEU_POP","Y_SLE_POP","Y_SNE_POP",
"Y_S_D_POP","Y_S_S_POP","Y_ULHU_POP","Y_ULH_POP","Y_ULW_POP","Y_USH_POP","Y_USW_POP",
"Y_ALIAS_DIR","Y_ALIGN_DIR","Y_ASCII_DIR","Y_ASCIIZ_DIR","Y_ASM0_DIR","Y_BGNB_DIR",
"Y_BYTE_DIR","Y_COMM_DIR","Y_DATA_DIR","Y_DOUBLE_DIR","Y_ENDB_DIR","Y_ENDR_DIR",
"Y_END_DIR","Y_ENT_DIR","Y_ERR_DIR","Y_EXTERN_DIR","Y_FILE_DIR","Y_FLOAT_DIR",
"Y_FMASK_DIR","Y_FRAME_DIR","Y_GLOBAL_DIR","Y_HALF_DIR","Y_K_TEXT_DIR","Y_K_DATA_DIR",
"Y_LABEL_DIR","Y_LCOMM_DIR","Y_LIVEREG_DIR","Y_LOC_DIR","Y_MASK_DIR","Y_NOALIAS_DIR",
"Y_OPTIONS_DIR","Y_RDATA_DIR","Y_REPEAT_DIR","Y_SDATA_DIR","Y_SET_DIR","Y_SPACE_DIR",
"Y_STRUCT_DIR","Y_TEXT_DIR","Y_VERSTAMP_DIR","Y_VREG_DIR","Y_WORD_DIR","':'",
"'='","'('","')'","'+'","'-'","'>'","LINE","@1","LBL_CMD","OPT_LBL","CMD","@2",
"@3","TERM","ASM_CODE","LOAD_OP","LOAD_COP","LOAD_IMM_OP","ULOADH_POP","LOADF_OP",
"STORE_OP","STORE_COP","STOREF_OP","SYS_OP","BINARY_OP_I","BINARY_OPR_I","BINARY_IMM_ARITH_OP",
"BINARY_IMM_LOGICAL_OP","SHIFT_OP","BINARY_OP_NOI","SUB_OP","DIV_POP","MUL_POP",
"SET_LE_POP","SET_GT_POP","SET_GE_POP","SET_EQ_POP","MULT_OP","NULLARY_BR_OP",
"UNARY_BR_OP","UNARY_BR_POP","BINARY_BR_OP","BR_GT_POP","BR_GE_POP","BR_LT_POP",
"BR_LE_POP","J_OPS","B_OP","MOVE_COP_OP","MOV_FROM_HILO_OP","MOV_TO_HILO_OP",
"MOV_COP_OP","CTL_COP_OP","FP_ABS_OP","FP_BINARY_OP","FP_CONVERT_OP","FP_NEG_OP",
"FP_CMP_OP","ASM_DIRECTIVE","@4","@5","@6","@7","@8","@9","@10","ADDRESS","@11",
"ADDR","BR_IMM32","@12","IMM16","UIMM16","IMM32","ABS_ADDR","DEST_REG","SRC1",
"SRC2","DEST","REG","SOURCE","REGISTER","F_DEST","F_SRC1","F_SRC2","FP_REGISTER",
"COP_REG","LABEL","STR_LST","STR","EXPRESSION","@13","EXPR","EXPR_LST","FP_EXPR_LST",
"OPTIONAL_ID","@14","OPT_ID","ID","@15", NULL
};
#endif

static const short yyr1[] = {     0,
   262,   261,   263,   263,   264,   264,   266,   265,   267,   265,
   265,   268,   268,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
   269,   269,   269,   269,   269,   269,   269,   269,   269,   270,
   270,   270,   270,   270,   270,   270,   270,   270,   271,   271,
   271,   272,   273,   273,   274,   274,   274,   275,   275,   275,
   275,   275,   275,   276,   276,   276,   277,   277,   277,   278,
   278,   279,   279,   279,   279,   279,   279,   279,   280,   280,
   280,   281,   281,   281,   281,   282,   282,   282,   283,   283,
   283,   284,   285,   285,   286,   286,   286,   286,   287,   287,
   287,   288,   288,   289,   289,   290,   290,   291,   291,   292,
   292,   293,   293,   293,   293,   293,   293,   293,   293,   294,
   294,   294,   294,   294,   294,   295,   295,   296,   296,   297,
   297,   298,   298,   299,   299,   300,   300,   301,   301,   301,
   301,   302,   302,   303,   303,   304,   304,   305,   305,   306,
   306,   306,   306,   306,   306,   306,   306,   306,   306,   307,
   307,   307,   307,   307,   307,   307,   307,   308,   308,   309,
   309,   309,   309,   309,   309,   309,   309,   310,   310,   310,
   310,   310,   310,   311,   311,   312,   312,   312,   312,   312,
   312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
   312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
   312,   312,   312,   312,   312,   312,   312,   313,   313,   314,
   313,   315,   313,   313,   313,   316,   313,   313,   313,   313,
   313,   313,   317,   313,   313,   313,   313,   313,   313,   313,
   313,   313,   318,   313,   313,   313,   313,   319,   313,   313,
   313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
   313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
   320,   313,   322,   321,   323,   323,   323,   323,   323,   323,
   323,   323,   323,   323,   325,   324,   326,   327,   328,   328,
   328,   328,   328,   329,   329,   329,   330,   331,   332,   333,
   334,   335,   336,   337,   338,   339,   340,   341,   341,   342,
   343,   343,   344,   344,   346,   345,   347,   347,   348,   348,
   348,   349,   349,   351,   350,   352,   352,   354,   353
};

static const short yyr2[] = {     0,
     0,     2,     2,     1,     2,     3,     0,     3,     0,     3,
     1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     1,     2,
     1,     3,     3,     3,     3,     3,     4,     4,     3,     4,
     4,     3,     4,     3,     4,     3,     4,     4,     4,     4,
     3,     4,     4,     3,     3,     4,     4,     4,     4,     3,
     4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     4,     4,     2,     3,     3,     4,     4,     4,     4,     4,
     4,     4,     4,     4,     4,     2,     2,     3,     2,     3,
     2,     2,     3,     3,     3,     4,     3,     3,     3,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     3,     2,     0,
     3,     0,     3,     1,     2,     0,     3,     3,     1,     2,
     1,     2,     0,     3,     2,     2,     1,     2,     3,     3,
     1,     3,     0,     3,     3,     4,     2,     0,     3,     2,
     3,     3,     3,     3,     3,     2,     2,     1,     2,     1,
     2,     2,     2,     2,     1,     2,     1,     2,     3,     4,
     0,     3,     0,     2,     3,     1,     4,     1,     4,     3,
     3,     3,     6,     6,     0,     2,     1,     1,     1,     6,
     1,     3,     3,     1,     3,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     1,     1,     3,     0,     2,     1,     1,     2,     1,
     3,     2,     1,     0,     2,     1,     0,     0,     2
};

static const short yydefact[] = {     1,
   388,    13,    12,   229,   228,   143,   142,   133,   231,   132,
   230,   146,   134,   176,   172,   177,   173,   178,   174,   179,
   175,   188,   181,   180,   182,   183,   185,   184,   189,     0,
   220,   221,   222,   223,   224,   225,   226,   227,   238,   239,
   240,   241,   242,   243,   264,   248,   262,   246,   276,   260,
   274,   258,   275,   259,   271,   255,   273,   257,   277,   261,
   266,   250,   267,   251,   272,   256,   270,   254,   265,   249,
   268,   252,   269,   253,   263,   247,   156,   233,   155,   232,
   201,   200,   199,   198,   101,   100,   103,   102,   112,   109,
   115,   110,   111,   105,   106,   104,   210,   211,   213,   214,
   206,   207,   205,   204,   215,   216,   218,   219,   208,   209,
   171,   170,   235,   234,   245,   244,   152,   147,   136,   108,
   130,   118,   119,   139,   149,   145,   144,   138,   137,   140,
   150,   141,   151,   154,   237,   153,   236,   124,   127,   125,
   126,   121,   122,   120,   131,   148,   135,     0,   203,   186,
   193,   192,   191,   190,   197,   196,   195,   194,   187,   202,
     0,   107,     0,     0,     0,   117,   116,   212,   217,     0,
   161,   160,   159,     0,     0,    31,     0,   158,   157,     0,
     0,   123,   168,   167,   166,   165,   164,   163,   162,   169,
   129,   128,   114,   113,     0,     0,     0,     0,   388,   280,
   282,   284,     0,   286,   388,   289,   293,     0,   297,   384,
   388,   301,   388,     0,   303,     0,     0,   388,   308,   327,
   291,   388,   388,     0,     0,     0,     0,   388,   318,   388,
   320,   388,   388,   388,   325,     0,     0,   331,     2,     0,
     4,    11,     7,     0,     0,     0,     0,     0,     0,     0,
     0,    29,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   388,     0,     0,     0,
     0,     0,     0,     0,   388,   388,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     9,     0,     0,    30,
   363,     0,   357,   333,     0,   367,     0,   364,     0,     0,
     0,     0,     0,     0,     0,   333,   333,   362,   333,     0,
   377,   279,   378,     0,     0,   285,   375,   388,   290,     0,
   296,   295,   387,   298,   388,     0,     0,     0,     0,   307,
   375,   328,   292,   310,   388,     0,     0,     0,     0,   316,
   319,   317,   321,   322,   323,   324,   326,     0,     0,   375,
     3,     0,   333,   368,   369,   333,     0,   333,   333,   333,
   333,   333,   365,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   358,    73,   370,
   388,   388,   345,   345,   345,   345,   345,    87,     0,   358,
    86,    89,     0,    91,   361,    92,     0,     0,     0,     0,
     0,     0,     0,     0,     5,     0,   389,    32,    17,     0,
   354,     0,     0,    18,   349,   351,    19,    20,    36,    34,
    33,    35,     0,     0,    21,    27,    26,   278,   373,   281,
   372,   283,   380,   388,   287,   288,   383,   294,   385,   386,
   299,   300,   302,   304,   305,     0,   309,   311,   312,   313,
   314,   315,   329,     0,   332,     8,    14,    15,    16,   348,
    22,    23,    24,    25,    28,    39,     0,    42,     0,    44,
   347,     0,    46,     0,     0,    51,     0,    54,     0,    55,
     0,     0,     0,     0,     0,    60,   359,    74,    75,   388,
     0,   388,   388,   388,   388,   388,   388,   388,   388,   388,
    88,    90,    93,    94,    95,     0,    97,   366,    98,    99,
    10,     6,   338,     0,   334,   336,   356,     0,     0,     0,
     0,    64,    62,    63,    61,     0,   371,     0,   376,   379,
   382,   306,   330,    38,    37,    41,    40,    43,    45,    47,
    48,    50,    49,    53,    52,    57,    56,    59,    58,    66,
    65,    68,    67,    70,    69,    72,    71,    77,   346,    76,
    79,    78,    81,    80,    83,    82,    85,    84,    96,     0,
     0,     0,     0,     0,   388,   355,   352,   353,     0,   374,
   381,     0,   340,   342,   335,     0,   341,     0,   339,     0,
     0,   337,     0,     0,     0,   350,   343,   344,     0,     0,
     0
};

static const short yydefgoto[] = {   599,
     1,   239,   240,   241,   352,   404,   242,   243,   244,   245,
   246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
   256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
   266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
   276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
   286,   287,   314,   315,   317,   320,   327,   331,   350,   409,
   410,   515,   490,   491,   470,   459,   460,   415,   292,   377,
   486,   389,   394,   307,   378,   297,   362,   507,   298,   356,
   379,   430,   431,   433,   434,   312,   435,   438,   322,   323,
   439,   416,   289
};

static const short yypact[] = {-32768,
   529,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    18,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    30,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    30,-32768,    30,    33,    33,-32768,-32768,-32768,-32768,    30,
-32768,-32768,-32768,    30,    30,-32768,    30,-32768,-32768,    30,
    30,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    30,    30,    30,    40,    52,-32768,
-32768,-32768,    68,-32768,-32768,    91,-32768,    92,-32768,-32768,
-32768,-32768,-32768,    93,-32768,    94,    30,-32768,-32768,    95,
    96,-32768,-32768,    98,   101,   103,    80,-32768,   104,    52,
   105,-32768,    52,    52,   119,   127,    30,-32768,-32768,   529,
-32768,-32768,-32768,    30,     8,    30,    30,    33,    30,     8,
    33,-32768,    30,    30,    30,    30,    30,    30,    30,    30,
    30,    30,    30,    30,    30,    30,-32768,    30,    30,    30,
    30,    30,    30,    30,    30,-32768,     8,    30,    30,    30,
     8,    33,    33,    33,    33,    33,-32768,  -194,   129,-32768,
-32768,    30,-32768,-32768,     2,-32768,   131,-32768,   132,    30,
    30,    30,    30,    30,    30,-32768,-32768,-32768,-32768,   136,
-32768,-32768,-32768,   135,   135,-32768,-32768,    52,-32768,   138,
-32768,-32768,   139,   141,    52,   146,   138,   152,   153,-32768,
-32768,-32768,-32768,-32768,    52,   154,   157,   158,   159,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   160,   162,-32768,
-32768,    82,-32768,-32768,-32768,-32768,     2,-32768,-32768,-32768,
-32768,-32768,-32768,    -2,    51,    -2,    -2,    30,    -2,    -2,
    30,    30,    30,    30,    30,    30,    30,-32768,-32768,-32768,
-32768,-32768,    30,    30,    30,    30,    30,-32768,    30,   161,
-32768,-32768,     8,-32768,-32768,-32768,     8,     8,    33,    33,
    33,    33,    33,    82,-32768,   164,-32768,-32768,-32768,     4,
    -3,  -170,   165,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    -2,    -2,-32768,-32768,-32768,-32768,   -83,   135,
-32768,   135,   -82,    52,    85,-32768,-32768,   163,-32768,-32768,
-32768,-32768,-32768,   163,-32768,    30,    85,-32768,-32768,-32768,
-32768,-32768,-32768,   171,    85,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    -2,-32768,    60,-32768,
-32768,     2,-32768,     2,    65,-32768,    -2,-32768,    -2,    -2,
    -2,    -2,    -2,    -2,    -2,-32768,-32768,-32768,-32768,-32768,
     2,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    33,-32768,-32768,-32768,-32768,
-32768,-32768,  -213,    30,-32768,  -175,-32768,   175,   165,   165,
   -76,-32768,-32768,-32768,-32768,   177,-32768,   178,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    30,
   165,   165,   -73,    30,-32768,-32768,-32768,-32768,   -75,-32768,
-32768,   -71,   -69,   -68,-32768,   -67,-32768,   -66,-32768,    30,
    30,-32768,   184,   -65,   -64,-32768,-32768,-32768,   191,   195,
-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,   -44,-32768,-32768,  -340,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -282,
-32768,-32768,  -335,-32768,  -275,  -349,  -118,  -393,   208,   137,
   400,-32768,  -187,  -183,  -142,  -154,  -260,  -372,  -250,  -237,
  -207,  -116,  -348,  -413,-32768,  -171,  -302,  -127,-32768,-32768,
-32768,    -1,-32768
};


#define	YYLAST		885


static const short yytable[] = {   288,
   363,   517,   411,   412,   291,   293,   411,   412,   411,   513,
   299,   456,   361,   309,   354,   355,   516,   473,   293,   521,
   293,   530,   290,   425,   426,   403,   427,   293,   447,   509,
   510,   293,   293,   530,   293,   363,   291,   293,   293,   393,
   296,   530,   570,   398,   571,   572,   310,   455,   493,   495,
   497,   499,   293,   308,   308,   468,   311,   291,   342,   405,
   406,   345,   346,   511,   536,   360,   291,   391,   392,   540,
   457,   291,   316,   458,   329,   461,   462,   463,   464,   465,
   574,   527,   575,   527,     2,     3,   339,   519,   520,  -375,
  -375,   396,   397,   359,   349,   319,   321,   326,   328,   332,
   333,   293,   336,   293,   293,   337,   308,   338,   341,   343,
   293,   293,   293,   293,   293,   293,   293,   293,   293,   293,
   293,   293,   293,   347,   539,   577,   578,   399,   400,   401,
   402,   348,   390,   569,   407,   395,   395,   395,   505,   506,
   417,   418,   428,   429,  -388,   441,   436,   437,   363,   363,
   508,   508,   508,   442,   443,   502,   445,   446,   449,   503,
   504,   450,   451,   448,   453,   452,   454,  -360,   512,   411,
   526,   528,   531,   488,   489,   533,   414,   583,   584,   576,
   579,   580,   581,   585,   588,   589,   590,   591,   596,   592,
   600,   597,   598,   593,   601,   351,   538,   313,   432,   444,
     0,     0,     0,   318,     0,     0,     0,     0,     0,   324,
     0,   325,     0,     0,     0,     0,   330,     0,     0,     0,
   334,   335,     0,     0,     0,     0,   340,     0,   313,     0,
   344,   313,   313,     0,   487,     0,     0,     0,     0,     0,
   487,   487,   487,   487,   487,   466,     0,   471,     0,     0,
   476,   478,     0,   413,   518,   508,     0,   413,     0,   514,
     0,     0,   529,     0,     0,   380,     0,     0,     0,     0,
     0,     0,     0,   380,   380,     0,     0,     0,     0,     0,
   487,   487,   558,     0,   560,   561,   562,   563,   564,   565,
   566,   567,   568,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   532,   522,   524,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   313,     0,     0,     0,
     0,   440,     0,   313,   487,     0,   487,     0,     0,     0,
     0,     0,   487,   313,   487,     0,   487,   487,   487,   487,
   487,   487,   487,     0,     0,     0,     0,     0,   534,     0,
     0,     0,     0,   471,     0,     0,     0,     0,   542,     0,
   544,   546,   548,   550,   552,   554,   556,     0,   294,     0,
   295,   573,   559,     0,     0,     0,     0,   300,     0,   380,
   380,   301,   302,     0,   303,     0,     0,   304,   305,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   306,     0,   381,   382,   383,   384,   385,   386,
   387,   388,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   582,   408,     0,
     0,   586,   313,     0,     0,     0,   419,   420,   421,   422,
   423,   424,     0,     0,     0,     0,     0,   594,   595,     0,
     0,   353,     0,   357,   358,     0,     0,     0,     0,     0,
   364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
   374,   375,   376,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   380,     0,
   380,   380,   380,   380,   380,   380,   380,   380,   380,     0,
   467,   469,   472,   474,   475,   477,   479,   480,   481,   482,
   483,   484,   485,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   501,     0,     0,     0,     0,
     0,     2,     3,     0,     0,     0,     0,     0,     0,     4,
     5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
     0,     0,     0,   587,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
    51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
    71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
   101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
   111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
   121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
   131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
   141,   142,   143,   144,   145,     0,     0,     0,     0,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
   197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
   207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
   227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
   237,   238,   492,   494,   496,   498,   500,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   523,   525,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   535,     0,   537,     0,
     0,     0,     0,     0,   541,     0,   543,     0,   545,   547,
   549,   551,   553,   555,   557
};

static const short yycheck[] = {     1,
   251,     5,     5,     6,     7,   148,     5,     6,     5,     6,
   165,   352,   250,   197,     7,     8,   410,   367,   161,   413,
   163,   435,     5,   306,   307,   286,   309,   170,   331,   402,
   403,   174,   175,   447,   177,   286,     7,   180,   181,   277,
     8,   455,   256,   281,   258,   259,     7,   350,   384,   385,
   386,   387,   195,   196,   197,     5,     5,     7,   230,   254,
   255,   233,   234,   404,     5,   249,     7,   275,   276,     5,
   353,     7,     5,   356,   217,   358,   359,   360,   361,   362,
   256,   430,   258,   432,     3,     4,     7,   258,   259,     5,
     6,   279,   280,   248,   237,     5,     5,     5,     5,     5,
     5,   244,     5,   246,   247,     5,   249,     5,     5,     5,
   253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,     5,   474,   519,   520,   282,   283,   284,
   285,     5,   275,   506,     6,   278,   279,   280,   399,   400,
    10,    10,     7,     9,     6,     5,   318,    10,   399,   400,
   401,   402,   403,   325,     9,   393,     5,     5,     5,   397,
   398,     5,     5,   335,     5,     7,     5,     7,     5,     5,
   254,   254,    10,   381,   382,     5,   295,   571,   572,     5,
   257,     5,     5,   257,   260,   257,   256,   256,     5,   257,
     0,   257,   257,   260,     0,   240,   472,   199,   315,   327,
    -1,    -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,   211,
    -1,   213,    -1,    -1,    -1,    -1,   218,    -1,    -1,    -1,
   222,   223,    -1,    -1,    -1,    -1,   228,    -1,   230,    -1,
   232,   233,   234,    -1,   377,    -1,    -1,    -1,    -1,    -1,
   383,   384,   385,   386,   387,   364,    -1,   366,    -1,    -1,
   369,   370,    -1,   256,   258,   506,    -1,   256,    -1,   256,
    -1,    -1,   434,    -1,    -1,   267,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   275,   276,    -1,    -1,    -1,    -1,    -1,
   423,   424,   490,    -1,   492,   493,   494,   495,   496,   497,
   498,   499,   500,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   446,   423,   424,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   318,    -1,    -1,    -1,
    -1,   323,    -1,   325,   467,    -1,   469,    -1,    -1,    -1,
    -1,    -1,   475,   335,   477,    -1,   479,   480,   481,   482,
   483,   484,   485,    -1,    -1,    -1,    -1,    -1,   467,    -1,
    -1,    -1,    -1,   472,    -1,    -1,    -1,    -1,   477,    -1,
   479,   480,   481,   482,   483,   484,   485,    -1,   161,    -1,
   163,   514,   491,    -1,    -1,    -1,    -1,   170,    -1,   381,
   382,   174,   175,    -1,   177,    -1,    -1,   180,   181,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   195,    -1,   268,   269,   270,   271,   272,   273,
   274,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   570,   292,    -1,
    -1,   574,   434,    -1,    -1,    -1,   300,   301,   302,   303,
   304,   305,    -1,    -1,    -1,    -1,    -1,   590,   591,    -1,
    -1,   244,    -1,   246,   247,    -1,    -1,    -1,    -1,    -1,
   253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
   263,   264,   265,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   490,    -1,
   492,   493,   494,   495,   496,   497,   498,   499,   500,    -1,
   364,   365,   366,   367,   368,   369,   370,   371,   372,   373,
   374,   375,   376,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   389,    -1,    -1,    -1,    -1,
    -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
    32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
    -1,    -1,    -1,   575,    46,    47,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
    72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
   102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
   112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
   122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
   132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
   142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
   152,   153,   154,   155,   156,    -1,    -1,    -1,    -1,   161,
   162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
   192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
   202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
   212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
   222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
   232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
   242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
   252,   253,   383,   384,   385,   386,   387,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   423,   424,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   467,    -1,   469,    -1,
    -1,    -1,    -1,    -1,   475,    -1,   477,    -1,   479,   480,
   481,   482,   483,   484,   485
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 384 "parser.y"
{parse_error_occurred = 0; scanner_start_line (); ;
    break;}
case 5:
#line 391 "parser.y"
{
			   this_line_labels =
			     cons_label (record_label ((char*)yyvsp[-1].p,
						       text_dir
						       ? current_text_pc ()
						       : current_data_pc (),
						       0),
					 this_line_labels);
				if (yyvsp[-1].p) free(yyvsp[-1].p);
			 ;
    break;}
case 6:
#line 403 "parser.y"
{
		  label *l = record_label ((char*)yyvsp[-2].p, (mem_addr)yyvsp[0].i, 1);
		  if (yyvsp[-2].p) free(yyvsp[-2].p);

		  l->const_flag = 1;
		  clear_labels ();
		;
    break;}
case 7:
#line 414 "parser.y"
{
		  clear_labels ();
		;
    break;}
case 9:
#line 420 "parser.y"
{
		  clear_labels ();
		;
    break;}
case 12:
#line 430 "parser.y"
{
			LINE_PARSE_DONE;
		;
    break;}
case 13:
#line 435 "parser.y"
{
		  clear_labels ();
		  FILE_PARSE_DONE;
		;
    break;}
case 14:
#line 444 "parser.y"
{
		  i_type_inst (yyvsp[-2].i == Y_LD_POP ? Y_LW_OP : yyvsp[-2].i,
			       yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  if (yyvsp[-2].i == Y_LD_POP)
		    i_type_inst_free (Y_LW_OP,
				      yyvsp[-1].i + 1,
				      addr_expr_reg ((addr_expr *)yyvsp[0].p),
				      incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
							4));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 15:
#line 460 "parser.y"
{
		  i_type_inst (yyvsp[-2].i, yyvsp[-1].i, addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 16:
#line 468 "parser.y"
{
		  i_type_inst_free (yyvsp[-2].i, yyvsp[-1].i, 0, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 17:
#line 474 "parser.y"
{
		  if (addr_expr_reg ((addr_expr *)yyvsp[0].p))
		    i_type_inst (Y_ADDI_OP, yyvsp[-1].i,
				 addr_expr_reg ((addr_expr *)yyvsp[0].p),
				 addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  else
		    i_type_inst (Y_ORI_OP, yyvsp[-1].i, 0,
				 addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 18:
#line 488 "parser.y"
{
		  i_type_inst_free (Y_ORI_OP, yyvsp[-1].i, 0, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 19:
#line 494 "parser.y"
{
		  int *x = (int *) yyvsp[0].p;

		  i_type_inst (Y_ORI_OP, 1, 0, const_imm_expr (*x));
		  r_type_inst (Y_MTC1_OP, yyvsp[-1].i, 0, 1);
		  i_type_inst (Y_ORI_OP, 1, 0, const_imm_expr (*(x+1)));
		  r_type_inst (Y_MTC1_OP, yyvsp[-1].i + 1, 0, 1);
		;
    break;}
case 20:
#line 505 "parser.y"
{
		  float x = (float) *((double *) yyvsp[0].p);
		  int *y = (int *) &x;

		  i_type_inst (Y_ORI_OP, 1, 0, const_imm_expr (*y));
		  r_type_inst (Y_MTC1_OP, yyvsp[-1].i, 0, 1);
		;
    break;}
case 21:
#line 515 "parser.y"
{
#ifdef BIGENDIAN
		  i_type_inst (Y_LWL_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  i_type_inst_free (Y_LWR_OP, yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      3));
#else
		  i_type_inst_free (Y_LWL_OP, yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      3));
		  i_type_inst (Y_LWR_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
#endif
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 22:
#line 539 "parser.y"
{
#ifdef BIGENDIAN
		  i_type_inst ((yyvsp[-2].i == Y_ULH_POP ? Y_LB_OP : Y_LBU_OP),
			       yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  i_type_inst_free (Y_LBU_OP, 1,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      1));
#else
		  i_type_inst_free ((yyvsp[-2].i == Y_ULH_POP ? Y_LB_OP : Y_LBU_OP),
				    yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      1));
		  i_type_inst (Y_LBU_OP, 1,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
#endif
		  r_sh_type_inst (Y_SLL_OP, yyvsp[-1].i, yyvsp[-1].i, 8);
		  r_type_inst (Y_OR_OP, yyvsp[-1].i, yyvsp[-1].i, 1);
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 23:
#line 567 "parser.y"
{
		  i_type_inst (Y_LWC1_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  if (yyvsp[-2].i == Y_L_D_POP)
		    i_type_inst_free (Y_LWC1_OP, yyvsp[-1].i + 1,
				      addr_expr_reg ((addr_expr *)yyvsp[0].p),
				      incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
							4));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 24:
#line 582 "parser.y"
{
		  i_type_inst (yyvsp[-2].i == Y_SD_POP ? Y_SW_OP : yyvsp[-2].i,
			       yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  if (yyvsp[-2].i == Y_SD_POP)
		    i_type_inst_free (Y_SW_OP, yyvsp[-1].i + 1,
				      addr_expr_reg ((addr_expr *)yyvsp[0].p),
				      incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
							4));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 25:
#line 598 "parser.y"
{
		  i_type_inst (yyvsp[-2].i, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 26:
#line 608 "parser.y"
{
#ifdef BIGENDIAN
		  i_type_inst (Y_SWL_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  i_type_inst_free (Y_SWR_OP, yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      3));
#else
		  i_type_inst_free (Y_SWL_OP, yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      3));
		  i_type_inst (Y_SWR_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
#endif
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 27:
#line 632 "parser.y"
{
		  i_type_inst (Y_SB_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));

		  yywarn ("Warning: Expansion of USH modifies its first argument");
		  r_sh_type_inst (Y_SRL_OP, yyvsp[-1].i, yyvsp[-1].i, 8);
		  i_type_inst_free (Y_SB_OP, yyvsp[-1].i,
				    addr_expr_reg ((addr_expr *)yyvsp[0].p),
				    incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
						      1));

		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 28:
#line 650 "parser.y"
{
		  i_type_inst (Y_SWC1_OP, yyvsp[-1].i,
			       addr_expr_reg ((addr_expr *)yyvsp[0].p),
			       addr_expr_imm ((addr_expr *)yyvsp[0].p));
		  if (yyvsp[-2].i == Y_S_D_POP)
		    i_type_inst_free (Y_SWC1_OP, yyvsp[-1].i + 1,
				      addr_expr_reg ((addr_expr *)yyvsp[0].p),
				      incr_expr_offset (addr_expr_imm ((addr_expr *)yyvsp[0].p),
							4));
		  free (((addr_expr *)yyvsp[0].p)->imm);
		  free ((addr_expr *)yyvsp[0].p);
		;
    break;}
case 29:
#line 665 "parser.y"
{
		  r_type_inst (yyvsp[0].i, 0, 0, 0);
		;
    break;}
case 30:
#line 671 "parser.y"
{
		  if (yyvsp[0].i == 1)
		    yyerror ("Breakpoint 1 is reserved for debugger");
		  r_type_inst (yyvsp[-1].i, yyvsp[0].i, 0, 0);
		;
    break;}
case 31:
#line 679 "parser.y"
{
		  nop_inst ();
		;
    break;}
case 32:
#line 685 "parser.y"
{
		  if (yyvsp[-1].i != yyvsp[0].i)
		    r_type_inst (Y_ADDU_OP, yyvsp[-1].i, 0, yyvsp[0].i);

		  i_type_inst_free (Y_BGEZ_OP, 0, yyvsp[0].i, branch_offset (2));
		  r_type_inst (Y_SUB_OP, yyvsp[-1].i, 0, yyvsp[0].i);
		;
    break;}
case 33:
#line 695 "parser.y"
{
		  r_type_inst (Y_SUB_OP, yyvsp[-1].i, 0, yyvsp[0].i);
		;
    break;}
case 34:
#line 701 "parser.y"
{
		  r_type_inst (Y_SUBU_OP, yyvsp[-1].i, 0, yyvsp[0].i);
		;
    break;}
case 35:
#line 707 "parser.y"
{
		  r_type_inst (Y_NOR_OP, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 36:
#line 713 "parser.y"
{
		  r_type_inst (Y_ADDU_OP, yyvsp[-1].i, 0, yyvsp[0].i);
		;
    break;}
case 37:
#line 719 "parser.y"
{
		  r_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 38:
#line 725 "parser.y"
{
		  i_type_inst_free (op_to_imm_op (yyvsp[-3].i), yyvsp[-2].i, yyvsp[-1].i,
				    (imm_expr *)yyvsp[0].p);
		;
    break;}
case 39:
#line 732 "parser.y"
{
		  i_type_inst_free (op_to_imm_op (yyvsp[-2].i), yyvsp[-1].i, yyvsp[-1].i,
				    (imm_expr *)yyvsp[0].p);
		;
    break;}
case 40:
#line 739 "parser.y"
{
		  r_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[0].i, yyvsp[-1].i);
		;
    break;}
case 41:
#line 745 "parser.y"
{
		  r_sh_type_inst (op_to_imm_op (yyvsp[-3].i), yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 42:
#line 751 "parser.y"
{
		  r_sh_type_inst (op_to_imm_op (yyvsp[-2].i), yyvsp[-1].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 43:
#line 757 "parser.y"
{
		  i_type_inst_free (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 44:
#line 763 "parser.y"
{
		  i_type_inst_free (yyvsp[-2].i, yyvsp[-1].i, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 45:
#line 768 "parser.y"
{
		  i_type_inst_free (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 46:
#line 774 "parser.y"
{
		  i_type_inst_free (yyvsp[-2].i, yyvsp[-1].i, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 47:
#line 780 "parser.y"
{
		  if ((yyvsp[0].i < 0) || (31 < yyvsp[0].i))
		    yywarn("Shift distance can only be in the range 0..31");
		  r_sh_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 48:
#line 788 "parser.y"
{
		  r_type_inst (imm_op_to_op (yyvsp[-3].i), yyvsp[-2].i, yyvsp[0].i, yyvsp[-1].i);
		;
    break;}
case 49:
#line 794 "parser.y"
{
		  r_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 50:
#line 800 "parser.y"
{
		  if (bare_machine && !accept_pseudo_insts)
		    yyerror ("Immediate form not allowed in bare machine");
		  else
		    {
		      if (!zero_imm ((imm_expr *)yyvsp[0].p))
			/* Use $at */
			i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		      r_type_inst (yyvsp[-3].i,
				   yyvsp[-2].i,
				   yyvsp[-1].i,
				   (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		    }
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 51:
#line 818 "parser.y"
{
		  check_uimm_range ((imm_expr *)yyvsp[0].p, UIMM_MIN, UIMM_MAX);
		  if (bare_machine && !accept_pseudo_insts)
		    yyerror ("Immediate form not allowed in bare machine");
		  else
		    {
		      if (!zero_imm ((imm_expr *)yyvsp[0].p))
			/* Use $at */
			i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		      r_type_inst (yyvsp[-2].i,
				   yyvsp[-1].i,
				   yyvsp[-1].i,
				   (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		    }
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 52:
#line 837 "parser.y"
{
		  r_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 53:
#line 843 "parser.y"
{
		  int val = eval_imm_expr ((imm_expr *)yyvsp[0].p);

		  if (bare_machine && !accept_pseudo_insts)
		    yyerror ("Immediate form not allowed in bare machine");
		  else
		    i_type_inst (yyvsp[-3].i == Y_SUB_OP ? Y_ADDI_OP
				 : yyvsp[-3].i == Y_SUBU_OP ? Y_ADDIU_OP
				 : (fatal_error ("Bad SUB_OP\n"), 0),
				 yyvsp[-2].i,
				 yyvsp[-1].i,
				 make_imm_expr (-val, NULL, 0));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 54:
#line 860 "parser.y"
{
		  int val = eval_imm_expr ((imm_expr *)yyvsp[0].p);

		  if (bare_machine && !accept_pseudo_insts)
		    yyerror ("Immediate form not allowed in bare machine");
		  else
		    i_type_inst (yyvsp[-2].i == Y_SUB_OP ? Y_ADDI_OP
				 : yyvsp[-2].i == Y_SUBU_OP ? Y_ADDIU_OP
				 : (fatal_error ("Bad SUB_OP\n"), 0),
				 yyvsp[-1].i,
				 yyvsp[-1].i,
				 make_imm_expr (-val, NULL, 0));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 55:
#line 877 "parser.y"
{
		  /* The hardware divide operation (ignore 1st arg) */
		  if (yyvsp[-2].i != Y_DIV_OP && yyvsp[-2].i != Y_DIVU_OP)
		    yyerror ("REM requires 3 arguments");
		  else
		    r_type_inst (yyvsp[-2].i, 0, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 56:
#line 886 "parser.y"
{
		  /* Pseudo divide operations */
		  div_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 57:
#line 892 "parser.y"
{
		  if (zero_imm ((imm_expr *)yyvsp[0].p))
		    yyerror ("Divide by zero");
		  else
		    {
		      /* Use $at */
		      i_type_inst_free (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		      div_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, 1, 1);
		    }
		;
    break;}
case 58:
#line 905 "parser.y"
{
		  mult_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 59:
#line 910 "parser.y"
{
		  if (zero_imm ((imm_expr *)yyvsp[0].p))
		    /* Optimize: n * 0 == 0 */
		    i_type_inst_free (Y_ORI_OP, yyvsp[-2].i, 0, (imm_expr *)yyvsp[0].p);
		  else
		    {
		      /* Use $at */
		      i_type_inst_free (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		      mult_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, 1);
		    }
		;
    break;}
case 60:
#line 924 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, 0, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 61:
#line 930 "parser.y"
{
		  r_type_inst (Y_SUBU_OP, 1, 0, yyvsp[0].i);
		  r_type_inst (Y_SLLV_OP, 1, 1, yyvsp[-1].i);
		  r_type_inst (Y_SRLV_OP, yyvsp[-2].i, yyvsp[0].i, yyvsp[-1].i);
		  r_type_inst (Y_OR_OP, yyvsp[-2].i, yyvsp[-2].i, 1);
		;
    break;}
case 62:
#line 939 "parser.y"
{
		  r_type_inst (Y_SUBU_OP, 1, 0, yyvsp[0].i);
		  r_type_inst (Y_SRLV_OP, 1, 1, yyvsp[-1].i);
		  r_type_inst (Y_SLLV_OP, yyvsp[-2].i, yyvsp[0].i, yyvsp[-1].i);
		  r_type_inst (Y_OR_OP, yyvsp[-2].i, yyvsp[-2].i, 1);
		;
    break;}
case 63:
#line 948 "parser.y"
{
		  long dist = eval_imm_expr ((imm_expr *)yyvsp[0].p);

		  check_imm_range ((imm_expr *)yyvsp[0].p, 0, 31);
		  r_sh_type_inst (Y_SLL_OP, 1, yyvsp[-1].i, -dist);
		  r_sh_type_inst (Y_SRL_OP, yyvsp[-2].i, yyvsp[-1].i, dist);
		  r_type_inst (Y_OR_OP, yyvsp[-2].i, yyvsp[-2].i, 1);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 64:
#line 960 "parser.y"
{
		  long dist = eval_imm_expr ((imm_expr *)yyvsp[0].p);

		  check_imm_range ((imm_expr *)yyvsp[0].p, 0, 31);
		  r_sh_type_inst (Y_SRL_OP, 1, yyvsp[-1].i, -dist);
		  r_sh_type_inst (Y_SLL_OP, yyvsp[-2].i, yyvsp[-1].i, dist);
		  r_type_inst (Y_OR_OP, yyvsp[-2].i, yyvsp[-2].i, 1);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 65:
#line 973 "parser.y"
{
		  set_le_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 66:
#line 978 "parser.y"
{
		  if (!zero_imm ((imm_expr *)yyvsp[0].p))
		    /* Use $at */
		    i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		  set_le_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i,
			       (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 67:
#line 989 "parser.y"
{
		  set_gt_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 68:
#line 994 "parser.y"
{
		  if (!zero_imm ((imm_expr *)yyvsp[0].p))
		    /* Use $at */
		    i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		  set_gt_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i,
			       (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 69:
#line 1006 "parser.y"
{
		  set_ge_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 70:
#line 1011 "parser.y"
{
		  if (!zero_imm ((imm_expr *)yyvsp[0].p))
		    /* Use $at */
		    i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		  set_ge_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i,
			       (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 71:
#line 1022 "parser.y"
{
		  set_eq_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 72:
#line 1027 "parser.y"
{
		  if (!zero_imm ((imm_expr *)yyvsp[0].p))
		    /* Use $at */
		    i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[0].p);
		  set_eq_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i,
			       (zero_imm ((imm_expr *)yyvsp[0].p) ? 0 : 1));
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 73:
#line 1038 "parser.y"
{
		  i_type_inst_free (yyvsp[-1].i, 0, 0, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 74:
#line 1044 "parser.y"
{
		  i_type_inst_free (yyvsp[-2].i, 0, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 75:
#line 1050 "parser.y"
{
		  i_type_inst_free (yyvsp[-2].i == Y_BEQZ_POP ? Y_BEQ_OP : Y_BNE_OP,
			       0, yyvsp[-1].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 76:
#line 1057 "parser.y"
{
		  i_type_inst_free (yyvsp[-3].i, yyvsp[-1].i, yyvsp[-2].i, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 77:
#line 1062 "parser.y"
{
		  if (bare_machine && !accept_pseudo_insts)
		    yyerror ("Immediate form not allowed in bare machine");
		  else
		    {
		      if (zero_imm ((imm_expr *)yyvsp[-1].p))
			i_type_inst (yyvsp[-3].i, yyvsp[-2].i,
				     (zero_imm ((imm_expr *)yyvsp[-1].p) ? 0 : 1),
				     (imm_expr *)yyvsp[0].p);
		      else
			{
			  /* Use $at */
			  i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[-1].p);
			  i_type_inst (yyvsp[-3].i, yyvsp[-2].i,
				       (zero_imm ((imm_expr *)yyvsp[-1].p) ? 0 : 1),
				       (imm_expr *)yyvsp[0].p);
			}
		    }
		  free ((imm_expr *)yyvsp[-1].p);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 78:
#line 1086 "parser.y"
{
		  r_type_inst (yyvsp[-3].i == Y_BGT_POP ? Y_SLT_OP : Y_SLTU_OP,
			       1, yyvsp[-1].i, yyvsp[-2].i); /* Use $at */
		  i_type_inst_free (Y_BNE_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 79:
#line 1093 "parser.y"
{
		  if (yyvsp[-3].i == Y_BGT_POP)
		    {
		      /* Use $at */
		      i_type_inst_free (Y_SLTI_OP, 1, yyvsp[-2].i,
					incr_expr_offset ((imm_expr *)yyvsp[-1].p, 1));
		      i_type_inst (Y_BEQ_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		    }
		  else
		    {
		      /* Use $at */
		      /* Can't add 1 to immediate since 0xffffffff+1 = 0 < 1 */
		      i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[-1].p);
		      i_type_inst_free (Y_BEQ_OP, yyvsp[-2].i, 1, branch_offset (3));
		      r_type_inst (Y_SLTU_OP, 1, yyvsp[-2].i, 1);
		      i_type_inst (Y_BEQ_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		    }
		  free ((imm_expr *)yyvsp[-1].p);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 80:
#line 1116 "parser.y"
{
		  r_type_inst (yyvsp[-3].i == Y_BGE_POP ? Y_SLT_OP : Y_SLTU_OP,
			       1, yyvsp[-2].i, yyvsp[-1].i); /* Use $at */
		  i_type_inst_free (Y_BEQ_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 81:
#line 1123 "parser.y"
{
		  i_type_inst (yyvsp[-3].i == Y_BGE_POP ? Y_SLTI_OP : Y_SLTIU_OP,
			       1, yyvsp[-2].i, (imm_expr *)yyvsp[-1].p); /* Use $at */
		  i_type_inst_free (Y_BEQ_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		  free ((imm_expr *)yyvsp[-1].p);
		;
    break;}
case 82:
#line 1132 "parser.y"
{
		  r_type_inst (yyvsp[-3].i == Y_BLT_POP ? Y_SLT_OP : Y_SLTU_OP,
			       1, yyvsp[-2].i, yyvsp[-1].i); /* Use $at */
		  i_type_inst_free (Y_BNE_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 83:
#line 1139 "parser.y"
{
		  i_type_inst (yyvsp[-3].i == Y_BLT_POP ? Y_SLTI_OP : Y_SLTIU_OP,
			       1, yyvsp[-2].i, (imm_expr *)yyvsp[-1].p); /* Use $at */
		  i_type_inst_free (Y_BNE_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		  free ((imm_expr *)yyvsp[-1].p);
		;
    break;}
case 84:
#line 1148 "parser.y"
{
		  r_type_inst (yyvsp[-3].i == Y_BLE_POP ? Y_SLT_OP : Y_SLTU_OP,
			       1, yyvsp[-1].i, yyvsp[-2].i); /* Use $at */
		  i_type_inst_free (Y_BEQ_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 85:
#line 1155 "parser.y"
{
		  if (yyvsp[-3].i == Y_BLE_POP)
		    {
		      /* Use $at */
		      i_type_inst_free (Y_SLTI_OP, 1, yyvsp[-2].i,
					incr_expr_offset ((imm_expr *)yyvsp[-1].p, 1));
		      i_type_inst (Y_BNE_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		    }
		  else
		    {
		      /* Use $at */
		      /* Can't add 1 to immediate since 0xffffffff+1 = 0 < 1 */
		      i_type_inst (Y_ORI_OP, 1, 0, (imm_expr *)yyvsp[-1].p);
		      i_type_inst (Y_BEQ_OP, yyvsp[-2].i, 1, (imm_expr *)yyvsp[0].p);
		      r_type_inst (Y_SLTU_OP, 1, yyvsp[-2].i, 1);
		      i_type_inst (Y_BNE_OP, 0, 1, (imm_expr *)yyvsp[0].p);
		    }
		  free ((imm_expr *)yyvsp[-1].p);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 86:
#line 1178 "parser.y"
{
		  if ((yyvsp[-1].i == Y_J_OP) || (yyvsp[-1].i == Y_JR_OP))
		    j_type_inst (Y_J_OP, (imm_expr *)yyvsp[0].p);
		  else if ((yyvsp[-1].i == Y_JAL_OP) || (yyvsp[-1].i == Y_JALR_OP))
		    j_type_inst (Y_JAL_OP, (imm_expr *)yyvsp[0].p);
		  free ((imm_expr *)yyvsp[0].p);
		;
    break;}
case 87:
#line 1188 "parser.y"
{
		  if ((yyvsp[-1].i == Y_J_OP) || (yyvsp[-1].i == Y_JR_OP))
		    r_type_inst (Y_JR_OP, 0, yyvsp[0].i, 0);
		  else if ((yyvsp[-1].i == Y_JAL_OP) || (yyvsp[-1].i == Y_JALR_OP))
		    r_type_inst (Y_JALR_OP, 31, yyvsp[0].i, 0);
		;
    break;}
case 88:
#line 1197 "parser.y"
{
		  if ((yyvsp[-2].i == Y_J_OP) || (yyvsp[-2].i == Y_JR_OP))
		    r_type_inst (Y_JR_OP, 0, yyvsp[0].i, 0);
		  else if ((yyvsp[-2].i == Y_JAL_OP) || (yyvsp[-2].i == Y_JALR_OP))
		    r_type_inst (Y_JALR_OP, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 89:
#line 1206 "parser.y"
{
		  i_type_inst_free ((yyvsp[-1].i == Y_BAL_POP ? Y_BGEZAL_OP : Y_BGEZ_OP),
				    0, 0, (imm_expr *)yyvsp[0].p);
		;
    break;}
case 90:
#line 1214 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 91:
#line 1220 "parser.y"
{
		  r_type_inst (yyvsp[-1].i, yyvsp[0].i, 0, 0);
		;
    break;}
case 92:
#line 1226 "parser.y"
{
		  r_type_inst (yyvsp[-1].i, 0, yyvsp[0].i, 0);
		;
    break;}
case 93:
#line 1232 "parser.y"
{
		  if (yyvsp[-2].i == Y_MFC1_D_POP)
		    {
		      r_type_inst (Y_MFC1_OP, yyvsp[0].i, 0, yyvsp[-1].i);
		      r_type_inst (Y_MFC1_OP, yyvsp[0].i + 1, 0, yyvsp[-1].i + 1);
		    }
		  else if (yyvsp[-2].i == Y_MTC1_D_POP)
		    {
		      r_type_inst (Y_MTC1_OP, yyvsp[0].i, 0, yyvsp[-1].i);
		      r_type_inst (Y_MTC1_OP, yyvsp[0].i + 1, 0, yyvsp[-1].i + 1);
		    }
		  else
		    r_type_inst (yyvsp[-2].i, yyvsp[0].i, 0, yyvsp[-1].i);
		;
    break;}
case 94:
#line 1249 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, yyvsp[0].i, 0, yyvsp[-1].i);
		;
    break;}
case 95:
#line 1255 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 96:
#line 1261 "parser.y"
{
		  r_type_inst (yyvsp[-3].i, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 97:
#line 1267 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 98:
#line 1273 "parser.y"
{
		  r_type_inst (yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i, 0);
		;
    break;}
case 99:
#line 1279 "parser.y"
{
		  r_cond_type_inst (yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i);
		;
    break;}
case 279:
#line 1558 "parser.y"
{
		  align_data (yyvsp[0].i);
		;
    break;}
case 280:
#line 1562 "parser.y"
{null_term = 0;;
    break;}
case 281:
#line 1563 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 282:
#line 1568 "parser.y"
{null_term = 1;;
    break;}
case 283:
#line 1569 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 286:
#line 1581 "parser.y"
{store_op = store_byte;;
    break;}
case 287:
#line 1583 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 288:
#line 1590 "parser.y"
{
		  align_data (2);
		  if (lookup_label ((char*)yyvsp[-1].p)->addr == 0)
		  {
		    record_label ((char*)yyvsp[-1].p, current_data_pc (), 1);
			if (yyvsp[-2].p) free(yyvsp[-2].p);
		  }
		  increment_data_pc (yyvsp[0].i);
		;
    break;}
case 289:
#line 1602 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		;
    break;}
case 290:
#line 1609 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		  set_data_pc (yyvsp[0].i);
		;
    break;}
case 291:
#line 1618 "parser.y"
{
		  user_kernel_data_segment (1);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		;
    break;}
case 292:
#line 1625 "parser.y"
{
		  user_kernel_data_segment (1);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		  set_data_pc (yyvsp[0].i);
		;
    break;}
case 293:
#line 1634 "parser.y"
{
		  store_op = store_double;
		  if (data_dir) set_data_alignment(3);
		;
    break;}
case 294:
#line 1639 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 300:
#line 1657 "parser.y"
{
		  extern_directive ((char*)yyvsp[-1].p, yyvsp[0].i);
		;
    break;}
case 301:
#line 1663 "parser.y"
{
		  fatal_error ("File contains an .err directive\n");
		;
    break;}
case 303:
#line 1672 "parser.y"
{
		  store_op = store_float;
		  if (data_dir) set_data_alignment (2);
		;
    break;}
case 304:
#line 1677 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 307:
#line 1689 "parser.y"
{
		  make_label_global ((char*)yyvsp[0].p);
		  if (yyvsp[0].p) free(yyvsp[0].p);
		;
    break;}
case 308:
#line 1696 "parser.y"
{
		  store_op = store_half;
		  if (data_dir) set_data_alignment (1);
		;
    break;}
case 309:
#line 1701 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		;
    break;}
case 310:
#line 1708 "parser.y"
{
		  record_label ((char*)yyvsp[0].p,
				text_dir
				? current_text_pc ()
				: current_data_pc (),
				1);
		  if (yyvsp[-1].p) free(yyvsp[-1].p);
		;
    break;}
case 311:
#line 1719 "parser.y"
{
		  lcomm_directive ((char*)yyvsp[-1].p, yyvsp[0].i);
		;
    break;}
case 317:
#line 1737 "parser.y"
{
		  yyerror ("Warning: repeat directive ignored");
		;
    break;}
case 318:
#line 1743 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		;
    break;}
case 319:
#line 1750 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		  set_data_pc (yyvsp[0].i);
		;
    break;}
case 320:
#line 1759 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		;
    break;}
case 321:
#line 1766 "parser.y"
{
		  user_kernel_data_segment (0);
		  data_dir = 1; text_dir = 0;
		  enable_data_alignment ();
		  set_data_pc (yyvsp[0].i);
		;
    break;}
case 322:
#line 1775 "parser.y"
{
		  if (streq ((char*)yyvsp[0].p, "noat"))
		    noat_flag = 1;
		  else if (streq ((char*)yyvsp[0].p, "at"))
		    noat_flag = 0;
		;
    break;}
case 323:
#line 1784 "parser.y"
{
		  if (data_dir)
		    increment_data_pc (yyvsp[0].i);
		  else if (text_dir)
		    increment_text_pc (yyvsp[0].i);
		;
    break;}
case 324:
#line 1793 "parser.y"
{
		  yyerror ("Warning: struct directive ignored");
		;
    break;}
case 325:
#line 1799 "parser.y"
{
		  user_kernel_text_segment (0);
		  data_dir = 0; text_dir = 1;
		  enable_data_alignment ();
		;
    break;}
case 326:
#line 1806 "parser.y"
{
		  user_kernel_text_segment (0);
		  data_dir = 0; text_dir = 1;
		  enable_data_alignment ();
		  set_text_pc (yyvsp[0].i);
		;
    break;}
case 327:
#line 1815 "parser.y"
{
		  user_kernel_text_segment (1);
		  data_dir = 0; text_dir = 1;
		  enable_data_alignment ();
		;
    break;}
case 328:
#line 1822 "parser.y"
{
		  user_kernel_text_segment (1);
		  data_dir = 0; text_dir = 1;
		  enable_data_alignment ();
		  set_text_pc (yyvsp[0].i);
		;
    break;}
case 331:
#line 1836 "parser.y"
{
		  store_op = store_word_data;
		  if (data_dir) set_data_alignment (2);
		;
    break;}
case 333:
#line 1846 "parser.y"
{only_id = 1;;
    break;}
case 334:
#line 1846 "parser.y"
{only_id = 0; yyval = yyvsp[0];;
    break;}
case 335:
#line 1849 "parser.y"
{
		  yyval.p = make_addr_expr (0, NULL, yyvsp[-1].i);
		;
    break;}
case 336:
#line 1854 "parser.y"
{
		  yyval.p = make_addr_expr (yyvsp[0].i, NULL, 0);
		;
    break;}
case 337:
#line 1859 "parser.y"
{
		  yyval.p = make_addr_expr (yyvsp[-3].i, NULL, yyvsp[-1].i);
		;
    break;}
case 338:
#line 1864 "parser.y"
{
		  yyval.p = make_addr_expr (0, (char*)yyvsp[0].p, 0);
		  if (yyvsp[0].p) free ((char*)yyvsp[0].p);
		;
    break;}
case 339:
#line 1870 "parser.y"
{
		  yyval.p = make_addr_expr (0, (char*)yyvsp[-3].p, yyvsp[-1].i);
		  if (yyvsp[-3].p) free ((char*)yyvsp[-3].p);
		;
    break;}
case 340:
#line 1876 "parser.y"
{
		  yyval.p = make_addr_expr (yyvsp[0].i, (char*)yyvsp[-2].p, 0);
		  if (yyvsp[-2].p) free ((char*)yyvsp[-2].p);
		;
    break;}
case 341:
#line 1882 "parser.y"
{
		  yyval.p = make_addr_expr (yyvsp[-2].i, (char*)yyvsp[0].p, 0);
		;
    break;}
case 342:
#line 1887 "parser.y"
{
		  yyval.p = make_addr_expr (- yyvsp[0].i, (char*)yyvsp[-2].p, 0);
		  if (yyvsp[-2].p) free ((char*)yyvsp[-2].p);
		;
    break;}
case 343:
#line 1893 "parser.y"
{
		  yyval.p = make_addr_expr (yyvsp[-3].i, (char*)yyvsp[-5].p, yyvsp[-1].i);
		  if (yyvsp[-5].p) free ((char*)yyvsp[-5].p);
		;
    break;}
case 344:
#line 1899 "parser.y"
{
		  yyval.p = make_addr_expr (- yyvsp[-3].i, (char*)yyvsp[-5].p, yyvsp[-1].i);
		  if (yyvsp[-5].p) free ((char*)yyvsp[-5].p);
		;
    break;}
case 345:
#line 1906 "parser.y"
{only_id = 1;;
    break;}
case 346:
#line 1906 "parser.y"
{only_id = 0; yyval = yyvsp[0];;
    break;}
case 347:
#line 1909 "parser.y"
{
		  check_imm_range(yyvsp[0].p, IMM_MIN, IMM_MAX);
		  yyval = yyvsp[0];
		;
    break;}
case 348:
#line 1915 "parser.y"
{
		  check_uimm_range(yyvsp[0].p, UIMM_MIN, UIMM_MAX);
		  yyval = yyvsp[0];
		;
    break;}
case 349:
#line 1922 "parser.y"
{
		  yyval.p = make_imm_expr (yyvsp[0].i, NULL, 0);
		;
    break;}
case 350:
#line 1927 "parser.y"
{
		  yyval.p = make_imm_expr (yyvsp[-4].i >> yyvsp[0].i, NULL, 0);
		;
    break;}
case 351:
#line 1932 "parser.y"
{
		  yyval.p = make_imm_expr (0, (char*)yyvsp[0].p, 0);
		;
    break;}
case 352:
#line 1937 "parser.y"
{
		  yyval.p = make_imm_expr (yyvsp[0].i, (char*)yyvsp[-2].p, 0);
		  free ((char*)yyvsp[-2].p);
		;
    break;}
case 353:
#line 1943 "parser.y"
{
		  yyval.p = make_imm_expr (- yyvsp[0].i, (char*)yyvsp[-2].p, 0);
		  free ((char*)yyvsp[-2].p);
		;
    break;}
case 355:
#line 1953 "parser.y"
{yyval.i = yyvsp[-2].i + yyvsp[0].i;;
    break;}
case 356:
#line 1956 "parser.y"
{
		  /* Y_INT '-' Y_INT */
		  if (yyvsp[0].i >= 0)
		    yyerror ("Syntax error");
		  yyval.i = yyvsp[-1].i - yyvsp[0].i;
		;
    break;}
case 363:
#line 1977 "parser.y"
{
		  if (yyvsp[0].i < 0 || yyvsp[0].i > 31)
		    yyerror ("Register number out of range");
		  if (yyvsp[0].i == 1 && !bare_machine && !noat_flag)
		    yyerror ("Register 1 is reserved for assembler");
		  yyval = yyvsp[0];
		;
    break;}
case 367:
#line 1992 "parser.y"
{
		  if (yyvsp[0].i < 0 || yyvsp[0].i > 31)
		    yyerror ("FP register number out of range");
		  yyval = yyvsp[0];
		;
    break;}
case 370:
#line 2007 "parser.y"
{
		  yyval.p = make_imm_expr (-(int)current_text_pc (), (char*)yyvsp[0].p, 1);
		;
    break;}
case 373:
#line 2018 "parser.y"
{
		  store_string ((char*)yyvsp[0].p, y_str_length, null_term);
		  free ((char*)yyvsp[0].p);
		;
    break;}
case 374:
#line 2023 "parser.y"
{
		  int i;

		  for (i = 0; i < yyvsp[0].i; i ++)
		    store_string ((char*)yyvsp[-2].p, y_str_length, null_term);
		  free ((char*)yyvsp[-2].p);
		;
    break;}
case 375:
#line 2033 "parser.y"
{only_id = 1;;
    break;}
case 376:
#line 2033 "parser.y"
{only_id = 0; yyval = yyvsp[0];;
    break;}
case 378:
#line 2038 "parser.y"
{
		  label *l = lookup_label ((char*)yyvsp[0].p);

		  if (l->addr == 0)
		    {
		      record_data_uses_symbol (current_data_pc (), l);
		      yyval.p = NULL;
		    }
		  else
		    yyval.i = l->addr;
		;
    break;}
case 379:
#line 2052 "parser.y"
{
		  store_op (yyvsp[0].p);
		;
    break;}
case 380:
#line 2056 "parser.y"
{
		  store_op (yyvsp[0].p);
		;
    break;}
case 381:
#line 2060 "parser.y"
{
		  int i;

		  for (i = 0; i < yyvsp[0].i; i ++)
		    store_op (yyvsp[-2].p);
		;
    break;}
case 382:
#line 2070 "parser.y"
{
		  store_op (yyvsp[0].p);
		;
    break;}
case 383:
#line 2074 "parser.y"
{
		  store_op (yyvsp[0].p);
		;
    break;}
case 384:
#line 2080 "parser.y"
{only_id = 1;;
    break;}
case 385:
#line 2080 "parser.y"
{only_id = 0; yyval = yyvsp[0];;
    break;}
case 387:
#line 2083 "parser.y"
{yyval.p = (void*)NULL;;
    break;}
case 388:
#line 2087 "parser.y"
{only_id = 1;;
    break;}
case 389:
#line 2087 "parser.y"
{only_id = 0; yyval = yyvsp[0];;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 2090 "parser.y"


/* Maintain and update the address of labels for the current line. */

#ifdef __STDC__
void
fix_current_label_address (mem_addr new_addr)
#else
void
fix_current_label_address (new_addr)
     mem_addr new_addr;
#endif
{
  label_list *l;

  for (l = this_line_labels; l != NULL; l = l->tail)
    {
      l->head->addr = new_addr;
    }
  clear_labels ();
}


#ifdef __STDC__
static label_list *
cons_label (label *head, label_list *tail)
#else
static label_list *
cons_label (head, tail)
     label *head;
     label_list *tail;
#endif
{
  label_list *c = (label_list *) malloc (sizeof (label_list));

  c->head = head;
  c->tail = tail;
  return (c);
}


#ifdef __STDC__
static void
clear_labels (void)
#else
static void
clear_labels ()
#endif
{
  label_list *n;

  for ( ; this_line_labels != NULL; this_line_labels = n)
    {
      resolve_label_uses(this_line_labels->head);
      n = this_line_labels->tail;
      free (this_line_labels);
    }
}


/* Operations on op codes. */

#ifdef __STDC__
int
op_to_imm_op (int opcode)
#else
int
op_to_imm_op (opcode)
     int opcode;
#endif
{
  switch (opcode)
    {
    case Y_ADD_OP: return (Y_ADDI_OP);
    case Y_ADDU_OP: return (Y_ADDIU_OP);
    case Y_AND_OP: return (Y_ANDI_OP);
    case Y_OR_OP: return (Y_ORI_OP);
    case Y_XOR_OP: return (Y_XORI_OP);
    case Y_SLT_OP: return (Y_SLTI_OP);
    case Y_SLTU_OP: return (Y_SLTIU_OP);
    case Y_SLLV_OP: return (Y_SLL_OP);
    case Y_SRAV_OP: return (Y_SRA_OP);
    case Y_SRLV_OP: return (Y_SRL_OP);
    default: fatal_error ("Can't convert op to immediate op\n"); return (0);
    }
}


#ifdef __STDC__
int
imm_op_to_op (int opcode)
#else
int
imm_op_to_op (opcode)
     int opcode;
#endif
{
  switch (opcode)
    {
    case Y_ADDI_OP: return (Y_ADD_OP);
    case Y_ADDIU_OP: return (Y_ADDU_OP);
    case Y_ANDI_OP: return (Y_AND_OP);
    case Y_ORI_OP: return (Y_OR_OP);
    case Y_XORI_OP: return (Y_XOR_OP);
    case Y_SLTI_OP: return (Y_SLT_OP);
    case Y_SLTIU_OP: return (Y_SLTU_OP);
    case Y_J_OP: return (Y_JR_OP);
    case Y_LUI_OP: return (Y_ADDU_OP);
    case Y_SLL_OP: return (Y_SLLV_OP);
    case Y_SRA_OP: return (Y_SRAV_OP);
    case Y_SRL_OP: return (Y_SRLV_OP);
    default: fatal_error ("Can't convert immediate op to op\n"); return (0);
    }
}


#ifdef __STDC__
static void
nop_inst (void)
#else
static void
nop_inst ()
#endif
{
  r_type_inst (Y_SLL_OP, 0, 0, 0); /* = 0 */
}


#ifdef __STDC__
static void
trap_inst (void)
#else
static void
trap_inst ()
#endif
{
  r_type_inst (Y_BREAK_OP, 0, 0, 0);
}


#ifdef __STDC__
static imm_expr *
branch_offset (int n_inst)
#else
static imm_expr *
branch_offset (n_inst)
     int n_inst;
#endif
{
  return (const_imm_expr (n_inst << 2)); /* Later shifted right 2 places */
}


#ifdef __STDC__
static void
div_inst (int op, int rd, int rs, int rt, int const_divisor)
#else
static void
div_inst (op, rd, rs, rt, const_divisor)
     int op, rd, rs, rt, const_divisor;
#endif
{
  if (rd != 0 && !const_divisor)
    {
      i_type_inst_free (Y_BNE_OP, 0, rt, branch_offset (2));
      trap_inst ();
    }

  if (op == Y_DIV_OP || op == Y_REM_POP)
    r_type_inst (Y_DIV_OP, 0, rs, rt);
  else
    r_type_inst (Y_DIVU_OP, 0, rs, rt);

  if (rd != 0)
    {
      if (op == Y_DIV_OP || op == Y_DIVU_OP)
	/* Quotient */
	r_type_inst (Y_MFLO_OP, rd, 0, 0);
      else
	/* Remainder */
	r_type_inst (Y_MFHI_OP, rd, 0, 0);
    }
}


#ifdef __STDC__
static void
mult_inst (int op, int rd, int rs, int rt)
#else
static void
mult_inst (op, rd, rs, rt)
     int op, rd, rs, rt;
#endif
{
  if (op == Y_MULOU_POP)
    r_type_inst (Y_MULTU_OP, 0, rs, rt);
  else
    r_type_inst (Y_MULT_OP, 0, rs, rt);
  if (op == Y_MULOU_POP && rd != 0)
    {
      r_type_inst (Y_MFHI_OP, 1, 0, 0);	/* Use $at */
      i_type_inst_free (Y_BEQ_OP, 0, 1, branch_offset (2));
      trap_inst ();
    }
  else if (op == Y_MULO_POP && rd != 0)
    {
      r_type_inst (Y_MFHI_OP, 1, 0, 0); /* use $at */
      r_type_inst (Y_MFLO_OP, rd, 0, 0);
      r_sh_type_inst (Y_SRA_OP, rd, rd, 31);
      i_type_inst_free (Y_BEQ_OP, rd, 1, branch_offset (2));
      trap_inst ();
    }
  if (rd != 0)
    r_type_inst (Y_MFLO_OP, rd, 0, 0);
}


#ifdef __STDC__
static void
set_le_inst (int op, int rd, int rs, int rt)
#else
static void
set_le_inst (op, rd, rs, rt)
     int op, rd, rs, rt;
#endif
{
  i_type_inst_free (Y_BNE_OP, rs, rt, branch_offset (3));
  i_type_inst_free (Y_ORI_OP, rd, 0, const_imm_expr (1));
  i_type_inst_free (Y_BEQ_OP, 0, 0, branch_offset (2));
  r_type_inst ((op == Y_SLE_POP ? Y_SLT_OP : Y_SLTU_OP), rd, rs, rt);
}


#ifdef __STDC__
static void
set_gt_inst (int op, int rd, int rs, int rt)
#else
static void
set_gt_inst (op, rd, rs, rt)
     int op, rd, rs, rt;
#endif
{
  r_type_inst (op == Y_SGT_POP ? Y_SLT_OP : Y_SLTU_OP, rd, rt, rs);
}


#ifdef __STDC__
static void
set_ge_inst (int op, int rd, int rs, int rt)
#else
static void
set_ge_inst (op, rd, rs, rt)
     int op, rd, rs, rt;
#endif
{
  i_type_inst_free (Y_BNE_OP, rs, rt, branch_offset (3));
  i_type_inst_free (Y_ORI_OP, rd, 0, const_imm_expr (1));
  i_type_inst_free (Y_BEQ_OP, 0, 0, branch_offset (2));
  r_type_inst (op == Y_SGE_POP ? Y_SLT_OP : Y_SLTU_OP, rd, rt, rs);
}


#ifdef __STDC__
static void
set_eq_inst (int op, int rd, int rs, int rt)
#else
static void
set_eq_inst (op, rd, rs, rt)
     int op, rd, rs, rt;
#endif
{
  imm_expr *if_eq, *if_neq;

  if (op == Y_SEQ_POP)
    if_eq = const_imm_expr (1), if_neq = const_imm_expr (0);
  else
    if_eq = const_imm_expr (0), if_neq = const_imm_expr (1);

  i_type_inst_free (Y_BEQ_OP, rs, rt, branch_offset (3));
  /* RD <- 0 (if not equal) */
  i_type_inst_free (Y_ORI_OP, rd, 0, if_neq);
  i_type_inst_free (Y_BEQ_OP, 0, 0, branch_offset (2)); /* Branch always */
  /* RD <- 1 */
  i_type_inst_free (Y_ORI_OP, rd, 0, if_eq);
}


/* Store the value either as a datum or instruction. */

#ifdef __STDC__
static void
store_word_data (int value)
#else
static void
store_word_data (value)
     int value;
#endif
{
  if (data_dir)
    store_word (value);
  else if (text_dir)
    store_instruction (inst_decode (value));
}



#ifdef __STDC__
void
initialize_parser (char *file_name)
#else
void
initialize_parser (file_name)
     char *file_name;
#endif
{
  input_file_name = file_name;
  only_id = 0;
  data_dir = 0;
  text_dir = 1;
}


#ifdef __STDC__
static void
check_imm_range(imm_expr* expr, int32 min, int32 max)
#else
static void
check_imm_range()
     imm_expr* expr;
     int32 min;
     int32 max;
#endif
{
  if (expr->symbol == NULL || SYMBOL_IS_DEFINED (expr->symbol))
    {
      /* If expression can be evaluated, compare its value against the limits
	 and complain if the value is out of bounds. */
      int32 value = eval_imm_expr (expr);

      if (value < min || max < value)
	{
	  char str[200];
	  sprintf (str, "immediate value (%d) out of range (%d .. %d)",
		   value, min, max);
	  yywarn (str);
	}
    }
}


#ifdef __STDC__
static void
check_uimm_range(imm_expr* expr, uint32 min, uint32 max)
#else
static void
check_uimm_range()^
     imm_expr* expr;
     int32 umin;
     int32 umax;
#endif
{
  if (expr->symbol == NULL || SYMBOL_IS_DEFINED (expr->symbol))
    {
      /* If expression can be evaluated, compare its value against the limits
	     and complain if the value is out of bounds. */
      uint32 value = eval_imm_expr (expr);

      if (value < min || max < value)
	{
	  char str[200];
	  sprintf (str, "immediate value (%d) out of range (%d .. %d)",
		   value, min, max);
	  yywarn (str);
	}
    }
}

#ifdef __STDC__
void
yyerror (char *s)
#else
void
yyerror (s)
     char *s;
#endif
{
  parse_error_occurred = 1;
  yywarn (s);
}


#ifdef __STDC__
void
yywarn (char *s)
#else
void
yywarn (s)
     char *s;
#endif
{
  error ("spim: (parser) %s on line %d of file %s\n", s, line_no, input_file_name);
  print_erroneous_line ();
}
