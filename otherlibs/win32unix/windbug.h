/***********************************************************************/
/*                                                                     */
/*                           Objective Caml                            */
/*                                                                     */
/*  Contributed by Sylvain Le Gall for Lexifi                          */
/*                                                                     */
/*  Copyright 2008 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../../LICENSE.  */
/*                                                                     */
/***********************************************************************/

/* $Id: windbug.h,v 1.2 2008-07-31 12:09:18 xleroy Exp $ */

/*#define DBUG*/

#ifdef DBUG

#include <stdio.h>
#include <windows.h>

#define DBUG_PRINT(fmt, ...) \
  do \
  { \
    if (dbug_test()) \
    { \
      fprintf(stderr, "DBUG (pid:%d, tid: %d): ", GetCurrentProcessId(), GetCurrentThreadId()); \
      fprintf(stderr, fmt, __VA_ARGS__); \
      fprintf(stderr, "\n"); \
      fflush(stderr); \
    }; \
  } while(0)

/* Initialize and cleanup dbug variable */
void dbug_init    (void);
void dbug_cleanup (void);

/* Test if we are in dbug mode */
int  dbug_test    (void);

#define DBUG_INIT    dbug_init()
#define DBUG_CLEANUP dbug_cleanup()

#else
#define DBUG_PRINT(fmt, ...) 
#define DBUG_INIT
#define DBUG_CLEANUP
#endif

