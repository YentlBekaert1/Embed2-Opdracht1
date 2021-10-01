#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <time.h>

int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	// Define gpio 27,22,26 as input
	INP_GPIO(27);
	INP_GPIO(22);
	INP_GPIO(26);

	//error function
	void finish_with_error(MYSQL *con){
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	
	//add MYSQL
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	//connect to Mariadb
	if (mysql_real_connect(con, "localhost", "root", "root_pswd", 
			NULL, 0, NULL, 0) == NULL) 
	{
		finish_with_error(con);
	}  

	//USE Databese inputs
	if (mysql_query(con, "USE inputs")) 
	{
		finish_with_error(con);
	}

	//create time variables
	time_t current_time;
	struct tm tm = *localtime(&current_time);

	void write_to_database(int gpio, int state){
		//get the time and put it in a string
		current_time = time(NULL);
		tm = *localtime(&current_time);
		char time[1024];
		sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

		//make the query to insert into table
		char Query[1024];
		sprintf(Query, "INSERT INTO subjects( time, input, state) VALUES ('%s', %d, %d)", time, gpio, state);

		//execute the query
		if (mysql_query(con, Query)) 
		{
			finish_with_error(con);
		}
	}

	//function to read change on input
	int buttonPress(int g){
		int return_value;
		if (GPIO_READ(g)){// !=0 <-> bit is 1 <- port is HIGH=3.3V
			return_value = 1;
		}
		else{ // port is LOW=0V
			return_value = 0;
		}
		return return_value;
	}
	
		int pressed_27 = 0;
		int old_value_27 =0;
		int value_27 = 0;

		int pressed_22 = 0;
		int old_value_22 =0;
		int value_22 = 0;

		int pressed_26 = 0;
		int old_value_26 =0;
		int value_26 = 0;
	

	//endless loop
	while(1)
	{
		int return_value_27 = buttonPress(27);
		//for debouncing
		if(return_value_27 == 1 && pressed_27 == 0){
				value_27 = 1;
				pressed_27 = 1;
		}
		else if(return_value_27 == 0 && pressed_27 == 1){
				value_27 = 0;
				pressed_27 = 0;
		}

		if(value_27 != old_value_27){
				char number_str[1];
				sprintf(number_str, "%d", value_27);
				printf("value gpio %d: %s\n",27, number_str);
				write_to_database(27,value_27);
				old_value_27 = value_27;
		}

		int return_value_22 = buttonPress(22);
		//for debouncing
		if(return_value_22 == 1 && pressed_22 == 0){
				value_22 = 1;
				pressed_22 = 1;
		}
		else if(return_value_22 == 0 && pressed_22 == 1){
				value_22 = 0;
				pressed_22 = 0;
		}

		if(value_22 != old_value_22){
				char number_str[1];
				sprintf(number_str, "%d", value_22);
				printf("value gpio %d: %s\n",22, number_str);
				write_to_database(22,value_22);
				old_value_22 = value_22;
		}

		int return_value_26 = buttonPress(26);
		//for debouncing
		if(return_value_26 == 1 && pressed_26 == 0){
				value_26 = 1;
				pressed_26 = 1;
		}
		else if(return_value_26 == 0 && pressed_26 == 1){
				value_26 = 0;
				pressed_26 = 0;
		}

		if(value_26 != old_value_26){
				char number_str[1];
				sprintf(number_str, "%d", value_26);
				printf("value gpio %d: %s\n",26, number_str);
				write_to_database(26,value_26);
				old_value_26 = value_26;
		}	
	}
	//close connection
	mysql_close(con);
	return 0;	
}
