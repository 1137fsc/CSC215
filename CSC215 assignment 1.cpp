//Jonathan Anderson
// CSC215
// Assignment 1.2

// Okay for this assignment, its supposed to be a game or something like that, where the user needs to have atleast 3 seperate choices to make.
// the useres choice has to be displayed back to them.   things need to be overcommented and has to be more than a demo.
//
// What I want to do is an old magic trick david coppperfield did on TV when I was a little kid. After some googling, I found the trick. It was called
// the interactive trick. They displayed a grid or circle of icons, and gave the watcher a series of choices to make. and in the end, they guessed which
// icon you were on. Now this can get pretty complicated... so I will just give them 4 choices and then tell them I found them... if I do it the math way,
// it leads me into more code than I currently know in C++! I can figure out how to move up or down or left and right... but I cant figure out how to remove
// choices so that they always end up in one spot, despite their choice. 

#include <iostream>
#include <string>     // to use strings
#include <windows.h> //for the sleep

using namespace std;

int main() {
    // 3x3 Grid with places as locations. paris = 0,0 and perth = 3,3)
    string grid[3][3] = { {"Paris", "Tokyo", "Montreal"},
                          {"Rio", "Dallas", "Moscow"},
                          {"Beijing", "Madrid", "Perth"} };

    cout << " I will guess exactly where you are in 4 moves. You cannot hide from me! \n\n";
    cout << "Pick a location to start from in this grid:\n\n";

    // Display the grid with positions. This is going to be a for loop with a nested for loop. basically count up to 3 on i and j. then print each iteration of
    // of counting up until you hit the max of each, ending the for loops. this will display the grid from above. 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "[" << i << "," << j << "] " << grid[i][j] << "\t";
        }
        cout << endl;
    }

    // User selects starting position
    string place;
    cout << "\n Choose a starting point: ";
    cin >> place;

    // now I need to seach and return which one they entered
    // first I need to declare the variables to hold their position

    int row = -1, col = -1; 
    
    for (int i = 0; i < 3; i++) {       //for loop, when int i is zero and i is less than 3, incrememnt up by one
        for (int j = 0; j < 3; j++) {   // same for j
            if (grid[i][j] == place) {  // look at the grid, find where the value in place matches the coordinates of the grid
                row = i;                // set the value for row to the matching row coordinate
                col = j;                // set the value for col to the matching col coordinate
                cout << "You chose to start at " <<"[" <<i<<","<<j<<"]"<< grid[row][col] << "\n\n"; // tell the user what they chose with the corresponding coordinates
            }
        }
    }
   
    // now we start the game, they need to move up/dn, left or right, diagonal, and then adjacent. this will bring them back to the middle... 
    cout << "\n Now Make a choice: move up or down. Enter UP or DN and press enter" << endl;
    string move1;  // this will hold what they chose for this move **edit, this needs to be a string, not char

    cout << "UP or DN?\n";
    cin >> move1; // and they will enter a string value of UP or DN ... okay I just realized they can try to move up if theyre already at the top... 
                  // need to find a good way to handle that... for now we'll just nmake sure to limit it. but this is going to be an issue later
    

    if (move1 == "UP") row = max(0, row - 1); // if they selected up, limited by the max of the row or 0... cant go past 0, row-1
    else if (move1 == "DN") row = min(2, row + 1); //if they selected down, limited by the max of the grid, min 2, row +1
    cout << "Searching for you...\n";
    Sleep(900); // added the sleep so it seems more realistic

    cout << "You moved to:" << grid[row][col] <<"\n\n";

    cout << "\n Your next choice to escape is left or right? Enter L or R and press enter" << endl;
    string move2; //basically the same as above, except i am going to move columns

    cout << "L or R?\n\n"; // basically the same as above
    cin >> move2;

    if (move2 == "L") col = max(0, col - 1);
    else if (move2 == "R") col = min(2, col + 1);

    cout << "\nI will find you again...\n";
    Sleep(900);
    cout << "\n Too Easy \n You have snuck off to:" << grid[row][col] << "\n";
   
    cout << "\n Now you can move any direction... UP, DN, L or R.\n";
    string move3;

    cout << "\nUP, DN, L, or R?\n";
    cin >> move3;

    if (move3 == "UP") row = max(0, row - 1);
    else if (move3 == "DN") row = min(2, row + 1);
    else if (move3 == "L") col = max(0, col - 1);
    else if (move3 == "R") col = min(2, col + 1);
    cout << "\n You think you can get away from me??\n";
    Sleep(900);
    cout << "\nYou are now at:" << grid[row][col] << "\n";

    cout << "\nYou get to make one more move, adjacent to your current position... but I am onto you! \n";

    cout << "\nUP, DN, L, or R? \n";

    string move4;

    cin >> move4;

    if (move4 == "UP") row = max(0, row - 1);
    else if (move4 == "DN") row = min(2, row + 1);
    else if (move4 == "L") col = max(0, col - 1);
    else if (move4 == "R") col = min(2, col + 1);
    cout << "\nI found you!! I caught you in:" << grid[row][col] << "\n";



   return 0;
}
