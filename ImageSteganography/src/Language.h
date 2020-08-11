/*
 * Initialization and Definition of Language class (Base Class).
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <iostream>
#include <map>
#include <vector>
#include <QChar>
#include <QString>

class Language
{
	private:
        std::map <QChar, unsigned int> Index;                   // Extract the index of the value matrix depending upon the character
        std::map <unsigned int, QChar> Key;                     // Extract the character from index
        std::vector < std::vector < unsigned int> > Values;     // Matrix containing the pixel value of the character
	protected:
        // Create Dictionary
        void insert_Keys (QChar C, unsigned int N)
		{
			Index[C] 	= N;
			Key[N] 		= C;
		}

        // Update the value matrix
        //void insert_values(unsigned int row, unsigned int val1, unsigned int val2, unsigned int val3)
        void insert_values(unsigned int val)
		{
            if (val < 10)
            {
                Values[val][0] = 0;
                Values[val][1] = 0;
                Values[val][2] = val;
            }
            else if (val >= 10 && val < 100)
            {
                Values[val][0] = 0;
                Values[val][1] = int(val / 10);
                Values[val][2] = val % 10;
            }
            else
            {
                Values[val][0] = int(val / 100);
                Values[val][1] = int((val % 100) / 10);
                Values[val][2] = val % 10;
            }
            //Values[val][0] = val1;
            //Values[val][1] = val2;
            //Values[val][2] = val3;
		}

        // Resize the value matrix
		void setSizeValues(unsigned int Rows, unsigned int Columns)
		{
			Values.resize(Rows, std::vector <unsigned int>(Columns, 0));
		}
	public:
        QString Characters;
        inline unsigned int operator [](QChar C)
		{
			return Index[C];
		}
		
        inline QChar operator [](unsigned int K)
		{
            return Key[K];
		}

        inline unsigned int operator () (QChar C, unsigned int Col)
		{
            return Values[Index[C]][Col];
		}


		
};
#endif /*	LANGUAGE_H_		*/

