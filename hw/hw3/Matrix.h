#ifndef __Matrix_h_
#define __Matrix_h_

using namespace std;

class Matrix{
public:
	//constructor
	Matrix() : data(NULL), num_row(0), num_column(0){}
	Matrix( const Matrix& rhs );
	Matrix( unsigned int row, unsigned int column, double fill );
	
	//accessor
	unsigned int num_rows() const{ return num_row; }
	unsigned int num_cols() const { return num_column; }
	double getEntryVal( unsigned int row, unsigned int column ) const;
	bool get( unsigned int row, unsigned int column, double& val ) const;
	bool isZeroMatrix() const;
	double* get_row( unsigned int row );
	double* get_col( unsigned int row );

	//modifier
	void setEntryVal( unsigned int row, unsigned int column, double val );
	bool set( unsigned int row, unsigned int column, double val );
	bool add( const Matrix& rhs );
	bool subtract( const Matrix& rhs );
	bool swap_row( unsigned int row1, unsigned int row2 );
	void multiply_by_coefficient( double coeff );
	void transpose();
	Matrix* quarter() const;
	void resize( unsigned int row, unsigned int column, double fill );
	
	//destructor
	~Matrix() { clear(); }
	void clear();
	
	//operator overload
	bool operator== ( const Matrix& rhs ) const;
	bool operator!= ( const Matrix& rhs ) const { return !( *this == rhs ); }
	void operator= ( const Matrix& rhs );
	

	
private:
	double** data;
	unsigned int num_row;
	unsigned int num_column;
	
	//helper function
	void allocSpace();
};

ostream& operator<< ( ostream& os, const Matrix& m );

#endif
