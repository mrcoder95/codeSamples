/*
 * Initialization and Definition of Steganography Class.
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef STEGANOGRAPHY_H_
#define STEGANOGRAPHY_H_

#include <iostream>
#include <map>
#include <vector>
#include <QChar>
#include "lang_eng.h"
#include "lang_deu.h"

enum Languages
{
    ENGLISH = 0,
    DEUTSCH = 1
};

class SteganographyClass
{
	private:
        // Insert elemnents to the tag matrix
        void insertElements (std::vector < std::vector < int> > &tag, unsigned int row, unsigned int col1, unsigned int col2, unsigned int col3)
		{
            tag[row][0] = col1;
            tag[row][1] = col2;
            tag[row][2] = col3;
		}

        // Start tag matrix initialization
		void startTagInitialization()
		{
            start_tag.resize(10, std::vector <int>(3, 0));
            insertElements(start_tag, 0, 9, 9, 9);
            insertElements(start_tag, 1, 9, 9, 8);
            insertElements(start_tag, 2, 9, 9, 7);
            insertElements(start_tag, 3, 9, 9, 6);
            insertElements(start_tag, 4, 9, 9, 5);
            insertTag(start_tag, 'L', 5);
            insertTag(start_tag, 'N', 6);
            insertTag(start_tag, '_', 7);
            switch (language)
            {
                case ENGLISH:   insertTag(start_tag, 'E', 8);
                                insertTag(start_tag, 'N', 9);
                                break;
                case DEUTSCH:   insertTag(start_tag, 'D', 8);
                                insertTag(start_tag, 'E', 9);
                                break;
            }
		}

        // End tag matrix initialization
		void endTagInitialization()
		{
            end_tag.resize(5, std::vector <int>(3, 0));
            insertElements(end_tag, 0, 9, 9, 5);
            insertElements(end_tag, 1, 9, 9, 6);
            insertElements(end_tag, 2, 9, 9, 7);
            insertElements(end_tag, 3, 9, 9, 8);
            insertElements(end_tag, 4, 9, 9, 9);
		}

        // Insert character to the tag
        void insertTag(std::vector < std::vector < int> > &tag, QChar c, unsigned int row)
		{
            int m, n, o;
			encodeText(m, n, o, c);
            insertElements(tag, row, m, n, o);
		}
	public:
        std::vector < std::vector < int> > start_tag;
        std::vector < std::vector < int> > end_tag;
        Language_English lanEng;
        Language_Deutsch lanDeu;
        QString Characters;
        Languages language;

        SteganographyClass()
        {
            startTagInitialization();
            endTagInitialization();
            language = ENGLISH;
        }

        void encodeText(int &m, int &n, int &o, QChar c)
		{
           switch (language)
           {
               case ENGLISH:   m = lanEng(c, 0);
                               n = lanEng(c, 1);
                               o = lanEng(c, 2);
                               break;
               case DEUTSCH:   m = lanDeu(c, 0);
                               n = lanDeu(c, 1);
                               o = lanDeu(c, 2);
                               break;
           }
		}

        QChar decodeText(int m, int n, int o)
        {
            unsigned int num = 0;

            num += m * 100;
            num += n * 10;
            num += o;
            switch (language)
            {
                case ENGLISH:   return lanEng[num];
                                break;
                case DEUTSCH:   return lanDeu[num];
                                break;
                default:        return lanEng[num];
            }
            return lanEng[num];
        }

        void setLanguage(Languages lan)
        {
            language = lan;
            switch (language)
            {
                case ENGLISH:   Characters = lanEng.Characters;
                                break;
                case DEUTSCH:   Characters = lanDeu.Characters;
                                break;
            }
            startTagInitialization();
            endTagInitialization();
        }

};
#endif /*		STEGANOGRAPHY_H_		*/
