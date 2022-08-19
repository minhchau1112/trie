#include<iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
    Node* children[ALPHABET_SIZE]; // mảng các nút con
    bool isEndOfWord; // cho biết kí tự đó có phải là kí tự cuối cùng của chuỗi chưa
};

struct Trie {
    Node* root; 
};

Node* getNode()
{
    Node* p = new Node;

    p->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        p->children[i] = NULL;
    }

    return p;
}

void InsertNode(Node* root, string key)
{
    Node* cur = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (cur->children[index] == NULL) cur->children[index] = getNode();

        cur = cur->children[index];
    }
    cur->isEndOfWord = true;
}

bool search(Node* root, string key)
{
    Node* cur = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (cur->children[index] == NULL) return false;
        cur = cur->children[index];
    }

    return (cur->isEndOfWord);
}

bool isEmpty(Node* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) return false;
    }
    return true;
}

Node* remove(Node* root, string key, int depth = 0)
{
    // Nếu cây rỗng thì return NULL
    if (root == NULL) return NULL;

    // Nếu kí tự cuối cùng của chuỗi key đang được xử lí thì :
    if (depth == key.size()) {

        // Nếu kí tự này đã là kí tự kết thúc trong cây thì biến nó trở thành chưa kết thúc
        if (root->isEndOfWord) root->isEndOfWord = false;

        // Nếu kí tự này không phải là tiền tố của bất kỳ chuỗi nào khác thì delete nó và cho nó = NULL
        if (isEmpty(root)) {
            delete root;
            root = NULL;
        }

        return root;
    }

    // Nếu chưa phải kí tự cuối cùng của chuỗi key thì lặp lại hàm với con tương ứng
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Nếu root không có con nào (con duy nhất của nó đã bị xóa) và nó không phải là kết thúc của một từ khác thì :
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete root;
        root = NULL;
    }

    return root;
}


// Driver
int main()
{
    Trie t;
    t.root = getNode();
    string keys[] = { "the", "this","that", "there", "those", "any", "by",
                     "bye", "their" };
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        InsertNode(t.root, keys[i]);

    search(t.root, "the") ? cout << "Yes\n" :
        cout << "No\n";
    search(t.root, "these") ? cout << "Yes\n" :
        cout << "No\n";
    search(t.root, "their") ? cout << "Yes\n" :
        cout << "No\n";
    search(t.root, "thaw") ? cout << "Yes\n" :
        cout << "No\n";
    t.root = remove(t.root, "their", 0);
    return 0;
}
