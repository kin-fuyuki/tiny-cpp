#pragma once
#ifndef TINYTERM_H
#define TINYTERM_H

#include <cstdio>
#include <cstring>
#include <stdarg.h>
#include <string>

namespace tiny {
	
struct ErrorLevel {
	int value;
	ErrorLevel(int var){
		this->value=var;
	}
	void setvalue(int var){
		this->value=var;
	}
};

extern tiny::ErrorLevel level;

inline const char* WHITE   		= "\033[0m";
inline const char* BLACK   		= "\033[30m";
inline const char* RED     		= "\033[31m";
inline const char* GREEN   		= "\033[32m";
inline const char* YELLOW  		= "\033[33m";
inline const char* BLUE    		= "\033[34m";
inline const char* MAGENTA 		= "\033[35m";
inline const char* CYAN    		= "\033[36m";
inline const char* BGRED   		= "\033[41m";
inline const char* BGBLACK 		= "\033[40m";
inline const char* BGGREEN 		= "\033[42m";
inline const char* BGYELLOW		= "\033[43m";
inline const char* BGBLUE  		= "\033[44m";
inline const char* BGMAGENTA	="\033[45m";
inline const char* BGCYAN  		= "\033[46m";
inline const char* BGWHITE 		= "\033[47m";
inline const char* BOLDBLACK  	= "\033[1m\033[30m";
inline const char* BOLDRED    	= "\033[1m\033[31m";
inline const char* BOLDGREEN  	= "\033[1m\033[32m";
inline const char* BOLDYELLOW 	= "\033[1m\033[33m";
inline const char* BOLDBLUE   	= "\033[1m\033[34m";
inline const char* BOLDMAGENTA	= "\033[1m\033[35m";
inline const char* BOLDCYAN   	= "\033[1m\033[36m";
inline const char* BOLDWHITE  	= "\033[1m\033[37m";

#define ending \
	mixer.append(info); mixer.append("\033[0m\n");\
	const char * finalinfo=mixer.c_str();\
	va_start (arg, finalinfo);\
	vfprintf (stdout, finalinfo, arg);\
	va_end (arg);

inline void echo(char * info,...){
	if (level.value==4)
	{
	va_list arg;
	std::string mixer=info;
	mixer.append("\n");
	const char * finalinfo=mixer.c_str();
	va_start (arg, finalinfo);
	vfprintf (stdout, finalinfo, arg);
	va_end (arg);}
}
inline void warning( char * info,...){
	if (level.value>=1)
	{
	va_list arg;
	std::string mixer=YELLOW;ending
}
}
inline void fatal( char * info,...){
	va_list arg;
	std::string mixer=BOLDWHITE+std::string(BGRED);ending
}
inline void error( char * info,...){
	if (level.value>=0)
	{
	va_list arg;
	std::string mixer=BOLDRED;ending
}}
inline void success(char * info , ...){
	if (level.value>=2)
	{
	va_list arg;
	std::string mixer=GREEN;ending}
}
inline void message(char * info , ...){
	if (level.value>=3)
	{
	va_list arg;
	std::string mixer=BOLDWHITE;ending}
}
inline void startup(char* game,char*version){
int lv=level.value;level.value=6;
	echo("%s %s",game,version);
	warning("be warned that");
	error("ERRORS MIGHT OCCUR!!!");
	success("but dont worry");
	message("this is not an error");
	fatal("I SWEAR");
level.value=lv;
}

}
#endif