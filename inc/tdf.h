#include <boost/unordered/unordered_map_fwd.hpp>
#include <boost/unordered_map.hpp>
#include <boost/array.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#ifndef TINYDATAFORMAT_H
#define TINYDATAFORMAT_H
#define TINYDEFINEHEADER "0000_TDF_HEADER_DEFINE"
#include "term.h"

#define GENSTART {int LAST = trimmed.find(' ', 3);if (LAST == std::string::npos) goto FAILTOPARSE;std::string KEY = trimmed.substr(2, LAST - 2);
#define GENEND (VALUE)};todelete.push_back(DAT.datapointer); (*current)[KEY]=DAT;break;}
#define GENMID ); if (idx != sub.size()) goto FAILTOPARSE;}catch(const std::invalid_argument&){goto FAILTOPARSE;}TDF_DATA DAT={

#define INTGENSTART GENSTART std::string sub = trimmed.substr(LAST + 1);size_t idx; int VALUE; try{ VALUE=stoi(sub, &idx,
#define INTGENEND , new int GENEND

#define SETSTART value){boost::unordered_map<std::string,TDF_DATA>*current=data;for(size_t i=0;i<path.size();i++){\
	auto it=current->find(path[i]);if(it==current->end()){if(i==path.size()-1){TDF_DATA DAT={
#define SETMID (value)};todelete.push_back(DAT.datapointer);(*current)[path[i]]=DAT;return;}else{\
	boost::unordered_map<std::string,TDF_DATA>*newmap=new boost::unordered_map<std::string,TDF_DATA>();TDF_DATA DAT={TDF_CLASS,newmap}\
	;todelete.push_back(DAT.datapointer);(*current)[path[i]]=DAT;current=newmap;}}else{if(i==path.size()-1){if(it->second.type!=
#define SETEND *>(it->second.datapointer)=value;return;}if(it->second.type!=TDF_CLASS)throw TDF_ERR(SET_MISMATCH,filepath,path);\
	current=(boost::unordered_map<std::string,TDF_DATA>*)(it->second.datapointer);}}}


#define GETSTART (std::vector<std::string>path){boost::unordered_map<std::string,TDF_DATA>*current=data;for(size_t i=0;i<path.size();i++){\
	auto it=current->find(path[i]);if(it==current->end())throw TDF_ERR(PATH_NOT_FOUND,filepath,path);if(i==path.size()-1){if(it->second.type!=
#define GETMID )throw TDF_ERR(GET_MISMATCH,filepath,path);return *static_cast<
#define GETEND *>(it->second.datapointer);}\
	if(it->second.type!=TDF_CLASS)throw TDF_ERR(GET_MISMATCH,filepath,path);current=(boost::unordered_map<std::string,TDF_DATA>*)(it->second.datapointer);}\
	throw TDF_ERR(PATH_NOT_FOUND,filepath,path);}

#define DEFAULTGET(TYPE_NAME, ACTUAL_TYPE) ACTUAL_TYPE TYPE_NAME(std::vector<std::string> path, ACTUAL_TYPE defaultval) {try { return\
	TYPE_NAME(path); } catch (TDF_ERR &e) { warning((char*)e.what()); return defaultval; } }

namespace tiny {
enum TDF_ERROR{
	SET_MISMATCH=1,
	GET_MISMATCH=2,
	PATH_NOT_FOUND=3,
	UNKNOWN_ERROR=-1,
	FILE_NOT_FOUND=4,
	FAILED_TO_PARSE=5,
	NULL_POINTER=6,
};
class TDF_ERR : public std::exception
  {
  public:
	std::string message;
	
	explicit TDF_ERR(TDF_ERROR err,std::string file,std::vector<std::string>path) _GLIBCXX_TXN_SAFE{
		message="TDF ERROR: ";
		
		switch(err){
			case SET_MISMATCH:
				message+="SET TYPE MISMATCH ";
				break;
			case GET_MISMATCH:
				message+="GET TYPE MISMATCH ";
				break;
			case PATH_NOT_FOUND:
				message+="PATH NOT FOUND ";
				break;
			case FILE_NOT_FOUND:
				message+="FILE NOT FOUND "+file;
				return;
			case FAILED_TO_PARSE:
				message+="FAILED TO PARSE "+file+" AT LINE :"+path[0];
				return;
			case NULL_POINTER:
				message+="NULL POINTER of selector "+path[0];
				message+="FAILED TO PARSE "+file+" AT LINE :"+path[1];
				return;
			default:
				message+="UNKNOWN ERROR ";
				break;
		}
		
		message+=" ON FILE: "+file+" AT PATH: ";
		for(size_t i=0;i<path.size();i++){
			message+=path[i];
			if(i!=path.size()-1)
			message+=" . ";
		}
	}
	virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW{
		return message.c_str();
	}
	};

enum TDF_Type : unsigned char {
    TDF_DEFINES = 10,	//bool
    TDF_BOOL = 3,		//bool
    TDF_CHAR = 1,		//char
    TDF_BINARY = 4,		//int
    TDF_INT = 5,		//int
    TDF_HEX = 7,		//int
    TDF_STR = 0,		//string
    TDF_BLOCK = 200,	//string
    TDF_FLOAT = 6,		//float
    TDF_POINTER = 8,	//vector<string>
    TDF_CLASS = 9,		//class
};
struct TDF_DATA {
    TDF_Type type;
    void* datapointer;
};
struct TDF_FUNCS{
	boost::unordered_map<char,int>funcs;
	TDF_DATA(*FUNCS[])(std::string);
};
struct TDF_FILE{
	boost::unordered_map<std::string,TDF_DATA>* data=nullptr;
	char*filepath;
	TDF_FUNCS FUNCS;
	std::vector<void*> todelete;
	void close(){
		for(size_t i=0;i<todelete.size();i++){
			delete static_cast<boost::unordered_map<std::string,TDF_DATA>*> (todelete[i]);
		}
	}
	void* read(){
		char CCHAR=' ';
		int INDEX=0;
		std::ifstream file(filepath);
		
		if (file.is_open()) {
			if (data!=nullptr)
			delete data;
			data=new boost::unordered_map<std::string,TDF_DATA>();
			todelete.push_back(data);
			boost::unordered_map<std::string,TDF_DATA>*current=data;
			
			std::vector<boost::unordered_map<std::string,TDF_DATA>*>stack={};
			std::vector<std::string>pathvec={};
			bool textblock=false;
			std::string BLOCK;
			std::string BLOCKKEY;
			std::vector<std::string> *defines=new std::vector<std::string>();
			TDF_DATA defdat={TDF_DEFINES,defines};
			(*current)[TINYDEFINEHEADER]=defdat;
			
			std::string line;
			while (std::getline(file, line)) {
				++INDEX;
				if (line.length()==0){continue;}
				if (textblock){
					std::string blockline = line;
					size_t lead = blockline.find_first_not_of(' ');
					if(lead != std::string::npos){
					  blockline = blockline.substr(lead);
					}
					if (blockline=="\\"){
						textblock=false;
						TDF_DATA DAT={TDF_BLOCK,new std::string(BLOCK)};
						todelete.push_back(DAT.datapointer);
						(*current)[BLOCKKEY]=DAT;
					}else{
						BLOCK+=line+"\n";
					}
				}
				else{
					std::string trimmed = line;
					size_t lead = trimmed.find_first_not_of(' ');
					if(lead != std::string::npos){
					  trimmed = trimmed.substr(lead);
					}else{
					  continue;
					}
					if (trimmed.empty() || trimmed[0]=='#'){continue;}
					if (trimmed.size() > 1 && trimmed[1]==' '){
						CCHAR=trimmed[0];
						switch (CCHAR) {
							
							case '"':GENSTART std::string VALUE; VALUE=trimmed.substr(LAST + 1); TDF_DATA DAT = { TDF_STR, new std::string GENEND
							
							
							case 'S':{
								int LAST = trimmed.find(' ', 2);
								std::string KEY;
								if (LAST != std::string::npos){
									KEY = trimmed.substr(2, LAST - 2);
								}else{
									KEY = trimmed.substr(2);
								}
								BLOCKKEY=KEY;
								BLOCK="";
								textblock=true;
							break;}
							
							
							case '\'':GENSTART if (LAST + 1 >= trimmed.size()) goto FAILTOPARSE;char VALUE=trimmed.at(LAST + 1);
								if (LAST + 2 < trimmed.size()) goto FAILTOPARSE;TDF_DATA DAT = { TDF_CHAR, new char GENEND
							
							
							case 'i': INTGENSTART 0 GENMID TDF_INT INTGENEND
							
							
							case 'h':INTGENSTART 16 GENMID TDF_HEX INTGENEND
							
							
							case 'b':INTGENSTART 2 GENMID TDF_BINARY INTGENEND
							
							
							case 'B': GENSTART if (LAST + 1 >= trimmed.size()) goto FAILTOPARSE; char c=trimmed.at(LAST + 1);
								bool VALUE = c=='T'; if (LAST + 2 < trimmed.size()) goto FAILTOPARSE; TDF_DATA DAT={TDF_BOOL,new bool GENEND
							
							
							case 'f':GENSTART std::string sub = trimmed.substr(LAST + 1);size_t idx;float VALUE; try{VALUE=stof(sub, &idx);
								if (idx != sub.size()) goto FAILTOPARSE;}catch(std::invalid_argument&){goto FAILTOPARSE;}TDF_DATA DAT={TDF_FLOAT,new float GENEND
							
							
							case '@':GENSTART
								std::string VALUE=trimmed.substr(LAST + 1);
								std::vector<std::string>*ptr=new std::vector<std::string>();
								size_t pos=0;
								std::string token;
								while((pos=VALUE.find('.'))!=std::string::npos){
									token=VALUE.substr(0,pos);
									ptr->push_back(token);
									VALUE.erase(0,pos+1);
								}
								ptr->push_back(VALUE);
								TDF_DATA DAT={TDF_POINTER,ptr};
								todelete.push_back(DAT.datapointer);
								(*current)[KEY]=DAT;
							break;}
							
							
							case '{':{
								int LAST = trimmed.find(' ', 3);
								std::string KEY;
								if (LAST != std::string::npos){
									KEY = trimmed.substr(2, LAST - 2);
								}else{
									KEY = trimmed.substr(2);
								}
								boost::unordered_map<std::string,TDF_DATA>*newmap=new boost::unordered_map<std::string,TDF_DATA>();
								TDF_DATA DAT={TDF_CLASS,newmap};
								todelete.push_back(DAT.datapointer);
								(*current)[KEY]=DAT;
								std::vector<std::string> *defines=new std::vector<std::string>();
								TDF_DATA defdat={TDF_DEFINES,defines};
								(*newmap)[TINYDEFINEHEADER]=defdat;
								stack.push_back(current);
								pathvec.push_back(KEY);
								current=newmap;
							break;}
							
							
							default:{
								try {
									int PATH=FUNCS.funcs.at(trimmed[0]);
									int LAST = trimmed.find(' ', 3);
									if (LAST == std::string::npos)goto FAILTOPARSE;
									std::string KEY = trimmed.substr(2, LAST - 2);
									(*current)[KEY]=FUNCS.FUNCS[PATH](trimmed);
									todelete.push_back((*current)[KEY].datapointer);
									if ((*current)[KEY].datapointer==nullptr) goto FAILTOPARSE;
								}catch(const std::out_of_range&){
									break;
								}
							break;}
							}
					}else if(trimmed == "}"){
						if(stack.empty())goto FAILTOPARSE;
						current=stack.back();
						stack.pop_back();
						if(!pathvec.empty())pathvec.pop_back();
					}else{
						auto it = current->find(TINYDEFINEHEADER);
						if (it == current->end() || it->second.type != TDF_DEFINES) goto FAILTOPARSE;
						std::vector<std::string>* defines = static_cast<std::vector<std::string>*>(it->second.datapointer);
						defines->push_back(line);
					}
				}
			}
			return data;
		}else{
			throw TDF_ERR(FILE_NOT_FOUND,filepath,{});
		}
		NULLPOINTER:
			throw TDF_ERR(NULL_POINTER,filepath,{std::string(1,CCHAR),std::to_string(INDEX)});
		FAILTOPARSE:
			throw TDF_ERR(FAILED_TO_PARSE,filepath,{std::to_string(INDEX)});
		delete data;
		data=nullptr;
		return nullptr;
	}
	//get
	
		#define ITSNOT it->second.type!=
		float getfloat GETSTART ITSNOT TDF_FLOAT GETMID float GETEND DEFAULTGET(getfloat, float)

        bool getbool GETSTART ITSNOT TDF_BOOL GETMID bool GETEND DEFAULTGET(getbool, bool)

		int getint GETSTART (ITSNOT TDF_INT)&&(ITSNOT TDF_HEX)&&(ITSNOT TDF_BINARY) GETMID int GETEND DEFAULTGET(getint, int)

        std::string getstring GETSTART (ITSNOT TDF_STR)&&(ITSNOT TDF_BLOCK) GETMID std::string GETEND DEFAULTGET(getstring, std::string)

        std::vector<std::string> getpointer GETSTART ITSNOT TDF_POINTER GETMID std::vector<std::string> GETEND DEFAULTGET(getpointer, std::vector<std::string>)

        char getchar GETSTART ITSNOT TDF_CHAR GETMID char GETEND DEFAULTGET(getchar, char)

		bool defined(std::vector<std::string>path){
			boost::unordered_map<std::string,TDF_DATA>*current=data;
			for(size_t i=0;i<path.size();i++){auto it=current->find(path[i]);
				if(it==current->end())return false;
				if(i==path.size()-1)return true;
				if(it->second.type!=TDF_CLASS)return false;
				current=(boost::unordered_map<std::string,TDF_DATA>*)it->second.datapointer;}
			return false;}
		DEFAULTGET(defined, bool)

		boost::unordered_map<std::string,TDF_DATA>* getclass(std::vector<std::string>path){
			boost::unordered_map<std::string,TDF_DATA>*current=data;
			for(size_t i=0;i<path.size();i++){
				auto it=current->find(path[i]);
				if(it==current->end())throw TDF_ERR(PATH_NOT_FOUND,filepath,path);
				if(i==path.size()-1){
					if(ITSNOT TDF_CLASS)throw TDF_ERR(GET_MISMATCH,filepath,path);
					return (boost::unordered_map<std::string,TDF_DATA>*)(it->second.datapointer);
				}
				if(ITSNOT TDF_CLASS)throw TDF_ERR(GET_MISMATCH,filepath,path);
				current=(boost::unordered_map<std::string,TDF_DATA>*)(it->second.datapointer);
			}
			throw TDF_ERR(PATH_NOT_FOUND,filepath,path);
		}
		boost::unordered_map<std::string,TDF_DATA>* getclass(std::vector<std::string>path,boost::unordered_map<std::string,TDF_DATA>* defaultval){
			try {
				return getclass(path);}
			catch(TDF_ERR e) {
				warning((char*)e.what());
				return defaultval;
			}
		}
//set

		void setbool(std::vector<std::string>path, bool SETSTART TDF_BOOL, new bool SETMID TDF_BOOL) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<bool SETEND

		void setint(std::vector<std::string>path, int SETSTART TDF_INT, new int SETMID TDF_INT) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<int SETEND

		void setstring(std::vector<std::string>path, std::string SETSTART TDF_STR, new std::string SETMID TDF_STR) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<std::string SETEND

		void setblock(std::vector<std::string>path, std::string SETSTART TDF_BLOCK, new std::string SETMID TDF_BLOCK) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<std::string SETEND

		void setfloat(std::vector<std::string>path, float SETSTART TDF_FLOAT, new float SETMID TDF_FLOAT) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<float SETEND

		void setchar(std::vector<std::string>path, char SETSTART TDF_CHAR, new char SETMID TDF_CHAR) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<char SETEND

		void setpointer(std::vector<std::string>path, std::vector<std::string> SETSTART TDF_POINTER, new std::vector<std::string> SETMID TDF_POINTER) throw TDF_ERR(SET_MISMATCH, filepath, path); *static_cast<std::vector<std::string> SETEND

		void define(std::vector<std::string>defines,char* name){
			auto it = data->find(TINYDEFINEHEADER);
			if (it == data->end() || it->second.type != TDF_DEFINES) {
				std::vector<std::string>* newdefines = new std::vector<std::string>();
				TDF_DATA defdat = { TDF_DEFINES, newdefines };
				(*data)[TINYDEFINEHEADER] = defdat;
				todelete.push_back(defdat.datapointer);
				it = data->find(TINYDEFINEHEADER);
			}
			std::vector<std::string>* currentdefines = static_cast<std::vector<std::string>*>(it->second.datapointer);
			for (size_t i = 0; i < defines.size(); i++) {
				currentdefines->push_back(defines[i]);
			}
			currentdefines->push_back(std::string("#define ") + name);
		}
	
	void save(){
		std::ofstream file(filepath, std::ios::out | std::ios::trunc);
		std::string DATA="";
		crawl(data,&DATA,"");
		file<<DATA;
		file.close();
	}
	private:
	void crawl(boost::unordered_map<std::string,TDF_DATA>*map,std::string*STR,std::string indent){
		auto it = map->find(TINYDEFINEHEADER);
		if (it != map->end() && it->second.type == TDF_DEFINES) {
			std::vector<std::string>* defines = static_cast<std::vector<std::string>*>(it->second.datapointer);
			for (auto& def : *defines) {
				*STR += def + "\n";
			}
		}
		for(auto&[key,val]:*map){
			if(key==TINYDEFINEHEADER)continue;
			switch(val.type){
				case TDF_STR:*STR+="\" "+key+" "+*static_cast<std::string*>(val.datapointer)+"\n";break;
				case TDF_CHAR:*STR+="' "+key+" "+*static_cast<char*>(val.datapointer)+"\n";break;
				case TDF_BLOCK:*STR+="S "+key+"\n"+*static_cast<std::string*>(val.datapointer)+"\n\\\n";break;
				case TDF_BOOL:*STR+="B "+key+" "+(*static_cast<bool*>(val.datapointer)?"T":"F")+"\n";break;
				case TDF_BINARY:*STR+="b "+key+" "+std::to_string(*static_cast<int*>(val.datapointer))+"\n";break;
				case TDF_INT:*STR+="i "+key+" "+std::to_string(*static_cast<int*>(val.datapointer))+"\n";break;
				case TDF_FLOAT:*STR+="f "+key+" "+std::to_string(*static_cast<float*>(val.datapointer))+"\n";break;
				case TDF_HEX:*STR+="h "+key+" "+std::to_string(*static_cast<int*>(val.datapointer))+"\n";break;
				
				case TDF_POINTER:{std::vector<std::string>*ptr=static_cast<std::vector<std::string>*>(val.datapointer);
					*STR+="@ "+key+" ";for(size_t i=0;i<ptr->size();i++){*STR+=(*ptr)[i];if(i<ptr->size()-1)*STR+=".";}*STR+="\n";break;}
				
				case TDF_CLASS:*STR+="{ "+key+"\n";crawl((boost::unordered_map<std::string,TDF_DATA>*)(val.datapointer),STR,"");*STR+="}\n";break;
			}
		}
	}
};

}
#endif