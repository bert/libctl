/* libctl: flexible Guile-based control files for scientific software 
 * Copyright (C) 1998 Steven G. Johnson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA  02111-1307, USA.
 *
 * Steven G. Johnson can be contacted at stevenj@alum.mit.edu.
 */

#ifndef CTL_H
#define CTL_H

#include <guile/gh.h>

#include <ctl-config.h>

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

/**************************************************************************/

  /* Basic types: */

typedef int integer;
typedef double number;
typedef short boolean;
typedef SCM list;
typedef SCM object;

  /* define vector3 as a structure, not an array, so that it can
     be a function return value and so that simple assignment works. */
typedef struct {
  number x,y,z;
} vector3;

  /* similarly for matrix3x3 */
typedef struct {
  vector3 c0, c1, c2; /* the columns */
} matrix3x3;

/**************************************************************************/

#ifndef GH_LOOKUP_OK
#  define gh_lookup scm_symbol_value0
#endif

#ifndef HAVE_GH_LOAD
#  define gh_load gh_eval_file 
#endif

extern void ctl_include(char *filename);

/**************************************************************************/

  /* vector3 and matrix3x3 utilities: */

extern number vector3_dot(vector3 v1,vector3 v2);
extern number vector3_norm(vector3 v);
extern vector3 vector3_scale(number s, vector3 v);
extern vector3 unit_vector3(vector3 v);
extern vector3 vector3_cross(vector3 v1,vector3 v2);
extern vector3 vector3_plus(vector3 v1,vector3 v2);
extern vector3 vector3_minus(vector3 v1,vector3 v2);

extern vector3 matrix3x3_vector3_mult(matrix3x3 m, vector3 v);
extern matrix3x3 matrix3x3_mult(matrix3x3 m1, matrix3x3 m2);
extern matrix3x3 matrix3x3_inverse(matrix3x3 m);

/**************************************************************************/

  /* type conversion */

#ifndef HAVE_GH_BOOL2SCM
  /* Guile 1.2 is missing gh_bool2scm for some reason; redefine: */
extern SCM bool2scm(boolean);
#define gh_bool2scm bool2scm
#endif

extern vector3 scm2vector3(SCM sv);
extern SCM vector32scm(vector3 v);
extern matrix3x3 scm2matrix3x3(SCM sm);
extern SCM matrix3x32scm(matrix3x3 m);

#define ctl_convert_number_to_scm(x) gh_double2scm(x)
#define ctl_convert_integer_to_scm(x) gh_int2scm(x)
#define ctl_convert_string_to_scm(x) gh_str02scm(x)
#define ctl_convert_boolean_to_scm(x) gh_bool2scm(x)
#define ctl_convert_vector3_to_scm(x) vector32scm(x)
#define ctl_convert_matrix3x3_to_scm(x) matrix3x32scm(x)
#define ctl_convert_object_to_scm(x) (x)
#define ctl_convert_list_to_scm(x) (x)

#define ctl_convert_number_to_c(x) gh_scm2double(x)
#define ctl_convert_integer_to_c(x) gh_scm2int(x)
#define ctl_convert_string_to_c(x) gh_scm2newstr(x, 0)
#define ctl_convert_boolean_to_c(x) gh_scm2bool(x)
#define ctl_convert_vector3_to_c(x) scm2vector3(x)
#define ctl_convert_matrix3x3_to_c(x) scm2matrix3x3(x)
#define ctl_convert_object_to_c(x) (x)
#define ctl_convert_list_to_c(x) (x)

/**************************************************************************/

  /* variable get/set functions */

extern integer ctl_get_integer(char *identifier);
extern number ctl_get_number(char *identifier);
extern boolean ctl_get_boolean(char *identifier);
extern char* ctl_get_string(char *identifier);
extern vector3 ctl_get_vector3(char *identifier);
extern matrix3x3 ctl_get_matrix3x3(char *identifier);
extern list ctl_get_list(char *identifier);
extern object ctl_get_object(char *identifier);

extern void ctl_set_integer(char *identifier, integer value);
extern void ctl_set_number(char *identifier, number value);
extern void ctl_set_boolean(char *identifier, boolean value);
extern void ctl_set_string(char *identifier, char *value);
extern void ctl_set_vector3(char *identifier, vector3 value);
extern void ctl_set_matrix3x3(char *identifier, matrix3x3 value);
extern void ctl_set_list(char *identifier, list value);
extern void ctl_set_object(char *identifier, object value);

/**************************************************************************/

  /* list traversal */

extern int list_length(list l);
extern integer integer_list_ref(list l, int index);
extern number number_list_ref(list l, int index);
extern boolean boolean_list_ref(list l, int index);
extern char* string_list_ref(list l, int index);
extern vector3 vector3_list_ref(list l, int index);
extern matrix3x3 matrix3x3_list_ref(list l, int index);
extern list list_list_ref(list l, int index);
extern object object_list_ref(list l, int index);

/**************************************************************************/

  /* list creation */

extern list make_integer_list(int num_items, integer *items);
extern list make_number_list(int num_items, number *items);
extern list make_boolean_list(int num_items, boolean *items);
extern list make_string_list(int num_items, char **items);
extern list make_vector3_list(int num_items, vector3 *items);
extern list make_matrix3x3_list(int num_items, matrix3x3 *items);
extern list make_list_list(int num_items, list *items);
extern list make_object_list(int num_items, object *items);

/**************************************************************************/

  /* object properties */

boolean object_is_member(char *type_name, object o);

extern integer integer_object_property(object o, char *property_name);
extern number number_object_property(object o, char *property_name);
extern boolean boolean_object_property(object o, char *property_name);
extern char* string_object_property(object o, char *property_name);
extern vector3 vector3_object_property(object o, char *property_name);
extern matrix3x3 matrix3x3_object_property(object o, char *property_name);
extern list list_object_property(object o, char *property_name);
extern object object_object_property(object o, char *property_name);

/**************************************************************************/

#ifdef __cplusplus
	   }                               /* extern "C" */
#endif                          /* __cplusplus */

#endif /* CTL_H */
