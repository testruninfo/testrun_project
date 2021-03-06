/***
        ------------------------------------------------------------------------

        Copyright 2018 Markus Toepfer

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
        @file           testrun_app.c
        @author         Markus Toepfer
        @date           2018-07-19

        @ingroup        testrun_lib

        @brief          Implementation of an default APP. 


        ------------------------------------------------------------------------
*/
#include "../include/testrun_app.h"

/*----------------------------------------------------------------------------*/

int testrun_app_run(int argc, char *argv[]){

        size_t size = 1000;
        char buffer[size];
        memset(buffer, 0, size);

        char path[PATH_MAX];
        memset(path, 0, PATH_MAX);

        if (argc == 1)
                testrun_config_print_usage(TESTRUN_DEFAULT_NAME);

        if (argc < 2)
                goto error;

        struct testrun_lib lib = testrun_lib_default();

        bool project = false;
        bool success = false;

        lib.config = testrun_config_read_user_input(
                                NULL,
                                &success, 
                                &project, 
                                argc, 
                                argv);

        if (!success)
                goto error;

        // adapt parameter of "NON CONFIGURED" items

        if (!lib.config.project.path) {

                if (!getcwd(path, PATH_MAX))
                        goto error;

                lib.config.project.path = path;
        }

        if (!lib.config.copyright.author){

                if (!testrun_utils_get_git_author(buffer, size))
                        goto error;

                lib.config.copyright.author = buffer;
        }

        if (project) {
                
                if (!testrun_lib_create_project(&lib))
                        goto error;
        } else {
                
                if (!testrun_lib_create_module(&lib, lib.config.project.name))
                        goto error;
        }

        return 0;
error:
        return -1;
}