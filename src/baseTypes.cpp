/*!
 * \file
 * \brief basetypes.cpp
 */

#include "baseTypes.h"


U2 readU2 (FILE *fp) 
{
	unsigned short ret = 0;
	unsigned char aux;

	fread(&ret, 1, 1, fp);
	fread(&aux, 1, 1, fp);

	ret <<= 8;
	ret |= aux;

	return ret;
}

U1 readU1 (FILE *fp)
{
	unsigned char ret;

	fread(&ret, 1, 1, fp);

	return ret;
}

U1 * readUTF8 (FILE* fp, int size) 
{
	

	std::vector<unsigned char> *ret = new std::vector<unsigned char>(size);

	for (int i = 0; i < size; i++) {
		ret->at(i) = readU1(fp);
	}

	return (U1*) ret;
} 

U4 readU4 (FILE *fp)
 {
	unsigned int ret = 0;
	unsigned char aux;

	for (int i=0; i<4; i++) {
		ret <<= 8;
		fread(&aux, 1, 1, fp);
		ret |= aux;
	}

	return ret;
}

string showUTF8 (unsigned char * s, int size) 
{
	std::vector<unsigned char> *v = (std::vector<unsigned char> *) s;
	string ret = "";
	size = v->size();
	int i = 0;

	while (i < size) {
		if (!(v->at(i) & 0x80)) { //utf8 only with 1 bit
			ret.push_back(v->at(i));
		} else {
			unsigned short auxCurrent;
			if (!(v->at(i+1) & 0x20)) { //utf8 of 2 bytes
				auxCurrent = ((v->at(i) & 0x1f) << 6) + (v->at(i+1) & 0x3f);
			} else { //utf8 of 3 bytes
				auxCurrent = ((v->at(i) & 0xf) << 12) + ((v->at(i+1) & 0x3f) << 6) + (v->at(i+2) & 0x3f);
				i++;
			}
			i++;
			ret.push_back(auxCurrent);
		}
		i++;
	}

	return ret;
}

string double_to_string (double d) 
{
	stringstream ret;
	switch (checkDouble(d)) {
		case 0:
			ret << d;
			break;
		case 1:
			ret << "+Inf";
			break;
		case 2:
			ret << "-Inf";
			break;
		case 3:
			ret << "NaN";
			break;
	}

	return ret.str();
}


//return 1 for +infinity, 2 for -inifity, 3 for NaN e 0 for number inside bound
int checkFloat (float f) 
{
	int ret = 0;
	element aux;
	aux.f = f;

	if ((aux.i >= 0x7f800001 && aux.i <= 0x7fffffff) || (aux.i >= 0xff800001 && aux.i <= 0xffffffff)) {
		ret = 3;
	} else if (aux.i == 0x7f800000) {
		ret = 1;
	} else if (aux.i == 0xff800000) {
		ret = 2;
	}

	return ret;
}

//return 1 for +infinity, 2 for -inifity, 3 for NaN e 0 for number inside bound
int checkDouble (double d) 
{
	int ret = 0;
	element aux;
	aux.d = d;

	if ((aux.l >= 0x7ff0000000000001L && aux.l <= 0x7ffffffffffffL) || (aux.l >= 0xfff0000000000001L && aux.l <= 0xffffffffffffffffL)) {
		ret = 3;
	} else if (aux.l == 0x7ff0000000000000L) {
		ret = 1;
	} else if (aux.l == 0xfff0000000000000L) {
		ret = 2;
	}

	return ret;
}

string float_to_string (float f) 
{
	stringstream ret;
	switch (checkFloat(f)) {
		case 0:
			ret << f;
			break;
		case 1:
			ret << "+Inf";
			break;
		case 2:
			ret << "-Inf";
			break;
		case 3:
			ret << "NaN";
			break;
	}

	return ret.str();
}

long u4_to_long (ClassLoaderType high, ClassLoaderType low) 
{
	int64_t ret;
	
	ret = (((int64_t) high.u4) << 32) | low.u4;
	
	return ret;
}

double u4_to_double (ClassLoaderType high, ClassLoaderType low) 
{
	double ret;
	uint64_t checkBoundaries = u4_to_long(high, low);
	
	if (checkBoundaries == 0x7ff0000000000000L) {
		//return infinity??
	} else if (checkBoundaries == 0xfff0000000000000L) {
		//return negative infinity??
	} else if ((checkBoundaries >= 0x7ff0000000000001L) && (checkBoundaries <= 0x7ffffffffffffL)) {
		//return NaN??
	} else if ((checkBoundaries >= 0xfff0000000000001L) && (checkBoundaries <= 0xffffffffffffffffL)) {
		//return NaN??
	} else {
		int64_t s = ((checkBoundaries >> 63) == 0) ? 1 : -1;
		int64_t e = ((checkBoundaries >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (checkBoundaries & 0xfffffffffffffL) << 1 : (checkBoundaries & 0xfffffffffffffL) | 0x10000000000000L;
		
		ret = s * m * pow(2, (e-1075));
	}
	
	return ret;
}

float u4_to_float (ClassLoaderType in) 
{
	float ret;
	
	int s = ((in.u4 >> 31) == 0) ? 1 : -1;
	int e = ((in.u4 >> 23) & 0xff);
	int m = (e == 0) ? (in.u4 & 0x7fffff) << 1 : (in.u4 & 0x7fffff) | 0x800000;

	ret = s * m * pow(2, (e-150));
		
	return ret;
}

