class Trie {

    class Node {
        Node* link[26];
        int cntEndswith = 0, cntPref = 0;

    public:
        Node() {
            for (int i = 0; i < 26; i++) {
                link[i] = NULL;
            }
        }

        bool containsch(char c) {
            return link[c - 'a'] != NULL;
        }

        Node* getNext(char c) {
            return link[c - 'a'];
        }

        void putchar(char c) {
            link[c - 'a'] = new Node();
        }

        void setEnd() {
            cntEndswith++;
        }

        void increaseCntPref() {
            cntPref++;
        }

        void decreaseCntPref() {
            cntPref--;
        }

        void decEnd() {
            cntEndswith--;
        }

        int getCntWord() {
            return cntEndswith;
        }

        int getCntPref() {
            return cntPref;
        }
    };

    Node* root;

public:

    Trie() {
        root = new Node();
    }

    void insert(string &word) {
        Node* node = root;
        for (auto c : word) {
            if (!node->containsch(c)) {
                node->putchar(c);
            }
             // Only increment prefix count during insertion
            node = node->getNext(c);
            node->increaseCntPref(); 
        }
        node->setEnd();  // Increment end count to mark word insertion
    }

    int countWordsEqualTo(string &word) {
        Node* node = root;
        for (auto c : word) {
            if (!node->containsch(c)) {
                return 0;  // Word doesn't exist in Trie
            }
            node = node->getNext(c);
        }
        return node->getCntWord();  // Return how many times the word was inserted
    }

    int countWordsStartingWith(string &prefix) {
        Node* node = root;
        for (auto c : prefix) {
            if (!node->containsch(c)) {
                return 0;  // Prefix doesn't exist in Trie
            }
            node = node->getNext(c);
        }
        return node->getCntPref();  // Return how many words share this prefix
    }

    void erase(string &word) {
        Node* node = root;
        for (auto c : word) {
            if (!node->containsch(c)) {
                return;  // Word doesn't exist, can't erase
            }
              // Decrease prefix count along the path
            node = node->getNext(c);
            node->decreaseCntPref();
        }
        node->decEnd();  // Decrease end count to mark the word as erased
    }
};
