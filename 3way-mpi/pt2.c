#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 4096

int NUM_THREADS;							 //Made this an int to run the number of cores testing from command line.
char (*line_numbers)[MAX_LINE_LEN] = NULL;                       //pointer that tracks the number of the lines that have been read so far
int *results = NULL;                                            //Pointer that tracks our highest ASCII value from the lines in the file.
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
void count_array(int rank, int numTasks, int *localResults)
{
  	int startPos = rank * (num_lines_read / numTasks);		//starting position in file
  	int endPos = startPos + (num_lines_read / numTasks);		//end position in file

	//Makes sure we have enough threads.
  	if(rank == numTasks - 1)
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
		localResults[i] = max_ascii;	//Adds that ascii value from the previous line to our array 
	}
	return NULL;
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

int main(int argc, char* argv[]) 
{
	int rc;
	int numtasks, rank;

	rc = MPI_Init(&argc,&argv);
	//If status of MPI is not true returns an error.
	if (rc != MPI_SUCCESS) {
	  	  fprintf (stderr, "Error starting MPI program. Terminating.\n");
          MPI_Abort(MPI_COMM_WORLD, rc);
        }

        MPI_Comm_size(MPI_COMM_WORLD,&numtasks); //Number of processes
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);     //Unique id of the process

	line_numbers = malloc(sizeof(*line_numbers) * MAX_LINES); //Saves memory for the lines we are processing.
	//If there are no line numbers that have been allocated an error will be returned.
	if(line_numbers == NULL)
	{
		fprintf(stderr, "Rand %d: failed to allocate space for the line number\n", rank);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if ( rank == 0 ) {
		results = malloc(sizeof(int) * MAX_LINES);   //Saves memory for the rank we are on for the rank through out the file.
		//If no results are found after the program is ran an error message is returned.
		if(results == 0){
			fprintf(stderr, "Rank 0 didn't allocate results\n");
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
		read_file(); //Reads the file
	}
	//Sends data between processes so all the data ends up in the root process
	MPI_Bcast(&num_lines_read, 1, MPI_INT, 0, MPI_COMM_WORLD);
	 for(int i = 0; i < num_lines_read; i++)
    {
        MPI_Bcast(line_numbers[i], MAX_LINE_LEN, MPI_CHAR>
    }

	int *localResults = calloc(MAX_LINES, sizeof(int));  //Creates memory for the results we get from the different machines running the program.'
	//If there are no local results returned an error message is returned.
	if (localResults == NULL)
	{
		fprintf(stderr, "Rank %d: failed to allocate a local result\n", rank);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
		
	count_array(rank, numtasks, localResults);    //Finds the max ascii value in the line.

	if(rank != 0)
	{
		results = malloc(sizeof(int) * MAX_LINES);    //Saves memeory for the reuslts from all the machines that helped run the program.
		//If no results are returned an error message is printed.
		if(results == NULL)
		{
			fprintf(stderr, "Rand %d: failed to allocate results\n", rank);
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	MPI_Reduce(localResults, results, MAX_LINES, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);


	if ( rank == 0 ) {
		print_results();  //Prints the results of the program.
	}
	free(localResults);
	free(results);
	free(line_numbers);

	MPI_Finalize();
	return 0;
}

