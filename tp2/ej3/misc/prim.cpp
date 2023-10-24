#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string currentLongestPrefix = strs[0];
        for (int i = 1; i < strs.size(); i++)
        {
            string currentPrefix = "";
            auto it = strs[i].begin();
            int k = 0;
            while (it != strs[i].end())
            {
                if (*it == currentLongestPrefix[k])
                {
                    currentPrefix.push_back(*it);                    
                }
                k++;
            }
            
            if (currentPrefix != currentLongestPrefix)
            {
                currentLongestPrefix = currentPrefix;
            }
        }
    }
};