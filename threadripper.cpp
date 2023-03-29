#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

using std::vector, std::thread, std::ofstream;
using std::cout; 

constexpr char nl{ '\n' };

int num_of_threads = 8;

constexpr int a{ 1000 };
constexpr int b{ 1000 };
constexpr int c{ 1000 };

vector<vector<int>> m1(a, vector<int>(b));
vector<vector<int>> m2(b, vector<int>(c));
vector<vector<int>> mr(a, vector<int>(c));

void multiply(int tid)
{
    // calculate the range of rows for this thread
    int start = tid * a / num_of_threads;
    int end = (tid + 1) * a / num_of_threads;

    // Multiply the matrices
    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < b; k++)
            {
                mr[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main()
{
    // initialize the matrices with random values
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            m1[i][j] = i + j;
        }
    }
    
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m2[i][j] = i - j;
        }
    }

    // start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Create and start the threads
    vector<thread> threads;
    for (int i = 0; i < num_of_threads; i++)
    {
        threads.push_back(thread(multiply, i));
    }

    // wait for thrads to finish
    for (auto &thread : threads)
    {
        thread.join();
    }

    // end timer and calculate duration
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Calculation done in " << duration.count()<< " microseconds\n";

    // output the result to a file
    ofstream outfile("outputth.txt");
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < c; j++) {
            outfile << mr[i][j] << " ";
        }
        outfile << nl;
    }

    return 0;
}

// g++ -std=c++20 -pthread threadripper.cpp -o threadripper
// ./threadripper
