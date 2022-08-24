class Bridge_Tree {
    int n;
    vector <vector <int>> components;
    vector <int> depth, low;
    stack <int> st;
    void find_bridges(int node, Graph &G, int par = -1, int d = 0) {
        low[node] = depth[node] = d;
        st.push(node);
        for (int e : G[node]) if(par != e) {
            if(depth[e] == -1) {
                find_bridges(e, G, node, d + 1);
                if (low[e] > depth[node]){
                    bridges.emplace_back(node, e);
                    components.push_back({});
                    for(int x = -1; x!= e; x = st.top(), st.pop()) 
                        components.back().push_back(st.top());
                }
            }
            low[node] = min(low[node], low[e]);
        }
        if(par == -1){
            components.push_back({});
            while(!st.empty())
                components.back().push_back(st.top()), st.pop();
        }   
    }
public:
    vector <int> id;
    vector <edge> bridges;
    Graph tree;
    void create_tree() {
        for(auto &comp : components){
            int idx = tree.add_node();
            for(auto &e: comp)
                id[e] = idx;
        }
        for(auto &[l,r]: bridges)
            tree.add_edge(id[l], id[r]);
    }
    Bridge_Tree(Graph &G): n(G.n) {
        depth.assign(n,-1), id.assign(n, -1), low.resize(n);
        for(int i = 0; i < n; i++)
            if(depth[i] == -1)
                find_bridges(i, G);
    }
};
