#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "Matrix.h"

using namespace std;

//private helper function
//allocate space for new matrix
void Matrix::allocSpace()
{
	data = new double*[num_row];
	for ( int i = 0; i < num_row; ++i ) {
		data[i] = new double[num_column];
	}
}


//return: true if matrix is zero matrix
//	  false vice versa. 
bool Matrix::isZeroMatrix() const{
	if ( data == NULL || num_rows()*num_cols() == 0 ){
		return true;
	}
	return false;
}


//Constructor
//takes: 3 arguments of matrix you want to create
//if:    either row or column == 0 will produce a zero matrix
//else:  fill the entries with the input value  
Matrix::Matrix( unsigned int row, unsigned int column, double fill ){
	if ( row == 0 || column == 0 ){
		data = NULL;
	} else {
		num_row = row;
		num_column = column;
		allocSpace();
		
		for ( int i = 0; i < row; ++i )
			for ( int j = 0; j < column; ++j )
				data[i][j] = fill;
		
	} 
}

//Copy Constructor
//takes: the target matrix you want to make a copy
//if:    the target matrix is zero matrix, you create a zero matrix
//else:  allocate memory for new matrix, make it identical to the target matrix
Matrix::Matrix( const Matrix& rhs ){
	if ( rhs.isZeroMatrix() ){
		data = NULL;
		num_row = num_column = 0;
	} else { 
		num_row = rhs.num_rows();
		num_column = rhs.num_cols();
		allocSpace();

				
		for ( int i = 0; i < num_row; ++i ){
			for ( int j = 0; j < num_column; ++j )
				data[i][j] = rhs.getEntryVal(i, j);
		}
	}
}


//helper accesor
//takes:    the row value and column value 
//ensures:  row value and column value is in the boundary
//returns:  the value of entry corresponding to that location 
double Matrix::getEntryVal( unsigned int row, unsigned int column ) const {
	return data[row][column];
}


//modifier
//takes:     the row value and column value 
//ensures:   row value and column value is in the boundary
//modifies:  the value of entry corresponding to that location 
void Matrix::setEntryVal( unsigned int row, unsigned int column, double val ) {
	data[row][column] = val;
}


//accesor
//takes:    the row value and column value and the value of the 
//					entry you want to get (passed by reference)
//
//modifies: the value of the variable ( passed by reference )
//returns:  false  if either row value or column value is out of boundary
// 	    true   if that entry exists 
bool Matrix::get( unsigned int row, unsigned int column, double& val ) const{
	if ( row >= num_rows() || column >= num_cols() ){
		return false;
	} else {
		val = getEntryVal( row, column );
		return true;
	}
}

//modifier
//takes:    the row value and column value and the value of the 
//						entry you want to set
//
//modifies: the corresponding entry value if exist
//returns:  false  if either row value or column value is out of boundary
// 	    true   if that entry exists 

bool Matrix::set( unsigned int row, unsigned int column, double val ){
	if ( row >= num_rows() || column >= num_cols() ){
		return false;
	} else {
		setEntryVal( row, column, val );
		return true;
	}
}


//modifier
//takes:    another matrix
//modifies: add the variable matrix to the one that is calling this function
//returns:  false  if two matrices have different size
// 	    true   added successfully  
bool Matrix::add( const Matrix& rhs ){
	if ( num_rows() != rhs.num_rows() || num_cols() != rhs.num_cols() ){
		return false;
	} else {
		for ( int i = 0; i < num_row; ++i )
			for ( int j = 0; j < num_column; ++j )
				setEntryVal(i, j, getEntryVal(i, j) 
						+ rhs.getEntryVal(i, j) );
	}
	return true;
}

//modifier
//takes:    another matrix
//modifies: subtract the variable matrix to the one that is calling this function
//returns:  false  if two matrices have different size
// 	    true   added successfully  
bool Matrix::subtract( const Matrix& rhs ){
	if ( num_rows() != rhs.num_rows() || num_cols() != rhs.num_cols() ){
		return false;
	} else {
		for ( int i = 0; i < num_row; ++i )
			for ( int j = 0; j < num_column; ++j )
				setEntryVal(i, j, getEntryVal(i, j) 
						- rhs.getEntryVal(i, j) );
	}
	return true;
}

//modifier
//takes:    a coefficient
//modifies: multiply the coefficient to the matrix that is calling this function
void Matrix::multiply_by_coefficient( double coeff ){
	if ( isZeroMatrix() ){
		return;
	} else {
		for ( int i = 0; i < num_row; ++i )
			for ( int j = 0; j < num_column; ++j )
				setEntryVal(i, j, coeff * getEntryVal(i, j) );
	}
}


//accesor
//takes:    the row value 
//returns:  NULL  			if the row value is out of boundary 
//	    The entries of that row	if the row is within the boyndary
double* Matrix::get_row( unsigned int row ){
	if ( isZeroMatrix() || row >= num_rows() ){ 
		return NULL; 
	} else { 
		double* tmp_row = new double[num_cols()];
		for ( int i = 0; i < num_cols(); ++i ){
			tmp_row[i] = getEntryVal(row, i);
		}
		return tmp_row; 
	}
}

//accesor
//takes:    the column value 
//returns:  NULL  			 if the column value is out of boundary 
//	    The entries of that column	 if the column is within the boyndary
double* Matrix::get_col( unsigned int col ){
	if ( isZeroMatrix() || col >= num_cols() ){ 
		return NULL; 
	} else { 
		double* tmp_col = new double[num_rows()];
		for ( int i = 0; i < num_rows(); ++i ){
			tmp_col[i] = getEntryVal(i, col);
		}
		return tmp_col; 
	}
}

//modifier
//takes:    two row value
//modifies: the matrix, swapping entries of two rows 
//returns:  false if either row value is out of boundary
//	    true  if two rows are successfully swapped
bool Matrix::swap_row( unsigned int row1, unsigned int row2 ){
	if ( row1 >= num_rows() || row2 >= num_rows() ){
		return false;
	} else {
		double* tmp_row = data[row1];
		data[row1] = data[row2];
		data[row2] = tmp_row;
		return true;
	}
}


//modifier
//modifies: transpose the matrix 
void Matrix::transpose(){
	if ( isZeroMatrix() ) return;
	double** tmp_data = new double*[num_cols()];
	for ( int i = 0; i < num_cols(); ++i ){
		tmp_data[i] = new double[num_rows()];
		for ( int j = 0; j < num_rows(); ++j ){
			tmp_data[i][j] = getEntryVal(j, i) ;
		}
	}

	clear();
	data = tmp_data;
	swap( num_row, num_column );
}


//accessor
//returns: Four matrix pointer, pointing to UL UR LL LR
//		 	which are four parts of the original matrix

Matrix* Matrix::quarter() const{
	int quaterNumRow = (num_rows()+1)/2; 
	int quaterNumCol = (num_cols()+1)/2;

	Matrix UL(quaterNumRow, quaterNumCol, 0);
	Matrix UR(quaterNumRow, quaterNumCol, 0);
	Matrix LL(quaterNumRow, quaterNumCol, 0);
	Matrix LR(quaterNumRow, quaterNumCol, 0);
	
	int DivisionRow, DivisionCol;
	
	if ( num_rows() % 2 == 0 )
		DivisionRow = num_rows()+1 / 2;
	else DivisionRow = ( (num_rows()+1) / 2) - 1;
	
	if ( num_cols() % 2 == 0 )
		DivisionCol = num_cols() / 2;
	else DivisionCol = ( (num_cols()+1) / 2) - 1;
	
	for (int i = 0; i < quaterNumRow; ++i )
		for ( int j = 0; j < quaterNumCol; ++j){
			UL.setEntryVal(i, j, getEntryVal(i, j) );
			UR.setEntryVal(i, j, getEntryVal(i, DivisionCol+j) );
			LL.setEntryVal(i, j, getEntryVal(DivisionRow+i, j) );
			LR.setEntryVal(i, j, getEntryVal(DivisionRow+i, DivisionCol+j) );
		}
	
	
	Matrix* m_ptr = new Matrix[4];
	m_ptr[0] = UL;
	m_ptr[1] = UR;
	m_ptr[2] = LL;
	m_ptr[3] = LR;
	
	return m_ptr;
}


//modifier
//takes:    new row value, column value and the fill value
//modifies: the matrix, resize the matrix and 
//	    fill the value to the entry which is not in the original value
//	    retain the value of the original matrix for the overlapping part
void Matrix::resize( unsigned int row, unsigned int column, double fill ){
	if ( row == 0 || column == 0 )
		clear();

	Matrix resized_m(row, column, fill);
	for ( int i = 0; i < row; ++i )
		for ( int j = 0; j < column; ++j )
			if ( i < num_rows() && j < num_cols() )
				resized_m.setEntryVal(i, j, getEntryVal(i, j) );
	clear();
	*this = resized_m; 
}

//destructor
//destructs the dynamic memories allocated 
void Matrix::clear(){
	if ( !isZeroMatrix() ){
		for ( int i = 0; i < num_rows(); ++i ){
			delete [] data[i];
		}
		delete [] data;
	}
	data = NULL;
}


//operator overload == 
//takes:    a matrix 
//returns:  false   if two matrix are not identical
//	    true    vice versa
bool Matrix::operator==( const Matrix& rhs ) const{
	if ( num_rows() != rhs.num_rows() || num_cols() != rhs.num_cols() ){
		return false;
	} else {
		if ( isZeroMatrix() )
			return true;
		
		for ( int i = 0; i < num_rows(); ++i )
			for ( int j = 0; j < num_cols(); ++j)
				if ( getEntryVal(i, j) != rhs.getEntryVal(i, j) )
					return false;
	}
	return true;
}

//operator overload = 
//takes:    a matrix 
//modifies: the calling matrix, copies the variable matrix to the calling matrix
void Matrix::operator= ( const Matrix& rhs ){
	
	clear();
	if ( rhs.isZeroMatrix() ){
		data = NULL;
		num_row = num_column = 0;
	} else { 
		num_row = rhs.num_rows();
		num_column = rhs.num_cols();
		allocSpace();

				
		for ( int i = 0; i < num_row; ++i ){
			for ( int j = 0; j < num_column; ++j )
				data[i][j] = rhs.getEntryVal(i, j);
		}
	}
}


//operator overload << 
//takes:    ostream, and a matrix you want to print
//prints the matrix by a certain structure
ostream& operator<< ( ostream& os, const Matrix& m ){
	
	os << endl;
	os << m.num_rows() << " x "<< m.num_cols() << " matrix:" << endl;
	
	if ( m.isZeroMatrix() ){
		os << "[ ]" << endl;
	} else {
		os << '[';
		for ( int i = 0; i < m.num_rows(); ++i ){
			if ( i > 0 ) os << ' ';
			for ( int j = 0; j < m.num_cols(); ++j ){
				os << ' ' << m.getEntryVal(i,j);
			}
			if (i < m.num_rows()-1 ){ 
				os << endl;
			} else {
				os << " ]" << endl;
			}
		}
	}
	return os;
} 

