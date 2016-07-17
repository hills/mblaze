#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

#include "blaze822.h"

int
main(int argc, char *argv[])
{
	char *map = blaze822_seq_open(0);
	if (!map)
		return 1;

	int i;
	char *f;
	struct blaze822_seq_iter iter = { 0 };
	for (i = 1; i < argc; i++) {
		while ((f = blaze822_seq_next(map, argv[i], &iter))) {
			printf("%s\n", f);
			free(f);
		}
	}

	return 0;
}
