
#include <array>
#include <iostream>
#include <string>

using namespace std;


bool is_visible(int** heights, int row, int col, int size) {
    // Border
    if (row == 0 || col == 0 || row == size-1 || col == size-1) {
        return true;
    }
    int height = heights[row][col];
    // up
    bool visible = true;
    for (int i = row - 1; i >= 0; i--) {
        if (heights[i][col] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }
    // down
    visible = true;
    for (int i = row + 1; i < size; i++) {
        if (heights[i][col] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }
    // left
    visible = true;
    for (int j = col - 1; j >= 0; j--) {
        if (heights[row][j] >= height) {
            visible = false;
            break;
        }
    }
    if (visible) {
        return true;
    }
    // right
    visible = true;
    for (int j = col + 1; j < size; j++) {
        if (heights[row][j] >= height) {
            visible = false;
            break;
        }
    }
    return visible;
}

int how_many_visible(int** heights, int size) {
    int visible = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (is_visible(heights, row, col, size)) {
                visible++;
            }
        }
    }
    return visible;
}


int get_scenic_score(int** heights, int row, int col, int size) {
    // Border
    if (row == 0 || col == 0 || row == size-1 || col == size-1) {
        return 0;
    }
    int height = heights[row][col];
    // up
    int viewing_distance = 0;
    for (int i = row - 1; i >= 0; i--) {
        viewing_distance++;
        if (heights[i][col] >= height) {
            break;
        }
    }
    int scenic_score = viewing_distance;
    // down
    viewing_distance = 0;
    for (int i = row + 1; i < size; i++) {
        viewing_distance++;
        if (heights[i][col] >= height) {
            break;
        }
    }
    scenic_score *= viewing_distance;
    // left
    viewing_distance = 0;
    for (int j = col - 1; j >= 0; j--) {
        viewing_distance++;
        if (heights[row][j] >= height) {
            break;
        }
    }
    scenic_score *= viewing_distance;
    // right
    viewing_distance = 0;
    for (int j = col + 1; j < size; j++) {
        viewing_distance++;
        if (heights[row][j] >= height) {
            break;
        }
    }
    return scenic_score * viewing_distance;
}

int get_highest_scenic_score(int** heights, int size) {
    int score;
    int highest_score = 0;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            score = get_scenic_score(heights, row, col, size);
            if (score > highest_score) {
                highest_score = score;
            }
        }
    }
    return highest_score;
}

int main() {
    int** heights = NULL;
    int size;
    int row = 0;
    int col;
    int height;
    string line;
    while (getline(cin, line)) {
        if (heights == NULL) {
            size = line.length();
            heights = new int*[size];
        }
        heights[row] = new int[size];
        for (col = 0; col < size; col++) {
            // via https://stackoverflow.com/a/30727561/1406873
            height = (int)line[col] - 48;
            heights[row][col] = height;
        }
        row++;
    }
    cout << how_many_visible(heights, size) << endl;
    cout << get_highest_scenic_score(heights, size) << endl;
    return 0;
}
