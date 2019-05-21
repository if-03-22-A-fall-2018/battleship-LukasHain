/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/

#include <stdio.h>
#include "battleship.h"

CellContent my_field[10][10];
CellContent op_field[10][10];
CellContent guess_field[10][10];
/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game() {
  FILE* my_fd = fopen("battleship.my", "r");
  FILE* op_fd = fopen("battleship.op", "r");

  for (size_t i = 0; i < FIELDSIZE; i++) {
    for (size_t u = 0; u < FIELDSIZE; u++) {
      fread(&my_field[i][u], sizeof(CellContent), 1, my_fd);
      fread(&op_field[i][u], sizeof(CellContent), 1, op_fd);
      guess_field[i][u] = Unknown;
    }
  }
  fclose(my_fd);
  fclose(op_fd);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col) {
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0) {
    return OutOfRange;
  }
  return my_field[row][col];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col) {
  if (get_my_guess(row, col) == OutOfRange) {
    return false;
  }
  guess_field[row][col] = op_field[row][col];
  if (guess_field[row][col] == Boat) {
    for (size_t i = -1; i <= 1; i++) {
      for (size_t u = -1; u <= 1; u++) {
        if (get_my_guess(row, col) != OutOfRange) {
          guess_field[i][u] = Water;
        }
      }
    }
  }

  return true;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col) {
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0) {
    return OutOfRange;
  }
  return guess_field[row][col];
}
