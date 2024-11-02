/*
File Name: lab7.cpp
Name: EECS 348 Lab 7 Matrix Program

Description: Program which implements a matrix class that allows users to perform various functions on a
    2D array. This includes: filling the matrix with numbers from a file, printing out the matrix, adding 2 matrices,
    multiplying 2 matrices, finding the sum of both diagonals of a matrix, and swapping 2 rows in a matrix.

Input: The user will be asked to create 2 matrices by inputting file names. 
Output: Displays both matrices as well as their sums, products, the sum of the diagonals of the first matrix, and 
    the first matrix after rows at index 0 and 2 have been swapped.
Author: Owen Berkholtz
Date: 11/02/2024
*/


#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

//Row and column size of the Matrices
const int SIZE = 4;




/* Class which handles matrices.

Methods: readMatrixFile, printMatrix, overloaded operator +, overloaded operator (*), sumDiagonal, and swapRows.

*/
class Matrix{
    private:
        int matrix[SIZE][SIZE]; //A 2D array which holds all integers in the matrix object.


    public:

    /* Method which reads a file given by the user and fills a matrix with the integers in the file.
    
    Input: user_file <-- A file typed in by the user.
    Output: None, fills the matrix.
    */
    void readMatrixFile(string user_file){
                static int linesRead = 0;  // Keep track of how many lines have been read
                int num; //Store the number read from the file temporarily.

                ifstream file(user_file); //Open the file the user gave.

                // Skip lines that have been read before.
                string line; //Store the line we are going to read.

                //Loop to check if the lines have been read. And skip the ones that have.
                for (int i = 0; i < linesRead; i++) {
                    //Try reading a line, if that is not possible, notify the user and return
                    if (!getline(file, line)) {
                        cout << "No more lines to read."; //Inform the user there are no more lines.
                        return;
                    }
                }


                //Fill the matrix with the next lines.
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {

                        if (file >> num) { //Read an integer
                            matrix[i][j] = num;} //Store that integer in the row and column specified.
                    }
                }
                linesRead += 4;  //Update the number of lines read
                file.close();//Close the file
            }




    /*Method to print out the matrix in a readable way.

    Input: None
    Output: Prints matrix for user.
    */
    void printMatrix() {
        cout << "====================" << endl; //Print out top border for the matrix.

        //Print the matrix out
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                cout << "[" << setw(3) << matrix[i][j] << "]"; //Print out the matrix number. Each cell has a width of 3 digits.
            }
            cout << endl; //Start new row
        }
        cout << "====================" << endl; //Print out bottom border of the matrix
    }



        /*Operator overload for the sum of 2 matrices

        Input: Takes the other matrix which will be added to the first matrix
        Output: Returns the sum of the two matrices.
        */
        Matrix operator +(Matrix m2){
            Matrix result; //Create a new matrix which will hold the sum matrix
            //Add the numbers in the matrix together.
            for(int i = 0; i <SIZE; i++){
               for(int j = 0; j <SIZE; j++){
                    result.matrix[i][j] = matrix[i][j] +m2.matrix[i][j]; //Add matrix numbers.
               } 
            }
            return result; //Return final matrix.
        }



        /*Operator overload for the product of 2 matrices.

        Input: Takes the other matrix which will multiplied to the first one.
        Output: Returns the product of the two matrices.
        */
        Matrix operator *(Matrix m2){
            Matrix result; //Create a new matrix for the product of the 2 matrices.
            //Multiply the matrix
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    // Start performing the dot product
                    result.matrix[i][j] = 0; //Store the sum for the current element
                    for (int k = 0; k < SIZE; k++) {
                        result.matrix[i][j] += matrix[i][k] * m2.matrix[k][j]; //Add products together
                    }
                }
            }
            return result;} // Return the final matrix
        


        /*Method to calculate the sum of the diagonals of the matrix.

        Input: None
        Output: The sum of the diagonals.
        */
        int sumDiagonal(){

            int sum = 0; //Create the sum variable

            //Add the diagonals to the sum
            for (int i = 0; i < SIZE; i++){
                sum += matrix[i][i]; //Top left to bottom right diagonal
                sum +=  matrix[i][SIZE-(i+1)]; //Top right to bottom left diagonal.
            }
            return sum; //Return the final sum
        }



        /*Method which swaps 2 rows in a matrix.
        
        Input: the 2 rows to swap
        Output: None, just swaps the matrix rows.
        */
        void swapRows(int row1, int row2){
            //Check if the rows are valid, if not then just return.
            if ((row1 < 0 || row1 >= SIZE) || (row2 < 0 || row2 >= SIZE)) {
                    cout << "Rows out of bounds" << endl;
                    return;
                }
            int store_row[SIZE]; //Temporary array which keeps track of row1
            //Copy row 1 into the temporary array
            for (int i = 0; i <SIZE; i++){
                store_row[i] = matrix[row1][i];
            }

            //Copy row 2 to row 1
            for(int j = 0; j <SIZE; j++){
                matrix[row1][j] = matrix[row2][j];
            }
            //Copy the temporary array to row 2
            for(int k = 0; k <SIZE; k++){
                matrix[row2][k] = store_row[k];
            }
        }
};




//main
int main()
{   
    string user_file1; //Create variable to store the name of the first file given by the user
    Matrix mat1; //Create the first matrix

    //Ask the user to give a file name
    cout << "Please enter file for matrix 1: ";
    cin >> user_file1;

    mat1.readMatrixFile(user_file1); //Fill the matrix with numbers from the file
    cout << "Matrix 1:" << endl; //label matrix 1
    mat1.printMatrix(); //Print it out for the user

    string user_file2;//Create variable to store the name of the second file given by the user
    Matrix mat2;//Create the second matrix

    //Ask the user to give a file name
    cout << "Please enter file for matrix 2: ";
    cin >> user_file2;


    mat2.readMatrixFile(user_file2);//Fill the matrix with numbers from the file
    cout << "Matrix 2:" << endl; //Label matrix 2
    mat2.printMatrix();//Print it out for the user

    cout << endl <<"******************************"<< endl;

    //Print the sum of matrices 1 and 2
    cout << endl<< "SUM OF MATRIX 1 AND 2:" << endl;
    Matrix mat3 = mat1+mat2;
    mat3.printMatrix();

    //Print the product of matrices 1 and 2
    cout << endl<< "PRODUCT OF MATRIX 1 AND 2:" << endl;
    Matrix mat4 = mat1*mat2;
    mat4.printMatrix();

    //Print the sum of the diagonals for matrix 1
    cout << endl << "SUM OF MATRIX 1 DIAGONALS: "<<mat1.sumDiagonal() << endl;

    //Swap rows 0 and 2 for matrix 1 and then print it.
    mat1.swapRows(0, 2);
    cout << endl << "MATRIX 1 AFTER SWAPPING ROWS:"<< endl;
    mat1.printMatrix();

    cout << endl <<"******************************"<< endl;
    return 0;
}