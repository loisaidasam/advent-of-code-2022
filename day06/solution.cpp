/**
 * Day 6
 *
 * sets
 */

#include <iostream>
#include <set>
#include <string>

using namespace std;

int solution(string input, int markerLen) {
    set<char> chars;    
    for (int i = 0; i < input.length(); i++) {
        chars.clear();
        int j;
        for (j = i; j < i + markerLen; j++) {
            chars.insert(input[j]);
            // cout << input[j];
        }
        // cout << endl;
        if (chars.size() == markerLen) {
            return j;
        }
    }
    return -1;
}

int main() {
    string input;
    cin >> input;
    cout << solution(input, 4) << endl;
    cout << solution(input, 14) << endl;
    return 0;
}
