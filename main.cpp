//Syed M Saad Bukhari
//23I-2001
//CY-B

#include<iostream>
#include<cmath>
#include<fstream>
#include<cstring>
#include<chrono>

using namespace std;
using namespace std::chrono;

void readgridandwords(char **grid, char **words, const char *filename, int size, int noofwords);
void displaygrid(char **grid, int size);
void displaywords(char **words, int noofwords);
float calculateavglength(char **words, int noofwords);
void displaycolors(char **colorgrid, int size, char **grid);
int forwardhorizontal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int backwardhorizontal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int forwardvertical(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int backwardvertical(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int forwardleftdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int backwardleftdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int forwardrightdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
int backwardrightdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size);
void displaytelegrid(char **telegrid, int size);
void displaywordgrid(char **telegrid, char **grid, int size);
int telescatter(char **telegrid, int size);

int main(int argc, char *argv[])      //For file name
{
    int charcount = 0;      //To count the number of characters in the file
    int noofwords = 1;      //To count the number of words in the file
    int size = 0;           //To store the size of the grid
    char ch;                //To read the characters from the file
    char key;               //To control the puzzle
    char checkkey;          //To check if the key is valid from user
    float avg_length = 0;   //To store the average length of the words
    int wordloop = 0;       //To loop through the words
    int forwardhorizontalcount = 0; //To count the number of words found in forward horizontal direction
    int backwardhorizontalcount = 0; //To count the number of words found in backward horizontal direction
    int forwardverticalcount = 0; //To count the number of words found in forward vertical direction
    int backwardverticalcount = 0; //To count the number of words found in backward vertical direction
    int forwarddiagcount = 0; //To count the number of words found in forward diagonal direction
    int backwarddiagcount = 0; //To count the number of words found in backward diagonal direction


    if (argc < 2)
    {
        cout << "Please enter the file name." << endl;
        return 1;
    }

    const char *filename = argv[1];    //Used to pass file name as argument

    ifstream file(filename);
    if (!file)
    {
        cout << "File not found." << endl;
        return -1;
    }

    // Counting the number of characters in the file
    while (file.get(ch) && ch != '\n') // Read until newline character
    {
        if (isalpha(ch)) // Check if ch is an alphabet character
        {
            charcount++;
        }
    }

    // Counting the number of words in the file
    while (file.get(ch))
    {
        if(ch == '\n')      // To skip if any new line character is found
        {
            continue;
        }

        if(ch == ',')        //Only counts the words separated by commas
        {
            noofwords++;
        }
    }

    file.close();

    size = sqrt(charcount) ;

    // Creating a 2D array for the grid and words
    char **grid = new char * [size];
    for (int i = 0; i < size; i++)
    {
        *(grid+i) = new char[size];
    }

    char **words = new char *[noofwords];
    for (int i = 0; i < noofwords; i++)
    {
        *(words+i) = new char[30];  // Max 30 characters in a word
    }

    //Telegrid to show the remainning letters in grid at end using DMA
    char **telegrid = new char * [size];
    for (int i = 0; i < size; i++)
    {
        *(telegrid+i) = new char[size];
    }

    //Grid to indicate colors
    char **colorgrid = new char * [size];
    for (int i = 0; i < size; i++)
    {
        *(colorgrid+i) = new char[size];
    }


    cout<<"\nWelcome To Teleword Puzzle Solver\n";
    cout<<"-----------------------------------\n";
    cout<<"\nCurrent File: "<<filename<<"\n";
    cout<<"-----------------------------------\n";
    cout<< "Grid Size: " << size << endl;
    cout<< "Number of Words: " << noofwords << endl;
    cout<<"\nYou have to choose a key to control the puzzle.";

    //Selecting  A key to control the game
    cout << "Enter a key to control the game: ";
    cin >> key;



    readgridandwords(grid, words, filename, size, noofwords);       // Function to read the grid and words

    //Filling the telegrid with the letters of the grid
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(*(telegrid+i)+j) = *(*(grid+i)+j);
        }
    }

    //Filling color grid with numbers to differentiate colors
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(*(colorgrid+i)+j) = '1';
        }
    }

    displaygrid(grid, size);// Function to display the grid and words
    displaywords(words, noofwords);  // Function to display words

    cout<<endl<<endl;
    cin>>checkkey;
    //Check if the key is valid
    while(checkkey != key)
    {
        cout << "Invalid Key. Please enter correct key.";
        cin >> checkkey;
    }


    //For total time
    high_resolution_clock::time_point start_time = high_resolution_clock::now();

    while(checkkey == key || checkkey == '\n')
    {

        displaycolors(colorgrid, size, grid); // Function to display colors in grid

        //TO check number of words
        if(wordloop > noofwords-1)
        {
            //total time calculation
            high_resolution_clock::time_point end_time = high_resolution_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(end_time - start_time);
            double time_taken = time_span.count();

            cout << "\nTotal time taken to solve the puzzle: " << time_taken << " seconds" << endl;
            break;
        }


        cout<<"\nEnter " << key << " to continue or any other key to exit: ";
        cin>>checkkey;

        cout<<"\nCurrent Word:"<<endl;
        cout<<wordloop+1<<". "<<*(words+wordloop)<<endl;

        high_resolution_clock::time_point start_time1 = high_resolution_clock::now();
        //Function call to check for word match with grid in forward horizontal direction
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = forwardhorizontal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 15;         //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        forwardhorizontalcount++; //To count the number of words found in forward horizontal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time1 = high_resolution_clock::now();
                        duration<double, std::milli> time_span1 = end_time1 - start_time1;
                        double time_taken1 = time_span1.count();

                        cout << "Time taken to solve the letter: " << time_taken1 << " milliseconds" << endl;

                        cout<<"\nThe word is found in forward horizontal direction\n";
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time2 = high_resolution_clock::now();
        //Function to call to check for word match with grid in backward horizontal direction
        for (int i = 0; i < size; i++)
        {
            for (int j = size-1; j >= 0; j--)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = backwardhorizontal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 0;          //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        backwardhorizontalcount++; //To count the number of words found in backward horizontal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time2 = high_resolution_clock::now();
                        duration<double, std::milli> time_span2 = end_time2 - start_time2;
                        double time_taken2 = time_span2.count();

                        cout << "Time taken to solve the letter: " << time_taken2 << " milliseconds" << endl;

                        cout<<"\nThe word is found in backward horizontal direction\n";     
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time3 = high_resolution_clock::now();
        //Function to call to check for word match with grid in forward vertical direction
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = forwardvertical(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 15;         //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        forwardverticalcount++; //To count the number of words found in forward vertical direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word
                        high_resolution_clock::time_point end_time3 = high_resolution_clock::now();
                        duration<double, std::milli> time_span3 = end_time3 - start_time3;
                        double time_taken3 = time_span3.count();

                        cout << "Time taken to solve the letter: " << time_taken3 << " milliseconds" << endl;

                        cout<<"\nThe word is found in forward vertical direction\n";

                    }

                }
            }
        }

        high_resolution_clock::time_point start_time4 = high_resolution_clock::now();
        //Function to call to check for word match with grid in backward vertical direction
        for (int i = size-1; i >= 0; i--)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = backwardvertical(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 15;         //To break the loop
                        i = 0;          //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        backwardverticalcount++; //To count the number of words found in backward vertical direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time4 = high_resolution_clock::now();
                        duration<double, std::milli> time_span4 = end_time4 - start_time4;
                        double time_taken4 = time_span4.count();

                        cout << "Time taken to solve the letter: " << time_taken4 << " milliseconds" << endl;

                        cout<<"\nThe word is found in backward vertical direction\n";
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time5 = high_resolution_clock::now();
        //Function to call to check for word match with grid in forward left diagonal direction
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = forwardleftdiagonal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 15;         //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        forwarddiagcount++; //To count the number of words found in forward diagonal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time5 = high_resolution_clock::now();
                        duration<double, std::milli> time_span5 = end_time5 - start_time5;
                        double time_taken5 = time_span5.count();

                        cout << "Time taken to solve the letter: " << time_taken5 << " milliseconds" << endl;

                        cout<<"\nThe word is found in forward left diagonal direction\n";
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time6 = high_resolution_clock::now();
        //Function to call to check for word match with grid in backward left diagonal direction
        for (int i = 0; i < size; i++)
        {
            for (int j = size-1; j >= 0; j--)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = backwardleftdiagonal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 0;          //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        backwarddiagcount++; //To count the number of words found in backward diagonal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time6 = high_resolution_clock::now();
                        duration<double, std::milli> time_span6 = end_time6 - start_time6;
                        double time_taken6 = time_span6.count();

                        cout << "Time taken to solve the letter: " << time_taken6 << " milliseconds" << endl;

                        cout<<"\nThe word is found in backward left diagonal direction\n";
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time7 = high_resolution_clock::now();
        //Function to call to check for word match with grid in forward right diagonal direction
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = forwardrightdiagonal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 15;         //To break the loop
                        i = 15;         //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        forwarddiagcount++; //To count the number of words found in forward diagonal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time7 = high_resolution_clock::now();
                        duration<double, std::milli> time_span7 = end_time7 - start_time7;
                        double time_taken7 = time_span7.count();

                        cout << "Time taken to solve the letter: " << time_taken7 << " milliseconds" << endl;

                        cout<<"\nThe word is found in forward right diagonal direction\n";
                    }

                }
            }
        }

        high_resolution_clock::time_point start_time8 = high_resolution_clock::now();
        //Function to call to check for word match with grid in backward right diagonal direction
        for (int i = size-1; i >= 0; i--)
        {
            for (int j = size-1; j >= 0; j--)
            {
                if (*(*(grid + i) + j) == *(*(words + wordloop) +0))         //To check if the first character of the word matches with the grid
                {
                    int flag = backwardrightdiagonal(i, j, wordloop, words, grid, telegrid, colorgrid, size);
                    if (flag == 1)
                    {
                        j = 0;          //To break the loop
                        i = 0;          //To break the loop
                        flag = 0;       //To reset the flag for further loop
                        backwarddiagcount++; //To count the number of words found in backward diagonal direction
                        cout<<"\nThe length of the word is "<<strlen(*(words + wordloop))<<endl; //To display the length of the word

                        high_resolution_clock::time_point end_time8 = high_resolution_clock::now();
                        duration<double, std::milli> time_span8 = end_time8 - start_time8;
                        double time_taken8 = time_span8.count();

                        cout << "Time taken to solve the letter: " << time_taken8 << " milliseconds" << endl;

                        cout<<"\nThe word is found in backward right diagonal direction\n";
                    }

                }
            }
        }

        wordloop++;
        cout<<endl;

    }

    cout<<"\nTeleword Grid:";
    displaytelegrid(telegrid, size); // Function to display the telegrid

    cout<<"\nWords found Grid:";
    displaywordgrid(telegrid,grid, size); // Function to display the letters which formed the words


    avg_length  = calculateavglength(words, noofwords); // Function to calculate the average length of the words

    cout<<"Teleword Puzzle Solved\n";
    cout<<"\nTeleword = ";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(*(*(telegrid+i)+j) != ' ')
            {
                cout << *(*(telegrid + i) + j);
            }
        }

    }
    cout<<endl;

    cout<<"\nStatistics: \n";
    cout << "Total number of words: " << noofwords << endl;
    cout<<"Total number of letters: "<<charcount<<endl;
    cout<<"Grid Size: "<<size<<endl;

    cout << "\nAverage length of the words: " << avg_length << endl;
    cout<<"\nTeleword Scatter: "<< telescatter(telegrid, size); // Function to display the telegrid;

    cout << "\nWord Distribution: ";
    cout <<"\nHorizontal " << forwardhorizontalcount + backwardhorizontalcount << " (" << forwardhorizontalcount<< "," << backwardhorizontalcount << ")" << endl;
    cout << "Vertical " << forwardverticalcount + backwardverticalcount << " (" << forwardverticalcount << "," << backwardverticalcount << ")" << endl;
    cout << "Diagonal " << forwarddiagcount + backwarddiagcount << " (" << forwarddiagcount << "," << backwarddiagcount << ")" << endl;

    cout<<"\n\nThank you for playing Teleword Puzzle. Goodbye!";





    // Deallocating the memory
    for (int i = 0; i < size; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
    grid= NULL;

    for (int i = 0; i < noofwords; i++)
    {
        delete[] words[i];
    }
    delete[] words;
    words = NULL;

    for (int i = 0; i < size; i++)
    {
        delete[] telegrid[i];
    }
    delete[] telegrid;
    telegrid = NULL;

    for (int i = 0; i < size; i++)
    {
        delete[] colorgrid[i];
    }
    delete[] colorgrid;
    colorgrid = NULL;

    


    return 0;

}

// Function to read the grid and words
void readgridandwords(char **grid, char **words, const char *filename, int size, int noofwords)
{
    //Reading the grid
    ifstream openfile(filename);
    char ch;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            openfile.get(ch);

            if (ch == '\n')      //to break the loop when it reaches the end of the grid
            {
                break;
            }

            if(isalpha(ch))      //To check if the character is an alphabet
            {
                *(*(grid+i)+j) = ch;
            }
            else
            {
                j--;        //To skip the non-alphabet characters
            }

        }
    }

    // Reading the words
    for (int i = 0; i < noofwords; i++)
    {
        int j = 0;
        while (!isalpha(openfile.peek()) && !openfile.eof())
        {
            openfile.ignore();
        }

        while (!openfile.eof()) // Continue until the end of the file
        {
            char ch = openfile.get();
            if (ch == ',' || ch == '\n') // If a comma or newline is encountered, end the word
            {
                break;
            }

            if (isalpha(ch)) // If ch is an alphabet character
            {
                *(*(words+i)+j) = ch;
                j++;
            }
        }
        *(*(words+i)+j) = '\0'; // Terminate the string with null character
    }

    openfile.close();
}

// Function to display the grid and words
void displaygrid(char **grid, int size)
{
    cout<<endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << *(*(grid+i)+j) << " ";
        }
        cout << endl;
    }

}

//Function to display words
void displaywords(char **words, int noofwords)
{
    cout << endl;

    for (int i = 0; i < noofwords; i++)
    {
        //For dot at the end of the last word
        if(i != noofwords-1)
        {
            cout << *(words+i)<<", ";
        }
        else
            cout << *(words+i)<<". ";

    }

}

//Function to calculate the average length of the words
float calculateavglength(char **words, int noofwords)
{
    int sum = 0;
    for (int i = 0; i < noofwords; i++) {
        sum += strlen(*(words + i));
    }

    return (float) sum / noofwords;
}

//Function to display colors inn grid
void displaycolors(char **colorgrid, int size, char **grid)
{
    cout<<endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            //Only display color green only if has value 2 in color grid
            if(*(*(colorgrid+i)+j) == '2')
            {
                cout << "\033[1;32m" << *(*(grid+i)+j) << "\033[0m" << " ";
            }
            else
            {
                cout << *(*(grid+i)+j) << " ";
            }
        }
        cout << endl;

    }
    //Reset the color grid to normal
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(*(colorgrid+i)+j) = '1';
        }
    }

}


//Function to check for word match with grid in forward horizontal direction
int forwardhorizontal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (y < size && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {

                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + x) + (y - m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + x) + (y - m)) = ' '; // Set word to blank in telegrid
                    flag = 1; // Set the flag to indicate that the word is found
                }
                y=15; //To break the loop
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            y++;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            y=15; //To break the loop
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in backward horizontal direction
int backwardhorizontal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (y >= 0 && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + x) + (y + m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + x) + (y + m)) = ' '; // Set word to blank in telegrid
                    flag = 1; // Set the flag to indicate that the word is found
                }
                y=-1; //To break the loop
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            y--;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            y=-1; //To break the loop
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in forward vertical direction
int forwardvertical(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x < size && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x-m)) + y) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x-m)) + y) = ' '; // Set word to blank in telegrid
                }
                flag = 1; // Set the flag to indicate that the word is found
                y=15; //To break the loop
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x++;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            y=15; //To break the loop
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}


//Function to check for word match with grid in backward vertical direction
int backwardvertical(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x >= 0 && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x+m)) + y) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x+m)) + y) = ' '; // Set word to blank in telegrid
                }
                y=15;
                flag = 1; // Set the flag to indicate that the word is found
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x--;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            y=15;
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in forward left diagonal direction
int forwardleftdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x < size && y >= 0 && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x-m)) + (y+m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x-m)) + (y+m)) = ' '; // Set word to blank in telegrid
                }
                flag = 1; // Set the flag to indicate that the word is found
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x++;
            y--;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in backward left diagonal direction
int backwardleftdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x >= 0 && y < size && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x+m)) + (y-m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x+m)) + (y-m)) = ' '; // Set word to blank in telegrid
                }
                flag = 1; // Set the flag to indicate that the word is found
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x--;
            y++;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in forward right diagonal direction
int forwardrightdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x < size && y < size && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x-m)) + (y-m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x-m)) + (y-m)) = ' '; // Set word to blank in telegrid
                }
                flag = 1; // Set the flag to indicate that the word is found
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x++;
            y++;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to check for word match with grid in backward right diagonal direction
int backwardrightdiagonal(int i, int j, int k, char **words, char **grid, char **telegrid, char **colorgrid, int size)
{
    int x = i;
    int y = j;
    int flag = 0; // Flag to indicate if the word is found
    int l = 0; // Index to track the position in the word

    int wordLength = strlen(*(words + k)); // Length of the word

    // Iterate over the characters of the word
    while (x >= 0 && y >= 0 && l < wordLength)
    {
        // Check if the character in the grid matches the character in the word
        if (*(*(grid + x) + y) == *(*(words + k) + l))
        {
            // If the last character of the word is found
            if (l == wordLength - 1)
            {
                // Mark the word's characters in the colorgrid and telegrid
                for (int m = 0; m < wordLength; m++)
                {
                    *(*(colorgrid + (x+m)) + (y+m)) = '2'; // Set the color of the word to green
                    *(*(telegrid + (x+m)) + (y+m)) = ' '; // Set word to blank in telegrid
                }
                flag = 1; // Set the flag to indicate that the word is found
                break; // Exit the loop since the word is found
            }
            // Move to the next character in the grid and the word
            x--;
            y--;
            l++;
        }
        else
        {
            // Reset the flag and break the loop if the characters don't match
            flag = 0;
            break;
        }
    }

    return flag; // Return the flag indicating whether the word is found or not
}

//Function to display the telegrid
void displaytelegrid(char **telegrid, int size)
{
    cout<<endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << *(*(telegrid+i)+j) << " ";
        }
        cout << endl;
    }
}

//Function to display the letters which formed the words
void displaywordgrid(char **telegrid, char **grid, int size)
{
    cout<<endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(*(*(telegrid+i)+j) == ' ')
            {
                cout << *(*(grid+i)+j) << " ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

//function for telword scatter to show number of rows touched by the teleword
int telescatter(char **telegrid, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        for (int j = 0; j < size; j++)
        {
            if(*(*(telegrid+i)+j) != ' ')
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            count++;
        }
    }
    return count;
}

