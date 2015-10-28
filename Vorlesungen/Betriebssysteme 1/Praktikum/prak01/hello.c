#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

int main( int argc, char *argv[] )
{
DIR *dip;
struct dirent *dit;

int i = 0;
int folderS = 0;
struct stat sb;	

if ((dip = opendir (argv [1])) == NULL){
perror ("opendir");
return 0;
}

\printf("Check 1\n");

while ((dit = readdir(dip)) != NULL){
i++;
//printf("\n%s", dit -> d_name);
//folderS += lstat(dit -> d_name);
sb = lstat(dit ->d_name);
printf("Size: %i Bytes\n",sb.st_size);
sb = NULL;
}

\printf("Check 2\n");

printf("\n\n readdir() found a total of %i files. Together they are %i Bytes long.\n", i, folderS);

\printf("Check 3\n");

if (closedir(dip) == 1 ){
perror("closedir");
return 0;
}

return 1;
}
