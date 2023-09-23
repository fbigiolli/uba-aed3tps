#include <vector>
#include <list>
#include <iostream>

using namespace std;

void dfs(vector<list<int>>& adjacency_list, vector<int>& status, vector<vector<int>>& tree_edges,vector<int>& back_edges_con_extremo_superior_en, vector<int>& back_edges_con_extremo_inferior_en, int v, int p)
{
    // Status en 2 significa que estamos viendo ese nodo, en -1 que no lo vimos todavia, y en 1 que ya lo vimos.
    status[v] = 2;
    for (int u:adjacency_list[v])
    {
        if (status[u] == -1)
        {
            tree_edges[v].push_back(u);
            dfs(adjacency_list,status,tree_edges,back_edges_con_extremo_superior_en,back_edges_con_extremo_inferior_en,u,v);
        }
        else if (u != p)
        {
            back_edges_con_extremo_inferior_en[v]++;
            back_edges_con_extremo_superior_en[u]++;
        }
    }
    status[v] = 1;
}

int cubren(vector<int>& memo, vector<vector<int>>& tree_edges,vector<int>& back_edges_con_extremo_superior_en, vector<int>& back_edges_con_extremo_inferior_en, int v, int p)
{
    if (memo[v] != -1)
        return memo[v];
    
    int res = 0;

    for (int hijo:tree_edges[v])
    {
        if (hijo != p)
        {
            res += cubren(memo,tree_edges,back_edges_con_extremo_superior_en,back_edges_con_extremo_inferior_en,hijo,v);
        }
    }
    
    res-= back_edges_con_extremo_superior_en[v];
    res += back_edges_con_extremo_inferior_en[v];

    memo[v] = res;
    return res;
}

void make_adjacency_list(vector<list<int>>& adjacency_list, int links_amount)
{
    for (int i = 0; i < links_amount; i++)
    {
        // Recibir los valores de las bases
        int base1;
        int base2;
        cin >> base1;
        cin >> base2;

        // Marcar como vecinas ambas bases
        adjacency_list[base1].push_back(base2);
        adjacency_list[base2].push_back(base1);
    }
}

int main()
{   
    int test_cases_amount;
    cin >> test_cases_amount;
    for (int i = 0; i < test_cases_amount; i++)
    {
        // Recibir los valores del test case
        int bases_amount;
        int links_amount;
        cin >> bases_amount;
        cin >> links_amount;

        // Inicializar memoria
        vector<list<int>> adjacency_list(bases_amount);
        vector<int> status(bases_amount,-1);
        vector<int> memo(bases_amount,-1);
        vector<vector<int>> tree_edges(bases_amount,vector<int>(links_amount));
        vector<int> back_edges_con_extremo_inferior_en(bases_amount,0);
        vector<int> back_edges_con_extremo_superior_en(bases_amount,0);

        // Construir la lista de adyacencias
        make_adjacency_list(adjacency_list,links_amount);

        // Resolver el problema
        dfs(adjacency_list,status,tree_edges,back_edges_con_extremo_superior_en,back_edges_con_extremo_inferior_en,0,-1);

        int important_links_amount = 0;
        vector<pair<int,int>> res;
        for (int i = 0; i < bases_amount; i++)
        {
            if (cubren(memo,tree_edges,back_edges_con_extremo_superior_en,back_edges_con_extremo_inferior_en, i, -1) == 2)
            {
                important_links_amount++;
            }
        }
        cout << important_links_amount;
    }   
    return 0;
}

