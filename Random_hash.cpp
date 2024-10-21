random_device rd;
    mt19937 gen(rd());
    map<ull, ull> mapping;
    set<ull> s= {0};
    for(auto i: v){
        ull random;
        do{
            random = gen();
        }while(s.find(random)!=s.end());
        mapping[i] = random;
        s.insert(random);
    }