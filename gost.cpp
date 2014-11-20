#include "gost.h"
#include "tables.h"
#include <cmath>

// #define DEBUG

using namespace permutations_gost;

inline bool shift(char ch, int count) {
	return (ch >> count) & 1;
}

std::string gost::encrypt(const std::string& input, bool encode) {
	blocks.clear();
	split_input_string(input);
	std::string result;

	#ifdef DEBUG
		int count = 1;
		for(auto x: blocks) {
			cout << "BLOCK #" << count <<endl;
			cout << "Bit representation : [" << x.to_string() << "]" << endl; 
			cout << "String representation : [" << to_std_string(x) << "]" << endl;
			count++;
		}
	#endif
	// @TODO: Simple replacement 
	// For each block in blocks
	for (auto block: blocks ) {
		bitset<BLOCK_SIZE_32> A, B;
		// Split current block
		for (int i = 0; i < BLOCK_SIZE_32; ++i) {
			A.set(i, block[i]);
			B.set(i, block[i + BLOCK_SIZE_32]);
		}

		// 32 cycles
		for (int i = 0; i < BLOCK_SIZE_32; ++i) {
			// First we need to get KEYi
			bitset<BLOCK_SIZE_32> key_i = get_key_i(i, encode);
			unsigned long ai = A.to_ulong();
			unsigned long current_ki = key_i.to_ulong();
			// Calculate f(ai, ki)
			int p = (int) pow(2, 32);		
			unsigned long result_f = (ai + current_ki) % (int)floor(p);

			bitset<BLOCK_SIZE_32> current_s(result_f);

			for (int k = 0; k < 7; ++k) {
				bitset<4> a_local;
				for (int j = 0; j < 4; ++j) {
					a_local.set(j, current_s[k * 4  + j]);
				}
				unsigned long index = a_local.to_ullong();
				unsigned long a_result = s_blocks[k * 8 + index] ;

				bitset<4> b_local(a_result);
				for (int j = 0; j < 4; ++j) {
					current_s.set(k * 4 + j, b_local[j]);
				}
				for (int j = 0; j < 4; ++j) {
					b_local.set(j, current_s[k * 4  + j]);
				}

			}

			current_s = current_s << 11 | current_s >> 21;
			current_s = current_s ^= B;

			// on the last step 
			if(i != 31) {
				B = A;
				A = current_s;
			} else {
				B = current_s;
			}
		}
		for (int j = 0; j < BLOCK_SIZE_32; j++) {
			block.set(j, A[j]);
			block.set(j + BLOCK_SIZE_32, B[j]);
		}	

		result += to_std_string(block);
	}
	return result;
}

bitset<BLOCK_SIZE_32> gost::get_key_i(int i, bool encode) {
	bitset<BLOCK_SIZE_32> result;
	int code_number = encode ? key_numbers[i] : key_numbers[31 - i];
	for (int i = 0; i < BLOCK_SIZE_32; i++) {
		result.set(i, key[code_number * BLOCK_SIZE_32 + i]);
	}
	return result;
}


std::string gost::encode(const std::string& input) {
	return encrypt(input, true);
}

std::string gost::decode(const std::string& input) {
	return encrypt(input, false);
}

void gost::set_key(const std::string& input) {
	for (size_t i = 0; i < input.size(); ++i) {
		if(i == KEY_SIZE) break;
		char ch = input.at(i);
		for (int j = 1; j <= 8; ++j) {
			key.set( (i + 1) * 8 - j, (ch >> (j - 1)) & 1);
		}
	}
	#ifdef DEBUG
		cout << "Bit representation of key = " << key.to_string() << endl;
	#endif
}

void gost::split_input_string(const std::string& input) {
	// Get all 8-bytes block count
	int blocks_count = input.size() / 8;
	bool need_complete_last_block = (input.size() % 8) > 0; 
	// Fill blocks
	for (int i = 0; i < blocks_count; i++) {
		bitset<BLOCK_SIZE_64> block;
		for (int j = i * 8; j < i * 8 + 8; j++) {
			char ch = input.at(j);
			for (int k = 1; k <= 8; k++) {
				int bit_index = (j % 8 + 1) * 8 - k;
				bool bit_value = shift(ch, k -1 );
				block.set(bit_index, bit_value);
			}
		}
		blocks.push_back(block);
	}

	if(need_complete_last_block) {
		int i = 0;
		bitset<BLOCK_SIZE_64> block;
		for (int j = blocks_count * 8; j < (int)input.size(); j++, i++) {
			char ch = input.at(j);
			for (int k = 1; k <= 8; k++) {			
				block.set((i+1) * 8 - k, shift(ch, k -1 ));
			}
		}
		blocks.push_back(block);
	}
}

std::string gost::to_std_string(const bitset<BLOCK_SIZE_64>& block) {
	string result = "";
	for (int i = 0; i < 8; i++) {
		bitset<8> current_char;
		for (int j = 0; j < 8; j++) {
			current_char.set(7 - j,block[ i * 8 + j ]);
		}
		unsigned long char_key = current_char.to_ulong();
		result += (char)char_key;
	}
	return result;
}