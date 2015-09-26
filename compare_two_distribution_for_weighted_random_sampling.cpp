//
//  compare_two_distribution_for_weighted_random_sampling.cpp
//  weighted_sampling_distribution
//
//  Created by Weigang Liu on 9/26/15.
//  Copyright © 2015 Weigang Liu. All rights reserved.
//


/*
// this file is aimed at trying out weight discrete distribution in genetic search
// the distribution being compared is discrete_distribution<int> and piecewise_constant_distribution<>
*/

#include <iostream>
#include <random>
#include <time.h>
using namespace std;


int main(int argc, const char * argv[]) {
    vector<int> index;
    vector<double> weight;
    vector<double> freq_d, prob_d;
    vector<double> freq_c, prob_c, prob_w;
    int sumC = 0, sumD = 0;
    double sumW = 0.0;
    default_random_engine gen;
    gen.seed(static_cast<unsigned>(time(NULL)));
    
    // generating weights for int 0, 1, 2..., 5
    uniform_real_distribution<> weight_dist(0.0, 1.0);
    for (int i = 0; i < 5; ++i) {
        freq_d.push_back(0);
        freq_c.push_back(0);
        index.push_back(i);
        weight.push_back(weight_dist(gen));
    }
    
    discrete_distribution<int> discrete_dist(weight.begin(), weight.end());
    piecewise_constant_distribution<> const_dist(index.begin(), index.end(),
                                                 weight.begin());
    
    // keep track of the number of occurence of each int
    for (int i = 0; i < 1000000; ++i) {
        int c = const_dist(gen);
        int d = discrete_dist(gen);
        freq_c[c]++;
        freq_d[d]++;
    }
    
    
    for (int i = 0; i < 5; ++i) {
        sumC += freq_c[i];
        sumD += freq_d[i];
        sumW += weight[i];
    }
    
    // calculate sampling probability based on 1000000 samples
    for (int i = 0; i < 5; ++i) {
        prob_d.push_back(freq_d[i]/sumD);
        prob_c.push_back(freq_c[i]/sumC);
        prob_w.push_back(weight[i]/sumW);
    }
    
    
    // comparing the results of sampling using discrete_distribution<> and 
    // piecewise_constant_distribution<>; it turns out that in most cases
    // discrete_distribution has better performance
    cout << "prob c: ";
    for ( auto i : prob_c) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "prob_d: ";
    for (auto i : prob_d) {
        cout << i << ' ';
    }
    cout << endl;
    
    cout << "prob_w: ";
    for (auto i : prob_w) {
        cout << i << ' ';
    }
    cout << endl;
    
    return 0;
}
