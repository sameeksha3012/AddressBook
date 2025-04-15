#include <stdio.h>
#include "file.h"
#include <string.h>

#define FILE_NAME "contacts.csv"

void saveContactsToFile(AddressBook *addressBook) \
{
     FILE *file = fopen("Csv_file.csv", "w");
    if (file == NULL) {
        perror("Error opening file for saving contacts");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully.\n");
  
}



void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *file = fopen("Csv_file.csv", "r");
    if (file == NULL) {
        printf("No existing contact file found. Starting fresh.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");

        if (name && phone && email) {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }
    }

    fclose(file);
    printf("Contacts loaded from file successfully.\n");
    
}
