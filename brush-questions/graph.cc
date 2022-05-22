#include <vector>
#include <queue>

using std::queue;
using std::vector;

// 《----------------------------------------------------------------------------------------------------------------------》
// 图的遍历 DFS BFS
    void DFS(const vector<vector<int> > & graph, int v, vector<bool> & visited) {
        if (visited[v]) return; // base case 递归出口
        visited[v] = true; // 标注为visited
        for (auto adjv : graph[v]) { // 遍历此顶点的邻节点
            DFS(graph, adjv, visited);
        }
    }
    void DFS(const vector<vector<int> > & graph, int v, vector<bool> & visited) {
        visited[v] = true; // 标注为visited
        for (auto adjv : graph[v]) { // 遍历此顶点的邻节点
            if (!visited[adjv]){ // 如果邻节点没有被访问过，DFS
                DFS(graph, adjv, visited);
            }
        }
    }
    void BFS(const vector<vector<int> > & graph, int v, vector<bool>& visited) {
        queue<int> que;
        que.push(v);
        while(!que.empty()) {
            int vertex = que.front();   que.pop(); // 从队中取出一个顶点
            visited[vertex] = true; // 标注为visited
            for (auto adjv : graph[vertex]) { // 遍历此顶点的邻节点，如果邻节点没有被访问过，入队
                if (!visited[adjv]) {
                    que.push(adjv);
                }
            }
        }
    }

// 《----------------------------------------------------------------------------------------------------------------------》
// 图的遍历 DFS
// 1、有向无环图（DAG) 无环 - > 所以，可以不用visited 数组
// 2、DAG的遍历（DFS）
    void traverse(vector<vector<int> >& graph, int vertex){
        if (vertex == graph.size() - 1) return; // 如果没有邻居节点 - 也就是题目中的递归出口
        for (auto neighbor : graph[s]) {  // 依次遍历所有邻居节点
            traverse(graph, neighbor);
        }
    }

// 3、回溯path
class Solution {
    vector<vector<int>> res1 = {};
    vector<int> onPath1 = {0};
    void traverse(vector<vector<int>>& graph, int vertex){
        if (vertex == graph.size() - 1) {
            res1.push_back(onPath1);
            return;
        }
        for (auto neighbor : graph[vertex]) {
            onPath1.push_back(neighbor); // 回溯的path
            traverse(graph, neighbor);
            onPath1.pop_back();
        }
    }
};

// 4、包括根节点的进入离开的路径path
class Solution {
    vector<vector<int> > res = {};
    vector<int> onPath = {};
    void traverse(vector<vector<int> >& graph, int vertex){
        onPath.push_back(vertex); // 所有节点的进入进出的信息path
        if (vertex == graph.size() - 1) {
            res.push_back(onPath);
            return;
        }
        for (auto neighbor : graph[vertex]) {
            traverse(graph, neighbor);
        }
        onPath.pop_back();
    }
};

// 总结 --- >> 带 路径参数 的 回溯DFS 有向无环图 图遍历框架
void dfs(const vector<vector<int> >& graph, const int vertex, vector<int> & path) {
    if (vertex == graph.size() - 1) {
        return;
    }
    for (auto neighbor : graph[vertex]) {
        path.push_back(neighbor); // 回溯的path
        dfs(graph, neighbor, path);
        path.pop_back();
    }
}

// 《----------------------------------------------------------------------------------------------------------------------》
// 拓扑排序 & 环路检测 使用入度 辅助数组
class Solution {
    void make_graph(const vector<vector<int> >& prerequisites, vector<vector<int> >& graph, vector<int> & vertex_in_degree) {
        for (auto prerequi : prerequisites) { // prerequi[0] <- prerequi[1]
            vertex_in_degree[prerequi[0]] ++;
            graph[prerequi[1]].push_back(prerequi[0]);
        }
    }
    bool isRing(const vector<vector<int> > & graph, vector<int> vertex_in_degree) {
        queue<int> degreeIsZeroQue;
        for (int i = 0; i < vertex_in_degree.size() ; ++i) { // 遍历入度为零的顶点，并且入队
            if (vertex_in_degree[i] == 0) degreeIsZeroQue.push(i);
        }
        if (degreeIsZeroQue.size() == 0) return true; // 如果所有的顶点入度都不为0， 那么肯定是存在环的
        int count = 0; // 计数 能够变成入度为0的个数
        while (degreeIsZeroQue.size() != 0) {
            int vertex = degreeIsZeroQue.front(); // 从队中取出一个入度为0的顶点
            degreeIsZeroQue.pop(); 
            count ++; // 计数 ++
            for(auto i : graph[vertex]) { // graph[vertex] 表示：图中 顶点vertex 邻居节点的vector
                vertex_in_degree[i] --; // 将邻居节点的度，都 -1
                if (vertex_in_degree[i] == 0) degreeIsZeroQue.push(i); // 如果邻居节点的度 为 0， 则入队
            }
        }
        return count == graph.size() ? false : true; // 能够变成入度为0的个数 如果 等于顶点个数，则没有环
    }
public:
    bool canFinish(int numCourses, vector<vector<int> >& prerequisites) {
        vector<vector<int> > graph(numCourses, vector<int>()); // vector<> 的技巧
        vector<int> vertex_in_degree(numCourses, 0);
        make_graph(prerequisites, graph, vertex_in_degree);
        return !isRing(graph, vertex_in_degree);
    }
};

// 《----------------------------------------------------------------------------------------------------------------------》
// 拓扑排序 & 环路检测 & DFS
class Solution {
    void DFS(const vector<vector<int> >& graph, int v, vector<bool>& visited, vector<bool>& onPath) {
        if (onPath[v] == true) {
            hasCycle = true;
            return;
        }
        if (visited[v]) return;
        visited[v] = true;
        onPath[v] = true;
        for (auto adjv : graph[v]) {
            DFS(graph, adjv, visited, onPath);
        }
        onPath[v] = false;
    }
    void buildGraph(vector<vector<int> >& graph, vector<vector<int> >& prerequisites) {
        for (auto prerequire : prerequisites) {
            graph[prerequire[1]].push_back(prerequire[0]);
        }
    }
    bool hasCycle = false;
public:
    bool canFinish(int numCourses, vector<vector<int> >& prerequisites) {
        vector<vector<int> > graph(numCourses, vector<int>());
        vector<bool> visited(numCourses, false);
        vector<bool> onPath(numCourses, false);
        buildGraph(graph, prerequisites);
        for (int v = 0; v < numCourses; ++v) {
            DFS(graph, v, visited, onPath);
        }
        return !hasCycle;
    }
};


// 《----------------------------------------------------------------------------------------------------------------------》
// 二分图判定 DFS
// -- leetcode.785
class Solution {
    void DFS(const vector<vector<int> >& graph, int v, vector<bool>& visited, vector<bool>& color) {
        if (ok == false) return; // 如果已经发现不是 二分图了，所以没必要再遍历下去了
        visited[v] = true;
        for (auto neighbour : graph[v]) { // 遍历邻居节点
            if (!visited[neighbour]) { // 如果邻居节点没有被访问过
                color[neighbour] = !color[v]; // 将邻居节点 着相反色
                DFS(graph, neighbour, visited, color);
            } else { // 如果邻居节点被访问过（说明已经着色了，需要判断邻居节点和它的颜色是否相反）
                if (color[neighbour] == color[v]) {
                    ok = false;
                }
            }
        }
    }
    bool ok = true;
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<bool> visited(graph.size(), false);
        vector<bool> color(graph.size(), false);
        for (int i = 0; i < graph.size(); ++i) {
            DFS(graph, i, visited, color);
        }
        return ok;
    }
};

// 《----------------------------------------------------------------------------------------------------------------------》
// 二分图判定 BFS 
// -- leetcode.785
class Solution {
    void BFS(const vector<vector<int> >& graph, int v, vector<bool>& visited, vector<bool>& color) {
        queue<int> que;
        que.push(v);
        while(!que.empty()) {
            if (ok == false) return;
            int vertex = que.front();  que.pop();
            visited[vertex] = true;
            for (auto neighbour : graph[vertex]) { // 遍历邻居节点
                if (!visited[neighbour]) { // 如果邻居节点没有被访问过
                    que.push(neighbour);
                    color[neighbour] = !color[vertex];  // 将邻居节点 着相反色
                } else {  // 如果邻居节点被访问过（说明已经着色了，需要判断邻居节点和它的颜色是否相反）
                    if (color[neighbour] == color[vertex]) {
                        ok = false;
                    }
                }
            }
        }
    }
    bool ok = true;
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<bool> visited(graph.size(), false);
        vector<bool> color(graph.size(), false);
        for (int i = 0; i < graph.size(); ++i) { // 因为图可能不是联通的
            BFS(graph, i, visited, color);
        }
        return ok;
    }
};

// 《----------------------------------------------------------------------------------------------------------------------》
// 拓扑排序 & 环路检测 & DFS & 输出拓扑排序 -- > DFS 后续遍历 的 逆序
class Solution {
    bool hasCycle = false;
    vector<int> topSort = {};
    void DFS(const vector<vector<int> >& graph, int v, vector<bool>& visited, vector<bool>& onPath) {
        if (onPath[v]) { hasCycle = true; return; }
        if (visited[v]) return;
        visited[v] = true;
        onPath[v] = true;
        for (auto adjV : graph[v]) {
            DFS(graph, adjV, visited, onPath);
        }
        onPath[v] = false;
        topSort.push_back(v);
    }
    void buildGraph(vector<vector<int> >& graph, vector<vector<int> >& prerequisites) {
        for (auto prerequi : prerequisites) {
            graph[prerequi[1]].push_back(prerequi[0]); // prerequi[0] <- prerequi[1] | 顶点prerequi[0] 是 顶点prerequi[1] 的邻节点
        }
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int> >& prerequisites) {
        vector<vector<int> > graph(numCourses, vector<int>());
        buildGraph(graph, prerequisites);

        vector<bool> visited(numCourses, false);
        vector<bool> onPath(numCourses, false);
        for (int i = 0; i < numCourses; ++i){
            DFS(graph, i, visited, onPath);
        }
        // std::reverse(topSort.begin(), topSort.end()); // DFS 后续遍历 的 逆序
        std::reverse(std::begin(topSort), std::end(topSort));
        return hasCycle == true ? vector<int>() : topSort;
    }
};

// 《----------------------------------------------------------------------------------------------------------------------》
// 带路径压缩的并查集
class UF_Set {
public:
    UF_Set(int N);
    ~UF_Set();
    void Union(int x, int y);
    int find(int x);
    bool isConnect(int x, int y);
    int count();
private:
    int* parent;
    int _count;
};
UF_Set::UF_Set(int N) {
    _count = N;
    parent = new int[N];
    for (int i = 0; i < N; ++i) {
        parent[i] = i;
    }
}
UF_Set::~UF_Set() { delete [] parent; }
void UF_Set::Union(int x, int y) {
    if (find(x) != find(y)) { // 多次调用find()，有利于路径压缩，并且本身find()的是复杂度就是O(1)
        parent[find(x)] = find(y);
    }
}
int UF_Set::find(int x) {
    while(x != parent[x]) {
        parent[x] = parent[parent[x]]; // 路径压缩
        x = parent[x];
    }
    return x;
}
bool UF_Set::isConnect(int x, int y) {
    return find(x) == find(y);
}
int UF_Set::count() { return _count; }