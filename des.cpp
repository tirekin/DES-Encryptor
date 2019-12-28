#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

#define bit64 uint64_t
#define bit32 uint32_t

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

bit64 expansion(bit32 &inp) {
    bitset<32> inp_bits = bitset<32>(inp);
    bitset<48> retval;

    retval[0] = inp_bits[31];
    retval[1] = inp_bits[0];
    retval[2] = inp_bits[1];
    retval[3] = inp_bits[2];
    retval[4] = inp_bits[3];
    retval[5] = inp_bits[4];

    retval[6] = inp_bits[3];
    retval[7] = inp_bits[4];
    retval[8] = inp_bits[5];
    retval[9] = inp_bits[6];
    retval[10] = inp_bits[7];
    retval[11] = inp_bits[8];

    retval[12] = inp_bits[7];
    retval[13] = inp_bits[8];
    retval[14] = inp_bits[9];
    retval[15] = inp_bits[10];
    retval[16] = inp_bits[11];
    retval[17] = inp_bits[12];

    retval[18] = inp_bits[11];
    retval[19] = inp_bits[12];
    retval[20] = inp_bits[13];
    retval[21] = inp_bits[14];
    retval[22] = inp_bits[15];
    retval[23] = inp_bits[16];

    retval[24] = inp_bits[15];
    retval[25] = inp_bits[16];
    retval[26] = inp_bits[17];
    retval[27] = inp_bits[18];
    retval[28] = inp_bits[19];
    retval[29] = inp_bits[20];

    retval[30] = inp_bits[19];
    retval[31] = inp_bits[20];
    retval[32] = inp_bits[21];
    retval[33] = inp_bits[22];
    retval[34] = inp_bits[23];
    retval[35] = inp_bits[24];

    retval[36] = inp_bits[23];
    retval[37] = inp_bits[24];
    retval[38] = inp_bits[25];
    retval[39] = inp_bits[26];
    retval[40] = inp_bits[27];
    retval[41] = inp_bits[28];

    retval[42] = inp_bits[27];
    retval[43] = inp_bits[28];
    retval[44] = inp_bits[29];
    retval[45] = inp_bits[30];
    retval[46] = inp_bits[31];
    retval[47] = inp_bits[0];

    return retval.to_ullong();
}

bit64 drop_parity_bits(bit64 key) {
    bitset<56> result;
    bitset<64> key_bits = bitset<64>(key);
    int result_index = 0;
    int i = 0;
    while(i < 64) {
        if(i==0 || i==8 || i==16 || i==24 || i==32 || i==40 || i==48 || i==56) {
            i++;
            continue;
        }
        result[result_index] = key_bits[i];
        result_index++;
        i++;
    }
    return result.to_ullong();
}

bit32 divide_left(bit64 key) {
    bitset<28> result;
    bitset<56> key_bits = bitset<56>(key);
    int key_index = 56;
    for(int i=0; i<28; i++) {
        cout << key_index << " ";
        result[i] = key_bits[key_index];
        key_index -= 8;
        if(key_index < 0) key_index += 65;
    }
    cout << endl;
    return result.to_ulong();
}

bit32 divide_right(bit64 key) {
    bitset<28> result;
    bitset<64> key_bits = bitset<64>(key);
    int key_index = 62;
    for(int i=0; i<28; i++) {
        cout << key_index << " ";
        result[i] = key_bits[key_index];
        key_index -= 8;
        if(key_index == -4) key_index = 27;
        else if(key_index < 0) key_index += 63;
    }
    cout << endl;
    return result.to_ulong();
}

bit32 left_shift_by(bit32 key, int n) {
    bitset<28> result;
    bitset<28> key_bits = bitset<28>(key);
    int left_most_bit = key_bits[27];
    int left_second_most_bit = key_bits[26];
    if(n==1) {
        result = key_bits << 1;
        result[0] = left_most_bit;
    } else if(n==2) {
        result = key_bits << 2;
        result[0] = left_second_most_bit;
        result[1] = left_most_bit;
    }
    return result.to_ulong();
}

bit64 combine(bit32 key1, bit32 key2) {
    bitset<48> result;
    bitset<56> combined;
    bitset<56> key1_bits = bitset<56>(key1);
    bitset<56> key2_bits = bitset<56>(key2);
    key1_bits = key1_bits << 28;
    combined = key1_bits ^ key2_bits;
    std::cout << key1_bits << endl;
    std::cout << key2_bits << endl;
    cout << "combined:" << combined << endl;
    result[0] = combined[13];
    result[1] = combined[16];
    result[2] = combined[10];
    result[3] = combined[23];
    result[4] = combined[0];
    result[5] = combined[4];

    result[6] = combined[2];
    result[7] = combined[27];
    result[8] = combined[14];
    result[9] = combined[5];
    result[10] = combined[20];
    result[11] = combined[9];

    result[12] = combined[22];
    result[13] = combined[18];
    result[14] = combined[11];
    result[15] = combined[3];
    result[16] = combined[25];
    result[17] = combined[7];

    result[18] = combined[15];
    result[19] = combined[6];
    result[20] = combined[26];
    result[21] = combined[19];
    result[22] = combined[12];
    result[23] = combined[1];

    result[24] = combined[40];
    result[25] = combined[51];
    result[26] = combined[30];
    result[27] = combined[36];
    result[28] = combined[46];
    result[29] = combined[54];

    result[30] = combined[29];
    result[31] = combined[39];
    result[32] = combined[50];
    result[33] = combined[44];
    result[34] = combined[32];
    result[35] = combined[47];

    result[36] = combined[43];
    result[37] = combined[48];
    result[38] = combined[38];
    result[39] = combined[55];
    result[40] = combined[33];
    result[41] = combined[52];

    result[42] = combined[45];
    result[43] = combined[41];
    result[44] = combined[49];
    result[45] = combined[35];
    result[46] = combined[28];
    result[47] = combined[31];

    return result.to_ullong();
}

bit32 divide_left_2(bit64 key) {
    bitset<56> key_bits = bitset<56>(key);
    key_bits = key_bits >> 28;
    return key_bits.to_ulong();
}

bit32 divide_right_2(bit64 key) {
    bitset<56> key_bits = bitset<56>(key);
    key_bits = key_bits << 28;
    key_bits = key_bits >> 28;
    return key_bits.to_ulong();
}

bit64 DES_encrypt(bit64 plaintext_block, bit64 key) {
    cout << "key: " << bitset<64>(key) << endl;
    key = drop_parity_bits(key);
    cout << "key: " << bitset<64>(key) << endl;
    bit32 left = divide_left_2(key);
    bit32 right = divide_right_2(key);
    for(int i=0; i<16; i++) {
        // Generate round keys
        cout << "left: " << bitset<28>(left) << endl;
        cout << "right: " << bitset<28>(right) << endl;
        if(i==0 || i==1 || i==8 || i==15) {
            left = left_shift_by(left, 1);
            right = left_shift_by(right, 1);
        } else {
            left = left_shift_by(left, 2);
            right = left_shift_by(right, 2);
        }
        cout << "shifted left: " << bitset<28>(left) << endl;
        cout << "shifted right: " << bitset<28>(right) << endl;
        bit64 round_key = combine(left, right);
        cout << hex << round_key << endl;
    }
}

int main() {
    bit64 inp;
    bit64 key;
    cin >> inp;
    cout << bitset<64>(inp) << endl;
    cout << bitset<64>(inp >> 1) << endl;
    cout << bitset<4>(15 << 1) << endl;
    //cout << hex << inp << endl;
    inp = initial_permutation(inp);
    //cout << bitset<64>(inp) << endl;
    //cout << hex << inp << endl;
    inp = final_permutation(inp);
    //cout << bitset<64>(inp) << endl;
    //cout << hex << inp << endl;
    divide_left(inp);
    divide_right(inp);
    cout << "Enter key: ";
    cin >> hex >> key;
    DES_encrypt(inp, key);
    return 0;
}