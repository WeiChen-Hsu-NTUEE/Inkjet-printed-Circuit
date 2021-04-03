#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include "../lib/tm_usage.h"

#include "function.h"

using namespace std;

void help_message() {
    cout << "how to compile: make" << endl;
    cout << "how to run: "
            " ./bin/conflict_graph inputs/objects.txt inputs/conflict.txt "
         << endl;
    cout << "how to clean: make clean" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //===read the file===//

    fstream fin_object(argv[1]);    // objects.txt
    fstream fin_conflict(argv[2]);  // conflict.txt
    fstream fout_conflict_adjList;
    fout_conflict_adjList.open("outputs/conflict_adjList.txt", ios::out);
    fstream fout_objVertex;
    fout_objVertex.open("outputs/objVertex.txt", ios::out);
    fstream fout_gurobi_MILP;
    fout_gurobi_MILP.open("outputs/gurobi_MILP.py", ios::out);

    //===count the number of the objects===//

    //objVertex_x[0] and objVertex_y[0] are for the chip, all objects start from [1]

    vector<vector<double> > objVertex_x;
    vector<vector<double> > objVertex_y;
    int num_object = CountObject(fin_object, fout_objVertex, objVertex_x, objVertex_y) - 1;  // -1 is for reducing the chip's number
    cout << "num_object = " << num_object << '\n' << '\n';

    //===build the adjacency list for the two types of conflicts===//

    // nothing in the _adjList[0], the obj start from _adjList[1]

    vector<list<int> > proximity_adjList(num_object + 1);
    ProximityConflict(fin_conflict, num_object, proximity_adjList);
    vector<list<int> > laplace_adjList(num_object + 1);
    LaplaceConflict(fin_conflict, num_object, laplace_adjList);

    //===write the result to conflict_adjList.txt===//

    int num_proximity_conflict = 0;

    fout_conflict_adjList << "proximity conflict:" << '\n';
    for (int i = 1; i < proximity_adjList.size(); i++) {
        fout_conflict_adjList << "o" << i << ": ";
        for (list<int>::iterator it = proximity_adjList[i].begin(); it != prev(proximity_adjList[i].end(), 1); it++) {
            fout_conflict_adjList << "o" << *it << " --> ";
            if (*it != 0) num_proximity_conflict++;
        }
        fout_conflict_adjList << "o" << *prev(proximity_adjList[i].end(), 1) << endl;
        if (*prev(proximity_adjList[i].end(), 1) != 0) num_proximity_conflict++;
    }

    cout << "num_proximity_conflict = " << num_proximity_conflict << '\n';

    fout_conflict_adjList << '\n';

    int num_laplace_conflict = 0;

    fout_conflict_adjList << "laplace conflict:" << endl;
    for (int i = 1; i < laplace_adjList.size(); i++) {
        fout_conflict_adjList << "o" << i << ": ";
        for (list<int>::iterator it = laplace_adjList[i].begin(); it != prev(laplace_adjList[i].end(), 1); it++) {
            fout_conflict_adjList << "o" << *it << " --> ";
            if (*it != 0) num_laplace_conflict++;
        }
        fout_conflict_adjList << "o" << *prev(laplace_adjList[i].end(), 1) << endl;
        if (*prev(laplace_adjList[i].end(), 1) != 0) num_laplace_conflict++;
    }

    cout << "num_laplace_conflict = " << num_laplace_conflict << '\n';

    fout_conflict_adjList << '\n';

    //===write the start vertex for objects with conflict to the objVertex.txt, which is for gnuplot===/

    //---draw proximity conflict relation on the objects---//

    fout_objVertex << "# proximity conflict" << '\n'
                   << '\n';

    for (int i = 1; i < proximity_adjList.size(); i++) {
        // int it_index; // turn the iterator in adjList into int
        for (list<int>::iterator it = proximity_adjList[i].begin(); it != proximity_adjList[i].end(); it++) {
            // it_index = std::distance(proximity_adjList[i].begin(), it);
            if (*it == 0) continue;
            fout_objVertex << objVertex_x[i][0] << " " << objVertex_y[i][0] << endl;
            fout_objVertex << objVertex_x[*it][0] << " " << objVertex_y[*it][0] << endl;
        }
        if (*proximity_adjList[i].begin() == 0) continue;
        fout_objVertex << endl;
    }

    //---draw lapalace conflict relation on the objects---//

    fout_objVertex << endl;

    fout_objVertex << "# laplace conflict" << endl
                   << endl;

    for (int i = 1; i < laplace_adjList.size(); i++) {
        // int it_index; // turn the iterator in adjList into int
        for (list<int>::iterator it = laplace_adjList[i].begin(); it != laplace_adjList[i].end(); it++) {
            // it_index = std::distance(laplace_adjList[i].begin(), it);
            if (*it == 0) continue;
            fout_objVertex << objVertex_x[i][0] << " " << objVertex_y[i][0] << endl;
            fout_objVertex << objVertex_x[*it][0] << " " << objVertex_y[*it][0] << endl;
        }
        if (*laplace_adjList[i].begin() == 0) continue;
        fout_objVertex << endl;
    }

    //===write gurobi_MILP.txt===//

    Print_gurobi_MILP(fout_gurobi_MILP, num_object, num_proximity_conflict, proximity_adjList, laplace_adjList);
    fout_gurobi_MILP.close();

    //===heuristic-based algorithm for the layer assignment===//

    tmusg.periodStart();

    vector<int> topological_order = TopologicalSort(laplace_adjList, num_object);
    /*
    cout << "sort the object by TopologicalSort: ";
    for (int i = 0; i < topological_order.size(); i++) {
        cout << topological_order[i] << " ";
    }
    cout << '\n' << '\n';
    */

    /*
    bool if_order_correct = CheckTopologicalOrder(laplace_adjList, topological_order, num_object);
    cout << "if_order_correct: " << if_order_correct << '\n';
    */

    vector<int> laplace_layer_num = LaplaceLayerAssignment(laplace_adjList, topological_order, num_object);
    cout << "laplace_layer_num = ";
    for (int i = 0; i < laplace_layer_num.size(); i++) {
        cout << laplace_layer_num[i] << " ";
    }
    cout << '\n' << '\n';

    vector<int>::iterator it = max_element(laplace_layer_num.begin(), laplace_layer_num.end());
    int total_layer_num = *it;

    CheckConflictInALayer(laplace_adjList, laplace_layer_num, total_layer_num);

    vector<list<int> > inverse_laplace_adjList = InverseEdge(laplace_adjList);
    
    /*
    cout << "inverse_laplace_adjList: " << '\n';
    for (int i = 1; i < inverse_laplace_adjList.size(); i++) {
        cout << i << ": ";
        for (list<int>::iterator it = inverse_laplace_adjList[i].begin(); it != inverse_laplace_adjList[i].end(); it++) {
            cout << *it << " ";
        }
        cout << '\n';
    }
    */
    

    vector<int> inverse_Topological_order = TopologicalSort(inverse_laplace_adjList, num_object);

    /*
    cout << "sort the object by Inverse_TopologicalSort: ";
    for (int i = 0; i < inverse_Topological_order.size(); i++) {
        cout << inverse_Topological_order[i] << " ";
    }
    cout << '\n' << '\n';
    */

    /*
    if_order_correct = CheckTopologicalOrder(inverse_laplace_adjList, inverse_Topological_order, num_object);
    cout << "if_order_correct: " << if_order_correct << '\n';
    */

    vector<int> inverse_laplace_layer_num = LaplaceLayerAssignment(inverse_laplace_adjList, inverse_Topological_order, num_object);
    /*
    cout << "inverse_layer_num = ";
    for (int i = 0; i < inverse_layer_num.size(); i++) {
        cout << inverse_layer_num[i] << " ";
    }
    cout << '\n' << '\n';
    */

    it = max_element(inverse_laplace_layer_num.begin(), inverse_laplace_layer_num.end()); 
    // cout << "total_layer_num: " << *it << '\n' << '\n';

    total_layer_num = *it;
    for (int i = 1; i < inverse_laplace_layer_num.size(); i++) {
        inverse_laplace_layer_num[i] = total_layer_num - inverse_laplace_layer_num[i]; // if using *it instead of max_layer_num, *it would be updated as inverse_layer_num been updated
    }

    cout << "inverse_laplace_layer_num = ";
    for (int i = 0; i < inverse_laplace_layer_num.size(); i++) {
        cout << inverse_laplace_layer_num[i] << " ";
    }
    cout << '\n' << '\n';

    CheckConflictInALayer(inverse_laplace_adjList, inverse_laplace_layer_num, total_layer_num);

    ProximityLayerAssignment(proximity_adjList, laplace_layer_num, inverse_laplace_layer_num, total_layer_num);

    tmusg.getPeriodUsage(stat);
    cout <<"heuristic-based algorithm CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //======//
    fin_object.close();
    fin_conflict.close();
    fout_conflict_adjList.close();
    fout_objVertex.close();
    return 0;
}