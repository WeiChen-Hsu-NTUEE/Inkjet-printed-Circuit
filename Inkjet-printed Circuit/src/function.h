#ifndef FUNCTION_H
#define FUNCTION_H

#include <fstream>
#include <iostream>
#include <list>
#include<iterator>
#include <vector>
#include<string>
#include<stack>
#include<algorithm>

using namespace std;

int CountObject(fstream &fin_object, fstream &fout_objVertex, 
                vector< vector <double> > &objVertex_x, 
                vector< vector <double> > &objVertex_y);
void ProximityConflict(fstream &fin_conflict, 
                       int num_object, 
                       vector < list<int> > &proximity_adjList);
void LaplaceConflict(fstream &fin_conflict, 
                     int num_object, 
                     vector < list<int> > &laplace_adjList);
void Print_gurobi_MILP(fstream &fout_gurobi_MILP, 
                       int num_object,
                       int num_proximity_conflict,
                       vector < list<int> > &proximity_adjList, 
                       vector < list<int> > &laplace_adjList);
vector<int> TopologicalSort(vector<list<int> > &conflict_adjList, 
                             int num_object);
void DFS(vector<list<int> > &conflict_adjList, 
         int num_object, 
         int &time, 
         vector<int> &color, 
         vector<int> &discover_time, 
         vector<int> &finish_time, 
         vector<int> &predecessor);
void DFS_Visit(vector<list<int> > &conflict_adjList, 
               int num_object, 
               int u, 
               int &time, 
               vector<int> &color, 
               vector<int> &discover_time, 
               vector<int> &finish_time, 
               vector<int> &predecessor);
void InsertionSort_with_DescendingOrder_by_FinishTime(vector<int> &finish_time, 
                                                      vector<int> &Topological_order);
bool CheckTopologicalOrder(vector<list<int> > &conflict_adjList, 
                           vector<int> &topological_order, 
                           int num_object);
vector<int> LaplaceLayerAssignment(vector<list<int> > &laplace_adjList, 
                            vector<int> &Topological_order, 
                            int num_object);
vector<list<int> > InverseEdge(vector<list<int> > &conflict_adjList);
void CheckConflictInALayer(vector<list<int> > &conflict_adjList, 
                           vector<int> &layer_num, 
                           int total_layer_num);
void ProximityLayerAssignment(vector<list<int> > &proximity_conflict, 
                              vector<int> &laplace_layer_num, 
                              vector<int> inverse_laplace_layer_num, 
                              int total_layer_num);

#endif