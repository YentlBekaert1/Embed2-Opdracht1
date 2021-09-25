#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <time.h>

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

int main()
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	// Define gpio 27 as input
	INP_GPIO(27);

	//create time variables
	time_t current_time;
	struct tm tm = *localtime(&current_time);

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
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}  

	//USE Databese inputs
	if (mysql_query(con, "USE inputs")) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}

	int pressed = 0;
	int old_value =0;
	int value = 0;

	//endless loop
	while(1)
	{
		//get te state of the input
		int value_input_27 = buttonPress(27);

		//for debouncing
		if(value_input_27 == 1 && pressed == 0){
			value = 1;
			pressed = 1;
		}else if(value_input_27 == 0 && pressed == 1){
			value = 0;
			pressed = 0;
		}

		if(value != old_value){
			char number_str[1];
			sprintf(number_str, "%d", value);
			printf("value: %s\n", number_str);
			
			//get the time and put it in a string
			current_time = time(NULL);
			tm = *localtime(&current_time);
			char time[1024];
			sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

			//make the query to insert into table
			char Query[1024];
			sprintf(Query, "INSERT INTO subjects( time, input, state) VALUES ('%s', 27, %d)", time, value);

			//execute the query
			if (mysql_query(con, Query)) 
			{
					fprintf(stderr, "%s\n", mysql_error(con));
					mysql_close(con);
					exit(1);
			}
			old_value = value;
		}
	}
	//close connection
	mysql_close(con);
	return 0;	
}

