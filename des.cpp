#include "des.h"

#define DEBUG

inline bool shift(char ch, int count) {
	return (ch >> count) & 1;
}

std::string des::calculating(const std::string& input, bool is_encode) {
	split_input_string(input);

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
		
	}
	
	return input;
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
		result.set(i, block[initial_permutation[i] - 1]);
	}
	return result;
}

void des::convert_key(const std::string& input) {
	for (unsigned int i = 0; i < 8; i++) {
		char ch = input.at(i);
		for (int j = 1; j <= 8; j++) {			
			source_key.set((i+1) * 8 - j, shift(ch, j - 1));
		}
	}
	#ifdef DEBUG
		std::cout << endl<<"Bit representation of key = " << source_key.to_string() << endl;
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
		for (int j = blocks_count * 8; j < input.size(); j++, i++) {
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