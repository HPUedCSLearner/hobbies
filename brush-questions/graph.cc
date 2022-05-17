#include <vector>

using std::vector;

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