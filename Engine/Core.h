#pragma once

struct Parameters {
    Parameters(int argc, char** argv) 
    : argc(argc)
    , argv(argv) {
    }

    int argc;
    char** argv;
};