#include <sstream>
#include <string>
#include <fstream>
#include <map>
std::string get(std::string);
std::map<std::string,std::string> variables;
std::map<std::string,int> functions;

#define CALL ""
#ifdef _WIN32
#undef CALL
#define CALL "call"
#endif

#ifdef linux
#undef CALL
#define CALL "exec"
#endif

#ifdef __APPLE__
#undef CALL
#define CALL "exec"
#endif
#include "term.h"
int call(
    std::string lines){
    std::string com;
    com.append(CALL);
    
    success("command:%s\nexecuting\n\n",lines.c_str());
    com.append(lines.c_str());

    system(com.c_str());
    success("\n\n");
    return 0;
}
ErrorLevel level(1);
int set(std::string setter){
    std::string name=setter.substr(setter.find_first_of(" ")+1,setter.find("=")-4);
    std::string value=setter.substr(setter.find("=")+1);
    variables[name]=value;
    warning("key %s set as value %s\n\n",name.c_str(),value.c_str());
    //success("\nvar: %s\n",variables[name].c_str());
    return 0;
}

int fn(std::string setter,int pos){
    std::string name=setter.substr(setter.find_first_of(":")+1);
    functions[name]=pos;
    warning("function %s set in position %i\n\n",name.c_str(),pos);
    //success("\nvar: %s\n",variables[name].c_str());
    return 0;
}
std::string get(std::string key){
    std::string k=key.substr(key.find_first_of('%')+1,key.find_last_of('%')-1);
    std::string var=variables[k];
    if (var==""){
        error("\ncould not get variable with key \"%s\"\n",k.c_str());
        exit(1);
    }
    //success("\ngetting variable \"%s\" with key \"%s\"\n",var.c_str(),k.c_str());
    return var;
}

#define A lines.append
int main(int argc, char *argv[]){

    for (int i=2;i<argc;i++){
        if (argv[i][0]=='-'&&argv[i][1]=='w'){i++;
            level= std::stoi(argv[i]);
        }else{
        std::string key="set ";
        key.append(std::to_string(i-2)).append("=").append(argv[i]);
        set(key);
    }}
    warning("tiny runner v0.8\n\n\n");
    std::fstream fileStream;
    fileStream.open(argv[1]);
    if (!fileStream.fail()){
    std::ifstream infile(argv[1]);
    std::string line;
    std::string lines;
    int mode=-1;
    bool infunc=false;
    while (std::getline(infile, line))
    {
        const char * l=line.c_str();
        error((char *)l);
        if (line.length()!=0){
            switch (l[0])
            {
            case '\\':
                if (l[1]=='n'){
                    call(lines);
                    lines.clear();}
                else{
                    A(++l);
                }
                break;
            case '%':
                lines.append(get(line));
                break;

            case ';':
                break;
            case 's':
                if (l[1]=='e'&&l[2]=='t'){
                            call(lines);
                            lines.clear();
                            set(line);}
                else{
                A(" "+line);

                }
                break;
            case ':':
                fn(line, infile.cur);
                /* code */
            
            default:
                A(" "+line);
                break;
            }
        }
        
    }
    call(lines);
    return 0;
    }
    error("could not locate file %s",argv[1]);
    return 1;
}