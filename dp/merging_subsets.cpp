#include <iostream>

int main() {
	int n = 5; // Set n to a desired value or read from input
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
			int subset = mask ^ submask;
			// do whatever you need to do here
		}
	}
	return 0;
}