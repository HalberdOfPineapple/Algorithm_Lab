#include<iostream>
#include<list>
#include<vector>
#include<climits>
#include<unordered_map>
using namespace std;

typedef pair<int,int> dw_pair;
string SEPERATION = "----------------------------------------------------------\n";

struct Vertex{
    int index;
    int depth = INT_MAX;
    int color = 0;
    int finish_time = INT_MAX;
    int key;
    Vertex* pi = nullptr;
};

typedef struct Edge{
    int src, dest, weight;
} Edge;

int parent(int i){ return (i-1)/2; }
int left(int i){ return 2*i + 1; }
int right(int i){ return 2*i + 2; }

class MinHeap{
public:
    int heap_size;
    vector<Vertex*> data;
    unordered_map<int,int> heap_index_map;
    MinHeap(vector<Vertex*>& vec){
        data = vec;
        build_min_heap();
    }

    bool empty()
    {
        return !heap_size;
    }

    void swap(int i,int j)
    {
        Vertex* temp = data[i];
        data[i] = data[j];
        data[j] = temp;
        heap_index_map[data[i]->index] = i;
        heap_index_map[data[j]->index] = j;
    }

    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int minimum = i;
        if (l < heap_size && data[l]->key < data[i]->key)
            minimum = l;
        if (r < heap_size && data[r]->key < data[minimum]->key)
            minimum = r;
        if (minimum != i)
        {
            swap(i,minimum);
            heapify(minimum);
        }
    }

    void build_min_heap()
    {
        heap_size = data.size();
        for (int i = data.size()/2-1; i >= 0; i--)
            heapify(i);
        for (int i = 0; i < heap_size; i++)
            heap_index_map.insert(make_pair(data[i]->index,i));
    }

    Vertex* top()
    {
        return data[0];
    }

    void pop()
    {
        data[0] = data[heap_size-1];
        heap_size--;
        heapify(0);
    }

    /**Note: i refers ith vertex in the graph
     * index refers its index in the heap vector*/
    void update_key(int i)
    {
        int index = heap_index_map[i];
//        if (index >= heap_size)
//            throw invalid_argument("invalid index for vertex to be updated");
        while (index > 0 && data[index]->key < data[parent(index)]->key)
        {
            swap(index,parent(index));
            index = parent(index);
        }
        heap_index_map[i] = index;
    }

};


class Graph{
public:
    vector<Vertex*> vertices;
    vector<list<dw_pair>> adj_list;
    Graph(int num_vet);
    Graph(int num_vet,vector<Edge>& input_edges);
    void print_edges();
    void add_edge(Edge& edge);

    Graph* mst_prim(int r);
};

Graph::Graph(int num_vet)
{
    for (int i = 0; i < num_vet; i++)
    {
        Vertex* v = new Vertex();
        v->index = i;
        vertices.push_back(v);

        list<dw_pair> adj;
        adj_list.push_back(adj);
    }
}

void Graph::add_edge(Edge& edge) {
    if (edge.src >= adj_list.size() || edge.src < 0)
        throw invalid_argument("invalid src vertex id\n");
    if (edge.dest >= adj_list.size() || edge.dest < 0)
        throw invalid_argument("invalid dest vertex id\n");
    adj_list[edge.src].push_back(make_pair(edge.dest,edge.weight));
    adj_list[edge.dest].push_back(make_pair(edge.src,edge.weight));
}

Graph::Graph(int num_vet,vector<Edge>& input_edges)
{
    for (int i = 0; i < num_vet; i++)
    {
        Vertex* v = new Vertex();
        v->index = i;
        vertices.push_back(v);

        list<dw_pair> adj;
        adj_list.push_back(adj);
    }

    for (Edge edge : input_edges)
        add_edge(edge);
}

void Graph::print_edges()
{
    for (int i = 0; i < adj_list.size(); i++)
    {
        printf("Vertex %d: ",i);
        for (dw_pair pair : adj_list[i])
            printf("(%2d,%2d) ",pair.first,pair.second);
        printf("\n");
    }
    printf("\n");
}

Graph* mst_prim(Graph* G,int r)
{
    Graph* mst = new Graph(G->vertices.size());

    for (Vertex* u : G->vertices)
    {
        u->key = INT_MAX;
        u->pi = nullptr;
        u->color = 1;
    }

    Vertex* root = G->vertices[r];
    root->key = 0;

    MinHeap pq(G->vertices);

    while (!pq.empty())
    {
        Vertex* u = pq.top();
        pq.pop();
        u->color = 0;

        if (u->pi != nullptr)
        {
            Edge edge = {u->pi->index,u->index,u->key};
            mst->add_edge(edge);
        }

        for (dw_pair pair : G->adj_list[u->index])
        {
            Vertex* v = G->vertices[pair.first];
            if (v->color && pair.second < v->key)
            {
                v->pi = u;
                v->key = pair.second;
                pq.update_key(v->index);
            }
        }
    }

    return mst;
}