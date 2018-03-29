#include <cassert>
#include <cstdio>
#include <iostream>
#include <cmath>

#include "board.h"

using namespace std;
// ===============================================
// | this file implements the headfile "board.h" |
// ===============================================


// ==========================================================================

// PRIVATE HELPER FUNCTION
// member function to destroy the board class
void Board::destroy() {
	
	if ( numRows()*numCols() == 0 ) return;
	
	for ( int j = 0; j <= rowNum; ++j ) {
		delete [] board[j];
		if ( j < rowNum ) {
			delete [] available[j];
		}
	}
	delete [] board;
	delete [] available;
	
	delete [] rowCells;
	delete [] colCells;
	
	board = NULL;
	available = NULL;
	rowCells = NULL;
	colCells = NULL;
	rowNum = colNum = 0;
}

// member helper function to copy the board class 
void Board::copy( const Board &old ) {
	
	this->rowNum = old.numRows();
	this->colNum = old.numCols();
	
	board = new char*[ rowNum + 1 ];
	available = new bool*[ rowNum ];
	rowCells = new char[ rowNum ];
	colCells = new char[ colNum ];

	for ( int j = 0; j <= rowNum; ++j ) {
		
		board[j] = new char[ colNum + 1 ];
		if ( j < rowNum ) available[j] = new bool[ colNum ];
		
		for ( int i = 0; i <= colNum; ++i ) {
			board[j][i] = old.getSymbol(j, i);
			if ( j < rowNum && i < colNum ) {
				available[j][i] = old.isavailable(j, i);
			}
		}
	}
}


// CONSTRUCTOR

// default
Board::Board() {
	this->rowNum = 0;
	this->colNum = 0;
	board = NULL;
	available = NULL;
	rowCells = colCells = NULL;
}

// takes in the inputs (height & width) of the board
Board::Board(int rowNum, int colNum) {
	
	//Initialize variable for board class
	this->rowNum = rowNum;
	this->colNum = colNum;

	board = new char*[ rowNum + 1 ];
	available = new bool*[ rowNum ];

	for ( int j = 0; j <= rowNum; ++j ) {
		
		board[j] = new char[ colNum + 1 ];
		if ( j < rowNum ) available[j] = new bool[ colNum ];
		
		for ( int i = 0; i <= colNum; ++i ) {
			board[j][i] = ' ';
			if ( j < rowNum && i < colNum ) {
				available[j][i] = true;
			}
		}
	}

	// Initiate the num of cells occupation for row/col
	for ( int j = 0; j < rowNum; ++j ) { board[j][colNum] = '0'; }
	for ( int i = 0; i < colNum; ++i ) { board[rowNum][i] = '0'; }
	board[rowNum][colNum] = ' ';
	
	assignRowCell( rowNum );
	assignColCell( colNum );
}

// operator =
Board& Board::operator= ( const Board &old) {
	// check for self-assignment
	if ( &old != this ) {
		//clear();
		copy( old );
	}
	return *this;
}


//MODIFIER

// set the row/col num cells 
void Board::setNumCells() {
	for ( int j = 0; j < rowNum; ++j ) { 
		board[j][colNum] = rowCells[j]; 
		if ( rowCells[j] == '0' ) {
			for ( int i = 0; i < colNum; ++i ) {
				available[j][i] = false;
			}
		}
	}
	for ( int i = 0; i < colNum; ++i ) { 
		board[rowNum][i] = colCells[i];
		if ( colCells[i] == '0' ) {
			for ( int j = 0; j < rowNum; ++j ) {
				available[j][i] = false;
			}
		} 
	}
}

// from the stored point set we can change the modified board to original one
void Board::remove_points( vector<Point> &board_pts, vector<Point> &valid_pts, int b_size, int v_size ) {
		
	for ( int i = valid_pts.size()-1; i >= v_size; --i ) {
		setAvailibilityTrue( valid_pts[i].y(), valid_pts[i].x() );
		valid_pts.pop_back();
	}
	for ( int i = board_pts.size()-1; i >= b_size; --i ) {
		setSymbol( board_pts[i].y(), board_pts[i].x(), ' ' );
		RowCellNumAdd( board_pts[i].y() );
		ColCellNumAdd( board_pts[i].x() );
		board_pts.pop_back();

	}

}

//PRINTING

// printing function
void Board::printActual() const {
	printf("+");
	for ( int i = 0; i < colNum; ++i ) printf("-");
	printf("+\n");

	for ( int j = 0; j < rowNum; ++j ) {
		printf("|");
		for ( int i = 0; i < colNum; ++i ) {
			printf("%c", board[j][i]);
		} 
		printf("|");
		printf("%c\n", rowCells[j]);
	}
	printf("+");
	for ( int i = 0; i < colNum; ++i ) printf("-");
	printf("+\n ");
	for ( int i = 0; i < colNum; ++i ) { printf("%c", colCells[i]);  }
	printf("\n\n");

}

