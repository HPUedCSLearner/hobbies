#include <vector>
#include <queue>

using std::queue;
using std::vector;

// 《----------------------------------------------------------------------------------------------------------------------》
// 图的遍历 DFS BFS
    void dfs(const vector<vector<int> > & graph, int v, vector<int> & visited) {
        if (visited[v]) return;
        visited[v] = true;
        for (auto adjv : graph[v]) {
            dfs(graph, adjv, visited);
        }
    }
    void bfs(const vector<vector<int> > & graph, int v, vector<int>& visited) {
        if (visited[v]) return;
        visited[v] = true;
        queue<int> que;
        for (auto adjv : graph[v]) {
            que.push(adjv);
        }
        while (que.size() != 0) {
            int vertex = que.front();
            que.pop();
            if (visited[vertex]) continue;
            visited[vertex] = true;
            for (auto adjv : graph[vertex]) {
                que.push(adjv);
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
// 拓扑排序 & 环路检测
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