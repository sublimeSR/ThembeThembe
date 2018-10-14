/*
 * record.h
 *
 *  Created on: 06-Oct-2018
 *      Author: sraut
 */

#ifndef INC_RECORD_HPP_
#define INC_RECORD_HPP_

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <iomanip>

// #include "Record.cxx"

class Record {

private:
	virtual int setParam(std::string firstline);

protected:
	std::string paramLine;
	void readMatrix(std::ifstream& ifs);
	std::string filename;

public:
	int* sip = NULL;
	int nRow, nGoals, nOwners, nCol;
	int import(std::string filename);
	int displayTable(int setw_int);
	Record() ;
	virtual ~Record() ;
};

#endif /* INC_RECORD_HPP_ */
