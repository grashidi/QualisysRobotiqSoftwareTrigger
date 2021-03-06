/* Software License Agreement (BSD License)
*
* Copyright (c) 2014, Robotiq, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
* * Neither the name of Robotiq, Inc. nor the names of its
* contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* Copyright (c) 2014, Robotiq, Inc
*/

/*
 *  \file main.c
 *  \date June 18, 2014
 *  \author Jonathan Savoie <jonathan.savoie@robotic.com>
 *  \maintener Nicolas Lauzier <nicolas@robotiq.com>
 */

#include "../../src/rq_sensor_com.h"
#include "../../src/rq_sensor_state.h"
#include "../../src/rq_int.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "../../src/Thread/rq_thread.h"
#define REGLE_TEMPS 10 //Au dix secondes

/**
 * \fn static void decode_message_and_do(char *buff)
 * \brief Decode the message received and execute the operation.
 * Accepted string 	: GET PYE
 * 					: GET FMW
 * 					: GET SNU
 * 					: SET ZRO
 * No other message will be accepted
 * \param *buff, String to decode and execute
 */
/*static void decode_message_and_do(UINT_8 *buff){
	if(buff == NULL || strlen(buff) < 7){
		return;
	}
	UINT_8 get_or_set[3];
	strncpy(get_or_set, &buff[0], 3);
	if(strstr(get_or_set, "GET")){
		UINT_8 nom_get_var[4];
		strncpy(nom_get_var, &buff[4], strlen(buff) -3);
		UINT_8 buffer[512];
		rq_state_get_command(nom_get_var, buffer);
		//
		//  Here comes the code to resend the high level data.
		//
	}
	else if (strstr(buff, "SET ZRO")){
		rq_set_zero();
	}
	//
	// Here comes the code to empty the string(buff).
	//
}*/

/**
 * \fn static void wait_for_other_connection()
 * \brief Function who wait for another connection
 */
static void wait_for_other_connection(){
	INT_8 ret;
	while(1){
		Sleep(1000);// wait 1 seconde
		ret = rq_sensor_state();
		if(ret == 0){
			break;
		}
	}
}

/**
 * \fn void get_data(void)
 * \brief Function to retrieve the power applied to the sensor
 * \param chr_return String to return forces applied
 */
static void get_data(INT_8 * chr_return){
	INT_8 i;
	INT_8 floatData[50];
	for(i = 0; i < 6; i++){
		sprintf(floatData, "%f", rq_state_get_received_data(i));
		if(i == 0){
			// strcpy(chr_return, "");
			strcat(chr_return, floatData);
		}
		else{
			strcat(chr_return," , ");
			strcat(chr_return,floatData);
		}
		// if(i == 5){
		// 	// strcat(chr_return, "");
		// }
	}
}

 int main(){
	 //IF can't connect with the sensor wait for another connection
	INT_8 ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	//Read high-level informations
	ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	//Initialize connection with the client
	ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	/*
	 * Here comes the code to establish a connection with the application
	*/

	//INT_8 buffer[512]; //Init of the variable receiving the message
	// INT_8 bufStream[512];
 // 	while(1){
 // 		/*strcpy(buffer,"");
 // 		*  // Here we receive the message of the application to read
 // 		*  // high level variable.
 // 		*if(strcmp(buffer, "") != 0)
 // 		*{
 // 		*	decode_message_and_do(buffer);
 // 		*}
 // 		*/
 //
 // 		ret = rq_sensor_state();
 // 		if(ret == -1){
 // 			wait_for_other_connection();
 // 		}
 // 		if(rq_sensor_get_current_state() == RQ_STATE_RUN){
 // 			strcpy(bufStream,"");
 // 			get_data(bufStream);
 // 			printf("%s\n", bufStream);
 // 			/*
 // 			 * Here comes the code to send the data to the application.
 // 			*/
 // 		}
 // 	}
 // 	return 0;
 // }


	 // fprintf(fp,"t(s),FX,FY,FZ,MX,MY,MZ");
	 int nb = 100;
	 // INT_8 bufVarHighLvl[30];
	 // rq_com_get_str_firmware_version(bufVarHighLvl);
	 // printf("Firmware version: %s\n", bufVarHighLvl);
	 // rq_com_get_str_serial_number(bufVarHighLvl);
	 // printf("Serial Number: %s\n", bufVarHighLvl);
	 // rq_com_get_str_production_year(bufVarHighLvl);
	 // printf("Production Year: %s\n", bufVarHighLvl);
	 printf("t(s),FX,FY,FZ,MX,MY,MZ\n");
	 INT_8 bufStream[512];
	 clock_t start, diff;
	  // struct timespec start, end;
	 // double diff;
	 int timerVerif = 1;

	 // rq_com_start_stream();
	 // ret = rq_sensor_state();
	 start = clock();
	  // rq_com_listen_stream();
	 // clock_gettime(CLOCK_MONOTONIC, &start);
	 while(1){
		  // rq_com_listen_stream();
		 ret = rq_sensor_state();
		 // if(ret == -1){
			//  wait_for_other_connection();
		 // }
		 // if(rq_sensor_get_current_state() == RQ_STATE_RUN){
		 // clock_gettime(CLOCK_MONOTONIC, &end);
		 // diff = (end.tv_sec - start.tv_sec) * 1e9;
		 // diff = (diff + (end.tv_nsec - start.tv_nsec)) * 1e-9;
			diff = clock() - start;
			 // if(floor(((((float)diff)/CLOCKS_PER_SEC)+(REGLE_TEMPS/nb))/(REGLE_TEMPS/nb)) >= timerVerif){
				 // fprintf(fp,"\n");
				 // fprintf(fp,"%f,",((float)diff)/CLOCKS_PER_SEC);
				 printf("%f, ",((double)diff)/(CLOCKS_PER_SEC));
				 strcpy(bufStream,"");
				 get_data(bufStream);
				 printf("%s\n", bufStream);
				 // fprintf(fp,bufStream);
				 // timerVerif++;
			 // }
		 // }
	 }
	 return 0;
	}
