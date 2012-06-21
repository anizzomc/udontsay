/* <package.h> */

#ifndef _PACKAGE_H_
#define _PACKAGE_H_

typedef enum {command_null, command_ping, command_pong} command_t;

typedef struct {
	command_t command;
	unsigned char size;
	unsigned char *data;
} package_t;

package_t package_new(command_t command, const unsigned char* data, unsigned char size);

package_t package_null();

void package_free(package_t *package);

#endif

/* </packag.h> */
