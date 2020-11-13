#include <iostream>
#include <string>
#include <vector>
#include "bktree.hpp"

int main(){
	bk_tree::bk_tree<bk_tree::metrics::hamming_distance> tree;
	std::vector<std::string> input {"tall", "tell", "teel", "feel", "tally", "tuck"};
	for(auto& s: input){
		tree.insert(s);
	}
	std::vector<std::pair<std::string, int>> results;
	for(int limit = 1; limit <= 3; limit++){
		results = tree.find("tale", limit);
		for(auto& p: results){
			std::cout << p.first << " " << p.second << std::endl;
		}
	}
	return 0;
}
