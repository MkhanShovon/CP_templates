class Trie
{
private:
    class Node
    {
        Node *links[26];    // Assuming lowercase English alphabet
        int cntEndWith = 0; // Count of words ending at this node
        int cntPrefix = 0;  // Count of words with prefix up to this node

    public:
        Node()
        {
            for (int i = 0; i < 26; i++)
            {
                links[i] = nullptr;
            }
        }

        ~Node()
        {
            for (int i = 0; i < 26; i++)
            {
                delete links[i];
            }
        }

        bool containsChar(char c) const
        {
            return links[c - 'a'] != nullptr;
        }

        Node *getNext(char c) const
        {
            return links[c - 'a'];
        }

        void putChar(char c, Node *node)
        {
            links[c - 'a'] = node;
        }

        void incrementEnd()
        {
            cntEndWith++;
        }

        void decrementEnd()
        {
            if (cntEndWith > 0)
                cntEndWith--;
        }

        void incrementPrefix()
        {
            cntPrefix++;
        }

        void decrementPrefix()
        {
            if (cntPrefix > 0)
                cntPrefix--;
        }

        int getEndCount() const
        {
            return cntEndWith;
        }

        int getPrefixCount() const
        {
            return cntPrefix;
        }
    };

    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    ~Trie()
    {
        delete root;
    }

    // Insert a word into the Trie
    void insert(const string &word)
    {
        Node *node = root;
        for (char c : word)
        {
            if (!node->containsChar(c))
            {
                node->putChar(c, new Node());
            }
            node = node->getNext(c);
            node->incrementPrefix();
        }
        node->incrementEnd();
    }

    // Count words equal to the given word
    int countWordsEqualTo(const string &word) const
    {
        Node *node = root;
        for (char c : word)
        {
            if (!node->containsChar(c))
            {
                return 0;
            }
            node = node->getNext(c);
        }
        return node->getEndCount();
    }

    // Count words starting with the given prefix
    int countWordsStartingWith(const string &prefix) const
    {
        Node *node = root;
        for (char c : prefix)
        {
            if (!node->containsChar(c))
            {
                return 0;
            }
            node = node->getNext(c);
        }
        return node->getPrefixCount();
    }

    // Erase a word from the Trie
    // Erase a word from the Trie
    void erase(const string &word)
    {
        // Stack to store nodes and characters for cleanup
        vector<pair<Node *, char>> nodes;
        Node *node = root;

        // Traverse the word and collect nodes
        for (char c : word)
        {
            if (!node->containsChar(c))
            {
                return; // Word not found
            }
            nodes.push_back({node, c});
            node = node->getNext(c);
            node->decrementPrefix();
        }
        node->decrementEnd();

        // Clean up nodes if necessary
        for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
        {
            Node *curr = it->first;
            char c = it->second;
            Node *child = curr->getNext(c);

            // If the child node has no prefixes and no words ending, delete it
            if (child->getPrefixCount() == 0 && child->getEndCount() == 0)
            {
                delete child;
                curr->putChar(c, nullptr);
            }
            else
            {
                // If the node still has prefixes or words ending, stop cleanup
                break;
            }
        }
    }

    // Check if a word exists in the Trie
    bool contains(const string &word) const
    {
        return countWordsEqualTo(word) > 0;
    }

    // Clear the entire Trie
    void clear()
    {
        delete root;
        root = new Node();
    }
};