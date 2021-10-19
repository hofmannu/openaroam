// File: dataprocessor.h
// AUthor: Urs Hofmann
// Mail: hofmannu@ethz.ch
// Date: 06.08.2021


#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <cstdint>

template <typename dataType>
class dataprocessor
{

private:
	void calc_max(
		const dataType* arrayIn, dataType* arrayOut,
		uint32_t dim0, uint32_t dim1);


public:


};


#endif