#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>

#include "board.h"


using namespace std;					
							
//global array for surrounding positions checking       
int nearby[8][2] = { { -1, -1 },   //upper left         //   +-----------+---------+-----------+-----> x-axis (col)
		     { -1,  0 },   //upper		//   | (y-1,x-1) | (y-1,x) | (y-1,x+1) |
		     { -1,  1 },   //upper right	//   +-----------+---------+-----------+
		     {  0,  1 },   //right		//   |  (y,x-1)  |  (y,x)  |  (y,x+1)  |
		     {  1,  1 },   //lower right	//   +-----------+---------+-----------+
		     {  1,  0 },   //lower 		//   | (y+1,x-1) | (y+1,x) | (y+1,x+1) |
		     {  1, -1 },   //lower left		//   +-----------+---------+-----------+
		     {  0, -1 } }; //left		//   |
							//   v
							// y-axis (row)
// A function that converts the ship type 
// to its length in char
char ShipNameToLength( const string& name ) {
	
	if ( name == "submarine" )   return '1';
	if ( name == "destroyer" )   return '2';
	if ( name == "cruiser" )     return '3';
	if ( name == "battleship" )  return '4';
	if ( name == "carrier" )     return '5';
	if ( name == "cargo" )       return '6';
	if ( name == "tanker" )      return '7';
	if ( name == "unknown" )     return '?';
	return '*';
}

// A function that converts the ship length 
// back to its ship type
string LengthToShipName( char length ){
	
	if ( length == '1' )   return "submarine ";
	if ( length == '2' )   return "destroyer ";
	if ( length == '3' )   return "cruiser   ";
	if ( length == '4' )   return "battleship";
	if ( length == '5' )   return "carrier   ";
	if ( length == '6' )   return "cargo     ";
	if ( length == '7' )   return "tanker    ";
	
	return "unknown";
	
}

// ==========================================================================
// Helper function that takes in the command line and deal with it
void CommandLineHandler( int argc, char *argv[], string &filename,
						bool &all_solution ) {

	filename = argv[1];

	// parse the optional arguments
	for ( int i = 2; i < argc; ++i ) {
		if ( argv[i] == string("find_all_solutions") ) 
			all_solution = true;
	}
}
// ============================================================================================
// Helper function to read the input arguments
// setting up the board
// reading the constraints and unknowns

void ReadFromFile( int argc, char *argv[], const string &filename, int &rowNum, int &colNum,
			Board &board, vector<char> &ships, bool &has_unknown, bool &has_unknown_ship, 
				         bool &has_constraint, vector< vector<char> > &constraints) {

	// Open the file
	ifstream istr(filename.c_str());

	// Read each line of the file
	string word;
	char c;
	
	while ( istr >> word ) {
		if ( word == "board" ) {
			istr >> rowNum >> colNum;
			for ( int j = 0; j < rowNum; ++j ) 
				constraints.push_back( vector<char>(colNum, ' ') );
			Board tmp( rowNum, colNum );
			board = tmp;
			tmp.clear();
		// Read the row Cell nums
		} else if ( word == "rows" ) {
			for ( int j = 0; j < rowNum; ++j ) {
				istr >> c;
				if ( c == '?' ) has_unknown = true;
				board.setRowcell( j, c );
			}
		// Read the col Cell nums
		} else if ( word == "cols" ) {
			for ( int i = 0; i < colNum; ++i ) {
				istr >> c;
				if ( c == '?' ) has_unknown = true;
				board.setColcell( i, c );
			}
		// Has constraints
		} else if ( word == "constraint" ) {
			has_constraint = true;
			int row, col;
			istr >> row >> col >> constraints[row][col];
		}
		 else { 
			// Unknown case
			if ( word == "unknown" ) has_unknown_ship = true;
			ships.push_back( ShipNameToLength( word ) ); }
	}
	// set the cell nums on board
	board.setNumCells();
}

// ======================================================================================
// Helper function to determine whether the point is in boundary
bool inBoundary( int row, int col, Board &board ) {
	return ( row >= 0 ) && ( row < board.numRows() ) 
		&& ( col >= 0 ) && ( col < board.numCols() );
}

// ======================================================================================
// Function that takes the row/col coordinates, the shiplength, direction of ship
// board information, constraints information 
// to check whether its possible to put the ship there
bool checkAvailability( int row, int col, int shipLength, int direction, Board &board, 
				bool has_constraint, const vector< vector<char> > &constraints ) {
	
		
	int rowPos, colPos;
	
	//check current position
	if ( !board.RowCellNumPositive(row) 
		|| !board.ColCellNumPositive(col) 
			|| !board.isavailable(row, col) ) return false;
	
	//if it is a submarine
	if ( shipLength == 1 ) {
		
		// if constraint is present
		if ( has_constraint ) {
			if ( constraints[row][col] != ' ' && constraints[row][col] != 'o' ) {
				return false;
			}
		}
		
		//check surroundings
		for ( int i = 0; i < 8; ++i ) {
			rowPos = row + nearby[i][0];
			colPos = col + nearby[i][1];
			if ( inBoundary( rowPos, colPos, board) ) {
				if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
					return false;
				}
			}
		}
		
	} else {
		//horizontal case
		if ( direction == 1 ) {
			
			//boundary & every part availability check
			for ( int i = 1; i < shipLength; ++i ) {
				if ( !inBoundary( row, col+i, board) ) {
					return false;
				}
				if ( !board.RowCellNumPositive(row) 
					|| !board.ColCellNumPositive(col+i) 
						|| !board.isavailable(row, col+i) ) return false;
			}
			
			//check whether the ship exceeds the column occupation number
			if ( shipLength > board.getSymbol( row, board.numCols() ) - '0' ) {
				return false;
			}
			
			//check whether every part of the ship violates the adjacency policy
			for ( int i = 0; i < shipLength; ++i ) {
				
				//leftmost part
				if ( i == 0 ) {
					
					//constraint check
					if ( has_constraint ) {
						if ( constraints[row][col] != ' ' && constraints[row][col] != '<' ) {
							return false;
						}
					}
					
					//3 adjacent pos check
					for ( int j = 6; j < 9 && j > 5; ++j ) {
						
						if ( j == 8 ) j = 0;
						rowPos = row + nearby[j][0];
						colPos = col + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
								return false;
							}
						}
					}
				} 
				
				//rightmost part
				if ( i == shipLength - 1 ) {
					
					//constraint check
					if ( has_constraint ) {
						if ( constraints[row][col+i] != ' ' && constraints[row][col+i] != '>' ) {
							return false;
						}
					}
					//3 adjacent pos check
					for ( int j = 2; j < 5; ++j ) {
						
						rowPos = row     + nearby[j][0];
						colPos = col + i + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
								return false;
							}
						}
					}
				}
				//middle part
				if ( i > 0 && i < shipLength-1 ) {
					if ( has_constraint ) {
						if ( constraints[row][col+i] != ' ' && constraints[row][col+i] != 'X' ) {
							return false;
						}
					}
				}
				//2 adjacent pos check
				for ( int j = 1; j < 6; j += 4 ) {
							
					rowPos = row     + nearby[j][0];
					colPos = col + i + nearby[j][1];
							
					if ( inBoundary( rowPos, colPos, board) ) {
						if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
							return false;
						}
					}
				}
			}
		}
		//vertical case
		if ( direction == 2 ) {
			for ( int j = 1; j < shipLength; ++j ) {
				if ( !inBoundary( row+j, col, board) ) {
					return false;
				}
				if ( !board.RowCellNumPositive(row+j) 
					|| !board.ColCellNumPositive(col) 
						|| !board.isavailable(row+j, col) ) return false;
			}
			
			//check whether the ship exceeds the row occupation number
			if ( shipLength > board.getSymbol( board.numRows(), col ) - '0' ) {
				return false;
			}
			
			//check whether every part of the ship violates the adjacency policy
			for ( int j = 0; j < shipLength; ++j ) {
				
				//upmost part
				if ( j == 0 ) {
					//constraint check
					if ( has_constraint ) {
						if ( constraints[row][col] != ' ' && constraints[row][col] != '^' ) {
							return false;
						}
					}
					//3 adjacent pos check
					for ( int i = 0; i < 3 ; ++i ) {
						
						rowPos = row + nearby[i][0];
						colPos = col + nearby[i][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
								return false;
							}
						}
					}
				} 
				
				//bottommost part
				if ( j == shipLength - 1 ) {
					
					//constraint check
					if ( has_constraint ) {
						if ( constraints[row+j][col] != ' ' && constraints[row+j][col] != 'v' ) {
							return false;
						}
					}
					//3 adjacent pos check
					for ( int i = 4; i < 7; ++i ) {
						
						rowPos = row + j + nearby[i][0];
						colPos = col     + nearby[i][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
								return false;
							}
						}
					}
				}
				//middle part
				if ( j > 0 && j < shipLength-1 ) {
					if ( has_constraint ) {
						if ( constraints[row+j][col] != ' ' && constraints[row+j][col] != 'X' ) {
							return false;
						}
					}
				}
				//2 adjacent pos check
				for ( int i = 3; i < 8; i += 4 ) {
							
					rowPos = row + j + nearby[i][0];
					colPos = col     + nearby[i][1];
							
					if ( inBoundary( rowPos, colPos, board) ) {
						if ( board.getSymbol( rowPos, colPos ) != ' ' ) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}


// =========================================================================================
// Add the ship, change the availability of the surrounding area
// also recording the changes for futhur operations.
void addShip( int row, int col, int shipLength, int direction, Board &board,
				vector< Point > &board_pts, vector< Point > &valid_pts) {
	
	int rowPos, colPos;
	
	if ( shipLength == 1 ) {
		
		//set the place we put ship unavailable and recore changes
		board.setAvailibilityFalse( row, col );
		valid_pts.push_back( Point( row, col ) );
		
		//change the output and recore changes
		board.setSymbol( row, col, 'o' );
		board_pts.push_back( Point( row, col ) );
		
		//decrease the row/col occupation num by 1
		board.RowCellNumMinus( row );
		board.ColCellNumMinus( col );

		//check surrounding 8 positions
		for ( int i = 0; i < 8; ++i ) {
			rowPos = row + nearby[i][0];
			colPos = col + nearby[i][1];
			if ( inBoundary( rowPos, colPos, board) ) {
				if ( board.isavailable( rowPos, colPos ) ){
					
					//set the surrounding unavailable and recore changes
					valid_pts.push_back( Point( rowPos, colPos ) );
					board.setAvailibilityFalse( rowPos, colPos );
				}
			}
		}
		
	} else {
		//horizontal
		if ( direction == 1 ) {
			for ( int i = 0; i < shipLength; ++i ) {
				
				//set the place we put ship unavailable and record changes
				board.setAvailibilityFalse( row, col+i );
				board_pts.push_back( Point( row, col+i ) );
				valid_pts.push_back( Point( row, col+i ) );
				
				//decrease the row/col occupation num by 1
				board.RowCellNumMinus( row );
				board.ColCellNumMinus( col+i );
						
				// if its the leftmost part
				if ( i == 0 ) {
					board.setSymbol( row, col+i, '<' );
					
					//change 3 specific locations
					for ( int j = 6; j < 9 && j > 5; ++j ) {
						
						if ( j == 8 ) j = 0;
						rowPos = row + nearby[j][0];
						colPos = col + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.isavailable( rowPos, colPos ) ) {
								valid_pts.push_back( Point( rowPos, colPos ) );
								board.setAvailibilityFalse( rowPos, colPos );
							}
						}
					}
				} 
				// if its the rightmost part
				if ( i == shipLength - 1 ) {
					board.setSymbol( row, col+i, '>' );
					
					//change 3 specific locations
					for ( int j = 2; j < 5; ++j ) {
						
						rowPos = row     + nearby[j][0];
						colPos = col + i + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.isavailable( rowPos, colPos ) ) {
								valid_pts.push_back( Point( rowPos, colPos ) );
								board.setAvailibilityFalse( rowPos, colPos );
							}
						}
					}
				} 
				
				// middle part
				if ( i > 0 && i < shipLength - 1 ){
					board.setSymbol( row, col+i, 'X' );
				}
				// check up and down					
				for ( int j = 1; j < 6; j += 4 ) {
							
					rowPos = row     + nearby[j][0];
					colPos = col + i + nearby[j][1];
							
					if ( inBoundary( rowPos, colPos, board) ) {
						if ( board.isavailable( rowPos, colPos ) ) {
							valid_pts.push_back( Point( rowPos, colPos ) );
							board.setAvailibilityFalse( rowPos, colPos );
						}
					}
				}
			}
			
		}
		//vertical
		if ( direction == 2 ) {
			for ( int i = 0; i < shipLength; ++i ) {
				
				//set the place we put ship unavailable
				board.setAvailibilityFalse( row+i, col );
				board_pts.push_back( Point( row+i, col ) );
				valid_pts.push_back( Point( row+i, col ) );

				//decrease the row/col occupation num by 1
				board.RowCellNumMinus( row+i );
				board.ColCellNumMinus( col );
				
				// upmost part
				if ( i == 0 ) {
					board.setSymbol( row+i, col, '^' );
					for ( int j = 0; j < 3; ++j ) {
						
						rowPos = row + nearby[j][0];
						colPos = col + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.isavailable( rowPos, colPos ) ) {
								valid_pts.push_back( Point( rowPos, colPos ) );
								board.setAvailibilityFalse( rowPos, colPos );
							}
						}
					}
				} 
				// bottom most part
				if ( i == shipLength - 1 ) {
					board.setSymbol( row+i, col, 'v' );
					for ( int j = 4; j < 7; ++j ) {
						
						rowPos = row + i + nearby[j][0];
						colPos = col     + nearby[j][1];
						
						if ( inBoundary( rowPos, colPos, board) ) {
							if ( board.isavailable( rowPos, colPos ) ){
								valid_pts.push_back( Point( rowPos, colPos ) );
								board.setAvailibilityFalse( rowPos, colPos );
							}
						}
					}
				} 
				//middle part
				if ( i > 0 && i < shipLength - 1 ){
					board.setSymbol( row+i, col, 'X' );
				}
				for ( int j = 3; j < 8; j += 4 ) {
						
					rowPos = row + i + nearby[j][0];
					colPos = col     + nearby[j][1];
						
					if ( inBoundary( rowPos, colPos, board) ) {
						if ( board.isavailable( rowPos, colPos ) ) {
							valid_pts.push_back( Point( rowPos, colPos ) );
							board.setAvailibilityFalse( rowPos, colPos );
						}
					}
				}
			}
		}
	}	
}

// ======================================================================================
// Helper function to check: for an unknown board with '?'
// the terminate situation should not only be we exhaust the 
// ships, but also the non-'?' cell num position should be 0
bool checkUnknownBoard( const Board &board ){

	for ( int j = 0; j < board.numRows(); ++j ){
		if ( board.getRowCell( j ) != '?'
			&& board.getSymbol( j, board.numCols() ) != '0'  ){
			return false;
		}
	}
	for ( int i = 0; i < board.numCols(); ++i ){
		if ( board.getColCell( i ) != '?' 
			&& board.getSymbol( board.numRows(), i ) != '0'  ){
			return false;
		}
	}
	return true;
}
// ======================================================================================
// the Main recursive function
// takes in the row/col coordinates, board information, ships, the current ship index
// the solution count, the answer, and the bool variables for unknowns, constraint
// also the points vector for retrieve of the original board
 
void placeShip( int row, int col, Board &board, vector<char> &ships, int index, 
			 int &count, vector<string> &answer, bool has_unknown,
				bool has_unknown_ship, bool has_constraint, bool all_solution,
			 		const vector< vector<char> > &constraints, 
							vector< Point > &board_pts, 
								vector< Point > &valid_pts ) {
	// if only one solution needed			
	if ( !all_solution && count > 0 ) return;
	
	// if we exhaust the ships
	if ( index < 0 ){
		// if we have unknown ships/ cell num
		if ( has_unknown || has_unknown_ship ) {
			if ( !checkUnknownBoard( board ) ) {
				return;
			}	
		}
		// if we have constraint
		if ( has_constraint ){
			for ( int j = 0; j < board.numRows(); ++j )
				for ( int i = 0; i < board.numCols(); ++i )
					if ( constraints[j][i] != ' ' &&
						constraints[j][i] != board.getSymbol( j, i )) 
						return;
		}
		// for one solution
		if ( !all_solution ){
					
			printf("Solution:\n");
			for ( int i = 0; i < answer.size(); ++i ){
				cout << answer[i] << endl;
			}
			board.printActual();
			count++;
			return;
		}
		
		// for all solutions
		printf("Solution:\n");
		
		for ( int i = 0; i < answer.size(); ++i ){
			cout << answer[i] << endl;
		} 
		board.printActual();

		count++;
		return;
	}
	
	char ship = ships[index];
	int shipLenth = ship - '0';
	
	// submarine no need to turn around
	if ( shipLenth == 1  ) {
		if( checkAvailability( row, col, 1, 0, board, has_constraint, constraints) ) {

			int b_size = board_pts.size();
			int v_size = valid_pts.size();
			addShip( row, col, 1, 0, board, board_pts, valid_pts );
			
			// store answers
			answer.push_back( "submarine  "+ to_string(row) +" " + to_string(col) );
			// if next one is same type, dont need to start at (0,0)
			if ( index > 0 && ships[index-1] == ship ){
				if ( inBoundary(row, col+1, board) )
					placeShip( row, col+1, board, ships, index-1, count, answer, has_unknown, 
								   has_unknown_ship, has_constraint, all_solution, 
										constraints, board_pts, valid_pts );
				else if  ( inBoundary(row+1, 0, board) )
					placeShip( row+1, 0, board, ships, index-1, count, answer, has_unknown, 
								  has_unknown_ship, has_constraint, all_solution, 
										constraints, board_pts, valid_pts );
			}
			else placeShip( 0, 0, board, ships, index-1, count, answer, has_unknown, 
								has_unknown_ship, has_constraint, all_solution, 
										constraints, board_pts, valid_pts );
			
			//trace back for other recursion
			answer.pop_back();
			board.remove_points( board_pts, valid_pts, b_size, v_size );

		}
	} else {
		// 1 represents horizontal
		// 2 represents vertical
		for ( int i = 1; i <= 2; ++i ) {
			if ( checkAvailability( row, col, shipLenth, i, board, has_constraint, constraints ) ) {

				int b_size = board_pts.size();
				int v_size = valid_pts.size();
				addShip( row, col, shipLenth, i, board, board_pts, valid_pts );

				//store answers
				string ans = LengthToShipName( shipLenth + '0' ) + " ";
				ans += to_string(row) +" " + to_string(col) 
						+ ((i==1) ? " horizontal" : " vertical");
				answer.push_back(ans);
				
				// if next one is same type, dont need to start at (0,0)

				if ( index > 0 && ships[index-1] == ship ){
					if ( inBoundary(row, col+1, board) )
						placeShip( row, col+1, board, ships, index-1, count, answer, has_unknown, 
									    has_unknown_ship, has_constraint, all_solution, 
											 constraints, board_pts, valid_pts );
					else if  ( inBoundary(row+1, 0, board) )
						placeShip( row+1, 0, board, ships, index-1, count, answer, has_unknown, 
								has_unknown_ship, has_constraint, all_solution, constraints, 
													board_pts, valid_pts );
				} 
				else placeShip( 0, 0, board, ships, index-1, count, answer, has_unknown, has_unknown_ship,
							 has_constraint, all_solution, constraints, board_pts, valid_pts );
				//trace back for other recursion
				answer.pop_back();
				board.remove_points( board_pts, valid_pts, b_size, v_size );
			}
		}
	}
	
	// keep searching
	if ( inBoundary(row, col+1, board) )
		placeShip( row, col+1, board, ships, index, count, answer, has_unknown, has_unknown_ship,
				        has_constraint, all_solution, constraints, board_pts, valid_pts );
				
	else if  ( inBoundary(row+1, 0, board) )
		placeShip( row+1, 0, board, ships, index, count, answer, has_unknown, has_unknown_ship,
				        has_constraint, all_solution, constraints, board_pts, valid_pts );

	
		
}
// ======================================================================================
// This section are four helper function about the unknown case

// Helper function to calculate the toal length of the unknown ships 
int unknownTotalLength( const vector<char> &ships, int start_index ){
	int len = 0;
	for ( int i = start_index; i < ships.size(); ++i ) {
		len += ships[i] - '0';
	}
	return len;
}

// Helper function to check whether the unknown ships is in order
bool orders( const vector<char> &ships, int start_index ) {
	for ( int i = start_index; i < ships.size()-1; ++i ){
		if ( ships[i] < ships[i+1] ) return false;
	}
	return true;
}

// Helper recursive function to deal with the unknown ships, generating the possibilities
// for different combination of the unknown ships, setting limitations and store them in
// a vector without repetition
void UnknownHandler( vector<char> &ships, vector< vector<char> > &ships_possibilities, 
			int start_index, int current_index, int maxlength, int minlength,
									int maxshiplength ) {
	if ( unknownTotalLength(ships, start_index) > maxlength ) return;
	if ( unknownTotalLength(ships, start_index) >= minlength ) {

		ships_possibilities.push_back(ships);
		
	}
	int new_start = current_index;
	for ( int i = new_start; i < ships.size(); ++i ) {
		ships[i]++;
		if ( ships[i] <= min( maxshiplength, 7 ) + '0'
				&& (orders(ships, start_index) ) ) {
								
			UnknownHandler(ships, ships_possibilities, start_index, i,
					       maxlength, minlength, maxshiplength);			
		}	
		ships[i]--;	
	}
}


// =======================================================================================
int main( int argc, char *argv[] ) {

	//get the file
	string filename;
	bool all_solution = false;
	CommandLineHandler( argc, argv, filename, all_solution );
	
	//create the variables
	int rowNum, colNum;
	int count = 0;
	bool has_constraint = false;
	bool has_unknown = false;
	bool has_unknown_ship = false;

	vector<char> ships;
	vector<string> answer;
	vector< vector<char> > constraints;
	vector<Point> board_pts;
	vector<Point> valid_pts;
	Board board;
	
	ReadFromFile( argc, argv, filename, rowNum, colNum, board, ships, has_unknown, 
					has_unknown_ship, has_constraint, constraints);
	
	sort( ships.begin(), ships.end() );
	
	// if we have unknown ship
	if ( has_unknown_ship ) {
		int rowCellNum = 0;
		int colCellNum = 0;
		int maxrow = 0;
		int maxcol = 0;
		vector< vector<char> > ships_possibilities;
		
		for ( int j = 0; j < rowNum; ++j ){
			if ( board.getRowCell( j ) == '?' )
				maxrow += colNum;
			else{
				maxrow += board.getRowCell( j ) - '0';
				rowCellNum += board.getRowCell( j ) - '0';
			}
		}
		for ( int i = 0; i < colNum; ++i ){
			if ( board.getColCell( i ) == '?' )
				maxcol += rowNum;
			else{
				maxcol += board.getColCell( i ) - '0';
				colCellNum += board.getColCell( i ) - '0';
			}
		}
		
		int maxUnknownLen = maxrow + maxcol;
		int minUnknownLen = rowCellNum + colCellNum;
		int start_index = 0;
		while ( ships[start_index] != '?' ) start_index++;

		for ( int i = start_index; i < ships.size(); ++i ){
			ships[i] = '1';
		}
		minUnknownLen /= 2;
		maxUnknownLen /= 2;
		for ( int i = 1; i < start_index; ++i ){
			minUnknownLen -= ships[i] - '0';
			maxUnknownLen -= ships[i] - '0';
		}
		if ( minUnknownLen < 1 ) minUnknownLen = 1;

		UnknownHandler( ships, ships_possibilities, start_index, start_index,  
				 maxUnknownLen, minUnknownLen, max(rowNum, colNum) );
				
		for ( int i = 0; i < ships_possibilities.size(); ++i ){
			ships = ships_possibilities[i] ;
			sort(ships.begin(), ships.end());
			placeShip( 0, 0, board, ships, ships.size()-1, count, answer, has_unknown,
							has_unknown_ship, has_constraint, all_solution,
								 	constraints, board_pts, valid_pts);
		}
	// if we dont have unknown ships
	} else {
		placeShip( 0, 0, board, ships, ships.size()-1, count, answer, has_unknown,
						has_unknown_ship, has_constraint, all_solution,
							 	constraints, board_pts, valid_pts);
	}
			
	if ( all_solution ) {
		if ( count == 0 ) printf("No Solution.\n");
		else printf("find %d solution(s)\n", count);
	}
	else if ( count == 0 ) printf("No Solution.\n");


}