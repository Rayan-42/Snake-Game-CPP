#include <iostream>
#include <conio.h>   // For keyboard input (_kbhit, _getch)
#include <windows.h> // For screen clearing (system("cls")) and Sleep()
#include <vector>    // For storing snake segments
#include <cstdlib>   // For random number generation
#include <ctime>     // For seeding random number generator

using namespace std;

// Define directions : 
enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

// The food class:
class Food {
public:
    int x, y; // food position
    
    // creating a new food in a random place :
    void createNew(int maxX, int maxY) {
        x = rand() % maxX;
        y = rand() % maxY;
    }
};

// The snake class:
class Snake {
public:
    vector<pair<int, int>> body; // body parts
    Direction dir; //direction of movement
    
    Snake() {
        // starting position in the center
        body.push_back({10, 5});
        dir = STOP;
    }
    
    // change the direction of movement
    void changeDir(Direction newDir) {
        // opposite direction is not allowed (up to down ):
        if ((dir == UP && newDir != DOWN) ||
            (dir == DOWN && newDir != UP) ||
            (dir == LEFT && newDir != RIGHT) ||
            (dir == RIGHT && newDir != LEFT) ||
            (dir == STOP)) {
            dir = newDir;
        }
    }
    
    // the snake movement
    void move(int maxX, int maxY) {
        if (dir == STOP) return;
        
        // Calculate new head position
        pair<int, int> newHead = body[0];
        
        // Update position based on direction
        switch (dir) {
            case UP:    newHead.second--; break;
            case DOWN:  newHead.second++; break;
            case LEFT:  newHead.first--; break;
            case RIGHT: newHead.first++; break;
        }
        
        // Implement wrap-around (teleport through walls):
        if (newHead.first < 0) newHead.first = maxX - 1;
        if (newHead.first >= maxX) newHead.first = 0;
        if (newHead.second < 0) newHead.second = maxY - 1;
        if (newHead.second >= maxY) newHead.second = 0;
        
        // Add new head and remove tail
        body.insert(body.begin(), newHead);
        body.pop_back();
    }
    
    // Increase snake length when eating food
    void grow() {
        body.push_back(body.back());
    }
    
    // check if snake collided with itself
    bool checkCollision() {
        for (size_t i = 1; i < body.size(); i++) {
            if (body[0] == body[i]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    // Initialize random number generator
    srand(time(0));
    
    // Game configuration
    const int WIDTH = 20;
    const int HEIGHT = 10;
    int score = 0;
    bool gameOver = false;
    bool paused = false;
    
    // Create game objects
    Snake snake;
    Food food;
    food.createNew(WIDTH, HEIGHT);
    snake.changeDir(RIGHT); // Start moving right
    
    // Main game loop
    while (!gameOver) {
        system("cls"); // Clear screen
        
        // draw top border
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;
        
        // draw game grid
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                // draw left border
                if (x == 0) cout << "#";
                
                // draw snake head
                if (x == snake.body[0].first && y == snake.body[0].second) {
                    cout << "O";
                }
                // draw snake body or food
                else {
                    bool isBody = false;
                    // check if this position is snake body
                    for (size_t i = 1; i < snake.body.size(); i++) {
                        if (x == snake.body[i].first && y == snake.body[i].second) {
                            cout << "o";
                            isBody = true;
                            break;
                        }
                    }
                    
                    // draw food if no snake segment here
                    if (!isBody) {
                        if (x == food.x && y == food.y) cout << "F";
                        else cout << " ";
                    }
                }
                
                // draw right border
                if (x == WIDTH - 1) cout << "#";
            }
            cout << endl;
        }
        
        // draw bottom border
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;
        
        // Display game information
        cout << "Score: " << score << endl;
        cout << "Controls: W (Up), A (Left), S (Down), D (Right), P (Pause), X (Exit)" << endl;
        if (paused) cout << "GAME PAUSED - Press P to resume" << endl;
        
        // Handle keyboard input
        if (_kbhit()) {
            char key = tolower(_getch());
            switch (key) {
                case 'w':
                    snake.changeDir(UP);
                    break;
                case 's':
                    snake.changeDir(DOWN);
                    break;
                case 'a':
                    snake.changeDir(LEFT);
                    break;
                case 'd':
                    snake.changeDir(RIGHT);
                    break;
                case 'x':
                    gameOver = true;
                    break;
                case 'p': 
                    paused = !paused; // toggle pause state
                    // wait for pause key to be pressed again
                    while (paused) {
                        if (_kbhit() && tolower(_getch()) == 'p') {
                            paused = false;
                        }
                        Sleep(100);
                    }
                    break;
            }
        }
        
        // Game logic (only when not paused)
        if (!paused) {
            snake.move(WIDTH, HEIGHT);
            
            // check for collisions
            if (snake.checkCollision()) {
                gameOver = true;
            }
            
            // check if food was eaten
            if (snake.body[0].first == food.x && snake.body[0].second == food.y) {
                score += 10;
                snake.grow();
                food.createNew(WIDTH, HEIGHT);
            }
            
            Sleep(600); // Slow game speed (800ms between moves)
        }
    }
    
    // Game over screen
    cout << "Game Over! Final Score: " << score << endl;
    cout << "Press any key to exit...";
    _getch();
    
    return 0;
}