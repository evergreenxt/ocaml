(***********************************************************************)
(*                                                                     *)
(*                           Objective Caml                            *)
(*                                                                     *)
(*            Xavier Leroy, projet Cristal, INRIA Rocquencourt         *)
(*                                                                     *)
(*  Copyright 1996 Institut National de Recherche en Informatique et   *)
(*  en Automatique.  All rights reserved.  This file is distributed    *)
(*  under the terms of the GNU Library General Public License, with    *)
(*  the special exception on linking described in file ../../LICENSE.  *)
(*                                                                     *)
(***********************************************************************)

(* $Id: threadUnix.ml,v 1.19 2004-07-13 12:25:13 xleroy Exp $ *)

(* Module [ThreadUnix]: thread-compatible system calls *)

let execv = Unix.execv
let execve = Unix.execve
let execvp = Unix.execvp
let wait = Unix.wait
let waitpid = Unix.waitpid
let system = Unix.system
let read = Unix.read
let write = Unix.write
let single_write = Unix.single_write
let select = Unix.select
let pipe = Unix.pipe
let open_process_in = Unix.open_process_in
let open_process_out = Unix.open_process_out
let open_process = Unix.open_process
let open_process_full = Unix.open_process_full
let sleep = Unix.sleep
let socket = Unix.socket
let socketpair = Unix.socketpair
let accept = Unix.accept
let connect = Unix.connect
let recv = Unix.recv
let recvfrom = Unix.recvfrom
let send = Unix.send
let sendto = Unix.sendto
let open_connection = Unix.open_connection
let establish_server = Unix.establish_server

open Unix

let rec timed_read fd buff ofs len timeout =
  if Thread.wait_timed_read fd timeout
  then begin try Unix.read fd buff ofs len
             with Unix_error((EAGAIN | EWOULDBLOCK), _, _) ->
                    timed_read fd buff ofs len timeout
       end
  else raise (Unix_error(ETIMEDOUT, "timed_read", ""))

let rec timed_write fd buff ofs len timeout =
  if Thread.wait_timed_write fd timeout
  then begin try Unix.write fd buff ofs len
             with Unix_error((EAGAIN | EWOULDBLOCK), _, _) ->
                    timed_write fd buff ofs len timeout
       end
  else raise (Unix_error(ETIMEDOUT, "timed_write", ""))
