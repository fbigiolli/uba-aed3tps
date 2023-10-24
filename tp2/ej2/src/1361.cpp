#include <queue>
#include <vector>

using namespace std;



class Solution {
public:

    void bfs(int v,vector<bool>& visitado,vector<int>& leftChild, vector<int>& rightChild) {
        visitado[v] = true;
        queue<int> q;
        q.push(v);
        while(!q.empty()) {
            int s = q.front();
            visitado[s] = true;
            q.pop();
            int currentLeftChild = leftChild[s];
            int currentRightChild = rightChild[s];
            
            if (currentLeftChild != -1 && !visitado[currentLeftChild])
            {
                q.push(currentLeftChild);
            }
            
            if (currentRightChild != -1 && !visitado[currentRightChild])
            {
                q.push(currentRightChild);
            }
        }
    }

    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<bool> visitado(n,false);
        bfs(0,visitado,leftChild,rightChild);
        bool res = true;
        for (int i = 0; i < visitado.size(); i++)
        {
            if (visitado[i] == false)
            {
                res = false;
                break;
            }
        }
        return res;
    }
};