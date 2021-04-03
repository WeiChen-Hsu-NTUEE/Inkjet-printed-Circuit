#include "function.h"

//===count the ber of the objects, and also record the vertices of the objects===//

int CountObject(fstream &fin_object,
                fstream &fout_objVertex,
                vector<vector<double> > &objVertex_x,
                vector<vector<double> > &objVertex_y) {
    fout_objVertex << "# chip's layout" << endl;
    string str;
    int num_object = 1;  // start from 1 for the boundary of the chip
    objVertex_x.resize(num_object);
    objVertex_y.resize(num_object);

    while (getline(fin_object, str)) {
        //===count the number of the objects===//
        if (str[0] == 'o') {
            num_object++;
            objVertex_x.resize(num_object);
            objVertex_y.resize(num_object);

            if (num_object >= 2) {
                objVertex_x[num_object - 2].push_back(objVertex_x[num_object - 2][0]);
                objVertex_y[num_object - 2].push_back(objVertex_y[num_object - 2][0]);
            }
        }

        //===record the vertices of the objects===//

        if (str[0] == 'l') {  // the chip itself would also be counted in

            int substr_startIndex = 0;
            for (substr_startIndex = 0; substr_startIndex < str.size(); substr_startIndex++) {
                if (str[substr_startIndex] == ' ') {
                    substr_startIndex++;
                    break;
                }
            }

            for (int substr_endIndex = substr_startIndex; substr_endIndex < str.size(); substr_endIndex++) {  // start from str[substr_startIndex], the number part
                if (str[substr_endIndex] == '+') {
                    string numericPart = str.substr(substr_startIndex, substr_endIndex - substr_startIndex);
                    double substrToNum = stod(numericPart);
                    objVertex_x[num_object - 1].push_back(substrToNum);
                    substr_startIndex = substr_endIndex + 1;
                } else if (str[substr_endIndex] == 'i') {
                    string numericPart = str.substr(substr_startIndex, substr_endIndex - substr_startIndex);
                    double substrToNum = stod(numericPart);
                    objVertex_y[num_object - 1].push_back(substrToNum);
                    break;
                }
            }
        }
    }

    objVertex_x[num_object - 1].push_back(objVertex_x[num_object - 1][0]);
    objVertex_y[num_object - 1].push_back(objVertex_y[num_object - 1][0]);

    for (int i = 0; i < num_object; i++) {
        for (int j = 0; j < objVertex_x[i].size(); j++) {
            fout_objVertex << objVertex_x[i][j] << " " << objVertex_y[i][j];
            fout_objVertex << endl;
        }
        fout_objVertex << endl;  // only one empty lines, making the entire chip in one block
    }

    fout_objVertex << endl;  // another empty lines, separating the following part (conflict relations) with the chip part
    return num_object;
}

//===build the adjacency list of proximity conflict===//

void ProximityConflict(fstream &fin_conflict,
                       int num_object,
                       vector<list<int> > &proximity_adjList) {
    string str;
    while (getline(fin_conflict, str)) {
        int objectConsidered = 0;
        bool readingObjectIndex = false;
        int lengthOfObjectIndex = 0;

        ///// end of the statement of proximity conflict /////
        if (str == "FIN") {
            break;
        }

        ///// defining a conflict /////
        if (str[0] == 'o') {
            for (int i = 0; i < str.size(); i++) {
                ///// start reading the index of an object/////
                if (str[i] == 'o' && readingObjectIndex == false) {
                    readingObjectIndex = true;
                }

                ///// continue reading the index /////
                else if ((i != str.length() - 1 && str[i] != ' ') &&
                         readingObjectIndex == true) {
                    lengthOfObjectIndex++;
                }

                ///// end of reading an index /////

                /// if the object is not the last one ///
                else if (str[i] == ' ' && readingObjectIndex == true) {
                    string numericPart = str.substr(i - lengthOfObjectIndex, i);
                    int substrToNum = stoi(numericPart);

                    /// do not know which object we are considering yet ///
                    if (objectConsidered == 0) {
                        objectConsidered = substrToNum;
                    }

                    /// already know which object we are considering ///
                    else {
                        proximity_adjList[objectConsidered].push_back(substrToNum);
                    }
                    readingObjectIndex = false;
                    lengthOfObjectIndex = 0;
                }

                /// if the object is the last one ///
                else if (i == str.length() - 1) {  // readingObjectIndex must be true
                    string numericPart = str.substr(i - lengthOfObjectIndex, i + 1);
                    int substrToNum = stoi(numericPart);
                    proximity_adjList[objectConsidered].push_back(substrToNum);
                    readingObjectIndex = false;
                    lengthOfObjectIndex = 0;
                }
            }
        }
    }
}

//===build the adjacency list of laplace conflict===//

void LaplaceConflict(fstream &fin_conflict,
                     int num_object,
                     vector<list<int> > &laplace_adjList) {
    string str;
    while (getline(fin_conflict, str)) {
        int objectConsidered = 0;
        bool readingObjectIndex = false;
        int lengthOfObjectIndex = 0;

        ///// end of the statement of proximity conflict /////
        if (str == "FIN") {
            break;
        }

        ///// defining a conflict /////
        if (str[0] == 'o') {
            for (int i = 0; i < str.size(); i++) {
                ///// start reading the index of an object/////
                if (str[i] == 'o' && readingObjectIndex == false) {
                    readingObjectIndex = true;
                }

                ///// continue reading the index /////
                else if ((i != str.length() - 1 && str[i] != ' ') &&
                         readingObjectIndex == true) {
                    lengthOfObjectIndex++;
                }

                ///// end of reading an index /////

                /// if the object is not the last one ///
                else if (str[i] == ' ' && readingObjectIndex == true) {
                    string numericPart = str.substr(i - lengthOfObjectIndex, i);
                    int substrToNum = stoi(numericPart);

                    /// do not know which object we are considering yet ///
                    if (objectConsidered == 0) {
                        objectConsidered = substrToNum;
                    }

                    /// already know which object we are considering ///
                    else {
                        laplace_adjList[objectConsidered].push_back(substrToNum);
                    }
                    readingObjectIndex = false;
                    lengthOfObjectIndex = 0;
                }

                /// if the object is the last one ///
                else if (i == str.length() - 1) {  // readingObjectIndex must be true
                    string numericPart = str.substr(i - lengthOfObjectIndex, i + 1);
                    int substrToNum = stoi(numericPart);
                    laplace_adjList[objectConsidered].push_back(substrToNum);
                    readingObjectIndex = false;
                    lengthOfObjectIndex = 0;
                }
            }
        }
    }
}

void Print_gurobi_MILP(fstream &fout_gurobi_MILP,
                       int num_object,
                       int num_proximity_conflict,
                       vector<list<int> > &proximity_adjList,
                       vector<list<int> > &laplace_adjList) {
    fout_gurobi_MILP << "import gurobipy as gp" << '\n'
                     << "from gurobipy import GRB\n"
                     << "import os, psutil\n"
                     << "import time\n\n"
                     << "start_time = time.time()\n\n"
                     << "process = psutil.Process(os.getpid())\n\n"
                     << "try:"
                     << "\n\n";
    //===create a new model===//
    fout_gurobi_MILP << "    m = gp.Model(\"mip1\")"
                     << "\n\n";

    //===create variables (layers) for every oblect===//
    for (int i = 1; i <= num_object; i++) {
        fout_gurobi_MILP << "    l" << i << " = m.addVar(vtype=GRB.INTEGER, name="
                         << "\"l" << i << "\")" << '\n';
    }

    //===ltot===//
    fout_gurobi_MILP << "    ltot = m.addVar(vtype=GRB.INTEGER, name=\"ltot\")" << '\n';

    //===an array of vars for the "or" constraints===//
    fout_gurobi_MILP << "    y = m.addVars(" << num_proximity_conflict * 2 << ", vtype=GRB.BINARY, name=\"y\")"
                     << "\n\n";

    //===set objective===//
    fout_gurobi_MILP << "    m.setObjective(ltot, GRB.MINIMIZE)"
                     << "\n\n";

    //===li <= ltot===//
    for (int i = 1; i <= num_object; i++) {
        fout_gurobi_MILP << "    m.addConstr(l" << i << " <= ltot)" << '\n';
    }

    fout_gurobi_MILP << "\n";

    //===proximity conflict===//
    int y_counter = 0;

    fout_gurobi_MILP << "    #proximity conflict:"
                     << "\n\n";

    for (int i = 1; i < proximity_adjList.size(); i++) {
        for (list<int>::iterator it = proximity_adjList[i].begin(); it != proximity_adjList[i].end(); it++) {
            if (*it == 0) continue;
            fout_gurobi_MILP << "    m.addConstr((y[" << y_counter << "] == 1) >> (l" << i << " + 1 <= l" << *it << "))" << '\n';
            y_counter++;
            fout_gurobi_MILP << "    m.addConstr((y[" << y_counter << "] == 1) >> (l" << *it << " + 1 <= l" << i << "))" << '\n';
            y_counter++;
            fout_gurobi_MILP << "    m.addConstr(y[" << y_counter - 2 << "] + y[" << y_counter - 1 << "] == 1)" << '\n';
        }
    }

    fout_gurobi_MILP << '\n';

    //===laplace conflict===//
    fout_gurobi_MILP << "    #laplace conflict:" << '\n';

    for (int i = 1; i < laplace_adjList.size(); i++) {
        for (list<int>::iterator it = laplace_adjList[i].begin(); it != laplace_adjList[i].end(); it++) {
            if (*it == 0) continue;
            fout_gurobi_MILP << "    m.addConstr(l" << i << " + 1 <= l" << *it << ")\n";
        }
    }

    fout_gurobi_MILP << '\n';

    fout_gurobi_MILP << "    m.optimize()\n\n";
    fout_gurobi_MILP << "    for v in m.getVars():\n"
                     << "        print('%s %g' % (v.varName, v.x))\n\n"
                     << "    print('Obj: %g' % m.objVal)\n\n"
                     << "except gp.GurobiError as e:\n"
                     << "    print('Error code ' + str(e.errno) + ': ' + str(e))\n\n"
                     << "except AttributeError:\n"
                     << "    print('Encountered an attribute error')\n\n"
                     << "print(\"gurobi CPU runtime: \", (time.time() - start_time), \"seconds\")\n"
                     << "print(\"memory: \", process.memory_info().rss, \"bytes\")  # in bytes";
}

//===============heuristic-based algorithm for the layer assignment===============//

vector<int> TopologicalSort(vector<list<int> > &conflict_adjList,
                            int num_object) {
    int time = 0;
    vector<int> color(num_object + 1, 0);  // 0 = white; 1 = gray; 2 = black
    vector<int> discover_time(num_object + 1, 0);
    vector<int> finish_time(num_object + 1, 0);
    vector<int> predecessor(num_object + 1, -1);
    DFS(conflict_adjList, num_object, time, color, discover_time, finish_time, predecessor);
    vector<int> topological_order(num_object + 1, 0);
    for (int i = 1; i < topological_order.size(); i++) {
        topological_order[i] = i;
    }
    /*
    cout << "finish_time: "; 
    for (int i = 0; i < finish_time.size(); i++) {
        cout << finish_time[i] << " ";
    }
    cout << '\n' << '\n';
    */
    InsertionSort_with_DescendingOrder_by_FinishTime(finish_time, topological_order);
    return topological_order;
}

void DFS(vector<list<int> > &conflict_adjList,
         int num_object,
         int &time,
         vector<int> &color,
         vector<int> &discover_time,
         vector<int> &finish_time,
         vector<int> &predecessor) {
    for (int u = 1; u < conflict_adjList.size(); u++) {
        if (color[u] == 0) {
            DFS_Visit(conflict_adjList, num_object, u, time, color, discover_time, finish_time, predecessor);
        }
    }
}

void DFS_Visit(vector<list<int> > &conflict_adjList,
               int num_object,
               int u,
               int &time,
               vector<int> &color,
               vector<int> &discover_time,
               vector<int> &finish_time,
               vector<int> &predecessor) {
    time++;
    discover_time[u] = time;
    color[u] = 1;
    for (list<int>::iterator it = conflict_adjList[u].begin(); it != conflict_adjList[u].end(); it++) {
        if (*it == 0) continue;
        if (color[*it] == 0) {
            predecessor[*it] = u;
            DFS_Visit(conflict_adjList, num_object, *it, time, color, discover_time, finish_time, predecessor);
        }
    }
    color[u] = 2;
    time++;
    finish_time[u] = time;
}

void InsertionSort_with_DescendingOrder_by_FinishTime(vector<int> &finish_time,
                                                      vector<int> &Topological_order) {
    // don't care about [0]
    for (int i = 2; i < finish_time.size(); i++) {
        int key1 = finish_time[i];
        int key2 = Topological_order[i];
        int j = i - 1;
        while (j >= 1 && key1 > finish_time[j]) {
            finish_time[j + 1] = finish_time[j];
            Topological_order[j + 1] = Topological_order[j];
            j--;
        }
        finish_time[j + 1] = key1;
        Topological_order[j + 1] = key2;
    }
}

bool CheckTopologicalOrder(vector<list<int> > &laplace_adjList,
                           vector<int> &topological_order,
                           int num_object) {
    bool if_order_corret = 1;  // 0: no; 1: yes
    vector<bool> object_already_appeared(num_object + 1, 0);
    for (int i = 1; i < topological_order.size(); i++) {
        object_already_appeared[topological_order[i]] = 1;
        for (list<int>::iterator it = laplace_adjList[topological_order[i]].begin(); it != laplace_adjList[topological_order[i]].end(); it++) {
            if (*it == 0) continue;
            if (object_already_appeared[*it] == 1) {
                if_order_corret = 0;
                return if_order_corret;
            }
        }
    }
    return if_order_corret;
}

vector<int> LaplaceLayerAssignment(vector<list<int> > &laplace_adjList,
                                   vector<int> &Topological_order,
                                   int num_object) {
    vector<int> layer_num(num_object + 1, 0);
    for (int i = 1; i < Topological_order.size(); i++) {
        for (list<int>::iterator it = laplace_adjList[Topological_order[i]].begin(); it != laplace_adjList[Topological_order[i]].end(); it++) {
            if (*it == 0) continue;
            if (layer_num[Topological_order[i]] >= layer_num[*it]) layer_num[*it] = layer_num[Topological_order[i]] + 1;
        }
        /*
        cout << "layer_num after " << i << " update: ";
        for (int j = 0; j < layer_num.size(); j++) {
            cout << layer_num[j] << " ";
        }
        cout << '\n';
        */
    }
    // cout << '\n';
    return layer_num;
}

vector<list<int> > InverseEdge(vector<list<int> > &conflict_adjList) {
    vector<list<int> > Inverse_conflict_adjList(conflict_adjList.size());
    for (int i = 1; i < conflict_adjList.size(); i++) {
        for (list<int>::iterator it = conflict_adjList[i].begin(); it != conflict_adjList[i].end(); it++) {
            if (*it == 0) continue;
            Inverse_conflict_adjList[*it].push_back(i);
        }
    }
    return Inverse_conflict_adjList;
}

void CheckConflictInALayer(vector<list<int> > &conflict_adjList,  // check whether the specific conflict exists in a layer
                           vector<int> &layer_num,
                           int total_layer_num) {
    vector<vector<int> > layer(total_layer_num + 1);
    for (int i = 1; i < layer_num.size(); i++) {
        layer[layer_num[i]].push_back(i);
    }
    for (int i = 0; i < layer.size(); i++) {
        cout << "layer " << i << " : ";
        for (int j = 0; j < layer[i].size(); j++) {
            cout << layer[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n'
         << '\n';

    for (int i = 1; i < conflict_adjList.size(); i++) {  // time complexity: O(V + E)
        for (list<int>::iterator it = conflict_adjList[i].begin(); it != conflict_adjList[i].end(); it++) {
            if (layer_num[i] == layer_num[*it]) {
                cout << "conflict detected between " << i << " and " << *it << " in layer " << layer_num[i] << '\n';
            }
        }
    }
    cout << '\n';
}

void ProximityLayerAssignment(vector<list<int> > &proximity_adjList,
                              vector<int> &laplace_layer_num,
                              vector<int> inverse_laplace_layer_num,
                              int total_layer_num) {
    vector<int> proximity_layer_num = laplace_layer_num;
    vector<bool> changeable(proximity_layer_num.size(), 1);  // 1 stands for changeable
    // debug on
    //cout << "changeable: ";
    //debug off
    for (int i = 0; i < proximity_layer_num.size(); i++) {
        if (laplace_layer_num[i] == inverse_laplace_layer_num[i]) {
            changeable[i] = 0;
        }
        //debug on
       // cout << changeable[i] << " ";
        //debug off
    }
    //debug on
    //cout << '\n' << '\n';
    //debug off

    /*debug on
    cout << "debug: proximity_layer_num = ";
    for (int i = 0; i < proximity_layer_num.size(); i++) {
        cout << proximity_layer_num[i] << " ";
    }
    cout << '\n'
         << '\n';
    //debug off*/

    //---go through proximity_adjList to see if there are objects having proximity conflict lie in the same layer---//
    for (int i = 1; i < proximity_adjList.size(); i++) {
        //debug on
        cout << "detecting if proximity conflict happens on object " << i << '\n';
        //debug off
        for (list<int>::iterator it = proximity_adjList[i].begin(); it != proximity_adjList[i].end(); it++) {
            if (*it == 0) continue;
            if (proximity_layer_num[i] == proximity_layer_num[*it]) {  // proximity_conflict happens in a layer
                //debug on
                cout << '\n' << "proximity conflict found between " << i << " and " << *it << '\n' << '\n';
                //debug off
                if (changeable[i] == 0) {
                    if (changeable[*it] == 0) {
                        proximity_layer_num[*it]++;                                 // both of the objects have unchangeable layer_num
                        for (int j = 1; j < proximity_layer_num.size(); j++) {  // move all the objects lying on the layers behind the one *it lies on
                            if (proximity_layer_num[j] >= proximity_layer_num[*it]) proximity_layer_num[j]++;
                        }
                        proximity_layer_num[*it]++;
                        continue;
                    }
                    // move *it
                    proximity_layer_num[*it]++;
                    for (list<int>::iterator it_it = proximity_adjList[*it].begin(); it_it != proximity_adjList[*it].end(); it_it++) {
                        if (proximity_layer_num[*it] != proximity_layer_num[*it_it]) {
                            continue;
                        }
                        if (proximity_layer_num[*it] == proximity_layer_num[*it_it]) {
                            if (proximity_layer_num[*it] == inverse_laplace_layer_num[*it]) {  // can't move to a later layer anymore
                                proximity_layer_num[*it]++;
                                for (int j = 1; j < proximity_layer_num.size(); j++) {         // move all the objects lying on the layers behind the one *it lies on
                                    if (proximity_layer_num[j] >= proximity_layer_num[*it]) proximity_layer_num[j]++;
                                }
                                continue;  // should be break?
                            }
                        }
                    }
                } 
                else {  // move i
                    proximity_layer_num[i]++;
                    for (list<int>::iterator i_it = proximity_adjList[i].begin(); i_it != proximity_adjList[i].end(); i_it++) {
                        if (proximity_layer_num[i] != proximity_layer_num[*i_it]) {
                            continue;
                        }
                        if (proximity_layer_num[i] == proximity_layer_num[*i_it]) {
                            if (proximity_layer_num[i] == inverse_laplace_layer_num[i]) {
                                proximity_layer_num[i]++;
                                for (int j = 1; j < proximity_layer_num.size(); j++) {
                                    if (proximity_layer_num[j] > proximity_layer_num[i]) proximity_layer_num[j]++;
                                }
                                continue;
                            }
                            proximity_layer_num[i]++;
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i < proximity_layer_num.size(); i++) { // ?????
        if (proximity_layer_num[i] == 0) proximity_layer_num[i] = laplace_layer_num[i];
    }

    //debug on
    cout << '\n' << "proximity_layer_num = ";
    for (int i = 0; i < proximity_layer_num.size(); i++) {
        cout << proximity_layer_num[i] << " ";
    }
    cout << '\n'
         << '\n';

    vector<vector<int> > layer(total_layer_num + 1);
    for (int i = 1; i < proximity_layer_num.size(); i++) {
        layer[proximity_layer_num[i]].push_back(i);
    }
    for (int i = 0; i < layer.size(); i++) {
        cout << "layer " << i << " : ";
        for (int j = 0; j < layer[i].size(); j++) {
            cout << layer[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n'
         << '\n';
    // debug off
}