/*!
 * \file
 * \brief fields.cpp
 */
/**
 * @file fields.cpp
 * @details Módulo responsável pela manipulação dos campos existentes no arquivo .class
 */

#include "fields.h"

void printField (field_info f, cp_info *cp, int index){
	printf("\tField %d : \n", index);
	printf("\t%s", getFieldFlags(f.accessFlags).c_str());
	printf("\t\tNome: %s\n",  dereferenceIndex(cp, f.name_index).c_str());
	printf("\t\tDescritor: %s\n", dereferenceIndex(cp, f.descriptor_index).c_str());
	printf("\t\tNumero de Atributos: %d\n", (int) f.attributes_count);

	for (int i = 0; i < f.attributes_count; i++) {
		printf("\t\t\tAtributo %d:", i);
		printAttribute(f.attributes[i], cp);
	}
}

void printFields (field_info *f, cp_info *cp, int length){
	for (int i = 0; i < length; i++) {
		printField(f[i], cp, i);
	}
}

field_info readField (FILE* fp,cp_info* cp) {
	field_info ret;

	ret.accessFlags = readU2(fp) & 0X0df;
	ret.name_index = readU2(fp);
	ret.descriptor_index = readU2(fp);
	ret.attributes_count = readU2(fp);
	ret.attributes = (attribute_info *) malloc(sizeof(attribute_info) * ret.attributes_count);
	for (int i = 0; i < ret.attributes_count; i++) {
		ret.attributes[i] = readAttribute(fp,cp);
	}

	return ret;
}

field_info *readFields (FILE* fp, int length,cp_info* cp) {
	field_info *ret = (field_info *) malloc(sizeof(field_info) * length);

	for (int i = 0; i < length; i++) {
		ret[i] = readField(fp,cp);
	}
	return ret;
}

string getFieldFlags (unsigned short flags) {
	bool first = true;
	string ret = "";

	if (flags & 0x01) {
		if (first) {
			 ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_PUBLIC";
	}

	if (flags & 0x02) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_PRIVATE";
	}

	if (flags & 0x04) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_PROTECTED";
	}

	if (flags & 0x08) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_STATIC";
	}

	if (flags & 0x010) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_FINAL";
	}

	if (flags & 0x040) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_VOLATILE";
	}

	if (flags & 0x080) {
		if (first) {
			ret += "\tflags: ";
			first = false;
		} else {
			ret += ", ";
		}
		ret += "ACC_TRANSIENT";
	}

	ret += "\n";

	return ret;
}
