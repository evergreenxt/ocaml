/***********************************************************************/
/*                                                                     */
/*                           Objective Caml                            */
/*                                                                     */
/*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         */
/*                                                                     */
/*  Copyright 1996 Institut National de Recherche en Informatique et   */
/*  en Automatique.  All rights reserved.  This file is distributed    */
/*  under the terms of the GNU Library General Public License, with    */
/*  the special exception on linking described in file ../../LICENSE.  */
/*                                                                     */
/***********************************************************************/

/* $Id: stat.c,v 1.15 2003-05-05 14:20:58 xleroy Exp $ */

#include <errno.h>
#include <mlvalues.h>
#include <memory.h>
#include <alloc.h>
#include "unixsupport.h"
#include "cst2constr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#ifndef S_IFLNK
#define S_IFLNK 0
#endif
#ifndef S_IFIFO
#define S_IFIFO 0
#endif
#ifndef S_IFSOCK
#define S_IFSOCK 0
#endif
#ifndef S_IFBLK
#define S_IFBLK 0
#endif

#ifndef EOVERFLOW
#define EOVERFLOW ERANGE
#endif

static int file_kind_table[] = {
  S_IFREG, S_IFDIR, S_IFCHR, S_IFBLK, S_IFLNK, S_IFIFO, S_IFSOCK
};

static value stat_aux(int use_64, struct stat *buf)
{
  CAMLparam0();
  CAMLlocal5(atime, mtime, ctime, offset, v);

  atime = copy_double((double) buf->st_atime);
  mtime = copy_double((double) buf->st_mtime);
  ctime = copy_double((double) buf->st_ctime);
  offset = use_64 ? Val_file_offset(buf->st_size) : Val_int (buf->st_size);
  v = alloc_small(12, 0);
  Field (v, 0) = Val_int (buf->st_dev);
  Field (v, 1) = Val_int (buf->st_ino);
  Field (v, 2) = cst_to_constr(buf->st_mode & S_IFMT, file_kind_table,
                               sizeof(file_kind_table) / sizeof(int), 0);
  Field (v, 3) = Val_int (buf->st_mode & 07777);
  Field (v, 4) = Val_int (buf->st_nlink);
  Field (v, 5) = Val_int (buf->st_uid);
  Field (v, 6) = Val_int (buf->st_gid);
  Field (v, 7) = Val_int (buf->st_rdev);
  Field (v, 8) = offset;
  Field (v, 9) = atime;
  Field (v, 10) = mtime;
  Field (v, 11) = ctime;
  CAMLreturn(v);
}

CAMLprim value unix_stat(value path)
{
  int ret;
  struct stat buf;
  ret = stat(String_val(path), &buf);
  if (ret == -1) uerror("stat", path);
  if (buf.st_size > Max_long && (buf.st_mode & S_IFMT) == S_IFREG)
    unix_error(EOVERFLOW, "stat", path);
  return stat_aux(0, &buf);
}

CAMLprim value unix_lstat(value path)
{
  int ret;
  struct stat buf;
#ifdef HAS_SYMLINK
  ret = lstat(String_val(path), &buf);
#else
  ret = stat(String_val(path), &buf);
#endif
  if (ret == -1) uerror("lstat", path);
  if (buf.st_size > Max_long && (buf.st_mode & S_IFMT) == S_IFREG)
    unix_error(EOVERFLOW, "lstat", path);
  return stat_aux(0, &buf);
}

CAMLprim value unix_fstat(value fd)
{
  int ret;
  struct stat buf;
  ret = fstat(Int_val(fd), &buf);
  if (ret == -1) uerror("fstat", Nothing);
  if (buf.st_size > Max_long && (buf.st_mode & S_IFMT) == S_IFREG)
    unix_error(EOVERFLOW, "fstat", Nothing);
  return stat_aux(0, &buf);
}

CAMLprim value unix_stat_64(value path)
{
  int ret;
  struct stat buf;
  ret = stat(String_val(path), &buf);
  if (ret == -1) uerror("stat", path);
  return stat_aux(1, &buf);
}

CAMLprim value unix_lstat_64(value path)
{
  int ret;
  struct stat buf;
#ifdef HAS_SYMLINK
  ret = lstat(String_val(path), &buf);
#else
  ret = stat(String_val(path), &buf);
#endif
  if (ret == -1) uerror("lstat", path);
  return stat_aux(1, &buf);
}

CAMLprim value unix_fstat_64(value fd)
{
  int ret;
  struct stat buf;
  ret = fstat(Int_val(fd), &buf);
  if (ret == -1) uerror("fstat", Nothing);
  return stat_aux(1, &buf);
}

