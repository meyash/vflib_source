/* 
 * vflmkpcf.c 
 * by Hirotsugu Kakugawa
 * - a vflibcap entry generator for X11 PCF bitmap fonts
 * - This program prints vflibcap entries to standard output.
 *
 *  15 May 2001
 */
/*
 * Copyright (C) 1996-2017 Hirotsugu Kakugawa. 
 * All rights reserved.
 *
 * License: GPLv3 and FreeType Project License (FTL)
 *
 */

#include "config.h"
#include "with.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#ifdef HAVE_STRING_H
#  include <string.h>
#endif
#include <ctype.h>
#ifdef HAVE_SYS_PARAM_H
#  include  <sys/param.h>
#endif
#ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
#endif

#include  "VFlib-3_7.h"
#include  "VFsys.h"
#include  "vflibcap.h"
#include  "pcf.h"
#include  "fsearch.h"
#include  "vflmklib.h"



void  gen_class_deafult(void);


char  *dpi   = NULL;
int    dpi_i = DEFAULT_KPS_DPI;

#define NDIRS    64
int   n_dirs; 
char  *pcf_fontdirs[NDIRS];

char *cmdline = NULL; 



int 
main(int argc, char **argv)
{
  int     i;
  int    xargc;
  char **xargv;

  dpi = malloc(256);
  sprintf(dpi, "%d", dpi_i);

  cmdline = copy_cmdline(argc, argv);

  n_dirs = 0;
  for (i = 0; i < NDIRS; i++){
    pcf_fontdirs[i] = NULL;
  }

  xargc = argc; 
  xargv = argv;

  for (xargc--,xargv++; xargc > 0; xargc--,xargv++){
    if ((strcmp(*xargv, "--help") == 0)
	|| (strcmp(*xargv, "-help") == 0)){
      printf("vflmkpcf: generates vflibcap entries for PCF fonts\n");
      printf("Usage: vflmkpcf [options]\n");
      printf("Options\n");
      printf("  -d DIR   : PCF font file directory\n");
      printf("  -r DPI   : Default device resolution\n");

      printf("Example: vflmkpcf -d /usr/X11R6/lib/X11/fonts// \n");
      exit(0);

    } else if (strcmp(*xargv, "-d") == 0){
      /* font dir */
      if (n_dirs == NDIRS){
	fprintf(stderr, "Too many PCF font directories\n");
	exit(1);
      }
      xargv++; xargc--;
      check_argc(xargc);
      pcf_fontdirs[n_dirs++] = x_strdup(*xargv);

    } else if (strcmp(*xargv, "-r") == 0){
      xargv++; xargc--;
      check_argc(xargc);
      dpi = strdup(*xargv);

    } else {
      if (*xargv[0] == '-'){
	fprintf(stderr, "vflmkpcf: unknown option %s\n", *xargv);
	exit(1);
      }
      break;

    }
  }

  banner("PCF", "vflmkpcf", cmdline);

  gen_class_deafult();    

  return 0;
}



void
gen_class_deafult(void)
{
  int   i;

  printf("(%s %s", 
	 VF_CAPE_VFLIBCAP_CLASS_DEFAULT_DEFINITION, FONTCLASS_NAME);
  printf("\n  (%s", VF_CAPE_FONT_DIRECTORIES);
  for (i = 0; i < n_dirs; i++)
    printf("\n       \"%s\"", pcf_fontdirs[i]);
  printf(")");
  printf("\n  (%s %s)", VF_CAPE_DPI, dpi);
  printf("\n  (%s \".gz\" \".Z\")", VF_CAPE_COMPRESSION_EXT);
  printf(")\n");
  printf("\n");
}

