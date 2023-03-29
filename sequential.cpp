#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using std::cout;
using std::vector, std::ofstream;

constexpr char nl{'\n'};

constexpr int a{ 1000 };
constexpr int b{ 1000 };
constexpr int c{ 1000 };

vector<vector<int>> m1(a, vector<int>(b));
vector<vector<int>> m2(b, vector<int>(c));

void multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{

    auto start = std::chrono::high_resolution_clock::now();
    // a×b matrix * c×d matrix = a×d matrix
    // iff b = c

    int a = matrix1.size();    // rows in 1
    int b = matrix1[0].size(); // cols in 1
    int c = matrix2.size();    // rows in 2
    int d = matrix2[0].size(); // cols in 2

    if (b == c)
    {
        vector<vector<int>> mr(a, vector<int>(d, 0));

        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < d; j++)
            {
                for (int k = 0; k < b; k++) mr[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        cout << "Calculation done in " << duration.count() << " microseconds" << nl;

        // output the result to a file
        ofstream outfile("outputseq.txt");
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < c; j++)
            {
                outfile << mr[i][j] << " ";
            }
            outfile << nl;
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

    multiply(m1, m2);
}

// g++ sequential.cpp -o seq
// ./seq