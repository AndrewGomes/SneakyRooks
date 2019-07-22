// Author: Andrew Gomes (an289864)
// Professor Sean Szumlanski
// FALL 2017 COP 3502
// SneakyRooks.c
//////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "SneakyRooks.h"

// Custom conversion function because we can't compile using the -lm flag
// thus not giving us access to the built-in pow(x, y) function.
int baseConvert(int power) {

	int i;
	int converted = 26;

	// Anything to the zero is 1.
	if (power == 0)
		return 1;

	// Anything to the power of 1 is itself.
	if (power == 1)
		return 26;

	//printf("Looking at 26 to the power of %i \n", power);

	// For anything else.
	for (i = 0; i < power - 1; i++) {
		converted *= 26;
	}

	return converted;
}

// Custom function: counts the number of letters in the string
int countLetters(char *rookString) {

	int i;
	int length = strlen(rookString);
	int newLength = 0;

	for (i = 0 ; i < length; i++)
		if (isalpha(rookString[i]))
			newLength++;
		else
			return newLength;

	return newLength;
}

void parseCoordinateString(char *rookString, Coordinate *rookCoordinate) {

	int i;
	int column = 0;
	int row;
	int numberValue;

	// Sizes of our string
	int fullLength = strlen(rookString);
	int letterLength = countLetters(rookString);
	int numberLength = fullLength - letterLength;

	// Handle the letters first.
	for (i = 0; i < letterLength; i++) {
			
		// Convert the character to the numeric value, except we're starting with
		// 'a' equalling 1 instead of 0.
		numberValue = (rookString[i] - 'a') + 1; 

		// Convert the character to base 10 and then add it to the total column value.
		column += numberValue * baseConvert(letterLength - 1 - i);

		//printf("Adding +[%i] \n", numberValue * baseConvert(letterLength - 1 - i));

	}

	// Now let's parse the numbers at the end. Trim off the 
	// letters at the front then we can look at the remaining numbers.
	rookString += letterLength;
	rookCoordinate->row = atoi(rookString);

	// Set up the column length
	rookCoordinate->col = column;

}

int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize) {

	int i;
	int takenRows[boardSize + 1];
	int takenColumns[boardSize + 1];
	Coordinate *parsedCoordinates = malloc(sizeof(Coordinate));

	for (i = 0; i < numRooks; i++) {

		// We'll first parse the string.
		parseCoordinateString(rookStrings[i], parsedCoordinates);

		//printf("Parsed coordinates: [r: %i] and [c: %i] --- [%s] with [%i] rooks\n", parsedCoordinates->row, parsedCoordinates->col, rookStrings[i], numRooks);

		// Next check to see if the row or column is already populated somewhere on the board
		// This is pretty quick since an index in our array (takenRows/takenColumns) will be NOT NULL if the row/col is taken.
		// A rook can attack another rook if they both have the same row/col number!
		if (takenRows[parsedCoordinates->row] == 5 || takenColumns[parsedCoordinates->col] == 5) {
			free(parsedCoordinates);

			// Clear the arrays
			memset(takenRows, 0, sizeof(takenRows));
			memset(takenColumns, 0, sizeof(takenColumns));

			return 0;
		}

		// Set the row AND column as taken. We'll just put a 5 because.
		takenRows[parsedCoordinates->row] = 5;
		takenColumns[parsedCoordinates->col] = 5;

	}

	// Clear the arrays
	memset(takenRows, 0, sizeof(takenRows));
	memset(takenColumns, 0, sizeof(takenColumns));

	free(parsedCoordinates);

	// All of our rooks are safe!
	return 1;
}

double difficultyRating(void) {
	return 2.75;
}

double hoursSpent(void) {
	return 3.0;
}