#include "gost.h"

#define DEBUG



inline bool shift(char ch, int count) {
	return (ch >> count) & 1;
}


std::string gost::encode(const std::string& input) {
	// @TODO: 
	return input;
}

std::string gost::decode(const std::string& input) {
	return input;
}

void gost::set_key(const std::string& input) {
	for (int i = 0; i < input.size(); ++i) {
		if(i == KEY_SIZE) break;
		char ch = input.at(i);
		for (int j = 1; j <= 8; ++j) {
			key.set( (i + 1) * 8 - j, (ch >> j -1) & 1);
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