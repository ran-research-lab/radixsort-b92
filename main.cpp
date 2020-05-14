#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <queue>
using namespace std;

// function ceilLogR:
//    given m and R computes ceiling(log_R(m))

unsigned int ceilLogR(unsigned int m, unsigned int R) {
    unsigned int i = 0;
    while(m > 0) {
        i++;
        m = m / R;
    }
    return i;
}


// function radixsort:
//    given a vector, and a radix: sorts the numbers using radix sort
void radixsort(vector<unsigned int> &v, unsigned int radix) {
    unsigned int mmax;
    unsigned int loops;

    mmax = v[0];
    for (auto e: v) { if (e > mmax) mmax = e; }

    // compute the number of loops for the radix sort
    loops = ceilLogR(mmax,radix);
    // create the buckets
    vector< queue<unsigned int> > buckets(radix);

    // the pow variable is used for computing the
    // digit that will be used to decide the bucket
    int pow = 1;

    for (int i = 0; i < loops; i++) {
        // a bucket sort using the ith digt
        for (auto e: v) {
            unsigned int chosenBucket = (e/pow)%radix;
            buckets[chosenBucket].push(e);
        }

        pow = pow * radix;
        v.clear();

        // read the numbers from the buckets back into the array
        for (auto &b: buckets) {
            while(!b.empty()) {
                v.push_back(b.front());
                b.pop();
            }
        }

    }

}


TEST_CASE( "largest", "[rec]" ) {
    vector<unsigned int> v{10, 435, 17, 670, 345, 128, 32, 50, 13, 120};
    radixsort(v,10);
    for (auto e: v)
        cout << e << endl;
}
