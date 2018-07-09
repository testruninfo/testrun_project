/***
        ------------------------------------------------------------------------

        Copyright 2018 [COPYRIGHT_OWNER]

        Licensed under the Apache License, Version 2.0 (the "License");
        you may not use this file except in compliance with the License.
        You may obtain a copy of the License at

                http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.

        ------------------------------------------------------------------------
*//**
        @file           testrun_lib.h
        @author         [AUTHOR]
        @date           2018-07-06

        @ingroup        testrun_lib

        @brief


        ------------------------------------------------------------------------
*/
#ifndef testrun_lib_h
#define testrun_lib_h

#include "testrun_copyright.h"

typedef struct testrun_lib testrun_lib;
typedef struct testrun_config testrun_config;

struct testrun_config {

        char *root_path;
        char *project_name;
        testrun_copyright copyright;

        void *custom;
};

struct testrun_lib {

        struct testrun_config config;

        bool (*create_folders)          (const testrun_lib *self);

        bool (*generate_makefiles)      (const testrun_lib *self);

        bool (*generate_test_scripts)   (const testrun_lib *self);

        bool (*generate_module_files)   (const testrun_lib *self,
                                         const char *module_name);


};

/*----------------------------------------------------------------------------*/

/**
        Generate the testrun.h header string.
*/
char *testrun_generate_testrun_header(testrun_config config);

#endif /* testrun_lib_h */

