#ifndef ALGORITHM_LAB_DISJOINT_SET_H
#define ALGORITHM_LAB_DISJOINT_SET_H
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;

string SEPERATION = "----------------------------------------------------------\n";

template<typename T>
struct List_Set;

template <typename T>
struct List_Node{
    T val;
    List_Node<T>* next = nullptr;
    List_Set<T>* set;
};

template<typename T>
struct List_Set{
    List_Node<T> *head,*tail;
    unsigned int length;
};

template<typename T>
struct List_Sets{
    unordered_set<List_Set<T>*> LS_set;
    unordered_map<T,List_Node<T>*> node_map;

    void make_set(T val)
    {
        auto node = new List_Node<T>;
        node->val = val;
        List_Set<T>* LS = new List_Set<T>;

        LS->head = node;
        LS->tail = node;
        LS->length = 1;

        node->set = LS;

        node_map.insert(make_pair(val,node));
        LS_set.insert(LS);
    }

    List_Set<T>* find_set(T val)
    {
        if (!node_map[val])
            return nullptr;
        return node_map[val]->set;
    }

    void LS_union(T x,T y)
    {
        if (!node_map[x] || !node_map[y])
            throw invalid_argument("Non-existent node");

        bool longer = node_map[x]->set->length >= node_map[y]->set->length;
        List_Set<T>* fir_LS = (longer ? node_map[x]->set : node_map[y]->set);
        List_Set<T>* sec_LS = (!longer ? node_map[x]->set : node_map[y]->set);
        List_Node<T>* iter = sec_LS->head;
        while(iter)
        {
            iter->set = fir_LS;
            iter = iter->next;
        }

        fir_LS->length += sec_LS->length;
        fir_LS->tail->next = sec_LS->head;
        fir_LS->tail = sec_LS->tail;

        LS_set.erase(sec_LS);
    }

    void print_LS(List_Set<T>* ls)
    {
        List_Node<T>* node = ls->head;
        cout << "Set: ";
        while(node)
        {
            cout << node->val << " ";
            node = node->next;
        }
        cout << "Length: " << ls->length;
        cout << endl;
    }

    void print_LS()
    {
        for (auto iter = LS_set.begin();iter != LS_set.end();iter++)
            print_LS(*iter);
    }



};

template<typename T>
struct Tree_Node{
    T val;
    int rank;
    Tree_Node<T>* parent;
};


template<typename T>
struct Tree_Sets{
    unordered_set<Tree_Node<T>*> root_set;
    unordered_map<T,Tree_Node<T>*> node_map;

    void make_set(T val)
    {
        Tree_Node<T>* node = new Tree_Node<T>;
        node->val = val;
        node->rank = 0;
        node->parent = node;

        root_set.insert(node);
        node_map.insert(make_pair(val,node));
    }

    Tree_Node<T>* find_set(T val)
    {
        if (!node_map[val])
            return nullptr;
        Tree_Node<T>* node = node_map[val];
        if (node != node->parent)
            node->parent = find_set(node->parent->val);
        return node->parent;
    }

    void ts_union(T x,T y)
    {
        if (!node_map[x] || !node_map[y])
            throw invalid_argument("invalid set element");
        link(find_set(x),find_set(y));
    }

private:
    void link(Tree_Node<T>* x,Tree_Node<T>* y)
    {
        if (x->rank > y->rank)
        {
            y->parent = x;
            root_set.erase(y);
        }
        else
        {
            x->parent = y;
            if (x->rank == y->rank)
                y->rank++;
            root_set.erase(x);
        }
    }
};


#endif //ALGORITHM_LAB_DISJOINT_SET_H
