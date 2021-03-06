; libctl: flexible Guile-based control files for scientific software 
; Copyright (C) 1998-2014 Massachusetts Institute of Technology and Steven G. Johnson
;
; This library is free software; you can redistribute it and/or
; modify it under the terms of the GNU Lesser General Public
; License as published by the Free Software Foundation; either
; version 2 of the License, or (at your option) any later version.
;
; This library is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.
; 
; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the
; Free Software Foundation, Inc., 59 Temple Place - Suite 330,
; Boston, MA  02111-1307, USA.
;
; Steven G. Johnson can be contacted at stevenj@alum.mit.edu.

; ****************************************************************

; Include other files that we need.  Note that the include.scm
; file must already have been loaded, since we need the include
; function it defines!

(include "utils.scm")
(include "vector3.scm")
(include "matrix3x3.scm")
(include "class.scm")
(include "io-vars.scm")
(include "extern-funcs.scm")
(include "help.scm")
(include "simplex.scm")
(include "math-utils.scm")
(include "interaction.scm")

(define-param interactive? #t)

; ****************************************************************
