#########################################################################
#                                                                       #
#                            Objective Caml                             #
#                                                                       #
#            Xavier Leroy, projet Cristal, INRIA Rocquencourt           #
#                                                                       #
#   Copyright 1999 Institut National de Recherche en Informatique et    #
#   en Automatique.  All rights reserved.  This file is distributed     #
#   under the terms of the Q Public License version 1.0.                #
#                                                                       #
#########################################################################

# $Id: Makefile,v 1.66 2007-11-22 22:14:43 doligez Exp $

include Makefile.shared

# To make custom toplevels

ocamlmktop: ocamlmktop.tpl ../config/Makefile
	sed -e 's|%%BINDIR%%|$(BINDIR)|' ocamlmktop.tpl > ocamlmktop
	chmod +x ocamlmktop
