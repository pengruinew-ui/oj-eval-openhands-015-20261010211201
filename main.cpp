#include <bits/stdc++.h>
using namespace std;

const string DB_FILE = "db.txt";

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string, vector<int>> db;
    // Load existing data if file exists
    {
        ifstream fin(DB_FILE);
        if(fin){
            string idx; long long val;
            while(fin >> idx >> val){
                auto &vec = db[idx];
                // Insert while keeping sorted order and uniqueness
                int v = (int)val;
                auto it = lower_bound(vec.begin(), vec.end(), v);
                if(it == vec.end() || *it != v) vec.insert(it, v);
            }
        }
    }
    int n; if(!(cin>>n)) return 0;
    string cmd;
    for(int i=0;i<n;++i){
        cin>>cmd;
        if(cmd=="insert"){
            string idx; int val; cin>>idx>>val;
            auto &vec = db[idx];
            auto it = lower_bound(vec.begin(), vec.end(), val);
            if(it == vec.end() || *it != val) vec.insert(it, val);
        }else if(cmd=="delete"){
            string idx; int val; cin>>idx>>val;
            auto it = db.find(idx);
            if(it != db.end()){
                auto &vec = it->second;
                auto pos = lower_bound(vec.begin(), vec.end(), val);
                if(pos != vec.end() && *pos == val){
                    vec.erase(pos);
                    if(vec.empty()) db.erase(it);
                }
            }
        }else if(cmd=="find"){
            string idx; cin>>idx;
            auto it = db.find(idx);
            if(it == db.end() || it->second.empty()){
                cout << "null\n";
            }else{
                const auto &vec = it->second;
                for(size_t i=0;i<vec.size();++i){
                    if(i) cout << ' ';
                    cout << vec[i];
                }
                cout << "\n";
            }
        }
    }
    // Write back to file
    {
        ofstream fout(DB_FILE, ios::trunc);
        for(const auto &p : db){
            for(int v : p.second){
                fout << p.first << ' ' << v << '\n';
            }
        }
    }
    return 0;
}
