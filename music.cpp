#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX_SONGS 100

/* =================== Array-based Playlist =================== */
string songNames[MAX_SONGS], artists[MAX_SONGS], genres[MAX_SONGS];
int arrCount = 0;

bool arrSongExists(const string& s, const string& a) {
    for (int i = 0; i < arrCount; ++i)
        if (songNames[i] == s && artists[i] == a)
            return true;
    return false;
}

void arrInsertSong(const string& s, const string& a, const string& g) {
    if (arrCount >= MAX_SONGS) {
        cout << "Array playlist full.\n";
        return;
    }
    if (arrSongExists(s, a)) {
        cout << "Song already exists.\n";
        return;
    }
    int pos = 0;
    while (pos < arrCount && songNames[pos] < s) ++pos;
    for (int i = arrCount; i > pos; --i) {
        songNames[i] = songNames[i - 1];
        artists[i] = artists[i - 1];
        genres[i] = genres[i - 1];
    }
    songNames[pos] = s;
    artists[pos] = a;
    genres[pos] = g;
    ++arrCount;
    cout << "Song inserted.\n";
}

bool arrDeleteSong(const string& s, const string& a) {
    for (int i = 0; i < arrCount; ++i) {
        if (songNames[i] == s && artists[i] == a) {
            for (int j = i; j < arrCount - 1; ++j) {
                songNames[j] = songNames[j + 1];
                artists[j] = artists[j + 1];
                genres[j] = genres[j + 1];
            }
            --arrCount;
            cout << "Song deleted.\n";
            return true;
        }
    }
    cout << "Song not found.\n";
    return false;
}

int arrFindSongIndex(const string& s, const string& a) {
    for (int i = 0; i < arrCount; ++i)
        if (songNames[i] == s && artists[i] == a)
            return i;
    return -1;
}

void arrDisplaySongs() {
    if (arrCount == 0) {
        cout << "No songs in array playlist.\n";
        return;
    }
    cout << "\n--- Array Playlist ---\n";
    for (int i = 0; i < arrCount; ++i)
        cout << i + 1 << ". " << songNames[i] << " by " << artists[i] << " [" << genres[i] << "]\n";
}

void arrClearAll() {
    arrCount = 0;
    ofstream("array_playlist.txt", ios::trunc);
    cout << "All songs removed from array playlist.\n";
}

void arrSaveToFile() {
    ofstream out("array_playlist.txt");
    for (int i = 0; i < arrCount; ++i)
        out << songNames[i] << '\n' << artists[i] << '\n' << genres[i] << '\n';
}

void arrLoadFromFile() {
    ifstream in("array_playlist.txt");
    string s, a, g;
    arrCount = 0;
    while (getline(in, s) && getline(in, a) && getline(in, g))
        arrInsertSong(s, a, g);
}

/* =================== Linked List Playlist =================== */
struct Node {
    string song, artist, genre;
    Node* next;
};
Node* head = nullptr;

bool llSongExists(const string& s, const string& a) {
    for (Node* t = head; t != nullptr; t = t->next)
        if (t->song == s && t->artist == a)
            return true;
    return false;
}

void llInsert(const string& s, const string& a, const string& g) {
    if (llSongExists(s, a)) {
        cout << "Song already exists in linked list.\n";
        return;
    }
    Node* newNode = new Node{s, a, g, nullptr};
    if (!head || head->song > s) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* t = head;
        while (t->next && t->next->song < s)
            t = t->next;
        newNode->next = t->next;
        t->next = newNode;
    }
    cout << "Song inserted in linked list.\n";
}

bool llDelete(const string& s, const string& a) {
    Node *cur = head, *prev = nullptr;
    while (cur) {
        if (cur->song == s && cur->artist == a) {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            delete cur;
            cout << "Song deleted from linked list.\n";
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Song not found in linked list.\n";
    return false;
}

void llSearch(const string& s, const string& a) {
    int pos = 1;
    for (Node* t = head; t; t = t->next, ++pos)
        if (t->song == s && t->artist == a) {
            cout << "Found at position: " << pos << endl;
            return;
        }
    cout << "Not found in linked list.\n";
}

void llDisplay() {
    if (!head) {
        cout << "Linked list is empty.\n";
        return;
    }
    cout << "\n--- Linked List Playlist ---\n";
    for (Node* t = head; t; t = t->next)
        cout << t->song << " by " << t->artist << " [" << t->genre << "]\n";
}

void llClearAll() {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    ofstream("linkedlist_playlist.txt", ios::trunc);
    cout << "All songs removed from linked list.\n";
}

void llSaveToFile() {
    ofstream out("linkedlist_playlist.txt");
    for (Node* t = head; t; t = t->next)
        out << t->song << '\n' << t->artist << '\n' << t->genre << '\n';
}

void llLoadFromFile() {
    ifstream in("linkedlist_playlist.txt");
    string s, a, g;
    while (getline(in, s) && getline(in, a) && getline(in, g))
        llInsert(s, a, g);
}

/* =================== Stack =================== */
struct Song {
    string name, artist, genre;
};

Song stackSongs[MAX_SONGS];
int stackTop = -1;

bool stackSongExists(const string& s, const string& a) {
    for (int i = 0; i <= stackTop; ++i)
        if (stackSongs[i].name == s && stackSongs[i].artist == a)
            return true;
    return false;
}

void stackPush(const string& s, const string& a, const string& g) {
    if (stackTop >= MAX_SONGS - 1) {
        cout << "Stack Overflow!\n";
        return;
    }
    if (stackSongExists(s, a)) {
        cout << "Song already exists in stack.\n";
        return;
    }
    stackSongs[++stackTop] = {s, a, g};
    cout << "Song pushed to stack.\n";
}

void stackPop() {
    if (stackTop < 0) {
        cout << "Stack Underflow!\n";
        return;
    }
    cout << "Popped: " << stackSongs[stackTop].name << " by " << stackSongs[stackTop].artist << " [" << stackSongs[stackTop].genre << "]\n";
    --stackTop;
}

void stackSearch(const string& s, const string& a) {
    for (int i = stackTop; i >= 0; --i)
        if (stackSongs[i].name == s && stackSongs[i].artist == a) {
            cout << "Found at position (from top): " << (stackTop - i + 1) << endl;
            return;
        }
    cout << "Not found in stack.\n";
}

void stackDisplay() {
    if (stackTop < 0) {
        cout << "Stack is empty.\n";
        return;
    }
    cout << "\n--- Stack Songs ---\n";
    for (int i = stackTop; i >= 0; --i)
        cout << stackSongs[i].name << " by " << stackSongs[i].artist << " [" << stackSongs[i].genre << "]\n";
}

void stackSaveToFile() {
    ofstream out("stack_playlist.txt");
    for (int i = 0; i <= stackTop; ++i)
        out << stackSongs[i].name << '\n' << stackSongs[i].artist << '\n' << stackSongs[i].genre << '\n';
}

void stackLoadFromFile() {
    ifstream in("stack_playlist.txt");
    string s, a, g;
    stackTop = -1;
    while (getline(in, s) && getline(in, a) && getline(in, g))
        stackSongs[++stackTop] = {s, a, g};
}

/* =================== Queue =================== */

Song queueSongs[MAX_SONGS + 1]; 
int qFront = 0, qRear = 0;

bool isQueueFull() {
    return (qFront == (qRear + 1) % (MAX_SONGS + 1));
}

bool isQueueEmpty() {
    return qFront == qRear;
}

bool queueSongExists(const string& s, const string& a) {
    for (int i = (qFront + 1) % (MAX_SONGS + 1);
       i != (qRear + 1) % (MAX_SONGS + 1); 
       i = (i + 1) % (MAX_SONGS + 1)) {
        if (queueSongs[i].name == s && queueSongs[i].artist == a)
            return true;
    }
    return false;
}

void enqueue(const string& s, const string& a, const string& g) {
    if (isQueueFull()) {
        cout << "Queue Overflow! Cannot enqueue.\n";
        return;
    }
    if (queueSongExists(s, a)) {
        cout << "Song already exists in queue.\n";
        return;
    }
    qRear = (qRear + 1) % (MAX_SONGS + 1);
    queueSongs[qRear] = {s, a, g};
    cout << "Song enqueued.\n";
}

void dequeue() {
    if (isQueueEmpty()) {
        cout << "Queue Empty! Cannot dequeue.\n";
        return;
    }
    qFront = (qFront + 1) % (MAX_SONGS + 1);
    cout << "Dequeued: " << queueSongs[qFront].name << " by " << queueSongs[qFront].artist << " [" << queueSongs[qFront].genre << "]\n";
}

void queueDisplay() {
    if (isQueueEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }
    cout << "\n--- Queue Playlist ---\n";
    int i = (qFront + 1) % (MAX_SONGS + 1), cnt = 1;
    while (i != (qRear + 1) % (MAX_SONGS + 1)) {
        cout << cnt++ << ". " << queueSongs[i].name << " by " << queueSongs[i].artist << " [" << queueSongs[i].genre << "]\n";
        i = (i + 1) % (MAX_SONGS + 1);
    }
}

void queueSearch(const string& s, const string& a) {
    int pos = 1;
    for (int i = (qFront + 1) % (MAX_SONGS + 1); i != (qRear + 1) % (MAX_SONGS + 1); i = (i + 1) % (MAX_SONGS + 1), ++pos) {
        if (queueSongs[i].name == s && queueSongs[i].artist == a) {
            cout << "Found at position (from front): " << pos << endl;
            return;
        }
    }
    cout << "Not found in queue.\n";
}

void queueSaveToFile() {
    ofstream out("queue_playlist.txt");
    for (int i = (qFront + 1) % (MAX_SONGS + 1); i != (qRear + 1) % (MAX_SONGS + 1); i = (i + 1) % (MAX_SONGS + 1)) {
        out << queueSongs[i].name << '\n' << queueSongs[i].artist << '\n' << queueSongs[i].genre << '\n';
    }
}

void queueLoadFromFile() {
    ifstream in("queue_playlist.txt");
    string s, a, g;
    qFront = qRear = 0;
    while (getline(in, s) && getline(in, a) && getline(in, g)) {
        if (!isQueueFull()) {
            qRear = (qRear + 1) % (MAX_SONGS + 1);
            queueSongs[qRear] = {s, a, g};
        }
    }
}

void queueClearAll() {
    qFront = qRear = 0;
    ofstream("queue_playlist.txt", ios::trunc);
    cout << "All songs removed from queue.\n";
}


/* =================== Main =================== */
int main() {
    arrLoadFromFile();
    llLoadFromFile();
    stackLoadFromFile();
    queueLoadFromFile();

    int ch, op;
    string s, a, g;

    while (true) {
        cout << "\n==== MUSIC PLAYER MENU ====\n";
        cout << "1. Array Playlist\n2. Linked List Playlist\n3. Stack (Recent)\n4. Queue (Upcoming)\n5. Exit\nEnter choice: ";
        cin >> ch; cin.ignore();

        if (ch == 1) {
            while (true) {
                cout << "\n-- Array Playlist --\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Clear All\n6. Save\n7. Back\nChoice: ";
                cin >> op; cin.ignore();
                if (op == 1) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    cout << "Genre: "; getline(cin, g);
                    arrInsertSong(s, a, g);
                } else if (op == 2) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    arrDeleteSong(s, a);
                } else if (op == 3) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    int idx = arrFindSongIndex(s, a);
                    if (idx != -1) cout << "Found at index: " << idx + 1 << endl;
                    else cout << "Not found.\n";
                } else if (op == 4) arrDisplaySongs();
                else if (op == 5) arrClearAll();
                else if (op == 6) arrSaveToFile();
                else break;
            }
        } else if (ch == 2) {
            while (true) {
                cout << "\n-- Linked List --\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Clear All\n6. Save\n7. Back\nChoice: ";
                cin >> op; cin.ignore();
                if (op == 1) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    cout << "Genre: "; getline(cin, g);
                    llInsert(s, a, g);
                } else if (op == 2) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    llDelete(s, a);
                } else if (op == 3) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    llSearch(s, a);
                } else if (op == 4) llDisplay();
                else if (op == 5) llClearAll();
                else if (op == 6) llSaveToFile();
                else break;
            }
        } else if (ch == 3) {
            while (true) {
                cout << "\n-- Stack --\n1. Push\n2. Pop\n3. Search\n4. Display\n5. Save\n6. Back\nChoice: ";
                cin >> op; cin.ignore();
                if (op == 1) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    cout << "Genre: "; getline(cin, g);
                    stackPush(s, a, g);
                } else if (op == 2) stackPop();
                else if (op == 3) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    stackSearch(s, a);
                } else if (op == 4) stackDisplay();
                else if (op == 5) stackSaveToFile();
                else break;
            }
        } else if (ch == 4) {
            while (true) {
                cout << "\n-- Queue --\n1. Enqueue\n2. Dequeue\n3. Search\n4. Display\n5. Save\n6. Back\nChoice: ";
                cin >> op; cin.ignore();
                if (op == 1) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    cout << "Genre: "; getline(cin, g);
                    enqueue(s, a, g);
                } else if (op == 2) dequeue();
                else if (op == 3) {
                    cout << "Song: "; getline(cin, s);
                    cout << "Artist: "; getline(cin, a);
                    queueSearch(s, a);
                } else if (op == 4) queueDisplay();
                else if (op == 5) queueSaveToFile();
                else break;
            }
        } else if (ch == 5) {
            cout << "Thank you for using the Music Player!\n";
            break;
        }
    }

    return 0;
}
