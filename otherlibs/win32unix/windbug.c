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

/* $Id: windbug.c,v 1.2 2008-07-31 12:09:18 xleroy Exp $ */

#include <windows.h>

int dbug = 0;

void dbug_init (void)
{
  dbug = (getenv("OCAMLDBUG") != NULL);
}

void dbug_cleanup (void)
{
}

int dbug_test (void)
{
  return dbug;
}
