/*
 * DueRecord.cpp
 *
 *  Created on: 13-Oct-2018
 *      Author: sraut
 */
#include "DueRecord.hpp"

using namespace std;

//#define SEC_IN_MONTH 2628000

int DueRecord::exportDues(std::string outfilename, int setw_int = 10) {

	ofstream ofs(outfilename.c_str());

	if (!ofs.is_open()) {
		cerr << "ERROR: exportDues() Failed: could to open output file "
				<< outfilename << " \n";
		return -1;
	} else {
		//cout << "writing to outfile \n";
		ofs << nRow << "," << nGoals << "," << nOwners << "," << prevDD << ","
				<< prevMM << "," << prevYY << "\n";

		for (int i = 0; i < nRow; i++) {
			for (int j = 0; j < nCol; j++) {
				int ind = i * nCol + j;
				//cout <<" " <<ind << "--";
				ofs << setw(setw_int) << this->sip[ind] << ",";
			}
			ofs << "\n";
		}
		ofs.close();
		return 0;
	}
}

int DueRecord::setParam(std::string paramLine) {

	std::stringstream ssHeader(paramLine);

	ssHeader >> nRow;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> nGoals;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> nOwners;

	nCol = nGoals * nOwners;

	cout << "DueRecord::setParams(): " << this->filename << "\n";
	cout << "nRow = " << nRow << " nGoals = " << nGoals << " nOwners = "
			<< nOwners << " nCol = " << nCol << " " << endl;

	//for (int i=0; i<6; i++) ssHeader.ignore();

	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> prevDD;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> prevMM;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> prevYY;

	std::cout << "DueRecord::setParam() [DD,MM,YYYY] = [" << prevDD << ","
			<< prevMM << "," << prevYY << "]" << endl;
	std::cout << "reading prevDate complete.\n";
//	cout << "DueRecord::setParam() completed.\n";

	if (prevDD > 28) {
		cerr
				<< "ERROR - renewalDD > 28 \nRenewal date need to be chosen less than or equal to 28th day of month"
				<< endl;
		return -1;
	}
	return 0;
}

/*
 void DueRecord::reReadPrevDate(){

 std::stringstream ssHeader(paramLine);

 // \*
 ssHeader >> nRow;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> nGoals;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> nOwners;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 // \*
 for (int i=0; i<6; i++) ssHeader.ignore();

 ssHeader >> prevDD;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> prevMM;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> prevYY;

 std::cout << "DueRecord::reReadPrevDate() [DD,MM,YYYY] = [" << prevDD << "," << prevMM << "," << prevYY << "]" << endl ;
 std::cout << "re-reading prevDate complete.\n";

 if (prevDD>28)
 {	cerr <<"ERROR - renewalDD > 28 \nRenewal date need to be chosen less than or equal to 28th day of month" << endl;
 EXIT_FAILURE;
 }
 }
 */

int DueRecord::updateDues(const Record& sipRef, std::string outfilename) {

	if (sipRef.sip == NULL) {
		cerr
				<< "ERROR: updateDues failed: empty table -> No record data found in "
				<< this->filename << "\n";
		return -1;
	}

	int nMonths = this->diffMM();

	cout << "nMonths = " << nMonths << "\n";

	if ((this->nRow != sipRef.nRow) || (this->nCol != sipRef.nCol)) {
		cerr
				<< "ERROR: updateDues failed:  nRow or nCol mismatch between " "due" " and " "sip" " \n";
		return -1;
	}

	this->prevDD = this->newTime.tm_mday;
	this->prevMM = this->newTime.tm_mon + 1;
	this->prevYY = this->newTime.tm_year + 1900;

	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			int ind = i * nCol + j;

			this->sip[ind] = this->sip[ind] + nMonths * sipRef.sip[ind];
		}
	}

	/*
	 cout << "duePrevDD = " << this->prevDD << "\n";
	 cout << "duePrevMM = " << this->prevMM << "\n";
	 cout << "duePrevYY = " << this->prevYY << "\n";
	 cout << "nMonths = " << nMonths << "\n";
	 cout << "dueNewDD = " << this->newTime.tm_mday << "\n";
	 cout << "dueNewMM = " << this->newTime.tm_mon << "\n";
	 cout << "dueNewYY = " << this->newTime.tm_year+1900<< "\n";
	 */
	if (this->exportDues(outfilename) == 0)
		return 0;
	else
		return -1;
}

int DueRecord::diffMM() {

	time_t t1 = time(0);   // get time now

	struct tm prevTime;
	prevTime.tm_hour = 00;
	prevTime.tm_min = 00;
	prevTime.tm_sec = 00;
	prevTime.tm_year = prevYY - 1900;
	prevTime.tm_mon = prevMM - 1; // month for tm struct goes from [0-11]
	prevTime.tm_mday = prevDD;

	struct tm temp = prevTime;

	int nMonths = 0;

	while (1) {
		char flag = 0;

		if (temp.tm_mon < 11) {
			flag = 1;
			temp.tm_mon++;
		} else if (temp.tm_mon == 11) {
			flag = 2;
			temp.tm_mon = 0;
			temp.tm_year++;
		} else
			cerr << "ERROR: month value > 11: out of range\n";

		if (mktime(&temp) < t1)
			nMonths++;
		else {
			if (flag == 1)
				temp.tm_mon--;
			else if (flag == 2) {
				temp.tm_mon = 11;
				temp.tm_year--;
			}

			break;
		}
	}

	newTime = temp;

	return nMonths;

	//int nxtYY, nxtMM, nxtDD;

	//	int curDD =  now->tm_mday;
	//	int curMM =  now->tm_mon;
	//	int curYY =  now->tm_year + 1900;

	//cout << "date = " << curDD << "\n";
	//cout << "month = " << curMM << "\n";
	//cout << "year = " << curYY << "\n";

	//	cout << "date = " << prevDD << "\n";
	//	cout << "month = " << prevMM << "\n";
	//	cout << "year = " << prevYY << "\n";

	//cout << "mktime(prev) =" << mktime(&prevTime) <<"\n";
	//cout << "time(0) " << time(0) <<"\n";

	/*
	 * 		struct tm  now = localtime( &t1 );
	 double diffSec = difftime( time(0) , mktime(&prevTime));
	 cout << "DiffSec = " << diffSec << "\n";

	 int nMonthsGone =  diffSec/SEC_IN_MONTH;

	 cout << "nMonthsGone = " << nMonthsGone << "\n";

	 if (now.tm_mday > prevTime.tm_mday)
	 { nxtYY = now.tm_year ;
	 nxtMM = now.tm_mon ;
	 nxtDD = prevTime.tm_mday ;
	 }
	 else if ( (prevTime.tm_mday - now.tm_mday) > 1 )
	 { nxtYY = now.tm_year ;
	 nxtMM = now.tm_mon - 1 ;
	 nxtDD = prevTime.tm_mday ;
	 }
	 now.tm_mday - prevTime.tm_mday

	 //		int diffMM=0;

	 // diffMM += 12*(curYY-prevYY);
	 */
}

