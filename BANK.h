#ifndef DIPLEVEL1_ZOOM_ONLINE_BANK_H
#define DIPLEVEL1_ZOOM_ONLINE_BANK_H

#include "stdio.h"
#include "stdlib.h"
#define SIZE 1000 // symbolic constant
struct trans{
    char note[200];
};

struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];
    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
    float loan_rate;
    char acc_s[10]; //account status
    int acc_level; // copy
    unsigned long long int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];

};

struct data db[SIZE];

// Global Variable Declaration

int users=0;
int NV=-1;
int emailExist=-1;
int pass_Exist=-1;
int two_charArray=-1;
int nrc_valid = -1;
int strongPass=-1;
int phone_valid=-1;

// For Function Declaration
void welcome();
void login();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char gmail[50]);
void emailExistChecking(char toCheck[50]);
void compare_two_charArray(char first[50] , char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned long long int phone);
void recording_alldata_toFile();
void copy_two_char_array(char receiver[200] ,char transmitter[200] );
int Counting(unsigned long long int Count);


void welcome(){

    int option=0;
    printf("Welcome to our Bank!\n");
    printf("Press 1 to Login!\nPress 2 to Register!\nPress 3 to Exit!:::");
    scanf("%d",&option);

    if(option == 1){

        login();

    } else if(option == 2){
        registration();

    } else if( option == 3){

        recording_alldata_toFile();
        exit(1);
    } else {
        welcome();
    }

}

void login(){

    char loginmail[50];
    char loginpass[50];
    printf("This is login!");

    printf("Enter your email:");
    scanf(" %[^\n]",&loginmail[0]);

    printf("Enter your password:");
    scanf(" %[^\n]",&loginpass[0]);



}


void loadingAllDataFromFile(){

    FILE *fptr = fopen("ncc_db1.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%llu%u%s%d",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,
                   &db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,
                   &db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,
                   &db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay);


            if(db[ncc].email[0] == '\0'){
                break;
            }

            users++;

        }

    }

    fclose(fptr);

}
void printingAllData(){

    for(int ncc=0; ncc<users ; ncc++){


        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%llu-%u-%s-%d",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address,db[ncc].transAmoLimitPerDay);


        printf("\n");
    }

}

void recording_alldata_toFile(){
    FILE *fptr = fopen("ncc_db1.txt","w");
    if(fptr==NULL){
        printf("cannot open file to record:\n");

    }

    for(int ncc=0; ncc<users; ncc++){
        fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%llu%c%u%c%s%c%d",db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',db[ncc].email,' ',db[ncc].password,
                ' ',db[ncc].pOrb, ' ',db[ncc].loan_s,' ',db[ncc].monthly_income,' ',db[ncc].loan_amount ,' ',db[ncc].loan_rate ,' ', db[ncc].acc_s ,' ',db[ncc].acc_level,
                ' ',db[ncc].phNumber , ' ',db[ncc].cur_amount,' ',db[ncc].address,' ',db[ncc].transAmoLimitPerDay);

        fprintf(fptr,"%c",'\n');
    }



}

void registration(){

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_pass[50];
    unsigned long long int re_phone=0;

    printf("This is NCC Bank User Registration!\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);
    NV=-1;
    myGmailValidation(reEmail);
    if( NV!= -1){

        emailExist=-1;
        emailExistChecking(reEmail);

        if( emailExist == -1 ){

            printf("Your email is valid!\n");
            printf("Enter your name:");
            scanf(" %[^\n]",&re_name[0]);
            nrc_valid=-1;
            while (nrc_valid==-1){
                printf("Enter your NRC:");
                scanf(" %[^\n]",&re_nrc[0]);

                nrc_validation(re_nrc);
                if(nrc_valid == -1){
                    printf("Your NRC Format was Not Valid!\n");
                }

            }
            printf("Your NRC Format was Valid!\n");
            printf("Enter your password.\nYour password should contain at least 4 small Character, 1 capital Character, 2 special Character and 2 numbers\n");
            strongPass=-1;
            while (strongPass == -1){
                printf("Enter your password!:");
                scanf(" %[^\n]",&re_pass[0]);
                myStrongPassword(re_pass);
                if(strongPass == -1){
                    printf("Your Password Format too weak and Try Again!\n");
                }
            }
            printf("Your password format was valid and saved!\n");

            phone_valid=-1;
            while (phone_valid==-1){
                printf("[X]Enter your Phone Number:");
                scanf("%llu",&re_phone);

                phone_validation(re_phone);

                if(phone_valid == -1){

                    printf("[-]Your phone number is already registered:\n");
                }

            }
            printf("[+] Your phone is correct and saved!\n");

            printf("[+] Enter your monthly income:");
            scanf("%u",&db[users].monthly_income);
            printf("[+] Enter your current amount:");
            scanf("%u",&db[users].cur_amount);

            printf("[+]Enter your address");
            scanf(" %[^\n]",&db[users].address[0]);

            copy_two_char_array(db[users].pOrb , db[2].pOrb);
            copy_two_char_array(db[users].loan_s,db[2].loan_s);

            db[users].loan_amount= db[2].loan_amount;
            db[users].phNumber= re_phone;
            db[users].loan_rate= db[2].loan_rate;
            copy_two_char_array(db[users].acc_s,db[2].acc_s);
            db[users].acc_level= db[2].acc_level;
            db[users].transAmoLimitPerDay= db[2].transAmoLimitPerDay;
            copy_two_char_array(db[users].trc[0].note,db[2].trc[0].note);
            copy_two_char_array(db[users].email,reEmail);
            copy_two_char_array(db[users].nrc,re_nrc);
            copy_two_char_array(db[users].password,re_pass);
            copy_two_char_array(db[users].name,re_name);

            db[users].id = users+1;
            users++;
            printingAllData();
            welcome();


        } else{

            printf("Your gmail already taken!\n");
            registration();

        }


    } else{
        printf("Your gmail format not valid!\n");
        registration();
    }



}

int charCounting(char toCount[50]){ // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++){

        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char gmail[50]){

    int here = 0;
    int v1 = 0;
    int v2 = 0;
    char fgmail[10] = {'@','g','m','a','i','l','.','c','o','m'};

    int i =0;
    for ( i =0; i<50; i++){
        if(gmail[i]==fgmail[0]){
            here = i;
            break;
        }
    }
    for ( int j = 0; j<10 ; j++){


        if(gmail[here+j]==fgmail[j]){
            v1++;
        }else{
            v2++;
        }
    }

    if (v1 == 10 && gmail[here+10]=='\0'){

        NV = 1;
    }else{

        NV = -1;

    }

}

void emailExistChecking(char toCheck[50]){

    int toCheckCount = charCounting(toCheck);
    int sameCounting=0;

    for(int ncc=0; ncc<users ; ncc++){
        int dbEmailCount = charCounting(db[ncc].email);

        sameCounting=0;
        if( toCheckCount == dbEmailCount){

            for(int gcc=0; gcc<toCheckCount ; gcc++){

                if(toCheck[gcc] != db[ncc].email[gcc] ){
                    break;
                } else{
                    sameCounting++;
                }

            }


        }

        if(toCheckCount == sameCounting){

            emailExist = ncc;
        }

    }


}

void nrc_validation(char nrc_toCheck[50]){

    int nrc_counter =charCounting(nrc_toCheck);
    int nrc_char=0;

    for(register int i=0; i< nrc_counter ; i++){

        if( nrc_toCheck[i] == ')'){
            break;
        }
        nrc_char++;
    }

    for(int i=0; i<3; i++){

        two_charArray=-1;
        compare_two_charArray(nrc_toCheck,db[i].nrc);
        if(two_charArray == 1){
            nrc_valid=1;
            break;
        }

    }


}

void compare_two_charArray(char first[50] , char second[50]){

    int first_counter =  charCounting(first);
    int second_counter = charCounting(second);
    int same_counter = 0;

    if( first_counter == second_counter) {
        for (register int i = 0; i < first_counter; i++) {
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if( first_counter == same_counter){
            two_charArray = 1;
        }
    }

}

void myStrongPassword(char pass[50]){

    int i=0;
    int special=0;
    int numberChar=0;
    int capChar=0;
    int smallChar=0;
    int pass_counter = charCounting(pass);
    while (strongPass == -1){
        if( i == pass_counter){
            strongPass=-1;
            break;
        }
        if( pass[i] >= 33 && pass[i] <= 42){

            special++;
        } else  if( pass[i] >= 48 && pass[i] <= 57){

            numberChar++;

        } else if( pass[i] >= 65 && pass[i] <= 90){

            capChar++;
        } else if( pass[i] >= 97 && pass[i] <= 122) {

            smallChar++;
        }
        i++;
        if( special > 1 && numberChar >1 && capChar > 0 && smallChar >3 && pass_counter >6){
            strongPass = 1;
        }
    }


}
void copy_two_char_array(char receiver[200] ,char transmitter[200] ){


    int transmit_counter = charCounting(transmitter);
    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }


}
void phone_validation(unsigned long long int Ph) {
    unsigned int standard = 959;
    int C = Counting(Ph);

    if (C == 12) {
        unsigned long long int first_three_digits = (Ph / 1000000000);
        unsigned long long int ninth_digit = (Ph / 100000000) % 10;

        if (first_three_digits == standard) {

            if (ninth_digit == 4 || ninth_digit == 7 || ninth_digit == 9) {
                printf("Valid");

            } else {
                printf("Not Valid\n");

                registration();
            }

        } else {
            printf("Digits aren't valid:\n");
            registration();
        }
    }
//9595010203
        if (C == 10) {
            unsigned long long int first_three_digit = (Ph / 10000000);
            unsigned long long int seventh_digit = (Ph / 1000000) % 10;

            if (first_three_digit == standard) {

                if (seventh_digit == 5) {
                    printf("Valid");

                } else {
                    printf("Not Valid\n");

                    registration();
                }

            } else {
                printf("Digits aren't valid:\n");
                registration();
            }
        }

            int phone_counter = 0;
            for (int i = 0; i < users; i++) {

                if (Ph != db[i].phNumber) {

                    phone_counter++;
                } else {
                    phone_valid = -1;
                    break;
                }

            }
            if (phone_counter == users) {
                phone_valid = 1;
            }

        }

int Counting(unsigned long long int Count){
    int count = 0;
    while(Count != 0){
        Count /= 10;
        count ++;
    }
    return count;

}

#endif

// write for ancient ph no
// write login and strong pw
// fix nrc validatio