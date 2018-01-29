//
//  main.c
//  data
//
//  Created by linChunbin on 9/26/17.
//  Copyright © 2017 linChunbin. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void menu(){
    printf("You can enter the following options:\n");
    printf("-n: File number (value needed)\n");
    printf("-o: offset value (value needed) \n");
    printf("-s: scale factor (value needed) \n");
    printf("-r: Rename files (name needed) \n");
    printf("-h: Help (display how the program should be called, including the different input options) ");
}
int data[1000];
Datas readingFile(char* fn);
void scaleFactor(Datas x,double sacle, char* fn);
char * selectFile(int num);
int main(int argc, char * argv[]) {
    Datas data1;
    char *ptr;
    double scale;
    switch(argc){
        case 2:
            if (strcmp(argv[1], "-h") == 0){
                menu();
                break;
            }
            else{
                printf("Enetered the wrong thing");
                break;
            }
        case 5:
            if(strcmp(argv[1], "-n") == 0){
                data1 = readingFile(argv[2]);
                if(strcmp(argv[3], "-s") == 0){
                    scale = strtod(argv[4],&ptr);
                    scaleFactor(data1,scale,argv[2]);
                }
                else if(strcmp(argv[3], "-o") == 0){
                    printf("offset function");
                }
                else if(strcmp(argv[3], "-r") == 0){
                    printf("rename function");
                    
                }
                
            }
            else if(strcmp(argv[1], "-s") == 0){
                if(strcmp(argv[3], "-n") != 0){
                    printf("Error, Please follow: \n");
                    menu();
                    break;
                }
                else
                {
                    data1 = readingFile(argv[4]);
                    scale = strtod(argv[2],&ptr);
                    scaleFactor(data1,scale,argv[4]);
                    break;
                }
            }
            else if(strcmp(argv[1], "-o") == 0){
                if(strcmp(argv[3], "-n") != 0){
                    printf("Error, Please follow: \n");
                    menu();
                }
                else
                {
                    data1 = readingFile(argv[4]);
                    printf("offset function");
                }
            }
            else if(strcmp(argv[1], "-r") == 0){
                if(strcmp(argv[3], "-n") != 0){
                    printf("Error, Please follow: \n");
                    menu();
                    break;
                }
                else
                {
                    data1 = readingFile(argv[4]);
                    printf("rename function");
                }
            }
            
    }
    return 0;
}

char * selectFile(int num){
    char* fn;
    switch (num){
        case 1:
            fn = ("Raw_data_01.txt");
            break;
        case 2:
            fn = ("Raw_data_02.txt");
            break;
        case 3:
            fn = ("Raw_data_03.txt");
            break;
        case 4:
            fn = ("Raw_data_04.txt");
            break;
        case 5:
            fn = ("Raw_data_05.txt");
            break;
        case 6:
            fn = ("Raw_data_06.txt");
            break;
        case 7:
            fn = ("Raw_data_07.txt");
            break;
        case 8:
            fn = ("Raw_data_08.txt");
            break;
        case 9:
            fn = ("Raw_data_09.txt");
            break;
        case 10:
            fn = ("Raw_data_10.txt");
            break;
    }
    return fn;
}
Datas readingFile(char* fn){
    Datas read;
    read.data= malloc(sizeof(int*));
    char* fpname;
    int filenum;
    char* ptr;
    filenum = strtod(fn,&ptr);
    fpname = selectFile(filenum);
    FILE* fp;
    fp = fopen(fpname,"r");
    if (fp==NULL){
        printf("Wrong file selected\n");
    }
    else{
        fscanf(fp,"%d %d",&(read.length),&(read.max));
        printf("The number is :%d\nand the max is %d\n",read.length,read.max);
        int data1;
        int i = 0;
        while(!feof(fp)){
            fscanf(fp,"%d",&data1);
            read.data[i] = data1;
            i++;
        }
        i = 0;
        while (i < read.length){
            printf("%d\n",read.data[i]);
            i++;
        }
      //  free(read.data);
        fclose(fp);
    }
    return read;
    
}
void scaleFactor(Datas x,double scale, char* fn){
    int i = 0;
    while(i < x.length){
        x.data[i] *= scale;
        printf("the value is %d\n",x.data[i]);
        i++;
    }
    char fpname[20];
    int filenum;
    char* ptr;
    filenum = strtod(fn,&ptr);
    sprintf(fpname,"Scaled_data_%d.txt",filenum);
    printf("%s",fpname);
    FILE* fp;
    fp = fopen(fpname,"w");
    if(fp == NULL){
        printf("wrong file selected\n");
    }
    else{
        i = 0;
        fprintf(fp,"%d ",x.length);
        printf("%f",scale);
        fprintf(fp,"%f \n",scale);
        while (i < x.length){
            x.data[i] *= scale;
            fprintf(fp,"%d \n",x.data[i]);
            i++;
        }
    }
    fclose(fp);
    
}

