/*
 * str.c - string functions
 *
 */
/*
 * Copyright (C) 1996-2017 Hirotsugu Kakugawa. 
 * All rights reserved.
 *
 * License: GPLv3 and FreeType Project License (FTL)
 *
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#if HAVE_STRING_H
# include <string.h>
#endif
#if HAVE_STRINGS_H
# include <strings.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#	include <sys/types.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#	include <sys/param.h>
#endif
#include "VFlib-3_7.h"
#include "VFsys.h"
#include "str.h"


Glocal char*
vf_strdup(char *s)
{
  char *p;

  if (s == NULL)
    return NULL;

  if ((p = (char*)malloc(strlen(s)+1)) == NULL){
    vf_error = VF_ERR_NO_MEMORY;
    return NULL;
  }
  strcpy(p, s);
  return p;
}


Glocal int
vf_strcmp_ci(char *s1, char *s2)
{
  for (;;){
    if ((*s1 == '\0') && (*s2 == '\0'))
      return 0;
    if ((*s1 == '\0') || (*s2 == '\0'))
      return 1;
    if (tolower(*s1) != tolower(*s2))
      return 1;
    s1++;
    s2++;
  }
}


Glocal int
vf_strncmp_ci(char *s1, char *s2, int n)
{

  while (n > 0){
    if ((*s1 == '\0') && (*s2 == '\0'))
      return 0;
    if ((*s1 == '\0') || (*s2 == '\0'))
      return 1;
    if (tolower(*s1) != tolower(*s2))
      return 1;
    s1++;
    s2++;
    n--;
  }
  return 0;
}


Glocal char*
vf_index(char *s, char ch)
{
  int  i;

  if ((i = vf_index_i(s, ch)) < 0)
    return NULL;
  return &s[i];
}


Glocal int
vf_index_i(char *s, char ch)
{
  int  i;

  i = 0;
  while (s[i] != '\0'){
    if (s[i] == ch)
      return i;
    i++;
  }
  return -1;
}


Glocal char*
vf_rindex(char *s, char ch)
{
  int  i;

  if ((i = vf_rindex_i(s, ch)) < 0)
    return NULL;
  return &s[i];
}


Glocal int
vf_rindex_i(char *s, char ch)
{
  int  i;

  if (s == NULL)
    return -1;

  i = strlen(s)-1;
  while (i >= 0){
    if (s[i] == ch)
      return i;
    --i;
  }
  return -1;
}


Glocal int
vf_index_str_i(char *s, char *t)
{
  int  i, tlen;

  if (s == NULL)
    return -1;

  tlen = strlen(t);
  i = 0;
  while (s[i] != '\0'){
    if (strncmp(&s[i], t, tlen) == 0)
      return i;
    i++;
  }
  return -1;
}


Glocal char*
vf_index_str(char *s, char *t)
{
  int  i;

  if ((i = vf_index_str_i(s, t)) < 0)
    return NULL;
  return &s[i];
}


Glocal int
vf_rindex_str_i(char *s, char *t)
{
  int  i, tlen;

  if ((s == NULL) | (t == NULL))
    return -1;

  tlen = strlen(t);
  i = strlen(s) - tlen;
  while (i >= 0){
    if (strncmp(&s[i], t, tlen) == 0)
      return i;
    --i;
  }
  return -1;
}

Glocal char*
vf_rindex_str(char *s, char *t)
{
  int  i;

  if ((i = vf_rindex_str_i(s, t)) < 0)
    return NULL;
  return &s[i];
}


Glocal int
vf_parse_bool(char *s)

{
  if (   (vf_strncmp_ci(s, "TRUE", 4) == 0)
      || (vf_strncmp_ci(s, "YES", 3) == 0) 
      || (vf_strncmp_ci(s, "OK", 2) == 0) 
      || (vf_strncmp_ci(s, "ON", 2) == 0) 
      || (vf_strncmp_ci(s, "T", 1) == 0)   /* lisp   */
      || (vf_strncmp_ci(s, "#T", 2) == 0)  /* scheme */
      || (vf_strncmp_ci(s, "1", 1) == 0)  )
    return TRUE;

  if (   (vf_strncmp_ci(s, "FALSE", 5) == 0)
      || (vf_strncmp_ci(s, "NO", 2) == 0) 
      || (vf_strncmp_ci(s, "OFF", 2) == 0) 
      || (vf_strncmp_ci(s, "NIL", 3) == 0)  /* lisp   */
      || (vf_strncmp_ci(s, "#F", 2) == 0)   /* scheme */
      || (vf_strncmp_ci(s, "0", 1) == 0)  )
    return FALSE;

    /*XXX*/
    /* Need a warning message? */   
    /* Need to specify default value? */

  return FALSE;
}


/*EOF*/
