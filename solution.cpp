#include <iostream>
using namespace std ;
class Matrix {
	private :
		int n , m ;
		int ** values ;
	public :
		//Constructors that create a null Matrix
		Matrix() {
			n = 0 ;
			m = 0 ;
			values = 0 ;
		}
		//a n x m Matrix with 0 entries
		Matrix(int rows , int columns) {
			n = rows ;
			m = columns ;
			values = new int*[n] ;
			for(int i = 0 ; i < n ; i++)
				values[i] = new int[m] ;
			for(int i = 0 ; i < n ; i++)
				for(int j = 0 ; j < m ; j++)
					values[i][j] = 0 ;
		}
		//copy constructor
		Matrix(Matrix const& mat) {
			n = mat.n ;
			m = mat.m ;
			values = new int*[n] ;
			for(int i = 0 ; i < n ; i++)
				values[i] = new int[m] ;
			for(int i = 0 ; i < n ; i++)
				for(int j = 0 ; j < m ; j++)
					values[i][j] = mat.values[i][j] ;
		}
		//destructor
		~Matrix() {
			if(values != 0) {
				for(int i = 0 ; i < n ; i++)
					delete[] values[i] ;
				delete[] values ;
			}
		}
		//operator +
		Matrix const operator+(Matrix const& mat) const {
			Matrix result(n , m) ;
			for(int i = 0 ; i < n ; i++)
				for(int j = 0 ; j < m ; j++)
					result.values[i][j] = values[i][j] + mat.values[i][j] ;
			return result ;
		}
		//operator *
		Matrix const operator*(Matrix const& mat) const {
			Matrix result(n , mat.m) ;
			for(int i = 0 ; i < n ; i++) {
				for(int j = 0 ; j < mat.m ; j++) {
					for(int k = 0 ; k < m ; k++)
						result.values[i][j] = result.values[i][j] + values[i][k] * mat.values[k][j] ;
				}
			}
			return result ;
		}
		//operator ~
		Matrix const operator~() const {
			Matrix result(m , n) ;
			for(int i = 0 ; i < m ; i++)
				for(int j = 0 ; j < n ; j++)
					result.values[i][j] = values[j][i] ;
			return result ;
		}
		//operator =
		void operator=(Matrix const& mat) {
			if(values != 0) {
				for(int i = 0 ; i < n ; i++)
					delete[] values[i] ;
				delete[] values ;
			}
			n = mat.n ;
			m = mat.m ;
			values = new int*[n] ;
			for(int i = 0 ; i < n ; i++)
				values[i] = new int[m] ;
			for(int i = 0 ; i < n ; i++)
				for(int j = 0 ; j < m ; j++)
					values[i][j] = mat.values[i][j] ;
		}
		//the function call operator that returns a reference to the ij th entry of the Matrix
		int& operator()(int i , int j) {
			return values[i][j] ;
		}
		//returns the subMatrix containing k consecutive rows and l columns, starting from the i,j th entry
		Matrix const operator()(int i , int j , int k , int l) const {
			Matrix result(k , l) ;
			for(int x = 0 ; x < k ; x++) {
				for(int y = 0 ; y < l ; y++) {
					result.values[x][y] = values[i + x][j + y] ;
				}
			}
			return result ;
		}
		//returns the matrix obtained by replacing the submatrix of M, consisting of consecutive rows and columns, starting with the i,j th entry by the matrix A.
		Matrix const operator()(int i , int j , Matrix const&A) const {
			Matrix result(*this) ;
			for(int x = 0 ; x < A.n ; x++) {
				for(int y = 0 ; y < A.m ; y++) {
					result.values[i + x][i + y] = A.values[x][y] ;
				}
			}
			return result ;
		}
} ;
