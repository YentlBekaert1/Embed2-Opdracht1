#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <gpiod.h>
#include <unistd.h>

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

//error function
void finish_with_error(MYSQL *con){
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv)
{  
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

	const char *chipname = "gpiochip0";
  	struct gpiod_chip *chip;
	int i, ret, val;
	struct gpiod_line *Input27;   
	struct gpiod_line *Input26; 
	struct gpiod_line *Input22;  

	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		return 1;
	}

// Open GPIO lines
  Input27 = gpiod_chip_get_line(chip, 27);
  if (!Input27) {
    perror("Get line failed\n");
    return 1;
  }
  // Open GPIO lines
  Input26 = gpiod_chip_get_line(chip, 26);
  if (!Input26) {
    perror("Get line failed\n");
    return 1;
  }
  // Open GPIO lines
  Input22 = gpiod_chip_get_line(chip, 22);
  if (!Input22) {
    perror("Get line failed\n");
    return 1;
  }
   // Open switch line for input
  ret = gpiod_line_request_input(Input27, "example1");
  if (ret < 0) {
    perror("Request line as input failed\n");
    return 1;
  }
  ret = gpiod_line_request_input(Input26, "example1");
  if (ret < 0) {
    perror("Request line as input failed\n");
    return 1;
  }
  ret = gpiod_line_request_input(Input22, "example1");
  if (ret < 0) {
    perror("Request line as input failed\n");
    return 1;
  }

//function to read change on input
	int buttonPress(int g){
	    if(g == 27){
			val = gpiod_line_get_value(Input27);
			if (val < 0) {
			perror("Read line input failed\n");
			return 1;
			}
		}else if(g == 26){
			val = gpiod_line_get_value(Input26);
			if (val < 0) {
			perror("Read line input failed\n");
			return 1;
			}
		}else if(g == 22){
			val = gpiod_line_get_value(Input22);
			if (val < 0) {
			perror("Read line input failed\n");
			return 1;
			}
		}

		int return_value;
		if (val){// !=0 <-> bit is 1 <- port is HIGH=3.3V
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
  mysql_close(con);
  exit(0);
}