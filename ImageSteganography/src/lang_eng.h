/*
 * Initialization and Definition of English Language class.
 * English Language class is derived from Language.
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef LANGUAGE_ENGLISH_H_
#define LANGUAGE_ENGLISH_H_

#include <iostream>
#include "Language.h"

// Derived Class
class Language_English: public Language
{
	private:
        // Create Dictionary to extract the index of the value matrix which contains the pixel value
        // And additional Dictionary to extract the characters using the index.
		void mapIndexes ()
		{
            for (int i = 0; i < Characters.size(); i++)
            {
                insert_Keys(Characters[i], i);
                insert_values(i);
            }
        }
	public:
		Language_English()
		{
            Characters = "0123456789";
            Characters += " !°§#$%&'()*+,-./:;<=>?@[\\]^_-`{|}~´";
            Characters += "்ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            Characters += '"';
            Characters += '\n';
            Characters += '\t';
            Characters += '\v';
            // Initialize the characters
            setSizeValues(Characters.size(), 3);
			mapIndexes();
		}
};
#endif 	/*	LANGUAGE_ENGLISH_H_	*/
