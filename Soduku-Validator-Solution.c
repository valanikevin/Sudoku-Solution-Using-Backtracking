/*
 Name: Kevin Valani
 Program: Sudoku Game.
 Revision: June 02, June 03, June 04.
 Code Working: According to requirements, user is required to enter first 2 rows of
                the Sudoku Game, and the program is supposed to generate valid
                random numbers to make the entire Sudoku Valid.
                i) At Beginning, The program will print the assignment given valid grid.
                ii) Program Will Ask Users To Enter Rows With Space In Between.
                iii) Program will check for duplicates, invalid, special characters, range, etc.
                iv) If everything is correct, program will print the valid Grid.
                v) If something is wrong, program will print the invalid processed grid.
 Built On: XCode. OS: MacOS.
 */

#include <stdio.h>
#include <stdbool.h>

//Methods That Are Declared And Used Below Main().
int validateSudoku(int[][9]);
int isSafe(int[][9],int,int,int);
void printGridFull(int[][9]);
void gridVerifier(int[][9],int,int);
int verifyGridComplete(int[][9]);
void noSpace(char[], int*);
void buildGrid(int[], int[], int[][9]);
int dupCheck(int[9]);

// The Heart OF CODE >>>>>>>>>>>>
int main(void) {
    //Main() Declarations.
    char userInput1[100];
    char userInput2[100];
    int gridArray[9][9];
    int arrayWOSpace1[100], arrayWOSpace2[100];
    
    //Default Validation Grib. -- Coming Straight From Assignment.
    int validGrid[ ][ 9 ] = {{5,3,4,6,7,8,9,1,2}, {6,7,2,1,9,5,3,4,8},{1,9,8,3,4,2,5,6,7}, {8,5,9,7,6,1,4,2,3},{4,2,6,8,5,3,7,9,1},{7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},{2,8,7,4,1,9,6,3,5},{3,4,5,2,8,6,1,7,9}};
    
    //Printing Validation.
    printf("\n\n-------Sudoku Solution Program-------\n\n");
    printGridFull(validGrid);
    printf("\n\n------------------------\n");
    if(validateSudoku(validGrid)){
        printf("The Above Sudoku Is Valid. \n\n");
    }
    else{
        printf("The Above Sudoku Is NOT Valid. \n\n");
    }
    //User Inputs.
    //If something is wrong, while loop will be running for correct inputs.
    bool un1Status = true;
    do{
        printf("Please Enter Your Inputs One By One With Space In Between. Press Enter When Done.\n");
        printf("Enter Row 1: ");
        scanf("%[^\n]%*c", userInput1);
        noSpace(userInput1, arrayWOSpace1);
           if(dupCheck(arrayWOSpace1)){
                printf("Duplicate: One Or More Duplicate Number Found.\n");
            }
           else{
               un1Status = false;
           }
    }
    
    while (un1Status);
    
    //For Input Number 2.
    bool un2Status = true;
    do{
        printf("Enter Row 2: ");
        scanf("%[^\n]%*c", userInput2);
        noSpace(userInput2, arrayWOSpace2);
           if(dupCheck(arrayWOSpace2)){
                printf("Duplicate: One Or More Duplicate Number Found.\n");
            }
           else{
               un2Status = false;
           }
    }
    while (un2Status);
    
    //Method Call For Build Grid.
    buildGrid(arrayWOSpace1, arrayWOSpace2, gridArray);
    //Grid Verifier.
    gridVerifier(gridArray,0,0);

    //End Of The Code.
    return 0;
}

//The Body Of Code >>>>>>>>>>>>>

//This Method Is Acting As Final Grid Checker And Validator.
int validateSudoku(int grid[][9]){
    int status = 0;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(isSafe(grid, i, j, grid[i][j])){
                status = 1;
                //printf("the Sudoku Is Valid.\n");
            }
            else{
                //printf("The Sudoku Is Not Valid.\n");
                return 0;
            }
        }
    }
    
    return status;
}

//Below Method Will Check For Duplicates.
int dupCheck(int ro[9]){
    bool gridResult = 0;
    //-1 Will Be Replaced By The Numbers. And Dual Loop Will Check and Match The Duplicates.
    int rowTemp[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    for(int i=0; i<9 ; i++){
        bool gridResult1 = 0;
        for(int j=0; j < 9; j++){
            if(ro[i]==rowTemp[j]){
                gridResult = 1;
                gridResult1 = 1;
            }
        }
        if (gridResult1 == 0){
            rowTemp[i] = ro[i];
        }
    }
    //Will Return 0 - 1 acting as Boolean true false.
    return gridResult;
}

//Below Method Will Build Grid.
void buildGrid(int r1[], int r2[], int grid[][9]){
    //This is because to replace the first 2 rows with user's rows.
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(i==0){
                grid[i][j]=r1[j];
            }
            else if(i==1){
                grid[i][j]=r2[j];
            }
            else{
                grid[i][j]=0;
            }
        }
    }
}

//Below Method Will Check And Make String To Non-Spaced Array.
void noSpace(char userInput[], int* arrayWOSpace){
    int counter = 0;
    for(int i=0; i<strlen(userInput); i++){
        if(!(userInput[i]==' '|| userInput[i]=='\t')){
            //printf("%c", userInput[i]);
            if(((userInput[i]-'0')<0||(userInput[i]-'0')>9)){
                //If invalid characters found, will exit loop and program.
                printf("Invalid: Contains Special Characters Or Aplhabets or Negative Number.\n");
                exit(0);
            }
            arrayWOSpace[counter] = userInput[i]-'0';
            counter++;
        }
    }
    //Checking the range. If total is less than 9, it will end loop.
    if(counter!=9){
        printf("Invalid: Required 9 Valid Digits. \n");
        exit(0);
    }
}

//This Method Is Work As An Verifier and Printer If Things Are Good.
void gridVerifier(int gridArray[][9],int i,int j) {

    if(verifyGridComplete(gridArray)) {
        //This will print Ful Grid.
        printGridFull(gridArray);
        exit(0);
    }
    

    if(gridArray[i][j]) {
        if(j<8)
            gridVerifier(gridArray,i,j+1);
        else
            gridVerifier(gridArray,i+1,0);
    }
    else {
        for(int n=1;n<=9;n++) {
            if(isSafe(gridArray,i,j,n)) {
                gridArray[i][j] = n;
                if(j<8)
                    gridVerifier(gridArray,i,j+1);
                else
                    gridVerifier(gridArray,i+1,0);
                gridArray[i][j] = 0;
            }
        }
    }
}
//This Is Like Sub Verifier To Upper Method.
int verifyGridComplete(int gridArray[][9]) {
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(gridArray[i][j] == 0)
                return 0;
    return 1;
}

//Below Method To Check the Safety Of Integer In Box, Horizontal Axis, Vertical Axis,
int isSafe(int gridArray[9][9],int curI,int curJ,int n) {
    int a = curI/3; a *= 3;
    int b = curJ/3; b *= 3;

    for(int i=a;i<a+3;i++) {
        for(int j=b;j<b+3;j++) {
            if(i==curI && j==curJ)
                continue;
            if(gridArray[i][j] == n)
                return 0;
        }
    }

    for(int i=0;i<9;i++) {
        if(i==curI)
            continue;
        if(gridArray[i][curJ] == n)
            return 0;
    }


    for(int j=0;j<9;j++) {
        if(j==curJ)
            continue;
        if(gridArray[curI][j] == n)
            return 0;
    }

    return 1;
}

//Below Method To Verify And irint Full Grid.
void printGridFull(int gridArray[][9]) {
    if(validateSudoku(gridArray)){
        //Pritining If Everything is Valid.
        for(int i=0;i<9;i++) {
            for(int j=0;j<9;j++) {
                printf("\t%d",gridArray[i][j]);
            }
            printf("\n");
        }
    }
    else{
        //Still Printing but Invalid.
        for(int i=0;i<9;i++) {
            for(int j=0;j<9;j++) {
                printf("\t%d",gridArray[i][j]);
            }
            printf("\n");
        }
        //Possible Reasons.
        printf("\n\nNo Valid Solution Found. Sorry :( \nReasons:\n1) Invalid Row1 & or Row2 Inputs.\n2) Input Did Not Followed Game Rules.\n\n");
    }
}
