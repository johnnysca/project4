#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

std::vector<int> parent, rank, path;

// function declaration
bool Union(int x, int y);
int Find(int x);

// to sort by cost of edge, min costs at top
struct comparator{
    bool operator()(const std::vector<int> &v1, const std::vector<int> &v2) const {
        return v1[2] > v2[2];
    }
};

bool Union(int x, int y){
    int parx = Find(x), pary = Find(y);
    if(parx == pary) return true; // same group

    if(rank[parx] > rank[pary]){
        rank[parx] += rank[pary];
        parent[pary] = parx;
    }
    else{
        rank[pary] += rank[parx];
        parent[parx] = pary;
    }
    return false;
}

int Find(int x){
    if(parent[x] != x) parent[x] = Find(parent[x]);
    return parent[x];
}

// KRUSKAL'S ALGO
int MST(std::vector<int> &parent, std::vector<int> &rank, std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, comparator> &minHeap, int edges){
    int cost = 0, n = 0;

    while(!minHeap.empty() && n != parent.size()-1){
        std::vector<int> curr = minHeap.top();
        minHeap.pop();
        if(!Union(curr[0], curr[1])){
            cost += curr[2];
            n++;
            path.push_back(curr[0]);
            path.push_back(curr[1]);
        }
    }
    std::cout << "path: ";
    for(auto &p : path) std::cout << p << " ";
    std::cout << std::endl;

    return cost;
}

void readFile(std::string &file){
    int vertices, edges, lines = 0, num;
    std::ifstream is(file);
    std::vector<int> data;
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, comparator> minHeap;

    while(is >> num){
        if(lines == 0) vertices = num;
        else if(lines == 1) edges = num;
        else{
            if(data.size() == 3){
                minHeap.push(data);
                data.clear();
            }
            data.push_back(num);
        }
        lines++;
    }
    minHeap.push(data);

    for(int i = 0; i<vertices; i++){
        parent.push_back(i);
        rank.push_back(1);
    }

    int cost = MST(parent, rank, minHeap, edges);
    std::cout << "cost: " << cost << "\n" << std::endl;

}

int main(){

    std::vector<std::string> files = {"sample_10.txt", "sample_100.txt", "sample_500.txt", "sample_1000.txt", "simpleinput_n=5.txt", "simpleinput_n=50.txt", "simpleinput_n=100.txt", "simpleinput_n=200.txt", "simpleinput_n=500.txt"};

    for(auto &file : files){
        readFile(file);
        parent.clear();
        rank.clear();
        path.clear();
    }
    return 0;
}
