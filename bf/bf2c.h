#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void write_header(ofstream &file){

    file << "#include <iostream>\n";
    file << "#include <string.h>\n";
    file << "#include <stdio.h>\n";
    file << "int main(){\n";
    file << "unsigned char* _  = new unsigned char[30000];\n";

}

void write_footer(ofstream &file){
    file << "\nreturn 0;}\n";
}

char get_character(ifstream &input_file){
    char c;

    do{
        c = input_file.get();
    }while(c != EOF && c != '[' && c != ']' && c != '<' && c != '>' && c != '.'
           && c != ',' && c != '+' && c != '-');

    return c;

}

void compile_to_cplusplus(ifstream &input_file, ofstream &file){

    write_header(file);

    char c = get_character(input_file);
    do{
        int movement_counter = 0;
        while( c == '>' || c == '<')
        {
            movement_counter += c == '>' ? 1 : -1;
            c = get_character(input_file);
        }
        if(movement_counter)
        {
            //fprintf(file,"_ += %d;", movement_counter);
            file << "_ += " << movement_counter << ";";
        }

        int value_counter = 0;
        while( c == '+' || c == '-')
        {
            value_counter += c == '+' ? 1 : -1;
            c = get_character(input_file);
        }
        if(value_counter)
        {
            //fprintf(file,"*_ += %d;",value_counter);
            file << "*_ += " << value_counter << ";";
        }

        if(c == '.')
        {
            //fprintf(file, "putchar(*_);\n");
            file << "putchar(*_);\n";
            c = get_character(input_file);
        }
        if(c == ',')
        {
            //fprintf(file, "*_ = getchar();\n");
            file << "*_ = getchar();\n";
            c = get_character(input_file);
        }
        if(c == '[')
        {
            //fprintf(file, "while(*_) {\n");
            file << "while(*_) {\n";
            c = get_character(input_file);
        }
        if(c == ']')
        {
            //fprintf(file, "}\n");
            file << "}\n";
            c = get_character(input_file);
        }
    }while(c!=EOF);
    write_footer(file);
}
