#include <iostream>
#include <string>
#include <bitset>

using namespace std;
#define bit64 unsigned long long
#define bit32 uint32_t

bit64 swap_places(bit64 left, bit64 right) {
    bitset<32> inp1_bits = bitset<32>(left);
    bitset<32> inp2_bits = bitset<32>(right);
    bitset<64> res;
    
}

bit64 final_permut(bit64 inp) {
    int perm[64] = 
    {   40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<64> res;
    for(int i=0; i<64; i++) {
        res[63-i] = inp_bits[64-perm[i]];
    }
}

void print_bits(bitset<64> b) {
    for(int i=0; i<64; i++) {
        cout << " " << i;
    }
    cout << endl;
    for(int i=0; i<64; i++) {
        cout << " " << b[i];
    }
    cout << endl;
}

bit64 apply_parity(bit64 inp) {
    bitset<56> res;
    bitset<64> inp_bits = bitset<64>(inp);
    // print_bits(inp_bits);
    // Index 0: Left-Most Bit
    // Indexes go from left-most to right-most...
    int parity[56]=
    {   57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,           
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    };

    for(int i=0; i<56; i++) {
        res[55-i] = inp_bits[64-parity[i]];
    }
    //cout << "MY PARITY:" << res << endl;
    return res.to_ullong();
}

bit32 get_left(bit64 inp) {
    bitset<56> inp_bits = bitset<56>(inp);
    bitset<28> res;
    for(int i=0; i<28; i++) {
        res[27-i] = inp_bits[55-i];
    }
    return res.to_ulong();
}

bit32 get_right(bit64 inp) {
    bitset<56> inp_bits = bitset<56>(inp);
    bitset<28> res;
    for(int i=0; i<28; i++) {
        res[i] = inp_bits[i];
    }
    return res.to_ulong();
}

bit32 shift_by(bit32 inp, int n) {
    bitset<28> inp_bits = bitset<28>(inp);
    bitset<28> res;
    uint left_most_bit = inp_bits[27];
    uint second_left_most_bit = inp_bits[26];
    if(n == 1) {
        res = inp_bits << 1;
        res[0] = left_most_bit;
    } else if(n == 2) {
        res = inp_bits << 2;
        res[0] = second_left_most_bit;
        res[1] = left_most_bit;
    }
    return res.to_ulong();
}

bit64 combine(bit32 left, bit32 right) {
    bitset<56> combined;
    bitset<28> left_bits = bitset<28>(left);
    bitset<28> right_bits = bitset<28>(right);
    for(int i=0; i<28; i++) {
        combined[i] = right_bits[i];
    }
    for(int i=0; i<28; i++) {
        combined[55-i] = left_bits[27-i];
    }
    return combined.to_ullong();
}

bit64 combine_64(bit32 left, bit32 right) {
    bitset<64> combined;
    bitset<32> left_bits = bitset<32>(left);
    bitset<32> right_bits = bitset<32>(right);
    for(int i=0; i<32; i++) {
        combined[i] = right_bits[i];
    }
    for(int i=0; i<32; i++) {
        combined[63-i] = left_bits[31-i];
    }
    return combined.to_ullong();
}

bit64 compress(bit64 inp) {
    int comp[48]= 
    {   14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    };
    bitset<56> inp_bits = bitset<56>(inp);
    bitset<48> res;
    for(int i=0; i<48; i++) {
        res[47-i] = inp_bits[56-comp[i]];
    }
    return res.to_ullong();
}

void generate_round_keys(bit64 key, bit64 round_keys[16]) {
    bit64 dropped_key = apply_parity(key);
    //cout << "Dropped key: " << hex << dropped_key << endl;
    bit32 left = get_left(dropped_key);
    //cout << "Left: " << hex << left << endl;
    bit32 right = get_right(dropped_key);
    //cout << "Right: " << hex << right << endl;

    for(int i=0; i<16; i++) {
        int shift_amount;
        if(i==0 || i==1 || i==8 || i==15) shift_amount = 1;
        else shift_amount = 2;
        left = shift_by(left, shift_amount);
        //cout << "Shifted Left: " << hex << left << endl;
        right = shift_by(right, shift_amount);
        //cout << "Shifted right: " << hex << right << endl;
        bit64 combined = combine(left, right);
        //cout << "Combined: " << hex << (combined) << endl;
        bit64 round_key = compress(combined);
        //cout << "Round key:" << hex << (round_key) << endl;
        round_keys[i] = round_key;
        //cout << "*************" << endl;
    }
}

bit32 get_left_half(bit64 inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<32> res;
    for(int i=0; i<32; i++) {
        res[31-i] = inp_bits[63-i];
    }
    return res.to_ulong();
}

bit32 get_right_half(bit64 inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<32> res;
    for(int i=0; i<32; i++) {
        res[i] = inp_bits[i];
    }
    return res.to_ulong();
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

bit64 final_permutation(bit64 &inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<64> out_bits;
    for(int i=0; i<8; i++) {
        final_permute_one_column(out_bits, inp_bits, i);
    }
    return out_bits.to_ullong();
}

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

bit64 initial_permutation(bit64 inp) {
    bitset<64> inp_bits = bitset<64>(inp);
    bitset<64> out_bits;
    for(int i=0; i<8; i++) {
        initial_permute_one_column(out_bits, inp_bits, i);
    }
    return out_bits.to_ullong();
}

bit64 apply_expansion(bit32 inp) {
    bitset<32> inp_bits = bitset<32>(inp);
    bitset<48> res;
    int expansion[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

    for(int i=0; i<48; i++) {
        res[47-i] = inp_bits[32-expansion[i]];
    }
    return res.to_ullong();
}

bit64 apply_sboxes(bit64 inp) {
    int permutation[32] = {
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
    };
    int sbox1[64] = { 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    };
    int sbox2[64] = {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    };
    int sbox3[64] = {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    };
    int sbox4[64] = {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    };
    int sbox5[64] = {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    };
    int sbox6[64] = {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    };
    int sbox7[64] = {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    };
    int sbox8[64] = {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    };
    int *sboxes[8] = {sbox1, sbox2, sbox3, sbox4, sbox5, sbox6, sbox7, sbox8};
    bit32 cols[8]; 
    bit32 rows[8];
    bit32 results[8];

    bitset<48> inp_bits = bitset<48>(inp);
    bitset<32> intermediate_result;
    bitset<48> result;
    int row_no = 0;
    // Determine which row & col of S-box to apply
    for(int i=47; i>=0; i-=6) {
        rows[row_no] = 2*inp_bits[i] + inp_bits[i-5]; // Row value, *'s are selected bits: (*----*)
        cols[row_no] = 8*inp_bits[i-1] + 4*inp_bits[i-2] + 2*inp_bits[i-3] + inp_bits[i-4]; // Column value, *'s are selected bits: (-****-)
        row_no++;
    }
    // Apply S-boxes
    for(int i=0; i<8; i++) {
        results[i] = sboxes[i][16*rows[i]+cols[i]];
    }
    // Combine S-box results
    int result_no = 0;
    for(int i=31; i>=0; i-=4) {
        bitset<4> current_result = bitset<4>(results[result_no]);
        intermediate_result[i] = current_result[3];
        intermediate_result[i-1] = current_result[2];
        intermediate_result[i-2] = current_result[1];
        intermediate_result[i-3] = current_result[0];
        result_no++;
    }
    //cout << "Sbox results combined: " << hex << intermediate_result.to_ullong() << endl;
    // Apply permutation
    for(int i=0; i<32; i++) {
        result[31-i] = intermediate_result[32-permutation[i]];
    }
    return result.to_ulong();
}

int main() {
    bit64 key;
    bit64 round_keys[16];
    bit64 plaintext;

    cout << "Enter key: ";
    cin >> hex >> key;
    cout << "Enter plaintext: ";
    cin >> hex >> plaintext;
    cout << "Your key:" << hex << key << endl;
    cout << "Your plaintext:" << hex << plaintext << endl;

    generate_round_keys(key, round_keys);
    for(int i=0; i<16; i++) {
        cout << "Round key " << i << " = " << hex << round_keys[i] << endl;
    }

    bit64 ip_result = initial_permutation(plaintext);
    cout << "After IP: " << ip_result << endl;

    bit32 right_half = get_right_half(ip_result);
    bit32 left_half = get_left_half(ip_result);
    for(int i=0; i<16; i++) {
        //cout << "Left half: " << left_half << endl;
        //cout << "Right half: " << right_half << endl;
        bit64 right_half_expanded = apply_expansion(right_half);
        //cout << "Expanded right half: " << right_half_expanded << endl;
        bit64 key_added = right_half_expanded ^ round_keys[i];
        //cout << "Key to add: " << round_keys[i] << endl;
        //cout << "Key added: " << key_added << endl;
        bit64 sbox_applied = apply_sboxes(key_added);
        //cout << "Sbox applied: " << hex << sbox_applied << endl;
        bit64 xored = sbox_applied ^ left_half;
        //cout << "XOR'd result: " << hex << xored << endl;
        left_half = right_half;
        right_half = xored;
        cout << "After Round " << i+1 << ": " << hex << left_half << right_half << endl;
    }

    bit64 res = combine_64(right_half, left_half);
    cout << "combined: " << res << endl;
    bit64 res_after_fp = final_permutation(res);
    cout << "Ciphertext: " << res_after_fp << endl;

}