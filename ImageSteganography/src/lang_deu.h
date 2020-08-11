/*
 * Initialization and Definition of Deutsch Language class.
 * Deutsch Language class is derived from Language.
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef LANGUAGE_DEUTSCH_H_
#define LANGUAGE_DEUTSCH_H_

#include <iostream>
#include "Language.h"

// Derived Class
class Language_Deutsch: public Language
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
        Language_Deutsch()
		{
            Characters = "0123456789";
            Characters += " !°§#$%&'()*+,-./:;<=>?@[\\]^_-`{|}~´";
            Characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            Characters += "ßüÜöÖäÄ";
            Characters += '"';
            Characters += '\n';
            Characters += '\t';
            Characters += '\v';
            // Initialize the characters
            setSizeValues(Characters.size(), 3);
			mapIndexes();
		}
};
#endif 	/*	LANGUAGE_DEUTSCH_H_	*/
