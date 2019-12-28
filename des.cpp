#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

#define bit64 uint64_t

void initial_permute_one_column(bitset<64> &out_bits, bitset<64> inp_bits, int col) {
    int i = 58 - 8*col; // columns start from 0, goes up to 7
    int initial = i;
    int j = col;
    int count = 0;
    while(count < 8) {
        out_bits[j] = inp_bits[i-1];
        j += 8;
        i += 2;
        if(i == initial + 8) i = initial-1;
        count++;
    }
}

void final_permute_one_column(bitset<64> &out_bits, bitset<64> inp_bits, int col) {
    int inp_initial;
    int out_initial = col;
    switch(col) {
        case 0:
            inp_initial = 40;
            break;
        case 1:
            inp_initial = 8;
            break;
        case 2:
            inp_initial = 48;
            break;
        case 3:
            inp_initial = 16;
            break;
        case 4:
            inp_initial = 56;
            break;
        case 5:
            inp_initial = 24;
            break;
        case 6:
            inp_initial = 64;
            break;
        case 7:
            inp_initial = 32;
            break;
        default:
            cout << "Error in final perm.";
            return;
    }

    for(int i=0; i<8; i++) {
        out_bits[out_initial+8*i] = inp_bits[inp_initial-1];
        inp_initial--;
    }
}

bit64 initial_permutation(bit64 &inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<64> out_bits;
    for(int i=0; i<8; i++) {
        initial_permute_one_column(out_bits, inp_bits, i);
    }
    return out_bits.to_ullong();
}

bit64 final_permutation(bit64 &inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<64> out_bits;
    for(int i=0; i<8; i++) {
        final_permute_one_column(out_bits, inp_bits, i);
    }
    return out_bits.to_ullong();
}

int main() {
    bit64 inp;
    cin >> inp;
    cout << bitset<64>(inp) << endl;
    cout << hex << inp << endl;
    inp = initial_permutation(inp);
    cout << bitset<64>(inp) << endl;
    cout << hex << inp << endl;
    inp = final_permutation(inp);
    cout << bitset<64>(inp) << endl;
    cout << hex << inp << endl;
    return 0;
}