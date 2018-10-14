/*
 * Config.hpp
 *
 *  Created on: 13-Oct-2018
 *      Author: sraut
 */

#ifndef INC_CONFIG_HPP_
#define INC_CONFIG_HPP_

#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include <cstdlib>

using namespace std;

class Config {

public:
	std::string infile_sip;
	std::string infile_due;
	std::string infile_inv;
	std::string outfile_due;
	int displayTable_fieldWidth;

	void printConfig();

	int updateField(std::string key, std::string value);

	int load(std::string filename_cfg);

	Config() {
		infile_sip = "./data/sip.txt";
		infile_due = "./data/due.txt";
		infile_inv = "./data/inv.txt";
		outfile_due = "./op/newDues.txt";
		displayTable_fieldWidth = 10;
	}

};

#endif /* INC_CONFIG_HPP_ */
