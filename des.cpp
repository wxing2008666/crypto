#include "des.h"

// #define DEBUG

inline bool shift(char ch, int count) {
	return (ch >> count) & 1;
}

std::string des::calculating(const std::string& input, bool is_encode) {
	blocks.clear();
	split_input_string(input);
	std::string result;

	#ifdef DEBUG
		int count = 1;
		for(auto x: blocks) {
			cout << "BLOCK #" << count <<endl;
			cout << "Bit representation : [" << to_bit_string(x) << "]" << endl; 
			cout << "String representation : [" << to_std_string(x) << "]" << endl;
			count++;
		}
	#endif

	// Let's start
	// for each 64-bit block on blocks
	for(auto block: blocks) {
		// Do initial permutation on each block
		bitset<BLOCK_SIZE_64> current_block = initial_permutation(block);
		// Left and right parts
		bitset<BLOCK_SIZE_32> L_part, R_part; 
		// Fill all parts
		for (int j = 0; j < BLOCK_SIZE_32; j++) {
			L_part.set(j, current_block[j]);
			R_part.set(j, current_block[j + BLOCK_SIZE_32]);
		}
		// Generate keys i (28 bits)
		bitset<BLOCK_SIZE_28> LKi, RKi; 
		for (int j = 0; j < BLOCK_SIZE_28; j++) {
			LKi.set(j, key[c0[j] - 1]);
			RKi.set(j, key[d0[j] - 1]);
		}
		// Feistel conversion cycles
		for (int i = 0; i < 16; i++) {
			// Left cyclic shift
			if(is_encode) {
				LKi = LKi << encode_shifts[i] | LKi>>(BLOCK_SIZE_28 - encode_shifts[i]);
				RKi = RKi << encode_shifts[i] | RKi>>(BLOCK_SIZE_28 - encode_shifts[i]);	
			} else {
				LKi = LKi >> decode_shifts[i] | LKi << (BLOCK_SIZE_28 - decode_shifts[i]);
				RKi = RKi >> decode_shifts[i] | RKi << (BLOCK_SIZE_28 - decode_shifts[i]);	
			}

			bitset<BLOCK_SIZE_48> key_i = get_key(LKi, RKi);
			// cout << "LKi = " << LKi.to_string() << endl;
			bitset<BLOCK_SIZE_32> e_func = (is_encode) ? expansion_func(R_part, key_i) : expansion_func(L_part, key_i);

			bitset<BLOCK_SIZE_32> local_R_part, local_L_part;
			if(is_encode) {
				local_L_part = R_part;
				local_R_part = L_part ^= e_func;
			} else {
				local_L_part = R_part ^= e_func;
				local_R_part = L_part;
			}

			R_part = local_R_part;
			L_part = local_L_part;				
		}
		for (int j = 0; j < BLOCK_SIZE_32; j++) {
			current_block.set(j, L_part[j]);
			current_block.set(j + BLOCK_SIZE_32, R_part[j]);
		}
		current_block = inverse_permutation(current_block);
		result += to_std_string(current_block);
	}
	return result;
}
bitset<BLOCK_SIZE_48> des::get_key(bitset<BLOCK_SIZE_28> LKi, bitset<BLOCK_SIZE_28> RKi) {
	bitset<BLOCK_SIZE_48> result;
	bitset<BLOCK_SIZE_56> lki_rki_merge;
	for (int i = 0; i < BLOCK_SIZE_28; i++) {
		lki_rki_merge.set(i, LKi[i]);
		lki_rki_merge.set(i + BLOCK_SIZE_28, RKi[i]);
	}
	for (int i = 0; i < BLOCK_SIZE_48; i++) {
		result.set(i,lki_rki_merge[ki_permutations[i] - 1]);
	}
	return result;
}


bitset<BLOCK_SIZE_32> des::expansion_func(bitset<BLOCK_SIZE_32> Ri, bitset<BLOCK_SIZE_48> Ki) {
	bitset<BLOCK_SIZE_32> result;

	//	Extention function
	bitset<BLOCK_SIZE_48> Ri_extension; // from 32 to 48
	bitset<BLOCK_SIZE_48> result_extension;

	for (int i = 0; i < BLOCK_SIZE_48; i++) {
		Ri_extension.set(i, Ri[extension_table[i] - 1]);
	}

	//"^="  ~  "XOR"
	result_extension = Ri_extension ^= Ki;

	// work with s-blocks (8 blocks)
	for (int i = 0; i < 8; ++i) {
		bitset<6> result_subblock;
		for (int j = 0; j < 6; j++) {
			result_subblock.set(j, result_extension[i * 6 + j]);
		}

		bitset<2> a;
		a.set(0,result_subblock[0]);
		a.set(1,result_subblock[5]);

		unsigned long row_index = a.to_ulong();

		bitset<4> b;
		b.set(0,result_subblock[1]);
		b.set(1,result_subblock[2]);
		b.set(2,result_subblock[3]);
		b.set(3,result_subblock[4]);

		unsigned long column_index = b.to_ulong();

		int s_block_result = s_blocks[i * 64 + column_index * 16 + row_index];
		bitset<4> current_subblock(s_block_result);

		for (int j = 0; j < 4; j++) {
			result.set(i * 4 + j, current_subblock[j]);
		}	
	}

	return s_permutation(result);
}

std::string des::encode(const std::string& input) {
	return calculating(input, true);
}

std::string des::decode(const std::string& input) {
	return calculating(input, false);
}

bitset<BLOCK_SIZE_64> des::initial_permutation(const bitset<BLOCK_SIZE_64>& block) {
	bitset<BLOCK_SIZE_64> result;
	for (int i = 0; i < BLOCK_SIZE_64; i++) {
		result.set(i, block[initial_permutations[i] - 1]);
	}
	return result;
}

bitset<BLOCK_SIZE_32> des::s_permutation(const bitset<BLOCK_SIZE_32>& block) {
	bitset<BLOCK_SIZE_32> result;
	for (int i = 0; i < BLOCK_SIZE_32; i++) {
		result.set(i, block[s_block_permutation[i] - 1]);
	}
	return result;
}

bitset<BLOCK_SIZE_64> des::inverse_permutation(const bitset<BLOCK_SIZE_64>& block) {
	bitset<BLOCK_SIZE_64> result;
	for (int i = 0; i < BLOCK_SIZE_64; i++) {
		result.set(i, block[inverse_p[i] - 1]);
	}
	return result;
}

void des::convert_key(const std::string& input) {
	for (unsigned int i = 0; i < 8; i++) {
		char ch = input.at(i);
		for (int j = 1; j <= 8; j++) {			
			key.set((i+1) * 8 - j, shift(ch, j - 1));
		}
	}
	#ifdef DEBUG
		std::cout << endl<<"Bit representation of key = " << key.to_string() << endl;
	#endif
}

void des::split_input_string(const std::string& input) {
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

std::string des::to_bit_string(const bitset<BLOCK_SIZE_64>& block) {
	return block.to_string();
}

std::string des::to_std_string(const bitset<BLOCK_SIZE_64>& block) {
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

