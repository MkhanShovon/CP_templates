// Sorting
bool sorta(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}
bool sortd(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first > b.first;
}
 
bool sortad(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}
 
bool sortda(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first > b.first;
}

// Comparator for the priority_queue
struct Compare
{
    bool operator()(const pll &a, const pll &b)
    {
        // First sort by the first element in descending order
        if (a.first != b.first)
            return a.first < b.first;
        // If first elements are equal, sort by the second element in ascending order
        return a.second > b.second;
    }
};