#include<stdio.h>
#include<stdlib.h>
#include<conio.h> // For kbhit and getch functions
#include<stdlib.h> // For rand function

// Global variables to store game parameters

int width = 20;            // Width of the game board
int height = 20;           // Height of the game board
int x, y;                   // Coordinates of the snake's head
int fruitx, fruity;         // Coordinates of the fruit
int score;                  // Player's score
int gameover;               // Flag indicating whether the game is over
int tailx[100], taily[100]; // Arrays to store coordinates of the snake's tail
int countTail = 1;          // Initial length of the snake
int flag;                   // Flag to store user input for direction (1: Left, 2: Down, 3: Up, 4: Right)


void setup(){
    gameover = 0;
    x = width / 2;
    y = height / 2;
    score = 0;

    countTail = 1;
    flag = -1;
    // Generate random coordinates for the fruit
    do{
        fruitx = rand() % 20;
    } while(fruitx == 0);

    do{
        fruity = rand() % 20;
    } while(fruity == 0);
}

void draw(){
    system("cls"); // Clear the console screen
    printf("\n\n\n\n");
    // Draw the game board
    for(int i = 0; i <= height; i++){
        for(int j = 0; j <= width; j++){
            if(i == 0 || i == height || j == 0 || j == width){
                printf("* "); // Draw the border
            }
            else{
                if(i == y && j == x){
                    printf("0 "); // Draw the snake's head
                }
                else if(j == fruitx && i == fruity){
                    printf("F "); // Draw the fruit
                }
                else{
                    int ch = 0;
                    for(int k = 0; k < countTail; k++){
                        if(j == tailx[k] && i == taily[k]){
                            printf("o "); // Draw the snake's tail
                            ch = 1;
                            break;
                        }
                    }
                    if(ch == 0){
                        printf("  "); // Empty space
                    }
                }
            }
        }
        printf("\n");
    }
}

void input(){
    if(kbhit()){ // Check if a key has been pressed
        switch(getch()){ // Get the pressed key
            case 'a': flag = 1; break; // Left
            case 's': flag = 2; break; // Down
            case 'w': flag = 3; break; // Up
            case 'd': flag = 4; break; // Right
            case 'x': gameover = 1; break; // Exit
        }
    }
}

void makelogic(){
    // Update the position of the snake based on user input
    switch(flag){
        case 1: x--; break; // Left
        case 2: y++; break; // Down
        case 3: y--; break; // Up
        case 4: x++; break; // Right
        default: break;
    }

    // Check for collision with the walls
    if(x < 0 || x > width || y < 0 || y > height){
        gameover = 1;
    }

    // Check for collision with the snake's own tail
    for(int i = 1; i < countTail; i++){
        if(x == tailx[i] && y == taily[i]){
            gameover = 1;
        }
    }

    // Check if the snake has eaten the fruit
    if(x == fruitx && y == fruity){
        // Generate new random coordinates for the fruit
        label1: fruitx = rand() % 20;
        if(fruitx == 0) goto label1;

        label2: fruity = rand() % 20;
        if(fruity == 0) goto label2;

        score = score + 10;
        countTail++;
    }

    // Update the position of the snake's tail
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;

    tailx[0] = x;
    taily[0] = y;
/*This code helps us to store of all the x and y cordinates of snake head and body
    Whenever snake eats new fruit counter in for loop will increase thereby accomodating one more point , if fruit is not eaten but 
    movement has happened in this case code will only change add new point ans shift other points without adding extra point int it */
    
    for(int i = 1; i < countTail; i++){  
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
}

int main(){
        char ch = 'y';
    do{
        setup();
        while(!gameover){
            draw();
            input();
            makelogic();

            // Add a delay for visualizing the movement (not recommended for real-time applications)
            for(int i = 0; i < 1000; i++){
                for(int j = 0; j < 40000; j++){
                }
            }
        }
        printf("Your score is : %d \n ",score);
        // Ask the user if they want to play again
        printf("press y to continue n to exit :\n");
        scanf(" %c", &ch);
    } while(ch == 'y' || ch == 'Y');

    return 0;
}


