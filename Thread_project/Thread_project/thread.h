#pragma once
/*
threads.h
--------------------------------------------------------------------------------------------------
Description- this module responsible on couning the end of each line.
*/
// includes --------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// definotions ----------------------------------------------------------------------------------

#define INITIAL_SIZE 10

// Function Declarations -----------------------------------------------------------------------

/*--------------------------------------------------------------------------------------------
DESCRIPTION - functions that help us know in which charecter each line is end.
PARAMETERS - fp: input file
RETURN - pointer to an array of integers. in each index the number of chrecters in the end of the
same row. include the line with EOF in the end.
    --------------------------------------------------------------------------------------------*/
int* end_lines(FILE* fp);
