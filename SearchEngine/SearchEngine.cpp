#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class SearchEngine
{
    // word -> {doc -> frequency}
    unordered_map<string, unordered_map<int,int>> index;

public:

    void addDocument(int id, const string& text)
    {
        stringstream ss(text);
        string word;

        while(ss >> word)
            index[word][id]++;
    }

    vector<pair<int,int>> search(const string& query)
    {
        unordered_map<int,int> score;

        stringstream ss(query);
        string word;

        while(ss >> word)
        {
            if(!index.count(word))
                continue;

            for(auto& [doc,freq] : index[word])
                score[doc] += freq;
        }

        vector<pair<int,int>> result;

        for(auto& [doc,sc] : score)
            result.push_back({doc,sc});

        sort(result.begin(), result.end(),
        [](auto& a, auto& b)
        {
            if(a.second != b.second)
                return a.second > b.second;

            return a.first < b.first;
        });

        return result;
    }
};

int main()
{
    SearchEngine engine;

    engine.addDocument(1,"apple banana apple");
    engine.addDocument(2,"banana orange");
    engine.addDocument(3,"apple orange apple apple");
    engine.addDocument(4,"banana apple");

    cout << "Query: apple\n";

    auto r1 = engine.search("apple");

    for(auto [doc,score] : r1)
        cout << "doc " << doc << " score=" << score << "\n";

    cout << "\nQuery: apple banana\n";

    auto r2 = engine.search("apple banana");

    for(auto [doc,score] : r2)
        cout << "doc " << doc << " score=" << score << "\n";
}
