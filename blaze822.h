#include <stdint.h>
#include <sys/types.h>

struct message;

// blaze822.c

struct message *blaze822(char *file);       // just header
struct message *blaze822_file(char *file);  // header + body (read(2))
struct message *blaze822_mmap(char *file);  // header + body (mmap(2))
struct message *blaze822_mem(char *buf, size_t len);  // header + body

char *blaze822_hdr_(struct message *mesg, const char *hdr, size_t len);
#define blaze822_hdr(mesg, hdr) blaze822_hdr_(mesg, "\0" hdr ":", 2+strlen((hdr)))
char *blaze822_chdr(struct message *mesg, const char *chdr);

char *blaze822_next_header(struct message *mesg, char *prev);

void blaze822_free(struct message *mesg);

time_t blaze822_date(char *);
char *blaze822_addr(char *, char **, char **);
char *blaze822_body(struct message *mesg);
size_t blaze822_bodylen(struct message *mesg);
size_t blaze822_headerlen(struct message *mesg);

// rfc2047.c

int blaze822_decode_rfc2047(char *, char *, size_t, char *);
int blaze822_decode_qp(char *start, char *stop, char **deco, size_t *decleno);
int blaze822_decode_b64(char *start, char *stop, char **deco, size_t *decleno);

// rfc2045.c

int blaze822_check_mime(struct message *msg);
int blaze822_mime_body(struct message *msg, char **cto, char **bodyo, size_t *bodyleno, char **bodychunko);
int blaze822_multipart(struct message *msg, struct message **imsg);
int blaze822_mime_parameter(char *s, char *name, char **starto, char **stopo);

// seq.c

char *blaze822_seq_open(char *file);
int blaze822_seq_load(char *map);
long blaze822_seq_find(char *ref);


char *blaze822_seq_cur();
int blaze822_seq_setcur(char *s);

struct blaze822_seq_iter {
	long lines;
	long cur;
	long start;
	long stop;

	long line;
	char *s;
};

char *blaze822_seq_next(char *map, char *range, struct blaze822_seq_iter *iter);
int blaze822_loop(int, char **, void (*)(char *));
