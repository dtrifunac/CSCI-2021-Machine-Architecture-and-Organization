#include "thermo.h"


// int set_temp_from_ports(temp_t *temp){//sets temperature to temp variable from THERMO_SENSOR_PORT
//     if(THERMO_SENSOR_PORT <0  || THERMO_SENSOR_PORT > 28800 || THERMO_STATUS_PORT & (1<<2)){//checks THERMO_SENSOR_PORT is negative or greater than 28800 or if there is an error case from THERMO_STATUS_PORT
//         temp->tenths_degrees = 0;
//         temp->temp_mode = 3;
//         return 1;
//     }
//     temp->tenths_degrees = (THERMO_SENSOR_PORT >> 5 )-450; //sets temp_tenths_degrees to tenths of degrees C
//     temp->temp_mode = 1;
    
//     if((THERMO_SENSOR_PORT & ((1<<5) -1))>15){//checks if temp->tenth_degrees should be rounded up
//         temp->tenths_degrees++;
//     }
//     if(THERMO_STATUS_PORT & 1<<5){//checks if temp should converted to Farhenheit
//         temp->tenths_degrees = (temp->tenths_degrees * 9) / 5 + 320;
//         temp->temp_mode = 2;
//         return 0;
//     }
//     return 0;

// }

// int set_display_from_temp(temp_t temp, int *display){ //returns an int with binary values indicating which 
//                                                       //parts of the display should light up to display temperature
//     int out = 0;
//     int temp_tenths;
//     int temp_ones;
//     int temp_tens;
//     int temp_hundreds;
//     int nums[] = {0b1111011,0b1001000,0b0111101,0b1101101,0b1001110,0b1100111,0b1110111,0b1001001,0b1111111,0b1101111};
//     if((temp.temp_mode ==1 && temp.tenths_degrees >= -450 && temp.tenths_degrees <= 450) || (temp.temp_mode ==2 && temp.tenths_degrees >= -490 && temp.tenths_degrees <= 1130)){//checks for no errors
//         temp_tenths = (temp.tenths_degrees)%10;
//         if (temp_tenths < 0){//takes the absolute value of temp_tenths
//             temp_tenths = -temp_tenths;
//         }
        
//         out |= nums[temp_tenths];
//         temp_ones = (temp.tenths_degrees)%100/10;
//         if (temp_ones < 0){//takes the absolute value of temp_ones
//             temp_ones = -temp_ones;
//         }
//         out |= nums[temp_ones]<<7;
//         temp_tens = (temp.tenths_degrees)%1000/100;
//         if (temp_tens < 0){//takes the absolute value of temp_tens
//             temp_tens = -temp_tens;
//         }
//         if (temp_tens != 0){//checks if there is a hundreds place, doesn't need to check for negativity because that would be out of range
//             out |= nums[temp_tens]<<14;
//         }
//         temp_hundreds = (temp.tenths_degrees)/1000;
//         if (temp_hundreds != 0){//checks if there is a hundreds place, doesn't need to check for negativity because that would be out of range
//             out |= nums[temp_hundreds]<<21;
//         }
//         if(temp_tens==0 && temp_hundreds !=0){//checks if there should be 0 in tens place because of a digit in the hundreds place
//             out |= nums[0]<<14;
//         }
        
//         if (temp.temp_mode == 1){//sets celsius symbol
//             out |= 0b1<<28;
//         }
//         else{ //sets Farhenheit symbol
//             out |= 0b10<<28;
//         }

//         if(temp.tenths_degrees < 0){//checks for negativity
//             if(temp_tens == 0){//checks if negative symbol should be put in the tens place
//                 out |= 1<<16;
//             }
//             else{//puts negative symbol in the hundreds place if there is a value in the tens place
//                 out |= 1<<23;
//             }
//         }
//         *display = out;
//         return 0;
//     }
// else{//error case
//     out = 0b000110111101111110111110000000;
//     *display = out;
//     return 1;
// }
// }

// int thermo_update(){//updates the display to the new temperature
//     temp_t temp;
//     int success1 = set_temp_from_ports(&temp);//sets temp using set_temp_from_ports()
//     int success2 = set_display_from_temp(temp, &THERMO_DISPLAY_PORT);//sets display using set_display_from_temp()
//     if(success1 + success2>0){//checks for errors in either function call
//         return 1;
//     }
//     else{
//         return 0;
//     }
// }
