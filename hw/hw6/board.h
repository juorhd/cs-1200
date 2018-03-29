#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "point.h"

using namespace std;

// ============================================================================
// | This class stores the grid representation of battleship.                 |
// | represented as NULL if the current grid location does not contain a tile |
// ============================================================================

class Board {

public:

	// CONSTRUCTOR
	Board();
	Board(int rowNum, int colNum);
	Board( const Board &old ) 			{ copy(old); }
	Board& operator= ( const Board &old);

	// ACCESSORS
	int numRows() const 			   	{ return rowNum; }
	int numCols() const 			   	{ return colNum; }
	char getRowCell( int row ) const		{ return rowCells[row]; }
	char getColCell( int col ) const		{ return colCells[col]; }
	char getSymbol( int row, int col ) const   	{ return board[row][col]; }
	bool isavailable( int row, int col ) const 	{ return available[row][col]; }
	bool RowCellNumPositive( int row ) const	{ return board[row][numCols()] > '0'; }
	bool ColCellNumPositive( int col ) const	{ return board[numRows()][col] > '0'; }

	// MODIFIERS
	void setSymbol( int row, int col, char symbol)  { board[row][col] = symbol; }
	void assignRowCell( int rowNum )		{ rowCells = new char[rowNum]; }
	void assignColCell( int colNum )		{ colCells = new char[colNum]; }
	void setRowcell( int row, char val )		{ rowCells[row] = val; }
	void setColcell( int col, char val )		{ colCells[col] = val; }
	void RowCellNumAdd ( int row ) 			{ board[row][numCols()]++;  }
	void RowCellNumMinus ( int row ) 		{ board[row][numCols()]--;  }
	void ColCellNumAdd ( int col ) 			{ board[numRows()][col]++;  }
	void ColCellNumMinus ( int col ) 		{ board[numRows()][col]--;  }
	void setAvailibilityFalse( int row, int col )   { available[row][col] = false; }
	void setAvailibilityTrue( int row, int col )    { available[row][col] = true; }
	void setNumCells();
	void remove_points( vector<Point> &board_pts, vector<Point> &valid_pts, int b_size, int v_size );

	// PRINTING
	void printActual() const;
	void printAvailability() const;

	// DESSTUCTOR
	~Board() 					{ destroy(); }
	void clear()   					{ destroy(); }
	

private:
	
	// PRIVATE HELPER FUNCTION
	void copy( const Board &old );
	void destroy();
	
	// REPRESENTATION
	char** board;
	bool** available;
	char* rowCells;
	char* colCells;
	
	int rowNum;
	int colNum;
};



#endif
