#pragma once

struct CLIArguments {
    CLIArguments(int argc, char** argv) 
    : argc(argc)
    , argv(argv) {
    }

    int argc;
    char** argv;
};