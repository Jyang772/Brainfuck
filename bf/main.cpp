#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#define DEFAULT_ARRAY_SIZE 30000

using namespace std;

string* bf_read_file(string);
string* minimize_file(string *);
char* bf_create_array(int);
char* bf_execute(string*, char*, char*);

struct Command* build_command_struct(string *);


struct Command{
    char type;
    int magnitude;
    struct Command *parent_command;
    struct Command *next_command;
    struct Command *child_command;
};

int main(int argc, char* argv[])
{

    string filename;
    int optimizeFlag = 0;
    int interactive = 0;

    int index;
    int c;

    if(argc == 1){
        interactive = 1;
    }
    else
        filename = argv[1];


    string* program = bf_read_file(filename);
    cout << *program << endl;
    char *prog_array = bf_create_array(DEFAULT_ARRAY_SIZE);
    char *ptr = prog_array;

    ptr = bf_execute(program,prog_array,ptr);

    cout << "End" << endl;

    delete program;
    return 0;
}


string* bf_read_file(string filename){
    std::ifstream is(filename,std::ios::in | std::ios::binary);

    string *contents = new string;
    if(is)
    {
        std::ostringstream buffer;
        buffer << is.rdbuf();
        is.close();
        *contents = buffer.str();

        cout << "before" << endl;
        minimize_file(contents);
        return contents;
    }
}

string* minimize_file(string* file_string){

    cout << "minimize_file" << endl;

    string validChars = "<>.,+-[]";
    int codeLength = file_string->length();
    int pos = 0;

    cout << "codeLength: " << codeLength << endl;

    for(int i=0; i<codeLength; i++)
    {
        char current_char = (*file_string)[i];
        if(validChars.find(current_char) != -1){
            cout << current_char << endl;
            (*file_string)[pos] = current_char;
            pos++;
        }
    }

    file_string->resize(pos);

    return file_string;

}

char *bf_create_array(int array_size){

    char *result = new char[array_size];
    memset(result,'\0',array_size);
    return result;

}

char *bf_execute(string* program, char *prog_array, char *ptr){

    cout << "bf_execute" << endl;
    struct Command *command_struct = build_command_struct(program);
    struct Command *head = command_struct;
    while (command_struct->next_command) {
        command_struct = command_struct->next_command;
        switch (command_struct->type) {
        case '+':
            *ptr += command_struct->magnitude;
            break;
        case '-':
            *ptr -= command_struct->magnitude;
            break;
        case '>':
            ptr += command_struct->magnitude;
            break;
        case '<':
            ptr -= command_struct->magnitude;
            break;
        case '.':
            putchar(*ptr);
            break;
        case ',':
            *ptr = getchar();
            break;
        case '[':
            if (*ptr != 0) {
                command_struct = command_struct->child_command;
            }
            break;
        case ']':
            if (*ptr != 0) {
                command_struct = command_struct->parent_command->child_command;	//Return to the 'S'
            } else {
                command_struct = command_struct->parent_command;
            }
        default:
            break;
        }
    }
    delete head;
    return ptr;
}




struct Command *new_command(char type, struct Command *parent){
    struct Command *comm = new Command;
    comm->type = type;
    comm->magnitude = 1;
    comm->parent_command = parent;
    comm->next_command = NULL;
    comm->child_command = NULL;
    return comm;
}


struct Command *build_command_struct(string *code)
{
    cout << "build_commmand_struct" << endl;
    int code_len = code->length();
    cout << "code_len: " << code_len << endl;

    struct Command *head = new_command('S', NULL);
    struct Command *comm = head;

    for(int i=0; i<code_len; i++){
        struct Command *next = new_command((*code)[i],comm->parent_command);
        comm->next_command = next;
        comm = next;

        cout << "comm->type : " << comm->type << endl;

        if(comm->type == '['){
            struct Command *child = new_command('S',comm);
            comm->child_command = child;
            comm = child;
        }
        else if(comm->type == ']')
            comm = comm->parent_command;
    }

    return head;
}


