#include <iostream>
using namespace std;
short get_int_digit()
{
    static int idx = 0;
    long long random_num = 0;
    static const int bits = 19, size = 8;
    for(idx = bits*size-2;idx<bits*size+2;idx++) 
    {   // idx start from 1
        static long long pi[size] = { 3141592653589793238, 4626433832795028841, 8716939937510582097, 4944592307816406286
            , 2089986280348253421, 1706798214808651328, 2306647093844609550, 5822317253594081284 };

        if (idx > size*bits)
            idx = 1;
        
        short pi_part_idx = 0;
        short bitIdx = 0;
        if(idx % bits == 0)  // idx's integer times bits
        {
            pi_part_idx = idx / bits -1;
            bitIdx = 19;
        }
        else
        {
            pi_part_idx = idx / bits;
            bitIdx = idx%bits;
        }  
        long long power = std::pow(10, (bits - bitIdx));
        random_num = pi[pi_part_idx] / power;
        random_num %= 10;
    }
    return random_num;
}
int main(int argc,char *argv[])
{
    get_int_digit();
    std::cout<<"haha"<<endl;
}