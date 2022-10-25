/* Program to assist in the challenge of solving sudoku sudokus.

     Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: [Stefan Temelkovski 1270368]
   Dated:     [04/09/21]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

#define EMTYCLL 0
/* Final set that relates to rows (Sets 0-8 = Rows 1-9) */
#define ENDRWST 8
/* Final set that relates to columns (Sets 9-17 = Columns 1-9) */
#define ENDCLMST 17
/* Divider for row of square sets */
#define SQRRWDIV "------+-------+------" 

void read_sudoku_array(int sudoku[], int prvs[]);
void sudoku_format(int cell);
void print_cells(int cellval, int cell);
int print_sudoku(int sudoku[]);
void is_valid_grid(int sudoku[]);
void print_invalid(int set, int val, int count);
void strategy_one(int sudoku[], int prvs[]);
int correct_number(int sudoku[], int prvs[], int cell);
int check_numbers(int sudoku[], int size, int cell);
void copy_grid(int sudoku[], int prvs[]);
void print_solved_cell(int cells[], int crctval[], int n);
void final_result(int sudoku[]);
void new_line();
void ta_daa();

/****************************************************************/

/* Main program controls all the action */

int
main(int argc, char *argv[]) {
	int sudoku[NCLL] = {0}, previous[NCLL] = {0};
	
	new_line();

	read_sudoku_array(sudoku, previous);
	print_sudoku(sudoku);
			
	is_valid_grid(sudoku);
	
	strategy_one(sudoku, previous);
	
	final_result(sudoku);
	
	/* all done, so pack up bat and ball and head home */
	return 0;
	
}

/****************************************************************/

/* Modified version of "read_int_array" from "Grok Exercise 7.2" 
Alistair Moffat, May 2013 */

/* Read in values from sudoku */

void
read_sudoku_array(int sudoku[], int prvs[]) {
	int cellval;
	int cell = 0;
	
	while (scanf("%d", &cellval) == 1) {
		/* Store in two arrays */
		sudoku[cell] = cellval;
		prvs[cell++] = cellval;
	}	     
	
}

/****************************************************************/

/* Print correctly formatted sudoku (Stage 1) */

int
print_sudoku(int sudoku[]) {
	int cell;
	int emptycells = 0;
	
	/* Print out each value in array */
	for (cell=0; cell<NCLL; cell++) {		
	    sudoku_format(cell);
	    print_cells(sudoku[cell], cell);
	    /* Count number of empty cells in grid */
	    if(sudoku[cell] == EMTYCLL) {
	    	emptycells++; 
	    }
	}
		
	new_line();
	new_line();
	
	printf("%2d cells are unknown\n", emptycells); 
	
	return emptycells;
	
}

/****************************************************************/

/* Format sudoku puzzle */

void
sudoku_format(int cell) {
	
	 /* To prevent the divison of 0 returning remainder 0 
	 from affecting the format */
	 if(cell == 0) {
	 }
	 /* New line at end of each row */
	 else if(cell % NDIG == 0) { 
	 	 new_line();	
	 }
	 /* Seperate each square */
	 else if(cell % NDIM == 0) {
	 	 printf("| ");	
	 }
	 
	 /* Seperate each row of squares */
	 if (rownum(cell-1) % NDIM == 0 && colnum(cell) == 1) {                       
	 	printf(SQRRWDIV); 	
	 	new_line();
	 }			
	 
}

/****************************************************************/

/* Print each sudoku value in grid format */
 
void
print_cells(int cellval, int cell) {
	
	/* Change inputs of 0 into period point */
	if(cellval == EMTYCLL && colnum(cell) == 9) {	
		/* Remove trailling whitespace if in final column (9) */
		printf(".");
	}	
	else if (cellval == EMTYCLL) {
    	printf(". ");	
	}
	/* print non-empty values */  
    else if (colnum(cell) == 9){  
    	/* Remove trailling whitespace if in final column (9) */
    	printf("%d", cellval);	
	}
	else {
		printf("%d ", cellval);
    }
    
}

/****************************************************************/

/* Determine if input values create a valid sudoku (Stage 2) */

void
is_valid_grid(int sudoku[]) {
	int set, cell, val;
	int count = 0, vio = 0, setvio = 0;
	/* Impossible set number (correctly 1-27) so first set (index 0) 
	is counted when comparing set against setno */
	int setno = -1; 
	
	fill_c2s();
	
	new_line();
	
	/* Check all 27 sets */
	for(set=0; set<NSET; set++) {
		/* Check cell against all valid sudoku numbers 1-9 */
		for(val=1; val<=9; val++) {
			/* Check all cells in set */
			for(cell=0; cell<NDIG; cell++) { 
				/* Increase if value found in set */
				if(sudoku[s2c[set][cell]] == val) {
					count++;
				}			
			}
			/* Increase set violation if more than one of same value found
			& first violation in set */
			if (count > 1 && set != setno) {
				setvio++;	
			}
			/* Increase violations if more than one of same value found */
			if (count > 1) {
				vio++;
				/* Store set where violation was found */
				setno = set;
			}		
			print_invalid(set, val, count);
			count = 0;		
		}		
	}	
	
	/* Exit program if violations to grid are found */
	if(vio > 0) {
		printf("\n%d different sets have violations\n", setvio);
		printf("%d violations in total\n", vio);
		exit(EXIT_FAILURE);
	}
	
}
	
/****************************************************************/

/* Prints where violations were found */

void
print_invalid(int set, int val, int count) {
	/* Sets 0-8 = Rows 1-9 */
	int row = set+1;
	/* Sets 9-17 = Columns 1-9 */
	int col = set-8;
	/* Sets 18-26 = Squares 1-9 */
	int sqr = set-17;
	
	/* Violation Found */
	if(count > 1) {
		/* Violated set is a row */
		if(set <= ENDRWST) {
		printf("set %2d (row %d): %d instances of %d\n", set, row, count, val); 
		}
		/* Violated set is a column */
		else if(ENDRWST < set && set <= ENDCLMST) {
		printf("set %2d (col %d): %d instances of %d\n", set, col, count, val);	
		}
		/* Violated set is a square */
		else {
		printf("set %2d (sqr %d): %d instances of %d\n", set, sqr, count, val);	
		}					
	}
	
}

/****************************************************************/

/* Attempt to solve sudoku using Strategy One (Stage 3) */

void
strategy_one(int sudoku[], int prvs[]) {
	int cell;
	int changes = 0, ncll = 0;
	int crctvals[NCLL] = {0}, cells[NCLL] = {0};
	
	for(cell=0; cell<NCLL; cell++) {
		/* Check for empty cells in grid */
		if(sudoku[cell] == EMTYCLL) {
			/* Find correct value for specific cell */
			sudoku[cell] = correct_number(sudoku, prvs, cell);   
			/* Increase if changes to grid are made */
			if(sudoku[cell] != EMTYCLL) {
				changes++;	
				/* Store solved cell positions and
				their correct value in arrays */        
				crctvals[ncll] = sudoku[cell];
				cells[ncll++] = cell;
			}
		}
	}
		
	/* Changes dependant on complete iterations of strategy one 
	and not changes made during that iteration */
	copy_grid(sudoku, prvs);
	
	/* Recursive calls to Strategy One until no more changes
	to the grid can be made */
	if(changes != 0) { 
		printf("strategy one\n");
		print_solved_cell(cells, crctvals, ncll);	
		new_line();
		strategy_one(sudoku, prvs);
	}
		
}

/****************************************************************/

/* Find all cellmates of the empty cell and determine it's correct value */

int
correct_number(int sudoku[], int prvs[], int cell) {
	int i, j, set, cellpos;
	int cllmts[NDIG*NGRP] = {0}, size = 0;
	
	/* Check all sets cell is apart of */
	for(i=0; i<NGRP; i++) {
		set = c2s[cell][i];
			/* Check all positions within particular set */
			for(j=0; j<NDIG; j++) {
				cellpos = s2c[set][j];
				/* Include all non-empty cellmates in array */
				if(prvs[cellpos] != EMTYCLL) {
					cllmts[size++] = prvs[cellpos];
				}
			}	
	}
	
	/* Return only possible value */
	return check_numbers(cllmts, size, cell);
	
}

/****************************************************************/

/* Find the correct value for the cell */

int
check_numbers(int cllmts[], int size, int cell) {
	int i, val, crctval;
	int count = 0, valcount = 0;

	/* Check cellmates against all possible sudoku values 1-9 */
	for(val=1; val<=9; val++) {
		for(i=0; i<size; i++) {
			/* Increase if value appears as cellmate */
			if(val == cllmts[i]) {
				count++; 
			}
		}
		/* Increase if value is not a cellmate */
		if(count == 0) {   
			valcount++;
			/* Store current value */
			crctval = val;
		} 
		/* Reset count for each value */
		count = 0;
	}
		
	/* Return value if there was only one value
	that did not appear as a cellmate */
	if(valcount == 1) {	
		return crctval;	
	}
	
	/* Keep cell empty if more than one potential value */
	return EMTYCLL;
	
}

/****************************************************************/

/* Copies modified array into a fixed array */ 

void
copy_grid(int sudoku[], int prvs[]) {
	int cell;
		
	for(cell=0; cell<NCLL; cell++) {
		prvs[cell] = sudoku[cell]; 
	}
	
}

/****************************************************************/

/* Print position of cell that was solved */

void
print_solved_cell(int cell[], int crctval[], int ncll) {
	int i;
	
	for(i=0; i<ncll; i++) {
		printf("row %d col %d must be %d\n", 
			rownum(cell[i]), colnum(cell[i]), crctval[i]);	
	}
	
}

/****************************************************************/

/* Print resultant sudoku grid of Strategy One */

void
final_result(int sudoku[]) {
	
	/* If no more empty cells...Ta Daa! */
	if(print_sudoku(sudoku) == 0){
		ta_daa();
	}
	
}

/****************************************************************/

/* Modified version of "blank_line" from 
"Sample solution comp20005 Assignment 1, 2020"
Alistair Moffat, April 2020 */

void
new_line() {
	
	printf("\n");
	
}

/****************************************************************/

void
ta_daa() {
	
	new_line();
	printf("ta daa!!!\n");
	
}

/****************************************************************/

/* algorithms are fun */

/****************************************************************/

