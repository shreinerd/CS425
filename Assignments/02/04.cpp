/////////////////////////////////////////////////////////////////////////////
//
//  lychrel.cpp
//
//  A program that searches for the largest (in terms of number of
//    iterations without exceeding a specified maximum) palindrome value.
//
//  The program reports a list of numbers that share the maximum number of
//    iterations, along with the size and final palindrome number
//

#include <algorithm>
#include <barrier>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

#include "LychrelData.h"

// A structure recording the starting number, and its final palindrome.
//   An vector of these records (typedefed to "Records") is built during
//   program execution, and output before the program terminates.
struct Record {
    Number n;
    Number palindrome;
};
using Records = std::vector<Record>;

// Application specific constants
const size_t MaxIterations = 7500;
const size_t MaxThreads = 10;
const size_t LastID = MaxThreads - 1;

//
// --- main ---
//
int main() {
    LychrelData data;

    std::cerr << "Processing " << data.size() << " values ...\n";

    size_t maxIter = 0;  // Records the current maximum number of iterations
    Records records; // list of values that took maxIter iterations

    size_t chunkSize = int(data.size() / MaxThreads + 1);

    std::mutex mutex;
    std::barrier barrier{MaxThreads};

    // Iterate across all available data values, processing them using the 
    //   reverse-digits and sum technique described in class.
    for (auto id = 0; id < MaxThreads; ++id) {
        std::thread t{[&,id]() {
            auto start = id * chunkSize;
            auto end = std::min(data.size(), start + chunkSize);

            for (auto i = start; i < end; ++i) {
                Number number = data[i];
                
                size_t iter = 0;
                Number n = number;
        
                // The Lychrel loop - for any iteration, take the number, reverse
                //   its digits, and sum those values together.  If that sum
                //   is a palindrome, stop processing
                while (!n.is_palindrome() && ++iter < MaxIterations) {
                    Number sum(n.size());   // Value used to store current sum of digits
        
                    bool carry = false;  // flag to indicate if we had a carry

                    auto f = n.begin();
                    auto r = n.rbegin();
                    auto s = sum.rbegin();
        
                    for (int j = 0; j < n.size(); ++j) {
                        auto v = *f++ + *r++ + carry;

                        carry = v > 9;
                        if (carry) { v -= 10; }

                        *s++ = v;
                    }
        
                    // If there's a final carry value, prepend that to the sum
                    if (carry) { sum.push_front(1); }
        
                    // Transfer the sum making it the next number to be processed
                    //   (i.e., reversed, summed, and checked if it's a
                    //   palindrome)
                    n = sum;
                }

                {
                    std::lock_guard lock{mutex};

                    // Update our records.  First, determine if we have a new
                    //   maximum number of iterations that isn't the control limit
                    //   (MaxIterations) for a particular number.  If we're less
                    //   tha the current maximum (maxIter) or we've exceeded the number
                    //   of permissible iterations, ignore the current result and move
                    //   onto the next number.
                    if (iter < maxIter || iter == MaxIterations) { continue; }
        
                    // Otherwise update our records, which possibly means discarding
                    //   our current maximum and rebuilding our records list.
                    Record record{number, n};
                    if (iter > maxIter) {
                        records.clear();
                        maxIter = iter;
                    }
            
                    records.push_back(record);
                }
            }
            barrier.arrive_and_wait();
        }};

        (id < LastID) ? t.detach() : t.join();
    }

    // Output our final results
    std::cout << "\nmaximum number of iterations = " << maxIter << "\n";
    for (auto& [number, palindrome] : records) {
        std::cout 
            << "\t" << number
            << " : [" << palindrome.size() << "] "
            << palindrome << "\n";
    }
}