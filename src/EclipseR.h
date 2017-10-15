/*
 * EclipseR.h
 *
 *  Created on: Sep 11, 2017
 *      Author: justin
 */

#ifndef ECLIPSER_H_
#define ECLIPSER_H_

#include <string>

#include "Eclipse.h"
#include "FileInput.h"
#include "ResizableArray.h"


void dataInputLoop(ResizableArray<Eclipse>& eclipseDataArray, FileInput& fileInput);

void dataManipLoop(ResizableArray<Eclipse>& eclipseDataArray, FileInput& fileInput);



/**
 * Main function where the program runs and calls helper functions
 * @return 0 if the program completes successfully
 */
int main();


#endif /* ECLIPSER_H_ */
