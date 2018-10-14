/*
 * DueRecord.hpp
 *
 *  Created on: 13-Oct-2018
 *      Author: sraut
 */

#ifndef INC_DUERECORD_HPP_
#define INC_DUERECORD_HPP_

#include <ctime>
#include "Record.hpp"

class DueRecord: public Record {
public:
	int prevDD, prevMM, prevYY;
	//void reReadPrevDate();
	int updateDues(const Record& sipRef, std::string outfilename);
	int exportDues(std::string outfilename, int setw_int);
	struct tm newTime;
	int diffMM();
	~DueRecord() { 	};

private:
	virtual int setParam(std::string paramline);
	/*
	 void setParam(std::string firstLine){

	 std::stringstream ssHeader(firstLine);

	 ssHeader >> nRow;
	 if (ssHeader.peek() == ',') ssHeader.ignore();
	 ssHeader >> nGoals;
	 if (ssHeader.peek() == ',') ssHeader.ignore();
	 ssHeader >> nOwners;
	 if (ssHeader.peek() == ',') ssHeader.ignore();
	 ssHeader >> prevDate;

	 std::cout << " read preDate...\n";

	 nCol = nGoals*nOwners;

	 std::cout << "nRow = " << nRow<< " "<<" nGoals = " << nGoals  << " " << "nOwners = " << nOwners  << "\n" << "nCol = "  << nCol << " " << std::endl;
	 std::cout << prevDate << std::endl;
	 std::cout << "setParam() completed ..\n";

	 }
	 */
};

#endif /* INC_DUERECORD_HPP_ */
