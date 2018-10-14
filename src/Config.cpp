/*
 * Config.cpp
 *
 *  Created on: 14-Oct-2018
 *      Author: sraut
 */
#include "Config.hpp"

void Config::printConfig() {

	cout << "infile_sip = " << this->infile_sip << "\n";
	cout << "infile_due = " << this->infile_due << "\n";
	cout << "infile_inv = " << this->infile_inv << "\n";
	cout << "outfile_due = " << this->outfile_due << "\n";
	cout << "displayTable_fieldWidth = " << this->displayTable_fieldWidth
			<< endl;

}

int Config::updateField(string key, string value) {

	if (key == "infile_sip")
		infile_sip = value;
	else if (key == "infile_due")
		infile_due = value;
	else if (key == "infile_inv")
		infile_inv = value;
	else if (key == "outfile_due")
		outfile_due = value;
	else if (key == "displayTable_fieldWidth")
		displayTable_fieldWidth = atoi(value.c_str());
	else {
		cerr << "ERROR: found unexpected key string in Config file \n";
		return -1;
	}
	return 0;
}

int Config::load(string filename_cfg) {

	cout << "Old Config:\n";
	printConfig();

	cout << endl;
	std::ifstream cfgFile;
	cfgFile.open(filename_cfg.c_str());

	if (!cfgFile.is_open()) {
		cerr << "ERROR: Config::load failed to open file : " << filename_cfg
				<< " \n";
		return -1;
	} else {
		string line;
		while (getline(cfgFile, line)) {

			istringstream iss_line(line);
			std::string key;
			if (std::getline(iss_line, key, '=')) {
				std::string value;
				if (std::getline(iss_line, value))

					//	cout << "Key = " << key << "\n";
					//	cout << "Value = " << value << "\n";
					if (updateField(key, value)) {
						cerr << "ERROR: Config::load failed for "
								<< filename_cfg << endl;
						cfgFile.close();
						return -1;
					}
			}

		}
		cfgFile.close();
		cout << "New Config:" << endl;
		printConfig();
	}

	return 0;
}
