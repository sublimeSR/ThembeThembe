/*
 * record.cxx
 *
 *  Created on: 06-Oct-2018
 *      Author: sraut
 */
#include "Record.hpp"

using namespace std;

int Record::displayTable(int setw_int) {

	if (sip == NULL) {
		std::cerr
				<< "ERROR: displayTable failed: empty table -> No record data found in "
				<< this->filename << " \n";
		return -1;
	} else {
		cout << "nRow = " << nRow << " nCol = " << nCol << endl;
		for (int i = 0; i < nRow; i++) {
			for (int j = 0; j < nCol; j++)
				cout << setw(setw_int) << sip[i * nCol + j] << " ";
			cout << endl;
		}
	}
	return 0;
}

int Record::setParam(string firstLine) {

	if (firstLine.empty()) {
		cerr << "ERROR Record::setParam input string not received\n";
		return -1;
	}

	stringstream ssHeader(firstLine);

	ssHeader >> nRow;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> nGoals;
	if (ssHeader.peek() == ',')
		ssHeader.ignore();
	ssHeader >> nOwners;

	nCol = nGoals * nOwners;

	cout << "Record::setParams(): " << this->filename << "\n";
	cout << "nRow = " << nRow << " nGoals = " << nGoals << " nOwners = "
			<< nOwners << " nCol = " << nCol << " " << endl;
//	cout << "Record::setParam() completed for " << this->filename <<" \n";

	return 0;

}

Record::Record(){

	nRow=0;nCol=0;nOwners=0;nGoals=0;
}

Record::~Record() {

	delete[] sip;
}

int Record::import(string filename) {

	if (filename.empty()) {
		cerr
				<< " ERROR: import failed : Record::import > missing input argument filename\n"
				<< endl;
		return -1;
	} else {
		ifstream myfile(filename.c_str());
		this->filename = filename;
		if (myfile.is_open()) {
			getline(myfile, paramLine);
			setParam(paramLine);
			readMatrix(myfile);
			myfile.close();
			return 0;
		} else {
			cerr << "ERROR: import failed: Unable to open file >> " << filename
					<< " \n";
			return -1;
		}
	}
}

void Record::readMatrix(ifstream& ifs) {

	sip = new int[(nRow) * (nCol)];

	string line;
	for (int r = 0; r < nRow; r++) {
		getline(ifs, line);
		//cout <<"LineStr : " <<line << "\n";

		stringstream ss(line);
		int jj = 0;
		for (int j = 0; j < 2 * nCol - 1; j++) {
			if (ss.peek() == ',')
				ss.ignore();
			else {
				ss >> sip[r * nCol + jj];
				jj++;
			}
		}
	}
	cout << "Record::readMatrix completed for " << this->filename << " \n";
}

