#pragma once

template <class T>
static int findInVec(vector<T> vec, T item) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == item)
			return i;
	}
	return -1;
}
