# Sparse_Matrix
This C++ program is designed to perform operations on sparse matrices efficiently using a linked list-based data structure. The supported operations include reading a matrix from a file, multiplying by a constant, adding two matrices, multiplying two matrices, writing a matrix to a file, and viewing a matrix. The matrix input is in the following format:
Rows starting with the pound sign (#) contain comments and should be disregarded by your program.

- The first row that does not start with a pound sign defines the size of the matrix (number of rows and columns) as well as the number of non-zero elements in it.  For example,
     m = 3   n = 10   numItems = 18
means that the matrix has 3 rows, 10 columns and 18 non-zero elements (of the 30 total elements).  
An exception to this is when there is a scaling (constant) factor like in the operation mult(A,c).  Then the test case file will indicate the value of that constant factor, so the corresponding row will look, for example, like this:
     m = 3   n = 10   numItems = 18   const = 376

- Each row after this first defining row contains information about exactly 1 non-zero element – the row and column coordinates of the cell where it is stored, and its value.  For example,
     2,8 = 5708
means that the element in row 2 and column 8 has value 5708.

- The elements in the test files are ordered by column first, and then by row.  That is, element (4,1) would precede element (2,3) (since column 1 comes before column 3), which itself would precede element (5,3) (since both have the same column 3 but row 2 precedes row 5).  Look at the test case files for more examples.
