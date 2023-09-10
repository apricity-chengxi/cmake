// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#else
#include <math.h>
#endif

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << "number" << std::endl;
        std::cout << "__cplusplus = " << __cplusplus << std::endl;
        return 1;
    }
    double inputValue = atof(argv[1]);
#ifdef USE_MYMATH
    double outputValue = mathfunctions::sqrt(inputValue);
#else
    double outputValue = sqrt(inputValue);
#endif
    std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;
    return 0;
}
