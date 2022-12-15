
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Point {
    public:
        int x;
        int y;
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }
        void print() {
            cout << "(" << this->x << ", " << this->y << ")";
        }
};

class Grid {
    public:
        char** grid;
        int size;
        int xMin, xMax, yMin, yMax;
        void draw_mark(int x, int y, char mark) {
            this->grid[x][y] = mark;
            if (mark == '#') {
                if (xMin == -1 || x < xMin) {
                    xMin = x;
                }
                if (xMax == -1 || x > xMax) {
                    xMax = x;
                }
                if (yMin == -1 || y < yMin) {
                    yMin = y;
                }
                if (yMax == -1 || y > yMax) {
                    yMax = y;
                }
            }
        }
        Grid(int size) {
            this->size = size;
            // Initialize the grid
            this->grid = new char*[size];
            for (int i = 0; i < size; i++) {
                this->grid[i] = new char[size];
                for (int j = 0; j < size; j++) {
                    this->draw_mark(i, j, '.');
                }
            }
            xMin = xMax = yMin = yMax = -1;
        }
        void draw_line(Point* p1, Point* p2) {
            // cout << "draw_line() from ";
            // p1->print();
            // cout << " to ";
            // p2->print();
            // cout << endl;
            int start, stop;
            if (p1->x == p2->x) {
                if (p1->y > p2->y) {
                    start = p2->y;
                    stop = p1->y;
                } else {
                    start = p1->y;
                    stop = p2->y;
                }
                for (int y = start; y <= stop; y++) {
                    this->draw_mark(p1->x, y, '#');
                }
            } else if (p1->y == p2->y) {
                if (p1->x > p2->x) {
                    start = p2->x;
                    stop = p1->x;
                } else {
                    start = p1->x;
                    stop = p2->x;
                }
                for (int x = start; x <= stop; x++) {
                    this->draw_mark(x, p1->y, '#');
                }
            }
        }
        void read_input() {
            // Build lines
            string line;
            Point* p1;
            Point* p2;
            int value, x, y;
            bool isX = true;
            while (getline(cin, line)) {
                p1 = NULL;
                stringstream stream(line);
                while (stream >> value) {
                    if (isX) {
                        x = value;
                    } else {
                        y = value;
                        p2 = new Point(x, y);
                        if (p1 != NULL) {
                            this->draw_line(p1, p2);
                        }
                        p1 = p2;
                    }
                    isX = ! isX;
                }
            }
        }
        bool drop_sand() {
            int x = 500;
            int y = 0;
            while (true) {
                if (this->grid[x][y + 1] == '.') {
                    y++;
                } else if (this->grid[x - 1][y + 1] == '.') {
                    x--;
                    y++;
                } else if (this->grid[x + 1][y + 1] == '.') {
                    x++;
                    y++;
                } else {
                    // Can't move anywhere else
                    break;
                }
                if (x < xMin) {
                    return false;
                } else if (x > xMax) {
                    return false;
                } else if (y > yMax) {
                    return false;
                }
            }
            this->draw_mark(x, y, 'o');
            return true;
        }
        void print_min_max(int xMin, int xMax, int yMin, int yMax) {
            // cout << xMin << endl << xMax << endl << yMin << endl << yMax << endl;
            for (int y = yMin; y <= yMax; y++) {
                for (int x = xMin; x <= xMax; x++) {
                    cout << this->grid[x][y];
                }
                cout << endl;
            }
            cout << endl;
        }
        void print() {
            this->print_min_max(494, 503, 0, 9);
            // this->print_min_max(this->xMin, this->xMax, this->yMin, this->yMax);
        }
};

int solution1(Grid* grid) {
    int num_sand_units = 0;
    while (grid->drop_sand()) {
        num_sand_units++;
    }
    return num_sand_units;
}

int main() {
    // Not sure how big this thing actually is, just using 1k ...
    int size = 1000;
    Grid* grid = new Grid(size);
    grid->read_input();
    // grid->print();
    // for (int i = 0; i < 26; i++) {
    //     cout << grid->drop_sand() << endl;
    //     grid->print();
    // }
    cout << solution1(grid) << endl;
    return 0;
}
