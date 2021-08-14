#include <iostream>
#include <set>
#include <random>
#include <cmath>
#include <vector>
#include "BST.hpp"

#include "util.hpp"

using namespace std;

int main() {

    int numOfDifferentN = 200;
    int numTrialsForEachN = 30;
    //Set n to 100
    int n = 100;
    //initialize a vector to store runtime result for BST and RBT
    vector<long long> runTimeForBST(numOfDifferentN, 0);
    vector<long long> runTimeForRBT(numOfDifferentN, 0);
    double totalTime = 0.0;
    Timer t;

    vector<int> nValues(numOfDifferentN, 0);
    for(int i = 0; i < numOfDifferentN; i++){
        nValues[i] = n;
        n = n + 50;
    }

    n = 100;
    default_random_engine generator;

    //get runtime for BST(insertion)(average)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){
        totalTime = 0.0;
    
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            uniform_real_distribution<double> distribution(1, n);
            generator.seed(1 + trialIndex);
            vector<double> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                double value = distribution(generator);
                nodes[i] = value;
            }

            BST<double> bst;
            for (int i = 0; i < n;i++){
                bst.insert(nodes[i]);
            }

            t.begin_timer();

            bst.insert(n+1);
            
            totalTime = totalTime + t.end_timer();

        }

        runTimeForBST[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    n = 100;
    totalTime = 0.0;

    //get runtime for RBT(insertion)(average)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){
        totalTime = 0.0;
    
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            uniform_real_distribution<double> distribution(1, n);
            generator.seed(1 + trialIndex);
            vector<double> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                double value = distribution(generator);
                nodes[i] = value;
            }

            set<double> rbt;
            for (int i = 0; i < n;i++){
                rbt.insert(nodes[i]);
            }

            t.begin_timer();
        
            rbt.insert(n+1);

            totalTime = totalTime + t.end_timer();

        }

        runTimeForRBT[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    //output statistics
    cout << "Data For BST's insertion(average)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForBST[i] << endl;
    }

    cout << "Data For RBT's insertion(average)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForRBT[i] << endl;
    }


    n = 100;
    totalTime = 0.0;
    //get runtime for BST(find)(average)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){
        totalTime = 0.0;
    
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            uniform_real_distribution<double> distribution(1, n);
            generator.seed(1 + trialIndex);
            vector<double> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                double value = distribution(generator);
                nodes[i] = value;
            }

            BST<double> bst;
            for (int i = 0; i < n;i++){
                bst.insert(nodes[i]);
            }

            t.begin_timer();
        
            for(int i=0;i<n;i++){
                bst.find(nodes[i]);
            }

            totalTime = totalTime + t.end_timer() / ((double)n);

        }

        runTimeForBST[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    n = 100;
    totalTime = 0.0;
    
    //get runtime for RBT(find)(average)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){

        totalTime = 0.0;
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            uniform_real_distribution<double> distribution(1, n);
            generator.seed(1 + trialIndex);
            vector<double> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                double value = distribution(generator);
                nodes[i] = value;
            }

            set<double> rbt;
            for (int i = 0; i < n;i++){
                rbt.insert(nodes[i]);
            }

            t.begin_timer();
            
            for(int i=0;i<n;i++){
                rbt.find(nodes[i]);
            }
            
            totalTime = totalTime + t.end_timer() / ((double)n);

        }

        runTimeForRBT[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    //output statistics
    cout << "Data For BST's find(average)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForBST[i] << endl;
    }

    cout << "Data For RBT's find(average)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForRBT[i] << endl;
    }

    n = 100;
    totalTime = 0.0;
    //get runtime for BST(insertion)(worst)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){

        totalTime = 0.0;
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            
            vector<int> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                nodes[i] = i+1;
            }

            BST<int> bst;
            for (int i = 0; i < n;i++){
                bst.insert(nodes[i]);
            }

            t.begin_timer();
        
            bst.insert(n+1);

            totalTime = totalTime + t.end_timer();

        }

        runTimeForBST[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    n = 100;
    totalTime = 0.0;
    //get runtime for RBT(insertion)(worst)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){

        totalTime = 0.0;
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            
            vector<int> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                nodes[i] = i+1;
            }

            set<int> rbt;
            for (int i = 0; i < n;i++){
                rbt.insert(nodes[i]);
            }

            t.begin_timer();
        
            rbt.insert(n+1);

            totalTime = totalTime + t.end_timer();

        }

        runTimeForRBT[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    //output statistics
    cout << "Data For BST's insertion(worst)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForBST[i] << endl;
    }

    cout << "Data For RBT's insertion(worst)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForRBT[i] << endl;
    }

    n = 100;
    totalTime = 0.0;
    //get runtime for BST(find)(worst)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){

        totalTime = 0.0;
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            
            vector<int> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                nodes[i] = i+1;
            }

            BST<int> bst;
            for (int i = 0; i < n;i++){
                bst.insert(nodes[i]);
            }

            t.begin_timer();
        
            bst.find(n+1);

            totalTime = totalTime + t.end_timer();

        }

        runTimeForBST[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    n = 100;
    totalTime = 0.0;
    //get runtime for RBT(find)(worst)
    for(int nINdex = 0; nINdex < numOfDifferentN; nINdex++){

        totalTime = 0.0;
        for (int trialIndex = 0; trialIndex < numTrialsForEachN; trialIndex++) {
            
            vector<int> nodes(n,0);
        
            for(int i = 0; i < n; i++){
                nodes[i] = i+1;
            }

            set<int> rbt;
            for (int i = 0; i < n;i++){
                rbt.insert(nodes[i]);
            }

            t.begin_timer();
        
            rbt.find(n+1);

            totalTime = totalTime + t.end_timer();

        }

        runTimeForRBT[nINdex] = totalTime / ((double)numTrialsForEachN);
        n = n + 50;
    }

    //output statistics
    cout << "Data For BST's find(worst)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForBST[i] << endl;
    }

    cout << "Data For RBT's find(worst)" << endl;
    cout << "input size,mean elasped time(ns)"  << endl;
    for(int i = 0; i < numOfDifferentN; i++){
        cout << nValues[i] <<","<< runTimeForRBT[i] << endl;
    }


    return 0;
}
