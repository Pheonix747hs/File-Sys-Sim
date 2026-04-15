#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    bool isFile;
    Node* parent;
    unordered_map<string, Node*> children;
    string content;

    Node(string name, bool isFile, Node* parent) {
        this->name = name;
        this->isFile = isFile;
        this->parent = parent;
    }
};

class FileSystem {
private:
    Node* root;
    Node* current;

public:
    FileSystem() {
        root = new Node("/", false, nullptr);
        current = root;
    }

    void mkdir(string name) {
        if (current->children.count(name)) {
            cout << "Already exists\n";
            return;
        }
        current->children[name] = new Node(name, false, current);
    }

    void touch(string name) {
        if (current->children.count(name)) {
            cout << "Already exists\n";
            return;
        }
        current->children[name] = new Node(name, true, current);
    }

    void ls() {
        for (auto &it : current->children) {
            if (it.second->isFile)
                cout << "[FILE] ";
            else
                cout << "[DIR] ";
            cout << it.first << "\n";
        }
    }

    void cd(string name) {
        if (name == "..") {
            if (current->parent != nullptr)
                current = current->parent;
            return;
        }

        if (!current->children.count(name) || current->children[name]->isFile) {
            cout << "Directory not found\n";
            return;
        }

        current = current->children[name];
    }

    void rm(string name) {
        if (!current->children.count(name)) {
            cout << "Not found\n";
            return;
        }

        delete current->children[name]; // basic delete
        current->children.erase(name);
    }

    void pwd() {
        vector<string> path;
        Node* temp = current;

        while (temp != nullptr) {
            path.push_back(temp->name);
            temp = temp->parent;
        }

        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++) {
            if (i == 0) cout << "/";
            else cout << path[i] << "/";
        }
        cout << "\n";
    }

    void write(string name, string content) {
        if (!current->children.count(name) || !current->children[name]->isFile) {
            cout << "File not found\n";
            return;
        }
        current->children[name]->content = content;
    }

    void read(string name) {
        if (!current->children.count(name) || !current->children[name]->isFile) {
            cout << "File not found\n";
            return;
        }
        cout << current->children[name]->content << "\n";
    }
};

int main() {
    FileSystem fs;
    string input;

    while (true) {
        cout << "> ";
        getline(cin, input);

        stringstream ss(input);
        string cmd;
        ss >> cmd;

        if (cmd == "exit") break;

        else if (cmd == "mkdir") {
            string name;
            ss >> name;
            fs.mkdir(name);
        }

        else if (cmd == "touch") {
            string name;
            ss >> name;
            fs.touch(name);
        }

        else if (cmd == "ls") {
            fs.ls();
        }

        else if (cmd == "cd") {
            string name;
            ss >> name;
            fs.cd(name);
        }

        else if (cmd == "rm") {
            string name;
            ss >> name;
            fs.rm(name);
        }

        else if (cmd == "pwd") {
            fs.pwd();
        }

        else if (cmd == "write") {
            string name;
            ss >> name;
            string content;
            getline(ss, content);
            if (!content.empty() && content[0] == ' ')
                content = content.substr(1);
            fs.write(name, content);
        }

        else if (cmd == "read") {
            string name;
            ss >> name;
            fs.read(name);
        }

        else {
            cout << "Unknown command\n";
        }
    }

    return 0;
}