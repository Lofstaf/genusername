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

int createUserName(char *fullName);
char* createUserName2(const char *fullName);

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
			free(users);
			fclose(filePointer);
			return -1;
		}
		users = newUsers;
		users[counter].id = counter + 1; // Vill inte att id börjar på 0.
		users[counter].fullName = strdup(lineBuffer);
		users[counter].userName = strdup(createUserName2(lineBuffer));
		
		counter++;
	}
	fclose(filePointer);
	printf("Counter: %d\n", counter);

	for (i = 0; i < counter; i++) {
		printf("\"%s\",%s\n", users[i].fullName, users[i].userName);
		i++;
	}

	for (i = 0; i < counter; i++) {
		free(users[i].fullName);
	}
	free(users);
	users = NULL;
	
	return 0;
}

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


char* createUserName2(const char *fullName) {
    if (fullName == NULL) {
        return NULL;  // Säkerhet: undvik att arbeta med NULL-strängar
    }

    int nameLength = strlen(fullName);
    if (nameLength < 2) {
        return NULL;  // Säkerhet: namn måste vara minst två bokstäver
    }

    // Dynamiskt allokera användarnamn
    char *userName = malloc(8);
    if (!userName) {
        return NULL;  // Om malloc misslyckas
    }

    // Skapa en lokal kopia av namnet för att omvandla det till lowercase
    char tempName[nameLength + 1];
    strcpy(tempName, fullName);

    // Omvandla till små bokstäver
    for (int i = 0; i < nameLength; i++) {
        tempName[i] = tolower(tempName[i]);
    }

    // Skapa användarnamn baserat på första två bokstäverna
    userName[0] = tempName[0];
    userName[1] = tempName[1];

    // Hitta mellanslag
    char *ptr = strchr(tempName, ' ');
    if (ptr != NULL && strlen(ptr) > 2) {
        userName[2] = ptr[1];
        userName[3] = ptr[2];
    } else {
        userName[2] = 'x';  // Reservbokstav om inget efternamn finns
        userName[3] = 'x';
    }

    userName[4] = '0';
    userName[5] = '0';
    userName[6] = '\0';  // Null-terminera strängen

    return userName;  // Returnera pekaren till användarnamnet
}






