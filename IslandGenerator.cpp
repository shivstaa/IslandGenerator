#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

bool moveExists(int** map, int width, int height, int x, int y, int* movement) {
    //boolean will return false or true depending on if there is a direction that works
    bool boolean = false;
    if (x + 1 >= width) { //hitting bound --> return false
        return false;
    }
    if (y + 1 >= height) { //hitting bound --> return false
        return false;
    }
    //checks for each direction; will set the array movement to 1 if so and boolean to true
    if ((map[y + 1][x] <= map[y][x]) && ((y + 1 >= 0) && (x >= 0)) && ((y + 1 < height) && (x < width))) {
        movement[0] = 1;
        boolean = true;
    }
    else {
        movement[0] = 0;
    }
    if ((map[y][x + 1] <= map[y][x]) && ((y >= 0) && (x + 1 >= 0)) && ((y < height) && (x + 1 < width))) {
        movement[1] = 1;
        boolean = true;
    }
    else {
        movement[1] = 0;
    }
    if ((map[y + 1][x + 1] <= map[y][x]) && ((y + 1 >= 0) && (x + 1 >= 0)) && ((y + 1 < height) && (x + 1 < width))) {
        movement[2] = 1;
        boolean = true;
    }
    else {
        movement[2] = 0;
    }
    if ((map[y + 1][x - 1] <= map[y][x]) && ((y + 1 >= 0) && (x - 1 >= 0)) && ((y + 1 < height) && (x - 1 < width))) {
        movement[3] = 1;
        boolean = true;
    }
    else {
        movement[3] = 0;
    }
    if ((map[y - 1][x] <= map[y][x]) && ((y - 1 >= 0) && (x >= 0)) && ((y - 1 < height) && (x < width))) {
        movement[4] = 1;
        boolean = true;
    }
    else {
        movement[4] = 0;
    }
    if ((map[y][x - 1] <= map[x][y]) && ((y >= 0) && (x - 1 >= 0)) && ((y < height) && (x - 1 < width))) {
        movement[5] = 1;
        boolean = true;
    }
    else {
        movement[5] = 0;
    }
    if ((map[y - 1][x - 1] <= map[x][y]) && ((y - 1 >= 0) && (x - 1 >= 0)) && ((y - 1 < height) && (x - 1 < width))) {
        movement[6] = 1;
        boolean = true;
    }
    else {
        movement[6] = 0;
    }
    if ((map[y - 1][x + 1] <= map[x][y]) && ((y - 1 >= 0) && (x + 1 >= 0)) && ((y - 1 < height) && (x + 1 < width))) {
        movement[7] = 1;
        boolean = true;
    }
    else {
        movement[7] = 0;
    }
    //returns either true or false whether there was a valid direction or not
    return boolean;
}

//creates the particle map with each value in it
int** makeParticleMap(int gridWidth, int gridHeight, int windowX, int windowY, int windowWidth, int windowHeight, int numParticles, int maxLife) {

    //2d array particleMap[height][width]
    int** particleMap = new int* [gridHeight];
    for (int i = 0; i < gridHeight; i++) {
        particleMap[i] = new int[gridWidth];
    }
    //windowXMax will be the max value X can be
    int windowXMax = windowX + windowWidth;
    //windowYMax will be the max value Y can be
    int windowYMax = windowY + windowHeight;

    int movement[8] = { 0,0,0,0,0,0,0,0 };

    //for loop that will first set a randomized X and Y value
    //will then check if there is any possible movement
    //if there is, it will then randomize a movement and check if the movement can be done
    //if so, move and add 1 and repeat; we will also decrement maxLife

    //entire particlemap will start with values at 0
    for (int a = 0; a < gridHeight; a++) {
        for (int b = 0; b < gridWidth; b++) {
            particleMap[a][b] = 0;
        }
    }
    for (int i = 0; i < numParticles; i++) {
        //random x location w / in the window
        int dropX = rand() % (windowXMax - windowX) + windowX;
        //random y location w / in the window
        int dropY = rand() % (windowYMax - windowY) + windowY;


        for (int j = 0; j < maxLife; j++) {
            if (moveExists(particleMap, gridWidth, gridHeight, dropX, dropY, movement)) {
                int var = rand() % 8;
                while (movement[var] != 1) {
                    var = rand() % 8;
                }

                if (movement[var] == 1) {
                    if (var == 0) {
                        dropY = dropY + 1;

                        particleMap[dropY][dropX] += 1;
                    }
                    else if (var == 1) {
                        dropX = dropX + 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 2) {
                        dropY = dropY + 1;
                        dropX = dropX + 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 3) {
                        dropY = dropY + 1;
                        dropX = dropX - 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 4) {
                        dropY = dropY - 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 5) {
                        dropX = dropX - 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 6) {
                        dropY = dropY - 1;
                        dropX = dropX - 1;
                        particleMap[dropY][dropX] += 1;

                    }
                    else if (var == 7) {
                        dropY = dropY - 1;
                        dropX = dropX + 1;
                        particleMap[dropY][dropX] += 1;

                    }
                }
                //if there is no valid move to be made, then we will kill all the particles
                else {
                    break;
                }
            }
        }



    }

    return particleMap;
}

//finds a max value from the map
int findMax(int** map, int windowWidth, int windowHeight) {
    int max = map[0][0];
    //loops through and checks if the initial max value is smaller than the next map value
    //if so, set max to the greater index value
    for (int i = 0; i < windowWidth; i++) {
        for (int j = 0; j < windowHeight; j++) {
            if (map[j][i] > max) {
                max = map[j][i];
            }
        }
    }
    return max;
}

//function will normalize the map of values created before
void normalizeMap(int** map, int width, int height, int maxVal, int waterLine) {

    //calls findMax function and stores the maximum integer
    int storeMax = findMax(map, width, height);

    //calculates the landZone that will be used for the map
    int landZone = 255 - waterLine;

    //2d dynamic array which will be the variables height and width (polishedIsland[height][width]) 
    char** polishedIsland = new char* [height];

    for (int k = 0; k < height; k++) {
        polishedIsland[k] = new char[width];
    }

    //loops through the entire 2d array and checks the value in a certian position and sets it to a temporary variable that will be checked
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int checkVal = map[j][i];

            //variable float value will divide checkVal by the maximum value and store it 
//value will then be mulitplied by 255 to be in the range 0 to 255
            float value = ((float)checkVal / storeMax); //rounding to 1?
            value = (value * 255);

            //checks for what value is and will set the character array position
            if (value < (0.5 * waterLine)) {
                polishedIsland[j][i] = '#';
            }
            else if ((value > (0.5 * waterLine)) && (value <= waterLine)) {
                polishedIsland[j][i] = '~';
            }
            else if (value > waterLine) {
                if ((value < (waterLine + (0.15 * landZone)))) {
                    polishedIsland[j][i] = '.';
                }
                else if ((value >= (waterLine + (0.15 * landZone))) && (value < (waterLine + (0.4 * landZone)))) {
                    polishedIsland[j][i] = '-';
                }
                else if ((value >= (waterLine + (0.4 * landZone))) && (value < (waterLine + (0.8 * landZone)))) {
                    polishedIsland[j][i] = '*';
                }
                else {
                    polishedIsland[j][i] = '^';
                }
            }

        }
    }
    //opens file to output to and outputs the entire 2d character array
    ofstream myfile;
    myfile.open("island.txt");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

            myfile << polishedIsland[j][i] << " ";
        }
    }
    myfile.close();

    //prints out the 2d character array created
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (polishedIsland[j][i] == '#') {
                cout << "\033[34m #" << " ";
            }
            else if (polishedIsland[j][i] == '~') {
                cout << "\033[36m ~" << " ";
            }
            else if (polishedIsland[j][i] == '.') {
                cout << "\033[33m ." << " ";
            }
            else if (polishedIsland[j][i] == '-') {
                cout << "\033[37m -" << " ";
            }
            else if (polishedIsland[j][i] == '*') {
                cout << "\033[32m *" << " ";
            }
            else if (polishedIsland[j][i] == '^') {
                cout << "\033[33m ^" << " ";
            }
            
        }
        cout << "\033[0m";
        cout << endl;
    }
}

int main() {
    srand(time(NULL));
    //variables that will be used for our functions
    int gridWidth, gridHeight, windowX, windowY, windowWidth, windowHeight, numParticles, maxLife, waterLine;
    printf("Island generator!\n");
    cout << "Enter grid width: ";
    cin >> gridWidth;
    cout << "\n" << "Enter grid height: ";
    cin >> gridHeight;
    cout << "\n" << "Enter drop-window x-coordinate (0 - <width>): ";
    cin >> windowX;
    cout << "\n" << "Enter drop-window y-coordinate (0 - <height>): ";
    cin >> windowY;
    cout << "\n" << "Enter drop-window width (>= 1): ";
    cin >> windowWidth;
    if (windowWidth < 1) {
        //error statement if windowWidth inputed is less than 1
        cout << "Err: invalid window width";
    }
    cout << "\n" << "Enter drop-window height (>= 1): ";
    cin >> windowHeight;
    if (windowHeight < 1) {
        //error statement if windowHeight inputed is less than 1
        cout << "Err: invalid window height";
    }
    cout << "\n" << "Enter number of particles to drop: ";
    cin >> numParticles;
    cout << "\n" << "Enter max life of particles: ";
    cin >> maxLife;
    cout << "\n" << "Enter value for waterline (40-200): ";
    cin >> waterLine;
    if (waterLine < 40 || waterLine > 200) {
        //error statement if waterLine is less than 40 or greater than 200
        cout << "Err: invalid waterline value (40-200)";
    }

    //sets mapMade to the particlemap
    int** mapMade = makeParticleMap(gridWidth, gridHeight, windowX, windowY, windowWidth, windowHeight, numParticles, maxLife);
    //sets maxVal to the maximum value possible
    int maxVal = findMax(mapMade, windowWidth, windowHeight);
    //runs the normalized map
    normalizeMap(mapMade, gridWidth, gridHeight, maxVal, waterLine);
}