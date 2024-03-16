#ifndef _UNI_TEST_H
#define _UNI_TEST_H
#include <check.h>

#include "./../3D_Viewer/c_code/cModules.h"
#include "../3D_Viewer/c_code/vectors.h"

Suite* make_matrix_suite(void);
Suite *make_vector_suite(void);
Suite *make_obj_loader_suite(void);

#endif