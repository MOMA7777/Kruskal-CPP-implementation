#include <bits/stdc++.h>
#define SET unordered_set<pair<int,int>, pair_hash>
using namespace std;

void union_(int element, int target);
int DetectCycle(int u, int v);

vector<int> parent   (100,  0);
vector<int> camefrom (100, -1);

struct Edge {
    private:
    public:
        Edge(int uNode, int vNode, int weight) : u(uNode), v(vNode), w(weight) { }
        
        int u;
        int v;
        int w;
        
        const bool operator< (const Edge & other) const {
            return w < other.w; 
        }

};

//custom hash function for pair<int,int> because C++ default dont have one.
struct pair_hash {
    size_t operator()(const std::pair<int, int>& p) const {
        size_t hash1 = hash<int>()(p.first);
        size_t hash2 = hash<int>()(p.second);
        return hash1 ^ (hash2 << 1);     
    }
};

SET KrusKal(vector<Edge> G, int &numberOfVertex) {
    SET MST;
    

    int terminator = 0;
    for (const auto & [u, v, weight] : G) {
        if (terminator == numberOfVertex-1) break;

        if ( DetectCycle(u,v) ) {continue;}
        else {
           union_(u, v);
           MST.insert({u,v});
           terminator++;
        }
    }

    return MST;
}

int main() {

    int V, E;
    cin >> V >> E;

    vector<Edge> G;
    while ( E-- ) {
        int u, v, w;
        cin >> u >> v >> w;

        G.push_back( {u,v,w} );
        parent[u] = u, parent[v] = v;
    }

    sort(G.begin(), G.end());
    
//    for(const auto & [u,v,w] : G) {
//        cout << "["<<u<<","<<v<<"] --> " << w << endl;
//    }

    SET mst = KrusKal( G, V );

    printf("\n\nMinimum Spaning Tree : \n");
    for (const auto & [u,v] : mst) {
        cout << "["<<u<<","<<v<<"]" << endl;
    }

    return 0;
}



void union_(int x, int y) {
    int rootx = parent[x];
    int rooty = parent[y];

    if (rootx > rooty) {
       camefrom[x] = y;
       while ( camefrom[y] != -1) { parent[y] = x, y = camefrom[y]; }
    }
    else {
        camefrom[y] = x;
        while ( camefrom[x] != -1) { parent[x] = y, x = camefrom[x]; }
    }
}

int DetectCycle(int u, int v) {
    if (parent[u] == parent[v]) return 1;
    return 0;
} 

