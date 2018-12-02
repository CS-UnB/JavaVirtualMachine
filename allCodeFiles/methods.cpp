/*!
 * \file
 * \brief Methods.cpp
 */

#include "methods.h"

method_info read_Method (FILE* fp,cp_info *cp) 
{
	method_info aux;

	aux.access_flags = readU2(fp) & 0xFFF;
	aux.name_index = readU2(fp);
	aux.descriptor_index = readU2(fp);
	aux.attributes_count = readU2(fp);
	aux.attributes = (attribute_info *) malloc(sizeof(attribute_info) * aux.attributes_count);
	for (int i = 0; i < aux.attributes_count; i++) 
	{
		aux.attributes[i] = readAttribute(fp,cp);
	}

	return aux;
}

method_info *read_Methods (FILE* fp, int length, cp_info *cp) 
{
	method_info *ret = (method_info *) malloc(sizeof(method_info) * length);

	for (int i = 0; i < length; i++) 
	{
		ret[i] = read_Method(fp,cp);
	}

	return ret;
}

void printMethod (method_info f, cp_info *cp) 
{
	
	cout << "" << endl;

	cout << "\tName: " << dereferenceIndex(cp, f.name_index) << endl;

	cout << "\tDescriptor: " << dereferenceIndex(cp, f.descriptor_index) << endl;

	cout << get_Method_Flags(f.access_flags);

	cout << "\tAttribute count: " << (int) f.attributes_count << endl;
	
	for (int i = 0; i < f.attributes_count; i++) 
	{
		cout << "\t\tAttribute " << i << ": " << endl;
		printAttribute(f.attributes[i], cp);
	}
}

void printMethod(method_info f, cp_info *cp, int index) 
{
	cout << "\tMethod " << index << ":" << endl;

	cout << "\t\tName: cp info #" << f.name_index << " " << dereferenceIndex(cp, f.name_index) << endl;

	cout << "\t\tDescriptor: cp info # " << f.descriptor_index << dereferenceIndex(cp, f.descriptor_index) << endl;

	cout << "\t" << get_Method_Flags(f.access_flags);
	
	cout << "\t\tAttribute count: " << (int) f.attributes_count << endl;
	for (int i = 0; i < f.attributes_count; i++) 
	{
		cout << "\tAttribute " << i << ": " << endl;
		printAttribute(f.attributes[i], cp);
	}
}


void printMethods (method_info *f, cp_info *cp, int length) 
{
	for (int i = 0; i < length; i++) 
	{
		printMethod(f[i], cp, i);
	}
}

string get_Method_Flags (uint16_t flags) 
{
	bool first = true;
	string ret = "";

	if (flags & 0x01) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_PUBLIC";
	}

	if (flags & 0x02) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_PRIVATE";
	}

	if (flags & 0x04) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_PROTECTED";
	}

	if (flags & 0x08) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_STATIC";
	}

	if (flags & 0x010) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_FINAL";
	}

	if (flags & 0x020) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_SYNCHRONIZED";
	}

	if (flags & 0x0100) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_NATIVE";
	}

	if (flags & 0x0400) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_ABSTRACT";
	}

	if (flags & 0x0800) 
	{
		if (first) 
		{
			ret += "\tflags: ";
			first = false;
		} 
		else 
		{
			ret += ", ";
		}
		ret += "ACC_STRICT";
	}

	ret += "\n";

	return ret;
}