
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


class File {
    public:
        string name;
        int size;
        File(string name, int size) {
            this->name = name;
            this->size = size;
        }
};

class Directory {
    public:
        string name;
        Directory* parent;
        vector<Directory*> dirs;
        vector<File*> files;
        Directory(string name, Directory* parent) {
            this->name = name;
            this->parent = parent;
        }
        void add_dir(string name) {
            Directory* dir = new Directory(name, this);
            this->dirs.push_back(dir);
        }
        void add_file(string name, int size) {
            File* file = new File(name, size);
            this->files.push_back(file);
        }
        Directory* get_dir(string name) {
            for (vector<Directory*>::iterator it = this->dirs.begin(); it != this->dirs.end(); ++it) {
                if ((*it)->name == name) {
                    return *it;
                }
            }
            return NULL;
        }
        void print(int depth) {
            for (int i = 0; i < depth; i++) {
                cout << " ";
            }
            cout << "- " << this->name << " (dir)" << endl;
            for (vector<Directory*>::iterator it = this->dirs.begin(); it != this->dirs.end(); ++it) {
                (*it)->print(depth + 2);
            }
            for (vector<File*>::iterator it = this->files.begin(); it != this->files.end(); ++it) {
                for (int i = 0; i < depth + 2; i++) {
                    cout << " ";
                }
                cout << "- " << (*it)->name << " (file, size=" << (*it)->size << ")" << endl;
            }
        }
        void print_full_dir() {
            cout << " < " << this->name;
            if (this->parent == nullptr) {
                cout << endl;
            } else {
                this->parent->print_full_dir();
            }
        }
        int get_size() {
            int size = 0;
            for (vector<File*>::iterator it = this->files.begin(); it != this->files.end(); ++it) {
                size += (*it)->size;
            }
            for (vector<Directory*>::iterator it = this->dirs.begin(); it != this->dirs.end(); ++it) {
                size += (*it)->get_size();
            }
            return size;
        }
        int sum_all_dirs_with_min(int min_size) {
            int total_size = 0;
            int size = this->get_size();
            if (size <= min_size) {
                total_size += this->get_size();
            }
            for (vector<Directory*>::iterator it = this->dirs.begin(); it != this->dirs.end(); ++it) {
                total_size += (*it)->sum_all_dirs_with_min(min_size);
            }
            return total_size;
        }
        int find_dir_to_delete() {
            int used = this->get_size();
            int unused = 70000000 - used;
            int needed = 30000000 - unused;
            return this->find_min_dir(needed, used);
        }
        int find_min_dir(int needed, int current_min) {
            int size = this->get_size();
            if (size >= needed && size < current_min) {
                current_min = size;
            }
            for (vector<Directory*>::iterator it = this->dirs.begin(); it != this->dirs.end(); ++it) {
                current_min = (*it)->find_min_dir(needed, current_min);
            }
            return current_min;
        }
};

Directory* build_fs() {
    Directory* root = new Directory("/", nullptr);
    Directory* cwd = NULL;
    string line, piece, name;
    int size;
    bool listing = false;
    while (getline(cin, line)) {
        // cout << line << endl;
        if (listing) {
            stringstream stream(line);
            stream >> piece;
            // Back to commands ...
            if (piece == "$") {
                listing = false;
            }
            // Directory
            else if (piece == "dir") {
                stream >> name;
                cwd->add_dir(name);
                continue;
            }
            // File
            else {
                size = stoi(piece);
                stream >> name;
                cwd->add_file(name, size);
                continue;
            }
        }
        // cout << "cwd: ";
        // if (cwd == NULL) {
        //     cout << "NULL" << endl;
        // } else {
        //     cwd->print_full_dir();
        // }
        if (line == "") {
            continue;
        }
        stringstream stream(line);
        stream >> piece;
        // cout << "stream(" << piece << ")" << endl;
        if (piece != "$") {
            cout << "Unknown state" << endl;
            return NULL;
        }
        stream >> piece;
        // cout << "stream(" << piece << ")" << endl;
        if (piece == "cd") {
            stream >> piece;
            // cout << "stream(" << piece << ")" << endl;
            if (cwd == NULL && piece == "/") {
                // cout << "root!" << endl;
                cwd = root;
            } else if (piece == "..") {
                cwd = cwd->parent;
            } else {
                cwd = cwd->get_dir(piece);
                if (cwd == NULL) {
                    cout << "INVALID DIR: " << piece << endl;
                    return NULL;
                }
            }
        } else if (piece == "ls") {
            listing = true;
        } else {
            cout << "Unknown cmd: " << piece << endl;
            return NULL;
        }
    }
    return root;
}

int main() {
    Directory* root = build_fs();
    root->print(0);
    cout << root->sum_all_dirs_with_min(100000) << endl;
    cout << root->find_dir_to_delete() << endl;
    return 0;
}
