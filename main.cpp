#include <iostream>
#include <cstdint>
#include <climits>
#include <ctime>
#include <cassert>

#define MAX (2000000)
#define STEP 100

#define LOOP(I, J, K)               \
for (int I = 0; I < MAX; I += STEP) \
for (int J = 0; J < 1;   J += STEP) \
for (int K = 1; K < MAX; K += STEP)

uint64_t f(uint64_t numLo, uint64_t numHi, uint64_t denom, uint64_t *rem)
{
    asm("");
    unsigned __int128 dividend128 = (((unsigned __int128)numHi)<<64) | ((unsigned __int128) numLo);
    unsigned __int128 divisor128 = (unsigned __int128)denom;
    *rem = (uint64_t)((dividend128 % divisor128) & 0xFFFFFFFFFFFFFFFF);
    return (uint64_t)((dividend128 / divisor128) & 0xFFFFFFFFFFFFFFFF);
}

extern "C" uint64_t __attribute__((ms_abi)) h(uint64_t low, uint64_t hi, uint64_t divisor, uint64_t *remainder);

int main(int argc, char **argv)
{
    LOOP(i,j,k)
    {
        uint64_t rem_f;
        uint64_t quot_f = f(i, j, k, &rem_f);

        uint64_t rem_h;
        uint64_t quot_h = h(i, j, k, &rem_h);
        
        if (!(quot_f == quot_h && rem_f == rem_h))
        {
            std::cout << "i, j, k: " << i << ", " << j << ", " << k << "\n"
                      << "quot_f, rem_f: " << quot_f << ", " << rem_f << "\n"
                      << "quot_h, rem_h: " << quot_h << ", " << rem_h << "\n";
            exit(-1);
        }
    }

    auto t1 = clock();
    LOOP(i,j,k)
    {
        uint64_t rem;
        f(i, j, k, &rem);
    }
    auto t2 = clock();
    
    auto t3 = clock();
    LOOP(i,j,k)
    {
        uint64_t rem;
        h(i, j, k, &rem);
    }
    auto t4 = clock();
    
    std::cout << t2 - t1 << ", " << t4 - t3 << "\n";

    return 0;
}
