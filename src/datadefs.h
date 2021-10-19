/*
	defines a general purpose multidimensional array and the corresponding
	functions for it

*/

#ifndef MULTIDIMARRAY_H
#define MULTIDIMARRAY_H

#include <cstdint>
#include <iostream>

using namespace std;

template <int ndim, typename dataType>
class multidimarray
{
public:
	uint32_t dim[ndim]; // number of elements along each dimension
	dataType* data; // poi

	dataType get_value(const uint32_t* idxPos);
	void set_value(const dataType val, const uint32_t* idxPos);
	void reshape(const uint32_t* newDim); // number of elements must stay constant

	// yet to be implemented / under construction
	void max(dataType* outArray, const uint32_t dimMax);
	// - permute
	// - flip
	// - max against a certain dimension
	// - min against a certain dimension


private:
	uint32_t get_linidx(const uint32_t* idxPos); // returns linear index
	uint32_t get_nelem(); // returns the total number of elements in array
	void inc_idx(uint32_t* idx);

};

#endif