/*
Name : Suraj Roy
Date 27/12/2022
Description : Implement a wc(word count) command with –l –w -c options
Sample Input : 
hi hello
word
Sample Output : 1   3   13 stdin
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 10

int my_copy(int source_fd, int dest_fd);
int word_count(int fd, int *lcount, int *wcount, int *ccount);
void print(char *pathname, int lines, int words, int character, int l_flag, int w_flag, int c_flag);

int main(int argc, char **argv)
{
       //declare variables
       int i, fd, c, ccount = 0, wcount = 0, lcount = 0, l_flag = 0, w_flag = 0, c_flag = 0;
       extern int optind;

       //get the flags using getopt and set the flags accordingly
       while ((c = getopt (argc, argv, "clw")) != -1)
       {
	      switch (c)
	      {
		     case 'l':
			    l_flag = 1;
			    break;
		     case 'w':
			    w_flag = 1;
			    break;
		     case 'c':
			    c_flag = 1;
			    break;
	      }
       }

       //if no files are given read from stdin
       if(argv[optind] == NULL)
       {
	      int fd = dup(0);
	      //read from stdin and get the word count
	      ccount = 0;
	      wcount = 0;
	      lcount = 0;

	      // to get the word count 
	      word_count(fd, &lcount, &wcount, &ccount);

	      // close the fd 
	      close(fd);

	      // print the file and respective word counts 
	      print("stdin", lcount, wcount, ccount, l_flag, w_flag, c_flag);
       }

       //if file name is passed
       else
       {
	      int c_total = 0, w_total = 0, l_total = 0;
      	      
	      //for multiple file cases
	      for (i = optind; i < argc; i++)
	      {
		     if ((fd = open(argv[i], O_RDONLY)) == -1 )
		     {

		    	    perror("open");
			    return -1;
		     }
		     ccount = 0;
		     wcount = 0;
		     lcount = 0;

	     	     // to get the word count 
	     	     word_count(fd, &lcount, &wcount, &ccount);
	     	     
	     	     // close the fd
	     	     close(fd);

	     	     // print the file and respective word counts 
	     	     print(argv[i], lcount, wcount, ccount, l_flag, w_flag, c_flag);
		    
		     //sum up 
		     c_total += ccount;
		     w_total += wcount;
		     l_total += lcount;
      	      }
      	      //printing total value 
	      printf("%d   %d   %d  total\n", l_total, w_total, c_total);
	}

}


//function for word count, line count and character count
int word_count(int fd, int *lcount, int *wcount, int *ccount)
{

       int read_len = 0, line = 0, word = 0, character = 0, i;
       char buff[BUFF_SIZE], ch;

       while( ((read_len = read(fd, buff, BUFF_SIZE)) != -1 ) && (read_len != 0))
       {
		
	      for(i = 0; i < read_len; i++)
	      {
		     //to get character
		     character++;
		     //to get lines
		     if(buff[i] == '\n')
		     {
			    line++;
		     }

		     //to get words
		     if(buff[i] == ' ' || buff[i] == '\n' || buff[i] == '\t')
		     {
    			    if(ch != ' ' && ch != '\t' && ch != '\n')
			    {
				   word++;
		    	    }
		     }
	      	     ch = buff[i];
      	      }
       }
       //if program is end without space,tab and newline
       if(read_len == 0 && ch != ' ' && ch != '\t' && ch != '\n' && character !=0)
       {
      	      word++;
       }
       *ccount = character;
       *lcount = line;
       *wcount = word;
}

//print lines word character value
void print(char *pathname, int lines, int words, int character, int l_flag, int w_flag, int c_flag)
{
       //check for flag outputs and printing 
       printf("\n");
       if(l_flag == 1 || (w_flag == 0 && l_flag == 0 && c_flag == 0))
       {
	      printf("%d   ", lines);
       }
       if(w_flag == 1 || (w_flag == 0 && l_flag == 0 && c_flag == 0))
       {
	      printf("%d   ", words);
       }
       if(c_flag == 1 || (w_flag == 0 && l_flag == 0 && c_flag == 0))
       {
	      printf("%d ", character);
       }       
       printf("%s\n", pathname);
}
