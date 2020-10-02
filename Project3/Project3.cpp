#include <iostream>
#include <cstring>
using namespace std;
#include<algorithm>



int _n; // num
const int MAX_SIZE = 15; // 입력 크기에 따라 충분히 (32 이상 될 수 없음)
int _distance[MAX_SIZE][MAX_SIZE]; // _distance
int _memory[MAX_SIZE][1 << MAX_SIZE]; // for memoization


int bitcount(int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}


int isPowerOfTwo(unsigned n)
{
    return n && (!(n & (n - 1)));
}

// Returns position of the only set bit in 'n' 
int getindex(unsigned n)
{
    if (!isPowerOfTwo(n))
        return -1;

    unsigned i = 1, pos = 1;

    // Iterate through bits of n till we find a set bit 
    // i&n will be non-zero only when 'i' and 'n' have a set bit 
    // at same position 
    while (!(i & n)) {
        // Unset current bit and set the next bit in 'i' 
        i = i << 1;

        // increment position 
        ++pos;
    }

    return pos;
}


void getInput() {
    cin >> _n;
    for (int i = 0; i < _n; i++) {
        for (int j = 0; j < _n; j++) {
            cin >> _distance[i][j];
        }
    }
    memset(_memory, 0, sizeof(int) * MAX_SIZE * (1 << MAX_SIZE));
}


int tsp(int from, int toFlag) {
    int& memo = _memory[from][toFlag]; // _memory[][] 가 0 로 초기화 되어 있어야 함.
    if (memo != 0) {
        return memo;
    }

    if (bitcount(toFlag) == 1) {
        int to = getindex(toFlag) - 1;
        return _distance[from][to];
    }


    memo = INT_MAX; // 그냥 충분히 큰 수를 사용해도 된다
    for (int i = 0; i < _n /* the nuber of cities */; i++) {
        if (!(toFlag & (1 << i))) continue;

        int v = _distance[from][i] + tsp(i, (toFlag & ~(1 << i)));
        memo = min(memo, v);
    }
    return memo;
}

int main() {
    getInput();
    int m = INT_MAX;
    int allFlag = (1 << _n) - 1;
    for (int i = 0; i < _n; i++) {
        int v = tsp(i, allFlag & ~(1 << i));
        m = min(m, v);
    }
    cout << m << endl;
    return 0;
}



//4
//0 29 82 46
//29 0 55 46
//82 55 0 68
//46 46 68 0




//input
//15
//0 29 82 46 68 52 72 42 51 55 29 74 23 72 46
//29  0 55 46 42 43 43 23 23 31 41 51 11 52 21
//82 55  0 68 46 55 23 43 41 29 79 21 64 31 51
//46 46 68  0 82 15 72 31 62 42 21 51 51 43 64
//68 42 46 82  0 74 23 52 21 46 82 58 46 65 23
//52 43 55 15 74  0 61 23 55 31 33 37 51 29 59
//72 43 23 72 23 61  0 42 23 31 77 37 51 46 33
//42 23 43 31 52 23 42  0 33 15 37 33 33 31 37
//51 23 41 62 21 55 23 33  0 29 62 46 29 51 11
//55 31 29 42 46 31 31 15 29  0 51 21 41 23 37
//29 41 79 21 82 33 77 37 62 51  0 65 42 59 61
//74 51 21 51 58 37 37 33 46 21 65  0 61 11 55
//23 11 64 51 46 51 51 33 29 41 42 61  0 62 23
//72 52 31 43 65 29 46 31 51 23 59 11 62  0 59
//46 21 51 64 23 59 33 37 11 37 61 55 23 59  0


//출처: https://baboc.tistory.com/274 [기다림과 눈물]