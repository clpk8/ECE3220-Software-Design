#include <stdio.h>
#include <string.h> // I used this to do some string operations
#include <stdlib.h>
#include <ctype.h> // I used this to do some error checking
//a menu so I can keep on call it when error occur
void menu(){
    printf("You can enter the following options:\n");
    printf("-n: File number (value needed)\n");
    printf("-o: offset value (value needed) \n");
    printf("-s: scale factor (value needed) \n");
    printf("-r: Rename files (name needed) \n");
    printf("-h: Help (display how the program should be called, including the different input options) \n");
    printf("-N: normalized the data\n");
    printf("-C: center the data\n");
    printf("-S: give the statistic of the data\n");
}
struct landm{     //I have a Struct here in order to save the length and max
    int length;   //after reading the data.
    int max;
    int valid; //when 1 means correct file readed, 0 when NULL
};
int data[1500];   //I used this to store unchanged data
double * modified_data; // I used this to store changed data
//Functions headers
struct landm readingFile(char* fn);
double * scaleFactor(int * data, double scale, char* fn, int length);
double * offsetData(int * data, double offset, char* fn, int length);
void writeToFile(double * data, double variable, char* fn, int length);
void renameFile2(int * data, struct landm info, char* newf);
void getStat(int * data, struct landm info, char* fn);
void normalize(int * data, struct landm info, char* fn);
void center(int * data, struct landm info, char* fn);
double getAverage(int * data, struct landm info);
int getMax(int * data, struct landm info);

int main(int argc, char * argv[]) {
    //initial decleartions
    struct landm info;
    int Ifstat = 0, Ifnorm = 0, IfCenter = 0;
    double scale = 0,offset = 0;
    char* ptr;
    char* fpname;
    char* fpn;
    char* newFileName = NULL;
    int filenum = 0;
    int i=1;
    // while loop that ran through the command line argument to switch the informations
    while (i<argc){
        // argv[x][y] x is index of argument in the command line
        // y is the index of character of that argument
        if(argv[i][0] == '-'){
            switch(argv[i][1]){ // this switch is when I know the previous one is '-'
                case 'h':{      // then I will switch the next one to find what I need
                    menu();
                    break;
                }
                case 'n':{
                    if(argv[i+1] == NULL){
                        printf("Please enter a file number!!\n");
                        return EXIT_FAILURE; // I found this way to terminate early
                    }
                    filenum = strtod(argv[i+1],&ptr);
                    fpn = argv[i+1];
                    i+=2; // I have this +2 to check the argument pass one
                    break;
                }
                case 'o':{
                    if(argv[i+1] == NULL){
                        printf("Please enter a offset value!!\n");
                        return EXIT_FAILURE;
                    }
                    if(isdigit(argv[i+1][0])){
                        offset = strtod(argv[i+1],&ptr);
                        i+=2;
                    }
                    else{
                        printf("Please enter a offset value!!\n");
                        return EXIT_FAILURE;
                    }
                    break;
                }
                case 's':{
                    if(argv[i+1] == NULL){
                        printf("Please enter a Scale value!!\n");
                        return EXIT_FAILURE;
                    }
                    if(isdigit(argv[i+1][0])){
                        scale = strtod(argv[i+1],&ptr);
                        i+=2;
                    }
                    else{
                        printf("Please enter a Scale value!!\n");
                        return EXIT_FAILURE;
                    }
                    break;
                    
                }
                case 'r':{
                    if(argv[i+1] == NULL){
                        printf("Please enter the name of your file!!\n");
                        return EXIT_FAILURE;
                    }
                    newFileName = argv[i+1];
                    i+=2;
                    break;
                }
                case 'S':{
                    Ifstat = 1;
                    i++;
                    break;
                }
                case 'N':{
                    Ifnorm = 1;
                    i++;
                    break;
                }
                case 'C':{
                    IfCenter = 1;
                    i++;
                    break;
                }
                default:{
                    printf("You've enter something that is not on the list!\n");
                    menu();
                    return EXIT_FAILURE;
                }
                    
            }
        }
        else if (isdigit(argv[i][0])){
            printf("%c is a random num\n",argv[i][0]);
            i++;
            menu();
            return EXIT_FAILURE;
            
        }
        else if (isalpha(argv[i][0])){
            printf("%c is a random char\n",argv[i][0]);
            i++;
            menu();
            return EXIT_FAILURE;
        }
        //after it went throught all the command line argument, if file number is not found... it is error
    }
    if(filenum == 0){
        printf("You need to enrter -n in any cases");
        menu();
        return EXIT_FAILURE;
    }
    //if it did not quit, then means we found the correct file
    info = readingFile(fpn); // it return a struct that I used to conatain infos
    
    if(info.valid == 0){
        printf("The file is invalid, please double check\n");
        return EXIT_FAILURE;
    }
    // in the switch, i set then to 1 if encounter the corsponding letter
    if(offset != 0){
        modified_data = offsetData(data, offset, fpn, info.length);
    }
    if(scale != 0){
        modified_data = scaleFactor(data, scale, fpn, info.length);
    }
    if (newFileName != NULL){
        renameFile2(data, info, newFileName); //use rename f 2
    }
    if (Ifstat == 1){
        getStat(data, info, fpn);
    }
    if (Ifnorm == 1){
        normalize(data, info, fpn);
    }
    if (IfCenter == 1){
        center(data, info, fpn);
    }
    return 0;
}
//reading function
struct landm readingFile(char* fn){
    char fpname[25];
    int filenum;
    char* ptr;
    filenum = strtod(fn,&ptr);
    sprintf(fpname,"Raw_data_%02d.txt",filenum);
    printf("\nThe File being readed is named %s\n",fpname);
    int data1;
    struct landm info;
    int length,max,i = 0;
    FILE* fp;
    fp = fopen(fpname, "r");
    if (fp == NULL){
        printf("Wrong file selected\n");
        info.valid = 0;
        return info;
    }
    else{
        fscanf(fp,"%d %d",&length,&max);
        while (!feof(fp)){
            fscanf(fp,"%d",&data1);
            data[i] = data1;
            i++;
        }
        fclose(fp);
    }
    info.valid = 1;
    info.length = length;
    info.max = max;
    return info;
    
}

// scaleFactor function
double * scaleFactor(int * data, double scale, char* fn, int length)
{
    int i = 0;
    double datain;
    char fpname[25];
    int filenum;
    char* ptr;
    double modifieddata[1500];
    filenum = strtod(fn,&ptr); // get the number off a string
    sprintf(fpname,"Scaled_data_%d.txt",filenum); //sprintf to pull the file name together
    printf("\nThe File created is named %s\n",fpname);
    while(i < length){
        datain = data[i] * scale;
        modifieddata[i] = datain;
        i++;
    }
    writeToFile(modifieddata, scale, fpname, length);
    return modifieddata;
}
//I wrote a write file because i found that i need to write file many time
void writeToFile(double * data, double variable, char* fn, int length){
    int i = 0;
    FILE* fp;
    fp = fopen(fn,"w");
    if(fp == NULL){
        printf("wrong file selected\n");
    }
    else{
        i = 0;
        fprintf(fp,"%d %.4f\n",length,variable);
        while(i < length){
            fprintf(fp, "%.4f \n",data[i]);
            i++;
        }
        fclose(fp);
    }
}
//offset function, follow the same logic of scale
double * offsetData(int * data, double offset, char* fn, int length){
    int i = 0;
    double modifieddata[1500];
    double datain;
    char fpname[20];
    int filenum;
    char* ptr;
    filenum = strtod(fn,&ptr);
    sprintf(fpname,"Offset_data_%d.txt",filenum);
    printf("\nThe File created is named %s\n",fpname);
    while(i < length){
        datain = data[i] + offset;
        modifieddata[i] = datain;
        i++;
    }
    writeToFile(modifieddata, offset, fpname, length);
    return modifieddata;
}
// rename when -r was found
void renameFile2(int * data, struct landm info, char* newf){
    char fpname[20];
    sprintf(fpname,"%s.txt",newf);
    int i = 0;
    FILE* fp;
    fp = fopen(fpname,"w");
    printf("The File created is named %s\n",fpname);
    if(fp == NULL){
        printf("wrong file selected\n");
    }
    else{
        fprintf(fp,"%d %d\n",info.length,info.max);
        while (i < info.length){
            fprintf(fp,"%d\n",data[i]);
            i++;
        }
        fclose(fp);
    }
    
}
//get stat when -S found
void getStat(int * data, struct landm info, char* fn){
    char statFile[25];
    int filenum, max;
    double average;
    char* ptr;
    filenum = strtod(fn,&ptr);
    sprintf(statFile,"Statistic_data_%d.txt",filenum);
    printf("\nThe File created is named %s\n",statFile);
    max = getMax(data, info);
    average = getAverage(data, info);
    FILE* fp;
    fp = fopen(statFile,"w");
    if(fp == NULL){
        printf("wrong file selected\n");
    }
    else{
        fprintf(fp,"%.4f %d\n",average,max);
        fclose(fp);
    }
    
}
//average function
double getAverage(int * data,struct landm info){
    double sum = 0;
    double average;
    int i = 0;
    while (i < info.length){
        sum += data[i];
        i++;     }
    average = sum / info.length;
    return average;
}
//max function
int getMax(int * data, struct landm info){
    int max, i = 0;
    max = data[i];
    while(i < info.length){
        i++;
        if (data[i] > max){
            max = data[i];
        }
    }
    return max;
}
//noramlize function when -N found
void normalize(int * data, struct landm info, char* fn){
    int filenum;
    char filename[25];
    char* ptr;
    double scale;
    filenum = strtod(fn,&ptr);
    sprintf(filename,"Normalized_data_%d.txt",filenum);
    printf("\nThe File created is named %s\n",filename);
    int max,min;
    double modifiedData[1500];
    int i = 0;
    max = data[i];
    min = data[i];
    while(i < info.length){
        i++;
        if(data[i] > max){
            max = data[i];
        }
        if(data[i] < min){
            min = data[i];
        }
    }
    i = 0;
    while(i < info.length){
        if (min == max){
            // if min and max are equal, you cant divide by 0, and scale is 0.5 in that case
            modifiedData[i] = data[i] * 0.5;
            scale = 0.5;
        }
        else{
            // find scale so i can print it to the file
            modifiedData[i] = ((double)(data[i] - min)/(double)(max - min));
            if (data[i]!= 0){
                scale = modifiedData[i] / data[i];
            }
            
        }
        i++;
    }
    writeToFile(modifiedData, scale, filename, info.length);
    
}
// center data, same logic to the normalize
void center(int * data, struct landm info, char* fn){
    int filenum;
    char filename[25];
    char* ptr;
    filenum = strtod(fn,&ptr);
    sprintf(filename,"Centered_data_%d.txt",filenum);
    printf("\nThe File created is named %s\n",filename);
    double average;
    double modifiedData[1500];
    average = getAverage(data, info);
    int i = 0;
    while(i < info.length){
        modifiedData[i] = data[i] - average;
        i++;
    }
    // I did this is I did data[i] - average, the offset should be negative of average
    average = average * -1;
    writeToFile(modifiedData, average, filename, info.length);
}












