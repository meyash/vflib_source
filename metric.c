/*
 * metric.c - font metrics
 * by Hirotsugu Kakugawa
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
#ifdef HAVE_SYS_TYPES_H
#	include <sys/types.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#	include <sys/param.h>
#endif

#include "VFlib-3_7.h"
#include "VFsys.h"
#include "consts.h"
#include "metric.h"



/**
 **   VF_FreeMetric1
 **/
Public void
VF_FreeMetric1(VF_METRIC1 metric1)
{
  vf_error = 0;
  vf_free(metric1);
}


/**
 **   VF_FreeMetric2
 **/
Public void
VF_FreeMetric2(VF_METRIC2 metric2)
{
  vf_error = 0;
  vf_free(metric2);
}


Glocal VF_METRIC1
vf_alloc_metric1(void)
{
  VF_METRIC1 metric;
  
  ALLOC_IF_ERR(metric, struct vf_s_metric1)
    return NULL;
  metric->bbx_width  = 0;
  metric->bbx_height = 0;
  metric->off_x      = 0;
  metric->off_y      = 0;
  metric->mv_x       = 0;
  metric->mv_y       = 0;
  return metric;
}

Glocal VF_METRIC2
vf_alloc_metric2(void)
{
  VF_METRIC2 metric;
  
  ALLOC_IF_ERR(metric, struct vf_s_metric2)
    return NULL;
  metric->bbx_width  = 0;
  metric->bbx_height = 0;
  metric->off_x      = 0;
  metric->off_y      = 0;
  metric->mv_x       = 0;
  metric->mv_y       = 0;
  return metric;
}


Glocal void
vf_metric1_to_metric2(VF_METRIC1 met1, double dpi, VF_METRIC2 met2)
{
  if ((met1 == NULL) || (met2 == NULL))
    return;
  met2->bbx_width  = (int)(met1->bbx_width * (dpi / 72.27) + 0.5);
  met2->bbx_height = (int)(met1->bbx_height * (dpi / 72.27) + 0.5);
  met2->off_x      = (int)(met1->off_x * (dpi / 72.27) + 0.5);
  met2->off_y      = (int)(met1->off_y * (dpi / 72.27) + 0.5);
  met2->mv_x       = (int)(met1->mv_x * (dpi / 72.27) + 0.5);
  met2->mv_y       = (int)(met1->mv_y * (dpi / 72.27) + 0.5);
}


Glocal void
vf_dump_metric1(VF_METRIC1 met)
{
  printf("Metric1: \n");
  printf("   bbx (%fx%f)\n", met->bbx_width, met->bbx_height);
  printf("   off (%f,%f)\n", met->off_x, met->off_y);
  printf("   mv  (%f,%f)\n", met->mv_x, met->mv_y);
}

Glocal void
vf_dump_metric2(VF_METRIC2 met)
{
  printf("Metric2: \n");
  printf("   bbx (%dx%d)\n", met->bbx_width, met->bbx_height);
  printf("   off (%d,%d)\n", met->off_x, met->off_y);
  printf("   mv  (%d,%d)\n", met->mv_x, met->mv_y);
}

/*EOF*/
