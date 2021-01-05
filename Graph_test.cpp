#include "Graph.h"

void mst_test_1()
{
    vector<Edge> edges = {
            {0,1,4} ,{1,2,8} ,{2,3,7},{3,4,9},
            {4,5,10},{3,5,14},{2,5,4},{2,8,2},
            {8,6,6} ,{7,8,7} ,{5,6,2},{7,6,1},
            {1,7,11},{0,7,8}
    };
    Graph G(9,edges);
    cout << "MST Test 1:\n";
    cout << "Example Graph adjcent list:\n";
    G.print_edges();


    Graph* mst = mst_prim(&G,0);
    cout << "A minimum spanning tree generated from example using Prim's Algorithm:" << endl;
    mst->print_edges();

    cout << SEPERATION;
}

void mst_test_2()
{
    vector<Edge> edges = {
            {0,1,1},{0,4,3},{0,3,4},
            {1,3,4},{3,4,4},{1,4,2},
            {2,4,4},{2,5,5},{4,5,7}
    };
    Graph G(6,edges);
    cout << "MST Test 2:\n";
    cout << "Example Graph adjcent list:\n";
    G.print_edges();


    Graph* mst = mst_prim(&G,0);
    cout << "A minimum spanning tree generated from example using Prim's Algorithm:" << endl;
    mst->print_edges();

    cout << SEPERATION;
}


int main()
{
    mst_test_1();
    mst_test_2();
    return 0;
}
