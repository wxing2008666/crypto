#include <string>
#include "huffman.h"

std::string huffman::encode(const std::string& input) {
	calculate_frequency(input);
	// for(auto x : m_alphabet) {
	// 	cout << x.symbol << " -> " << x.frequency << endl;
	// }
	return "1";
}

std::string huffman::decode(const std::string& input) {
	return "Decode method called";
}

inline double comparator(unit a, unit b) {
	return a.frequency < b.frequency;
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
			m_alphabet.push_back({(char)sym, accuracy(freq, 4), std::string("")});
		}
	);
	sort(m_alphabet.begin(), m_alphabet.end(), comparator);
}