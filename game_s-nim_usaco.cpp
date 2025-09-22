#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

const int MAX_PILE = 1e4;

int main() {
	int move_num;
	std::cin >> move_num;
	vector<int> can_remove(move_num);
	for (int &n : can_remove) { std::cin >> n; }

	vector<int> nimbers(MAX_PILE + 1);
	for (int i = 1; i <= MAX_PILE; i++) {
		std::set<int> reachable;
		for (int n : can_remove) {
			if (i - n >= 0) { reachable.insert(nimbers[i - n]); }
		}

		for (int n = 0; n <= MAX_PILE; n++) {
			if (!reachable.count(n)) {
				nimbers[i] = n;
				break;
			}
		}
	}

	int game_num;
	std::cin >> game_num;
	vector<char> wins(game_num);
	for (int g = 0; g < game_num; g++) {
		int pile_num;
		std::cin >> pile_num;

		int xor_sum = 0;
		for (int p = 0; p < pile_num; p++) {
			int pile;
			std::cin >> pile;
			xor_sum ^= nimbers[pile];
		}

		wins[g] = xor_sum == 0 ? 'L' : 'W';
	}

	for (const char &w : wins) { cout << w; }
	cout << endl;
}