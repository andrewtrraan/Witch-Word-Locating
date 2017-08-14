#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <windows.h>
/*
Boggle
Andrew Tran
Description: a recursive word search program that finds the matching letter from a word in a grid then
recurivsely calls a function ot keep matching the rest of the letters in the word
then outputs if the word is found or not
Mr. Trink
Date Submitted: 14/05/2017*/

using namespace std;
//parameters: string, array, column, row, height, width

//rows are the x
//columns are y
bool theRecruse(string theEntered, char **theArray, int row, int column, int curIndex, bool **theBools, int width, int height )
{
    //return true if the curreny index is equal to the length of the word
    if(curIndex==theEntered.length())
    {
        return true;
    }

    //reutnr false if the the letter found exceeds the row side or the column size
    if (row<0 ||row>width-1||column<0||column>height-1)
    {
        return false;
    }

    //reutnr false if the letter at the current index does not amtch the letter that is being searched
    if(theArray[row][column]!= theEntered[curIndex])
    {
        return false;
    }

    //if the letter at the current index matches the ltter being searched mark it with a boolean to know htat it has been visted
    if(theArray[row][column]==theEntered[curIndex])
    {
        theEntered[curIndex]=theBools[row][column];
    }

    //reutrn false if the letter has already been visted
    if(theArray[row][column]=false)
    {
        return false;
    }


    //search for the letter with recursion calls
    //up, down, left, right, right up, right down, left up left down
    bool isFound =
         theRecruse(theEntered,theArray,  row+1,  column, curIndex+1, theBools, width, height)||theRecruse(theEntered,theArray,  row-1,  column, curIndex+1, theBools,width, height)
        ||theRecruse(theEntered,theArray,  row,  column+1, curIndex+1, theBools, width, height)||theRecruse(theEntered,theArray,  row,  column-1, curIndex+1, theBools,width,height)
        ||theRecruse(theEntered,theArray,  row+1,  column-1, curIndex+1, theBools, width, height)||theRecruse(theEntered,theArray,  row+1,  column+1, curIndex+1, theBools, width, height)
        ||theRecruse(theEntered,theArray,  row-1,  column-1, curIndex+1, theBools,width, height)||theRecruse(theEntered,theArray,  row-1,  column+1, curIndex+1, theBools,width,height);
    return isFound;

}


bool wordSearch(string theEntered, char **theArray, bool **theBools, int width, int height)
{
    //boolean used to indicate if word has been found
    bool wordFound=false;

    //for loops that search for the first letter of the wanted word
    for(int row =0; row<width; row++)
    {
        for(int column =0; column<height; column++)
        {
            //if the first letter is found call the recursion function
            if(theEntered[0] == theArray[row][column])
            {
                wordFound=theRecruse(theEntered,theArray,  row,  column, 0, theBools, width, height);
                //if the word is found returnt true
                if (wordFound)
                {
                    return true;
                }

            }

        }
    }

    return false;
}



int main()
{

    //opening message

    //output text to be grey colour
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout<<"My name is Annagramma Hawkin and I am a witch that is in need of some help. I'd really love generate some new spells without doing any work!"
        <<" I recently bought this boggle generator thing that generates random words. You can help me by specifying the row and column grid dimensions and choosing a unique word."<<endl;

    cout<<"\nSo are you willing to help your favourite witch out? (Y or N): ";

    //string to get user's answer
    string willHelp;

    //boolean used to check if willing to help
    bool yesHelp =false;

    //boolean to check if the row input is valid
    bool validRow =false;

    //boolean to check if column output is vaid
    bool validCol = false;

    //makes sure new letters are genrated with each run
    srand(time(NULL));
    //stores the word that tue user will enter
    string userEntered;


    //set the intial row size to 0
    int rowSize =0;

    //set the intial column size to 0
    int columnSize =0;

    //row buffer that will be converted to the row size
    string rowBuffer;

    //column buffer taht will be converted to the column size
    string columnBuffer;

    //do while loop that makes sure the user enters either y or no and keeps looping until they do
    do
    {

        getline(cin, willHelp);

        //transform the entered word into all capitals
        transform(willHelp.begin(), willHelp.end(),willHelp.begin(), ::toupper);

        if(willHelp != "Y"&&"N")
        {
            cout<<"That is not a valid answer. Please give the witch a serious answer. :( Will you please helpe me? (Y or N): ";
            yesHelp =false;
        }
        else if(willHelp == "Y"||"N")
        {
            yesHelp =true;
        }
    }
    while(yesHelp !=true);

    //if the user enters y or yes to help
    if(willHelp =="Y")
    {


        //output text to be mustard colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

        //ask the user for row size
        cout<<"\nHow many rows would you like the grid to have?: ";

        //keeps looping until a valid row size is entered
        do
        {
            //convert and set size
            getline(cin, rowBuffer);
            rowSize =atoi(rowBuffer.c_str());

            //if input is greater than 0 set boolean to true
            if(rowSize>0)
            {
                validRow =true;

            }

            //any other input set the boolean to false and output instruction message
            else
            {
                validRow=false;
                cout<<"Please enter a valid row size which is any number greater than 0: ";
            }
        }
        while(validRow!=true);

        //output text to be mustard colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        //ask the user for column size
        cout<<"\nHow many columns would you like the grid to have?: ";

        //keeps looping until a valid column size is entered
        do
        {
            //convert and set size
            getline(cin, columnBuffer);
            columnSize = atoi(columnBuffer.c_str());

            //if input is greater than 0 set the boolean to true
            if(columnSize>0)
            {
                validCol=true;
            }

            //any other input set the boolean to false and output instruction message
            else
            {
                validCol=false;
                cout<<"Please enter a valid column size which is any number greater than 0: ";
            }

        }
        while(validCol!=true);

        //generate two dimensonal char array for the leters
        char **arrayLetters;
        arrayLetters= new char*[rowSize];
        for(int row =0; row<rowSize; row++)
        {
            arrayLetters[row] = new char[columnSize];
        }


        //generate two dimensonal boolean array
        bool **booleanArray;
        booleanArray= new bool*[rowSize];
        for(int row =0; row<rowSize; row++)
        {
            booleanArray[row] = new bool[columnSize];
        }

        //two dimensonal array that will hold the orignally and untouched genrated array
        char **ogArray;
        ogArray= new char*[rowSize];
        for(int row =0; row<rowSize; row++)
        {
            ogArray[row] = new char[columnSize];
        }

        //two dimensonal array that will hold the new grid
        char **newArray;
        newArray= new char*[rowSize];
        for(int row =0; row<rowSize; row++)
        {
            newArray[row] = new char[columnSize];
        }
        // bool booleanArray[5][5];

        //string that will store user's answer to seaarch for another word
        string searchAnother;

        //variable to store randomly genraeted ints
        int randASCII=0;

        //bool to make sure correct grid outputs after wrong guess
        bool outputNewGrid = false;

        cout<<endl;

        //for loop that ouputs the grid with the user's size specifications
        for(int row =0; row<rowSize; row++)
        {
            for(int column =0; column<columnSize; column++)
            {
                //65 starting value and the 25+ is adding 25 to 65 which is total range of 90 (A to Z in ASCII)
                randASCII=rand()%25+65;

                //fill in the letter array with random letters
                arrayLetters[row][column] = (char)randASCII;

                //fill a copy of the array with the same letters which will be used to reset the guessing array after each guess
                ogArray[row][column]=(char)randASCII;

                //output text to be red colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                //output the filled array
                cout<< arrayLetters[row][column]<< " ";

                //set all the booleans in the boolean array to false intially
                booleanArray[row][column]=false;
            }
            cout<<endl;
        }
        cout<<endl;


        do
        {

            //set the bool that a new grid has been genreated to false
            bool newGrid =false;

            //output text to be pink colour
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            //ask the user to enter a word
            cout<<"\nHurry up and find a new word so I can create a new spell!: ";
            getline(cin, userEntered);


            //transform the entered word into all capitals
            transform(userEntered.begin(), userEntered.end(),userEntered.begin(), ::toupper);

            //if the user wants to generate a new grid
            if((newGrid ==false)&&(userEntered =="NEW GRID"))
            {

                //set the boolean that a new grid has been gernated to true
                newGrid=true;

                //set the boolean to true to output the new grid
                outputNewGrid =true;

                //output text to be yellow colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                cout<<"\nHere is the new grid. Find a word!\n"<<endl;

                //for loop that ouputs the new grid
                for(int row =0; row<rowSize; row++)
                {

                    for(int column =0; column<columnSize; column++)
                    {
                        //65 starting value and the 25+ is adding 25 to 65 which is total range of 90 (A to Z in ASCII)
                        randASCII=rand()%25+65;

                        //fill in the letter array with random letters
                        newArray[row][column] = (char)randASCII;

                        //set the array values to the newly generated values
                        arrayLetters[row][column]= newArray[row][column];

                        //output the array
                        cout<< arrayLetters[row][column]<< " ";

                    }
                    cout<<endl;
                }
                //output text to be grey colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                //ask the user if they want to search for a word in the new grid
                cout<<"\nNow that the new grid has been crafted, would you to search for a word? (Y or N): ";
            }

            //if a new grid was not generated and the return statement was true
            else if((newGrid ==false)&&wordSearch(userEntered, arrayLetters, booleanArray, rowSize, columnSize))
            {
                //output text to be yellow colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout<<"\nWow, you're good at this! You found a word!"<<endl;

                for(int row =0; row<rowSize; row++)
                {
                    for(int column =0; column<columnSize; column++)
                    {
                        //set the current array back to its orignal values
                        arrayLetters[row][column] =(char) ogArray[row][column];

                    }
                }
                //output text to be grey colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout<<"\nWould you like to continue searching for words? (Y or N): ";
            }

            else
            {
                //output text to be red
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout<<"\nYou're embarrassing yourself... Why haven't you found a word!\n"<<endl;

                //if a new grid was not generated
                if(outputNewGrid ==false)
                {

                    for(int row =0; row<rowSize; row++)
                    {

                        for(int column =0; column<columnSize; column++)
                        {

                            //reset the array to its orignally generated vlaues
                            arrayLetters[row][column] = (char)ogArray[row][column];

                            //output the array
                            cout<<arrayLetters[row][column]<< " ";

                        }
                        cout<<endl;
                    }
                }

                //if a new array was genenrated
                else if(outputNewGrid ==true)
                {
                    //set the boolean for a new array being generated back to false
                    outputNewGrid =false;
                    for(int row =0; row<rowSize; row++)
                    {

                        for(int column =0; column<columnSize; column++)
                        {


                            //set the array to the newly generated values
                            arrayLetters[row][column] =(char) newArray[row][column];

                            //output the array
                            cout<<arrayLetters[row][column]<< " ";

                        }
                        cout<<endl;
                    }

                }
                //output text to be grey colour
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout<<"\nWould you like to search for another word? It'd really help me come up with new spells! (Y or N): ";
            }

            //set the new grid generated boolean back to galse
            newGrid=false;

            //get the uer's anwer
            getline(cin, searchAnother);
        }
        //keep loop until the user does not enter y
        while(searchAnother=="y");


        //     arrayLetters= new char*[rowSize];
        for(int row =0; row<rowSize; row++)
        {
            delete arrayLetters[row];
            delete ogArray[row];
            delete booleanArray[row];
            delete newArray[row];
        }

    }
    else
    {
        cout<<"Darn! It was worth a try, have a nice day."<<endl;
    }
    return 0;
}
