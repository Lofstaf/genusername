/*
Open file
Read line until newline
Store in struct as full name
Generate user name based on full name
Repeat until end of file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The maximum length allowed for a single line in the file.
#define MAX_LINE_LENGTH 256

struct User {
	int id;
	char *fullName;
	char *userName;
};

char* createUserName(const char *fullName);

int main(int argc, char *argv[]) {
	struct User *users = NULL;
	int counter = 0;
	char lineBuffer[MAX_LINE_LENGTH];
	char *fileName = argv[1];
	int i = 0;
	
	if (argc < 2) {
		printf("No arguments.\n");
		return -1;
	}

	FILE *filePointer = fopen(fileName, "r");
	if(filePointer == NULL) {
		printf("File error!\n");
		return -1;
	}

	while(fgets(lineBuffer, MAX_LINE_LENGTH, filePointer) != NULL) {
		// Remove newline at end of string.
		lineBuffer[strcspn(lineBuffer, "\n")] = '\0';
		struct User *newUsers = realloc(users, (counter + 1) * sizeof(struct User));
		if (newUsers == NULL) {
			printf("Memory allocation error!\n");
			for (int i = 0; i < counter; i++) {
            	free(users[i].fullName);
				free(users[i].userName);
			}
			free(users);
			fclose(filePointer);
			return -1;
		}
		users = newUsers;
		users[counter].id = counter + 1; // Don't want id to start at 0.
		users[counter].fullName = strdup(lineBuffer);
		users[counter].userName = createUserName(lineBuffer);

		counter++;
	}
	fclose(filePointer);
	printf("Counter: %d\n", counter);

	for (i = 0; i < counter; i++) {
		printf("\"%s\",%s\n", users[i].fullName, users[i].userName);
	}

	for (i = 0; i < counter; i++) {
		free(users[i].fullName);
		free(users[i].userName);
	}
	free(users);
	users = NULL;
	
	return 0;
}

char* createUserName(const char *fullName) {
    if (fullName == NULL) {
        return NULL;  // Safety: avoid null strings.
    }

    int nameLength = strlen(fullName);
    if (nameLength < 2) {
        return NULL;  // Safety: name must be at least two letters.
    }

    // Dynamically allocate userName
    char *userName = malloc(8);
    if (!userName) {
        return NULL;  // If malloc failes
    }

    // Temporary copy to convert to lower case,
    char tempName[nameLength + 1];
    strcpy(tempName, fullName);

    // Conver to lower case.
    for (int i = 0; i < nameLength; i++) {
        tempName[i] = tolower(tempName[i]);
    }

    // Create user name based on first two letters
    userName[0] = tempName[0];
    userName[1] = tempName[1];

    // Find spaces
    char *ptr = strchr(tempName, ' ');
    if (ptr != NULL && strlen(ptr) > 2) {
        userName[2] = ptr[1];
        userName[3] = ptr[2];
    } else {
        userName[2] = 'x';  // In case of no last name
        userName[3] = 'x';
    }

    userName[4] = '0';
    userName[5] = '0';
    userName[6] = '\0';  // Null terminate string

    return userName;  // Return pointer to user name
}

/*
int createUserName(char *fullName) {
	int nameLength = strlen(fullName);
	char userName[8];
	char *ptr;
	int i;
	
	// Change name to lower case.
	for (i = 0; i < nameLength; i++) {
		fullName[i] = tolower(fullName[i]);
	}

	userName[0] = fullName[0];
	userName[1] = fullName[1];
	// Find space in full name.
	ptr = strchr(fullName, ' ');	
	userName[2] = ptr[1];
	userName[3] = ptr[2];
	userName[4] = '0';
	userName[5] = '0';

	printf("%s, ", userName);
	return 0;
}
*/




