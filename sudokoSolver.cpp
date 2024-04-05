//Sudoku Solver in C++
#include<iostream>
#include<vector>

using namespace std;

const int N=9;

//Function to print the solved Sudoku
void printGrid(const vector<vector<int>>&grid){
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }

}

//function to check if it's safe to place a number at a given position
bool isSafe(vector<vector<int>>& grid,int row, int col, int num) {
     // Check if the number is not already present in current row, current column, and current 3x3 subgrid
    for (int x=0; x < N; ++x){
       if(grid[row][x]==num || grid[x][col]==num || grid[(row - row % 3) + (x/3)][(col - col % 3) + (x % 3)] == num ){
           return false;
         }

       }
       return true;

}

// Function to solve puzzle using backtracking
bool solveSudoku (vector<vector<int>>& grid){
    int row = -1;
    int col = -1;
    bool isEmpty = true;

    //find the first empty cell
    for(int i = 0; i < N && isEmpty; ++i){
        for(int j = 0; j < N && isEmpty; ++j){
            if(grid[i][j] == 0){
                row = i;
                col = j;
                isEmpty = false;
            }
        }
    }

    //If there are no empty cells, the puzzle is solved
    if(isEmpty){
        return true;
    }

    //Try placing number from 1 to 9 in the empty cell
    for(int num = 1; num <= 9; ++num){
        if(isSafe(grid, row, col, num)){
            grid[row][col] = num;


            //Recursively solve the remaining puzzle
            if(solveSudoku(grid)){
                return true;
            }

            //If placing num at (row,col) don't lead to a solution, backtrack
            grid[row][col]= 0;  
        }
    }

    //If no number can be placed at (row,col),trigger backtracking
    return false;
}

int main(){
    vector<vector<int>> grid = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}

    };


    if(solveSudoku(grid)){
        cout << " Sudoku puzzle solved successfully:\n";
        printGrid(grid);
     }
     else{
        cout << "No solution exist for the given Sudoku puzzle.\n";
    }

    return 0;

    }