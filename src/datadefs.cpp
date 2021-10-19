#include "datadefs.h"

template<int ndim, typename dataType>
uint32_t multidimarray<ndim, dataType>::get_linidx(const uint32_t* idxPos)
{
	uint32_t idx = 0;
	for (uint32_t iDim = (ndim -1); iDim >= 0; iDim--)
	{
		idx += idxPos;
		if (iDim > 0)
			idx *= dim[iDim - 1];
	}
	return idx;
}

// returns the total number of elements contained in this array
template<int ndim, typename dataType>
uint32_t multidimarray<ndim, dataType>::get_nelem()
{
	uint32_t nElem = 1;
	#pragma unroll
	for (uint32_t iDim = 0; iDim < ndim; iDim++)
	{
		nElem *= dim[iDim];
	}
	return nElem;
}

// automatically returns value of a position in the array
template<int ndim, typename dataType>
dataType multidimarray<ndim, dataType>::get_value(const uint32_t* idxPos)
{
	return data[get_linidx(idxPos)];
}

// define the value of a specified position in our array
template<int ndim, typename dataType>
void multidimarray<ndim, dataType>::set_value(const dataType val, const uint32_t* idxPos)
{
	uint32_t idx = get_linidx(idxPos);
	data[idx] = val;
	return;
}

// calculate the maximum projection along a certain dimension
template<int ndim, typename dataType>
void multidimarray<ndim, dataType>::max(dataType* outArray, const uint32_t dimMax)
{
	uint32_t nElem = get_nelem();
	
	// initialize index list and set all of them to zero
	uint32_t currIdx[ndim];
	for (uint32_t iDim = 0; iDim < 0; iDim++)
		currIdx[iDim] = 0;

	for (uint32_t iElem = 0; iElem < nElem; iElem++)
	{
		inc_idx(currIdx); // increment index (moves over to next index position)
		// stopped here
	}
	return;
}

// incline a multidimension array index to the next linearized element
template<int ndim, typename dataType>
void multidimarray<ndim, dataType>::inc_idx(uint32_t* idx)
{
	idx[0]++;

	for (uint32_t iDim = 0; iDim < (ndim - 1); iDim++)
	{
		if (idx[iDim] >= dim[iDim])
		{
			idx[iDim] = 0;
			idx[iDim + 1] += 1;
		}
		else
		{
			return; // no more overflow? we are done here
		}
	}
	return;
}

// function reshapes the array into a different dimensionality
// number of elements and number of dimensions stays the same
template<int ndim, typename dataType>
void multidimarray<ndim, dataType>::reshape(const uint32_t* newDim)
{
	// check if number of array elements stays the same
	uint32_t nElemOld = 1;
	uint32_t nElemNew = 1;
	#pragma unroll
	for (uint32_t iDim = 0; iDim < ndim; iDim++)
	{
		nElemOld *= dim[iDim];
		nElemNew *= newDim[iDim];
	}

	if (nElemOld == nElemNew)
	{
		#pragma unroll
		for (uint32_t iDim = 0; iDim < ndim; iDim++)
		{
			dim[iDim] = newDim[iDim];
		}
	}
	else
	{
		cout << "Number of elements cannot change" << endl;
	}

	return;
}