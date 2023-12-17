#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class EulerianPathCycle {
public:
    vector<int> findEulerianPathCycle(const vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> path;
        vector<vector<int>> tempGraph = graph;

        int oddVertexCount = 0;
        int startVertex = 0;

        for (int i = 0; i < n; ++i) {
            int degree = 0;
            for (int j = 0; j < n; ++j) {
                degree += graph[i][j];
            }

            if (degree % 2 != 0) {
                ++oddVertexCount;
                startVertex = i;
            }
        }

        if (oddVertexCount > 2) {
            path.push_back(-1); // No solution
            return path;
        }

        if (oddVertexCount == 2) {
            startVertex = findEulerianStartVertex(graph);
        }

        dfs(startVertex, tempGraph, path);

        return path;
    }

private:
    int findEulerianStartVertex(const vector<vector<int>>& graph) {
        int n = graph.size();
        for (int i = 0; i < n; ++i) {
            int degree = 0;
            for (int j = 0; j < n; ++j) {
                degree += graph[i][j];
            }

            if (degree % 2 != 0) {
                return i;
            }
        }
        return 0;
    }

    void dfs(int vertex, vector<vector<int>>& graph, vector<int>& path) {
        for (size_t i = 0; i < graph.size(); ++i) {
            if (graph[vertex][i] != 0) {
                --graph[vertex][i];
                --graph[i][vertex];
                dfs(i, graph, path);
            }
        }
        path.push_back(vertex);  // Corrected here to add single vertices
    }
};

int main() {
    

    vector<int> inputVector;
    char c;
    int balanceBracket = 0;

    while (cin >> c) {
        if (c == '1') {
            inputVector.push_back(1);
        } else if (c == '0') {
            inputVector.push_back(0);
        } else if (c == '[') {
            balanceBracket++;
        } else if (c == ']') {
            balanceBracket--;
        }

        // Assuming the input is complete when balanceBracket becomes zero
        if (balanceBracket == 0) {
            break;
        }
    }

    // Assuming the inputVector represents a square matrix, you need to convert it into a 2D vector
    vector<vector<int>> adjacencyMatrix;
    size_t size = static_cast<size_t>(sqrt(inputVector.size()));

    for (size_t i = 0; i < size; ++i) {
        vector<int> row(inputVector.begin() + i * size, inputVector.begin() + (i + 1) * size);
        adjacencyMatrix.push_back(row);
    }

    EulerianPathCycle eulerianPathCycle;
    vector<int> result = eulerianPathCycle.findEulerianPathCycle(adjacencyMatrix);

    if (result[0] == -1) {
        cout << "No Solution" << endl;
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i];
            if (i < result.size() - 1) {
                cout << "---";
            }
        }
        cout << endl;
    }

    return 0;
}