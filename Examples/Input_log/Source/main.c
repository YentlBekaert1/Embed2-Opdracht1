#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
//#include <my_global.h>
#include <mysql.h>

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

	// Define gpio 17 as output
	INP_GPIO(17);
	OUT_GPIO(17);
	INP_GPIO(27);

	 MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "root_pswd", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

/*   if (mysql_query(con, "CREATE DATABASE testdb")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }
 */
  mysql_close(con);
	int pressed = 0;
	int old_value =0;
	int value = 0;

	while(1)
	{
		// Toggle 17 (blink a led!)
		//GPIO_SET = 1 << 17;
		//sleep(1);

		//GPIO_CLR = 1 << 17;
		//sleep(1);
		

		//int input_value = GPIO_READ(27);
		//char number_str[1];
		//sprintf(number_str, "%d", input_value);
		//printf("waarde: %s\n", number_str);
		/*if (GPIO_READ(27)) // !=0 <-> bit is 1 <- port is HIGH=3.3V
    		input_27_state = 1;
		else
			input_27_state = 0;

		if(old_state != input_27_state)
			printf("state changed");
			old_state = input_27_state;	
			sleep(1);*/
		
		int value_input_27 = buttonPress(27);

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
			old_value = value;
		}

	}
	return 0;	
}


