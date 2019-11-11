//
//  main.cpp
//  project2
//
//  Created by Lamia Uddin on 2019-11-03.
//  Copyright © 2019 Lamia Uddin. All rights reserved.
//

#include <iostream>
#include <cmath>
#ifndef MARMOSET_TESTING
int main();
#endif

char *encode( char *plaintext, unsigned long key);
char *decode( char *cihpertext, unsigned long key);

char *encode( char *plaintext, unsigned long key){
    unsigned char temp{0};
    unsigned int r{0};
    unsigned char R{};
    unsigned int i{0};
    unsigned int j{0};
    unsigned int k{};
    unsigned char stateArray[256];
    for(int a{0};a<256;a++){
        stateArray[a]=a;
    }
    
    for(int b{0};b<256;b++){
        k=i%64;
        j=(j+stateArray[i]+((key>>k)&1L))%256;
        temp=stateArray[i];
        stateArray[i]=stateArray[j];
        stateArray[j]=temp;
        i=(i+1)%256;
    }
    
    //initializing array

    int increase{0};
    int capacity{0};
    for ( int q{0}; true; ++q ) {
        if ( plaintext[q] == '\0' ) {
            capacity=q;
            break;
    }
    }

    while ((capacity % 4) != 0){
            capacity+=1;
            increase++;
        
        }
    
   unsigned char inputArray[capacity];
    
    for(int d{0};d<capacity-increase;d++){
        inputArray[d]=plaintext[d];
    }
    
    for(int e{capacity-increase};e<capacity;e++){
        inputArray[e]='\0';
    }
    
    for(int c{0};c<capacity;c++){
    i=(i+1)%256;
    j=(j+stateArray[i])%256;
    temp=stateArray[i];
    stateArray[i]=stateArray[j];
    stateArray[j]=temp;
    r=(stateArray[i]+stateArray[j])%256;
    R=stateArray[r];
    inputArray[c] = R ^ inputArray[c];
    
    //scrambling state array
    }
    unsigned int number{};
    char* numbers {new char [5*(capacity/4)+1]};
    
    for(int k{0};k<(capacity/4);k++){
        number = (inputArray[4*k] <<24);
        number = number +(inputArray[4*k+1] <<16);
        number = number +(inputArray[4*k+2] <<8);
        number = number +(inputArray[4*k+3]);
        
        for(int r{5*k+4};r>=5*k;r--){
            numbers[r]=number%85 + '!';
            number=number/85;
        }
    }
    //ascii armour
    
    numbers[5*(capacity/4)] = '\0';
    
    return numbers;
}


char *decode( char *cihpertext, unsigned long key ){
    unsigned char temp{0};
    unsigned int r{0};
    unsigned char R{};
    unsigned int i{0};
    unsigned int j{0};
    unsigned int k{};
    int capacity{};
    for ( int q{0}; true; ++q ) {
           if ( cihpertext[q] == '\0' ) {
               capacity=q;
               break;
       }
       } //finds length of ciphertext without null character
    
    for(int z{0};z<capacity;z++){
        cihpertext[z]=cihpertext[z]-'!';
    } //removes the ! from all the elements to get back to original values
    
    char* newnumbers{new char [4*(capacity/5)+1]};
    unsigned int concatnum{};
    for(int t{0}; t<(capacity/5); t++){
        concatnum = ((cihpertext[5*t]) * pow(85, 4))+ ((cihpertext[5*t+1])* pow(85, 3))+((cihpertext[5*t+2]) * pow(85, 2))+((cihpertext[5*t+3]) * pow(85, 1))+((cihpertext[5*t+4]) * pow(85, 0));
        
        newnumbers[4*t]= concatnum >> 24;
        newnumbers[4*t+1]= concatnum >>16;
        newnumbers[4*t+2]= concatnum>>8;
        newnumbers[4*t+3]= concatnum;
    }
    //combines the 5 seperate numbers into one number and then sections off into the original 4 numbers
    
    unsigned char stateArray[256];
    for(int a{0};a<256;a++){
        stateArray[a]=a;
    }

    for(int b{0};b<256;b++){
        k=i%64;
        j=(j+stateArray[i]+((key>>k)&1L))%256;
        temp=stateArray[i];
        stateArray[i]=stateArray[j];
        stateArray[j]=temp;
        i=(i+1)%256;
    }
    for(int c{0};c<4*(capacity/5);c++){
       i=(i+1)%256;
       j=(j+stateArray[i])%256;
       temp=stateArray[i];
       stateArray[i]=stateArray[j];
       stateArray[j]=temp;
       r=(stateArray[i]+stateArray[j])%256;
       R=stateArray[r];
       newnumbers[c] = R ^ newnumbers[c];
    }
    //rescrambles and XOR the array with the key to get plaintext back
    
    newnumbers[4*(capacity/5)] = '\0';
    return newnumbers;
}
#ifndef MARMOSET_TESTING
int main() {
    char text[]{"....a string of size 1 000 000 bytes...."};
   
    char *ciphertext{ encode(text, 51231)};
    
    std::cout << ciphertext << std::endl;
    
    char *plaintext{decode(ciphertext, 51231)};
    
    std::cout << plaintext << std::endl;
 
    return 0;
}
#endif





