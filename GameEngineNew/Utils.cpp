//
//  Utils.cpp
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/30/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#include "Utils.h"

void Utils::ERROR(const string &msg, bool doExit)
{
	cerr << "\nERROR! " << msg << endl;
	if (doExit) exit(0);
}

double Utils::TIME(void)
{
	return (double)clock() / (double)CLOCKS_PER_SEC;
}

void Utils::SLEEP(int millis)
{
	this_thread::sleep_for(chrono::milliseconds(1));
}

void Utils::addToPath(const string &p)
{
    getPath().push_back(p);
}

void Utils::removeFromPath(const string &p)
{
	for (int i = (int)p.length() - 1; i >= 0; i--) {
		if (getPath()[i] == p) getPath().erase(PATH.begin() + i);
	}
}

bool Utils::getFullFileName(const string &fileName, string &fullName)
{
	for (int i = -1; i < (int) getPath().size(); i++) {
		if (i < 0) fullName = fileName;
		else fullName = getPath()[i] + fileName;
        
		FILE *f = fopen(fullName.c_str(), "rb");
		if (f != NULL) {
			fclose(f);
			return true;
		}
	}
	fullName = "";
	return false;
}

FILE* Utils::openFileForReading(const string &fileName)
{
	string fullName;
	bool fileExists = getFullFileName(fileName, fullName);
	if (fileExists) {
		cout << "Opening file '" << fileName << "'" << endl;
		return fopen(fullName.c_str(), "rb");
	}
    
	string msg = "Could not open file " + fileName;
	ERROR(msg.c_str(), false);
	return NULL;
}

bool Utils::getToken(FILE *f, string &token, const string &oneCharTokens)
{
	token = "";
	while (!feof(f)) {
		int c = getc(f);
		int tokenLength = (int)token.length();
		int cIsSpace = isspace(c);
		bool cIsOneCharToken = ((int)oneCharTokens.find((char)c) >= 0);
        
		if (cIsSpace && tokenLength == 0) { // spaces before token, ignore
			continue;
		}
		else if (cIsSpace) { // space after token, done
			break;
		}
		else if (c == EOF) { // end of file, done
			break;
		}
		else if ((tokenLength == 0) && cIsOneCharToken) { // oneCharToken, done
			token += (char)c;
			break;
		}
		else if (cIsOneCharToken) { // oneCharToken after another token, push back
			ungetc(c, f);
			break;
		}
		else if ((tokenLength == 0) && (c == '\"' || c == '\'')) { // quoted string, append til end quote found
			char endQuote = c;
			while (!feof(f)) {
				int d = getc(f);
				if (d == endQuote) return true;
				token += (char)d;
			}
			break;
		}
		else if (c == '\"' || c == '\'') { // quote after token started, push back
			ungetc(c, f);
			break;
		}
		else {
			token += (char)c;
		}
	}
	//cout << token << endl;
	return (token.length() > 0);
}

