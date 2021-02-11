#include <stdio.h>
#include <stdlib.h> //atoi(...)

/*
    to-do list
    1) key "-add"  - to add case and deadline separated by space;
    2) key "-show" - to show all the cases with deadlines;
    3) key "-del"  - to delete the case(you must specify case name).
*/

int scanning(char **argv) // Identifying the number of strings
{
    int ch, count = 0;
    FILE *fscan;
    fscan = fopen("to-do_list", "r");
    
    if (!fscan){
        printf("File open for scanning error");
        return 0;
    }
    
    while((ch = fgetc(fscan)) != EOF){
        if(ch == '\n')
            ++count;
    }
    
    if(fclose(fscan))
        printf("File close for scanning error");
        
    return count;
}

int add_the_case(char **argv)
{
    FILE *f1;
    f1 = fopen("to-do_list", "a");
    
    if(!f1){
        printf("File open error\n");
        return 1;
    }
    
    for(int i = 0; *(*(argv + 2) + i) != '\0'; ++i) // Read the string character by character
        fputc(*(*(argv + 2) + i), f1);
    fputc(' ', f1);
    for(int i = 0; *(*(argv + 3) + i) != '\0'; ++i)
        fputc(*(*(argv + 3) + i), f1);
    fputc('\n', f1);
    
    if(fclose(f1)){
        printf("File close error\n");
        return 1;
    }
    return 0;
}

int show_all_the_cases(char **argv)
{
    FILE *f1;
    int ch = 0;
    f1 = fopen("to-do_list", "r");
    
    if(!f1){
        printf("File open error\n");
        return 1;
    }
    
    while((ch = fgetc(f1)) != EOF)
        fputc(ch, stdout);
    
    if(fclose(f1)){
        printf("File close error\n");
        return 1;
    }
    return 0;
}

int delete_the_case(char **argv)
{
    char arr[scanning(argv)][50];
    FILE *f1;
    f1 = fopen("to-do_list", "r");
    if (!f1){
        printf("File open error\n");
        return 1;
    }
    int case_number = atoi(*(argv + 2)), i = 0, j = 0, ch, check = 0; // case_number - 1
    while((ch = fgetc(f1)) != EOF){
        if(check == 0)
            arr[i][j++] = ch;
        if (ch == '\n'){
            arr[i][j] = '\0';
            ++i;
            j = 0;
        }
        if(i == case_number - 1)
            check = 1;
        if(i == case_number)
            check = 0;
    }
    int count_of_strings = i;
    i = j = 0;
    if(fclose(f1)){
        printf("File close error\n");
        return 1;
    }
    if(!(f1 = fopen("to-do_list", "w"))){
        printf("File open error two\n");
        return 1;
    } 
    while(i < count_of_strings){ // Maybe <=
        if(i == case_number - 1){
            ++i;
            continue;
        }
        if(arr[i][j] != '\n')
            fputc(arr[i][j++], f1);
        else if(arr[i][j] == '\n'){
            fputc(arr[i++][j], f1);
            j = 0;
        }
    }
    if(fclose(f1)){
        printf("File close error\n");
        return 1;
    }
    
    return 0;
}

int strings_compare(char *str1, char *str2)
{
    for(int i = 0; str1[i] != '\0' || str2[i] != '\0'; ++i){
        if (str1[i] != str2[i])
            return 1;
        if (str1[i] == '\0' && str2[i] != '\0')
            return 1;
        if (str1[i] != '\0' && str2[i] == '\0')
            return 1;
    }
    return 0;
}

void help()
{
    printf("Program to-do list\n");
    printf("Input key -add to add case and deadline separated by space\n");
    printf("Input key -show to show all the cases with deadlines\n");
    printf("Input key -del to delete case(you must specify case name)\n");
}

int main(int argc, char **argv)
{
    if(argc < 1){
        printf("Too few arguments\n");
        return 1;
    }
    else if(argc > 4){
        printf("Too many arguments\n");
        return 1;
    }
    
    if(strings_compare(*(argv + 1), "-add") == 0 && argc == 4)
        add_the_case(argv);
    else if(strings_compare(*(argv + 1), "-show") == 0 && argc == 2)
        show_all_the_cases(argv);
    else if(strings_compare(*(argv + 1), "-del") == 0 && argc == 3)
        delete_the_case(argv);
    else if(strings_compare(*(argv + 1), "-help") == 0 && argc == 2)
        help();
    else
        printf("misuse of the program\n");
        
    return 0;
}
