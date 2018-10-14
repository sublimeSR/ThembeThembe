/*
 * MF.cxx
 * 
 * Copyright 2018 sraut <sraut@HPdv5>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "main.hpp"

using namespace std;


int main(int argc, char **argv) {

	int errFlag = 0;

	Config cfg;

	if (argc<2)
	{	cerr << "ERROR: invalid use: please input config file location as an input argument e.g.\n $ThembeThembe ./configfilepath/config.txt\n";
		return -1;
	}
	string filename_config(argv[1]);


	Record sip, invAmt;

	if (!errFlag && cfg.load(filename_config) == 0)
		cout << "config load completed.\n";
	else
		errFlag=-1;


	if (!errFlag && sip.import(cfg.infile_sip) == 0)
		cout << "sip import completed.\n";
	else errFlag = -1;

	if (!errFlag && sip.displayTable(cfg.displayTable_fieldWidth) == 0)
		 cout << "sip displayTable completed.\n";
	else errFlag = -1;

	if (!errFlag && invAmt.import(cfg.infile_inv)==0)
		 cout << "invAmt import completed.\n";
	else errFlag = -1;


	if (!errFlag && invAmt.displayTable(cfg.displayTable_fieldWidth)==0)
		cout << "invAmt displayTable completed.\n";
	else errFlag = -1;

	DueRecord due;

	if (!errFlag && due.import(cfg.infile_due) == 0)
		cout << "due import completed.\n";
	else errFlag = -1;

	if (!errFlag && due.displayTable(cfg.displayTable_fieldWidth) == 0)
		cout << "due displayTable completed.\n";
	else errFlag = -1;

	if (!errFlag && due.updateDues(sip, cfg.outfile_due) ==0 )
		 cout << "due updateDues completed.\n";
	else errFlag = -1;

	if (!errFlag && due.displayTable(cfg.displayTable_fieldWidth)==0)
		cout << "newDue displayTeble() completed.\n";
	else errFlag = -1;

	//cout <<"errFlag = " << errFlag;

	return errFlag;
	//return 0;
}

/*
 *
 procedural implementation

 #include <iostream>
 #include <fstream>
 #include <sstream>
 string line;

 ifstream myfile ("sip.txt");

 if (myfile.is_open())
 {

 getline (myfile,line);
 cout << line << endl;
 stringstream ssHeader(line);

 int nRow, nGoals, nOwners, nCol;
 ssHeader >> nRow;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> nGoals;
 if (ssHeader.peek() == ',') ssHeader.ignore();
 ssHeader >> nOwners;

 nCol = nGoals*nOwners;

 cout << "nRow = " << nRow<< " "<<" nGoals = " << nGoals  << " " << "nOwners = " << nOwners  << "\n" << "nCol = "  << nCol << " " << endl;

 int *sip;

 sip = new int [ (nRow)*(nCol) ];

 //int r=0;
 //while ( getline (myfile,line) )
 for (int r = 0; r < nRow; r++ )
 {
 getline (myfile, line);
 cout <<"LineStr : " <<line << "\n";

 stringstream ss(line);
 int jj=0;
 for (int j=0; j < 2*nCol-1; j++ )
 {
 //cout  << "..";
 if (ss.peek() == ',')
 ss.ignore();
 else
 { ss >> sip[r*nCol + jj] ;
 jj++;
 //  cout << sip[r*nCol + j] ;
 }
 }

 //   r++;
 }

 cout << "nRow = " << nRow << " nCol = " << nCol <<"\n";

 cout <<"SIP_table = \n";
 for (int i=0; i< nRow; i++)
 {
 for (int j=0; j< nCol; j++)
 cout << sip[i*nCol + j] << " ";

 cout << endl;
 }

 myfile.close();
 delete[] sip;
 }
 else cout << "Unable to open file";

 */

