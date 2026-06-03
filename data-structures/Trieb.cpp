class Trie{
    class Node{
        Node* link[2];
        
        public:
        Node(){
            link[0]=link[1]=NULL;
        }

        bool contains(ll v){
            return link[v]!=NULL;
        }

        void put(ll v){
            link[v]=new Node();
        }

        Node* getNext(ll v){
            return link[v];
        }


    };

    public:
    Node* root;
    Trie(){
        root=new Node();
    }

    void insert(ll num){
        Node* node=root;

        for(ll i=31;i>=0;i--){
            ll bit=(num>>i)&1;
            if(!node->contains(bit)){
                node->put(bit);
            }
            node=node->getNext(bit);
        }
    }

    ll getMax(ll num){
        Node* node=root;
        ll ans=0;
        for(ll i=31;i>=0;i--){
            ll bit=(num>>i)&1;
            if(node->contains(1-bit)){
                ans|=(1<<i);
                node=node->getNext(1-bit);
            }
            else if(node->contains(bit)){
                node=node->getNext(bit);
            }
        }
        return ans;
    }
};