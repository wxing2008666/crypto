#include <string>
#include "huffman.h"

#define DEBUG

inline double get_total_freq(std::vector<unit> v) {
	double total_freq = 0;
	for(auto elem: v) {
		total_freq += elem.frequency;
	}
	return total_freq;
}

inline double comparator(std::vector<unit> a, std::vector<unit> b) {
	return get_total_freq(a) > get_total_freq(b);
}

std::string huffman::encode(const std::string& input) {
	calculate_frequency(input);
	std::vector<std::vector<unit>> tree;

	for(auto elem: m_alphabet) {
		std::vector<unit> local_list;
		local_list.push_back(elem);
		tree.push_back(local_list);
	}
	#ifdef DEBUG
		current_tree_state(tree);
	#endif
	// @TODO: while true
	while(true) {
		// @TODO: sort tree
		sort(tree.begin(), tree.end(), comparator);
		// @TODO: Get two elements with the lowest frequency
		// Delete this elements from vector
		auto back = tree.back();
		tree.pop_back();
		auto before_back = tree.back(); 
		tree.pop_back();
		// append to all units of last tree element byte "1"
		change_bytecode(back, '1');
		// append to all units of tree element before last byte "0"
		change_bytecode(before_back, '0');
		// merge last vector and vector before last
		back.insert(back.end(), before_back.begin(), before_back.end());
		tree.push_back(back);

		#ifdef DEBUG
			current_tree_state(tree);
		#endif

		if((get_total_freq(back) + get_total_freq(before_back)) >= 1) break; 
	}

	#ifdef DEBUG
		for(auto unit: tree.at(0)) {
			cout << unit.symbol << " = " << unit.bytecode << endl;
		}
	#endif

	//get list of codes
	codes.insert(codes.begin(), tree.at(0).begin(), tree.at(0).end());

	std::string encoded;
	// build encoded string
	for(char letter: input) {
		for(auto code: codes) {
			if(code.symbol == letter) {
				encoded.append(code.bytecode);
			}
		}
	}

	return encoded;
}

void huffman::current_tree_state(const std::vector<std::vector<unit>>& tree) {
	cout << "===============================" << endl;
	cout << "{" << endl;
	for(auto v: tree) {
		cout << " {" << endl;
		cout << "  ";
		for(auto unit : v) {
			cout << "{ " << unit.symbol << "(" << unit.frequency << ", '" << unit.bytecode << "') "<< "} ";
		}
		cout << endl << " }" << endl;
	}
	cout << "}" << endl;
	cout << "===============================" << endl;
}

void huffman::change_bytecode(std::vector<unit>& v, char byte) {
	for(auto& u: v) {
		std::reverse(u.bytecode.begin(), u.bytecode.end());
		u.bytecode += byte;
		std::reverse(u.bytecode.begin(), u.bytecode.end());
	}
}

std::string huffman::decode(const std::string& input) {
	std::string decoded;
	std::string current_prefix;
	for(char letter: input) {
		current_prefix += letter;
		for(unit u: codes) {
			if(u.bytecode == current_prefix) {
				decoded += u.symbol;
				current_prefix.clear();
			}
		}
	}
	return decoded;
}


inline double accuracy(double val, int accuracy) {
	double grid = pow(0.1, accuracy);
	return floor(val / grid + 0.5) * grid;
}

void huffman::calculate_frequency(const std::string& input) {
	set<char> uniq(input.begin(), input.end());
	std::for_each(
		uniq.begin(),
		uniq.end(),
		[=](const char& sym) {
			double freq = (double)std::count(input.begin(), input.end(), sym) / (double)input.size();
			m_alphabet.push_back({sym, accuracy(freq, 4)});
		}
	);
}