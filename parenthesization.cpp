#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Operation {
public:
    char goal{};
    bool valid = false;
    int characterNumber;
    int expressionSize{};
    vector<char> expression;
    vector<char> characters;
    bool firstIndexing = true;
    vector<vector<char>> table;
    vector<pair<int, int>> finalPath;
    map<pair<int,int>, vector<char>> set;

    explicit Operation(int);
    void takeCharacters();
    void createTable();
    void takeExpression();
    char multiplication(char, char);
    void showTime();
    void parenthesization(bool);
    void indexing(map<pair<pair<int, int>, char>, vector<pair<pair<int,int>, char>>>&, pair<pair<int, int>, char>);
};

Operation::Operation(int characterNumber) {
    this->characterNumber = characterNumber;
}

void Operation::takeCharacters() {
    string line;
    cin >> line;
    int n = (int) line.size();
    for (int i = 0; i < n; i++) {
        this->characters.push_back(line[i]);
    }
    this->goal = this->characters.back();
}

void Operation::createTable() {
    string line;
    for (int i = 0; i < this->characterNumber; i++) {
        cin >> line;
        this->table.emplace_back();
        for (int j = 0; j < this->characterNumber; j++) {
            this->table[i].push_back(line[j]);
        }
    }
}

void Operation::takeExpression() {
    string line;
    cin >> line;
    int n = (int) line.size();
    for (int i = 0; i < n; i++) {
        this->expression.push_back(line[i]);
    }
    this->expressionSize = (int) this->expression.size();
}

char Operation::multiplication(char first, char second) {
    int firstNum, secondNum;
    for (int i = 0; i < this->characterNumber; i++) {
        if ( first == this->characters[i] ) {
            firstNum = i;
        }
        if ( second == this->characters[i] ) {
            secondNum = i;
        }
    }
    return this->table[firstNum][secondNum];
}

void Operation::showTime() {
    vector<pair<pair<int,int>, char>> index;
    map<pair<pair<int, int>, char>, vector<pair<pair<int,int>, char>>> path;
    int n = this->expressionSize;
    for (int i = 0; i < n; i++) {
        this->set[make_pair(i+1, i+1)].push_back(this->expression[i]);
    }
    char e, b, tempChar;
    for (int s = 1; s < n; s++) {
        for (int i = 1; i <= n - s; i++) {
            for (int k = i; k < i + s; k++) {
                for (int j = 0; j < this->set[make_pair(i, k)].size(); j++) {
                    e = this->set[make_pair(i, k)][j];
                    for (int l = 0; l < this->set[make_pair(k+1, i+s)].size(); l++) {
                        b = this->set[make_pair(k+1, i+s)][l];
                        tempChar = multiplication(e, b);
                        if(find(set[make_pair(i, i+s)].begin(), set[make_pair(i, i+s)].end(), tempChar) == set[make_pair(i, i+s)].end()) {
                            this->set[make_pair(i, i+s)].push_back(tempChar);
                            index.emplace_back(make_pair(i, k), e);
                            index.emplace_back(make_pair(k+1, i+s), b);
                            path.insert({make_pair(make_pair(i, i+s), tempChar), index});
                            index.clear();
                            if( (i == 1 && i+s == n) && tempChar == goal) {
                                auto ultimateValue = path[make_pair(make_pair(1, this->expressionSize), this->goal)];
                                indexing(path, ultimateValue[0]);
                                indexing(path, ultimateValue[1]);
                                this->valid = true;
                                parenthesization(valid);
                            }
                        }
                    }
                }
            }
        }
    }
    if (!this->valid) {
        parenthesization(valid);
    }
}

void Operation::indexing(map<pair<pair<int, int>, char>, vector<pair<pair<int,int>, char>>> &trail, pair<pair<int, int>, char> tempPair) {
    if (this->firstIndexing) {
        this->finalPath.push_back(tempPair.first);
        this->firstIndexing = false;
    }
    if ( tempPair.first.second - tempPair.first.first >= 1 ) {
        for (auto & iter : trail) {
            if (iter.first == tempPair) {
                this->finalPath.push_back(tempPair.first);
                indexing(trail, iter.second[0]);
                indexing(trail, iter.second[1]);
            }
        }
    }
}

void Operation::parenthesization(bool check) {
    if (check) {
        int count = 0;
        int size = this->expressionSize;
        for (auto & index : this->finalPath) {
            for(int i = 0; i < size; i++){
                if( !( this->expression[i] == '(' || this->expression[i] == ')' ) ) {
                    count++;
                }
                if ( count == index.first ) {
                    this->expression.insert(this->expression.begin()+i, '(');
                }
                if ( count == index.second && index.second <= this->expressionSize) {
                    this->expression.insert(this->expression.begin()+i+2, ')');
                    count++;
                }
                size = (int) this->expression.size();
            }
            count = 0;
        }
        for (char i : this->expression) {
            cout << i;
        }
    } else {
        cout << "No parenthesization is possible.";
    }
}

int main() {

    //Take the number of characters
    int characterNumber;
    cin >> characterNumber;

    //Take the characters
    Operation myOp(characterNumber);
    myOp.takeCharacters();

    //Take the table
    myOp.createTable();

    //Take the expression
    myOp.takeExpression();

    //Do the operation
    if (myOp.expressionSize == 1) {
        if (myOp.expression[0] == myOp.goal) {
            cout << myOp.expression[0];
        } else {
            cout << "No parenthesization is possible.";
        }
    } else {
        myOp.showTime();
    }
    return 0;
}