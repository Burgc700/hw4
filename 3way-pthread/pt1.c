#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 4096

int NUM_THREADS;							 //Made this an int to run the number of cores testing from command line.
char (*line_numbers)[MAX_LINE_LEN];                       //pointer that tracks the number of the lines that have been read so far
int *results;                                            //Pointer that tracks our highest ASCII value from the lines in the file.
int num_lines_read = 0;						//tracks number of lines read

//Opens the file and the reads the contents in the file.
void read_file() {
	//opens file
	int file = open("/homes/eyv/cis520/wiki_dump.txt", O_RDONLY);

	//Checks to make sure there is content in the file
	if(file == -1)
	{
		perror("Could not open file");
		exit(1);
	}

	char buffer[MAX_LINE_LEN];	//buffer for storing lines
	ssize_t bytes_read;			//Number of bytes that have been read.
	//int current_line_number;		//current line we are reading
	int line_pos = 0;

	//Loops as long as the number of bytes read is greater than 0 for that line
	while((bytes_read = read(file, buffer, sizeof(buffer))) > 0)
	{
		//Loops through each byte that is read from the file.
		for(ssize_t i = 0; i < bytes_read; i++)
		{
			char curr_pos = buffer[i];	//postion we are at in the line

			//Checks to make sure we are not at the end of the line
			if(curr_pos == '\n')
			{
				line_numbers[num_lines_read][line_pos] = '\0';	//Marks the end of that line
				num_lines_read++;								//Increments the number of line read.
				line_pos = 0;									//Resets the line position to 0

				//Makes sure we haven't reach limit for max lines read.
				if(num_lines_read >= MAX_LINES)
				{
					close(file);
					return;
				}
			}
			else
			{
				//Makes sure still in bounds of the max line length and sets the current position to that spot in the line
				if(line_pos < MAX_LINE_LEN - 1)
				{
					line_numbers[num_lines_read][line_pos++] = curr_pos;
				}
			}
		}
	}

	//Makes sure bytes read says positive
	if(bytes_read == -1)
	{
		perror("Failed to read file");
		close(file);
		exit(1);
	}

	//Checks for lines with no text in them.
	if(line_pos > 0 && num_lines_read < MAX_LINES)
	{
		line_numbers[num_lines_read][line_pos] = '\0';
		num_lines_read++;
	}
	close(file);
}

//Adds the file to the correct array and finds the value with the highest ascii value per row.
void *count_array(void *myID)
{
	long id = (long) myID;		//converts myID to a long

  	int startPos = id * (num_lines_read / NUM_THREADS);		//starting position in file
  	int endPos = startPos + (num_lines_read / NUM_THREADS);		//end position in file

	//Makes sure we have enough threads.
  	if(id == NUM_THREADS - 1)
	{
		//Sets end position to the end of row we are reading
		endPos = num_lines_read;
	}

	//Loops through points from start and end positions
	for(int i = startPos; i < endPos; i++)
	{
		int max_ascii = 0;	//place value for the max ASCII on that line.

		//Loops through the line that was just read.
		for(int j = 0; line_numbers[i][j] != '\0'; j++)
		{
			unsigned char currChar = (unsigned char) line_numbers[i][j];	//current position in the last line.

			//Checks if ASCII value of the current position is greater than the one we already have.
			if(currChar > max_ascii)
			{
				//sets the ascii value to the new value of the new highest number
				max_ascii = currChar;
			}
		}
		results[i] = max_ascii;	//Adds that ascii value from the previous line to our array 
	}
	pthread_exit(NULL);
	//return NULL;
}

//Prints the results of the arrays to the command prompt.
void print_results()
{
	//Loops through the lines read to get the line number
	for(int i = 0; i < num_lines_read; i++)
	{
		printf("%d: %d\n", i, results[i]);	//Prints the line number and max ascii value for that line
	}
}

int main(int argc, char* argv[]) {
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
		return 1;
	}

	NUM_THREADS = atoi(argv[1]); //Lets you change the number of threads when manual testing to make sure it runs
	if(NUM_THREADS <= 0)
	{
		fprintf(stderr, "Number of threads must be greater than 0\n");
		return 1;
	}

	//Allocates memory for the number of lines read so it can read more lines.
    line_numbers = malloc(sizeof(*line_numbers) * MAX_LINES);
    //Allocates memory for the results of the highest ASCII for each line.
    results = malloc(sizeof(*results) * MAX_LINES);
    //checks to make sure our line number and results are not null.
    if(line_numbers == NULL || results == NULL)
    {
        perror("malloc failed");
        return 1;
    }


	int rc;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;

	/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	read_file();

	for (long i = 0; i < NUM_THREADS; i++ ) {
	      rc = pthread_create(&threads[i], &attr, count_array, (void *)i);
	      if (rc) {
	        printf("ERROR; return code from pthread_create() is %d\n", rc);
			free(line_numbers);
			free(results);
		exit(-1);
	      }
	}

	/* Free attribute and wait for the other threads */
	pthread_attr_destroy(&attr);
	for(int i=0; i<NUM_THREADS; i++) {
	     rc = pthread_join(threads[i], &status);
	     if (rc) {
		   printf("ERROR; return code from pthread_join() is %d\n", rc);
		   exit(-1);
	     }
	}

	print_results();
	free(line_numbers);
    free(results);


	// pthread_mutex_destroy(&mutexsum);
	printf("Main: program completed. Exiting.\n");
	return 0;
	//pthread_exit(NULL);
}

