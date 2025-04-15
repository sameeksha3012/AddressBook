#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if (addressBook->contactCount == 0) {
        printf("No contacts available to display.\n");
        return;
    }

    Contact temp;
    int compare = 0;

    // Sorting based on the criteria
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = i + 1; j < addressBook->contactCount; j++) {
            switch(sortCriteria) {
                case 1: // Sort by Name
                    compare = strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
                    break;
                case 2: // Sort by Phone
                    compare = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
                    break;
                case 3: // Sort by Email
                    compare = strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email);
                    break;
                default:
                    printf("Invalid sorting criteria.\n");
                    return;
            }

            if (compare > 0) {
                // Swap the contacts if they are in the wrong order
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // Displaying sorted contacts in tabular form
    printf("\n==========================================================================\n");
    printf("| %-20s | %-15s | %-30s |\n", "Name", "Phone", "Email");
    printf("|----------------------|-----------------|--------------------------------|\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("| %-20s | %-15s | %-30s |\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        
        // Check if it's the last contact, don't print the separator for the last one
        if (i < addressBook->contactCount - 1) {
            printf("|----------------------|-----------------|--------------------------------|\n");
        }
    }

    printf("==========================================================================\n\n");
    
}

void listContactsMenu(AddressBook *addressBook) 
{
    printf("\nSorting criteria:\n");
    printf("1. By Name (Alphabetical Order)\n");
    printf("2. By Phone (Numerical Order)\n");
    printf("3. By Email\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Please choose between 1, 2, or 3.\n");
        return;
    }

    listContacts(addressBook, choice); // Call the listContacts function to sort and display by the chosen criterion
}




void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int validate_name(char name[]) 
{
    int i=0;
    while(name[i]!='\0')
    {
        if(isalpha(name[i]))
        {
            i++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void capitalize_name(char name[])
{
    if (islower(name[0]))
    {
        name[0] = toupper(name[0]);
    }
    for (int i = 1; name[i] != '\0'; i++)
    {
        if (isupper(name[i]))
        {
            name[i] = tolower(name[i]);
        }
    }
}

// TO VALIDATE THE PHONE NUMBER 
int validate_phone(char phone[])
{
    int i=0;
    while(phone[i]!='\0')
    {
        if(!isdigit(phone[i]))
        {
            return 0;
        }
        i++;
    }
    if(i==10) // Ensure it's a 10-digit number
        return 1;
    return 0;
}

// TO VALIDATE THE EMAIL-ID
int validate_email(char *email)
{
    char *p;
    p = strstr(email,".com");
    if(p == NULL)
    {
        return 0;
    }
    p = strstr(email,"@");
    if(p == NULL)
    {
        return 0;
    }
    return 1;
}

int is_duplicate(AddressBook *addressBook, char *name, char *phone, char *email)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("The name '%s' is already present. Please enter a new name.\n", name);
            return 1;
        }
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("The phone number '%s' is already present. Please enter a new phone number.\n", phone);
            return 1;
        }
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("The email '%s' is already present. Please enter a new email.\n", email);
            return 1;
        }
    }
    return 0;
}

void createContact(AddressBook *addressBook)
{
    char name[20];
    char phone[20];
    char email[50];
    int valid_flag;

    printf("\n-------- Welcome to the Unique AddressBook --------\n");
    printf("Creating a new contact...\n");
    printf("==============================================\n\n");

    // NAME:
    do
    {
        printf("Enter the Name: ");
        scanf(" %[^\n]", name);

        valid_flag = validate_name(name);
        if (!valid_flag)
        {
            printf("Invalid name. Names can only contain alphabets.\n");
            continue;
        }

        capitalize_name(name);

        if (is_duplicate(addressBook, name, "", ""))
        {
            valid_flag = 0;
        }
    } while (!valid_flag);

    // PHONE:
    do
    {
        printf("Enter the Phone: ");
        scanf(" %[^\n]", phone);

        valid_flag = validate_phone(phone);
        if (!valid_flag)
        {
            printf("Invalid phone number. Ensure it's a 10-digit number.\n");
            continue;
        }

        if (is_duplicate(addressBook, "", phone, ""))
        {
            valid_flag = 0;
        }
    } while (!valid_flag);

    // EMAIL-ID:
    do
    {
        printf("Enter the Email: ");
        scanf(" %[^\n]", email);

        valid_flag = validate_email(email);
        if (!valid_flag)
        {
            printf("Invalid email ID. Ensure it contains '@' and ends with '.com'.\n");
            continue;
        }

        if (is_duplicate(addressBook, "", "", email))
        {
            valid_flag = 0;
        }
    } while (!valid_flag);

    // Store in structure
    int box = addressBook->contactCount;
    strcpy(addressBook->contacts[box].name, name);
    strcpy(addressBook->contacts[box].phone, phone);
    strcpy(addressBook->contacts[box].email, email);
    addressBook->contactCount++;

     printf("\n==========================================================================\n");
    printf("| Contact Saved Successfully!                                             |\n");
   printf("|----------------------|-----------------|--------------------------------|\n");
    printf("| %-20s | %-15s | %-30s |\n", "Name", "Phone", "Email");
    printf("|----------------------|-----------------|--------------------------------|\n");
    printf("| %-20s | %-15s | %-30s |\n", name, phone, email);
    printf("============================================================================\n");
    saveContactsToFile(addressBook);
}

//Searching Contact Number
//TO SEARCH BY NAME:
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// TO SEARCH BY NAME:
int searching_by_name(char *name, AddressBook *addressbook) {
    // Convert the search name to lowercase
    toLowerCase(name);
    
    printf("Contact Count: %d\n", addressbook->contactCount);

    for (int i = 0; i < addressbook->contactCount; i++) {
        // Convert the contact's name to lowercase and compare
        char contactName[50];
        strcpy(contactName, addressbook->contacts[i].name); // Copy contact name to a temporary variable
        toLowerCase(contactName); // Convert the contact name to lowercase for comparison
        
        if (strcmp(name, contactName) == 0) { // Compare lowercase strings
            // Contact found
            printf("Contact Found\n");
            printf("Name: %s\n", addressbook->contacts[i].name);
            printf("Phone: %s\n", addressbook->contacts[i].phone);
            printf("Email: %s\n", addressbook->contacts[i].email);
            return i; // Return the index of the contact
        }
    }

    printf("Oops! Contact Not Found\n");
    return -1; // If not found
}

// TO SEARCH BY PHONE NUMBER
int searching_by_phone(char *phone, AddressBook *addressbook) {
    int found = 0;
    for (int i = 0; i < addressbook->contactCount; i++) {
        if (strcmp(phone, addressbook->contacts[i].phone) == 0) {
            // Contact found by phone number
            printf("Contact Found\n");
            printf("Name: %s\n", addressbook->contacts[i].name);
            printf("Phone: %s\n", addressbook->contacts[i].phone);
            printf("Email: %s\n", addressbook->contacts[i].email);
            found = 1;
            return i; // Return the index of the contact
        }
    }

    if (!found) {
        printf("Oops! Contact Not Found\n");
        return -1; // If not found
    }

    return -1;
}

// TO SEARCH BY EMAIL-ADDRESS
int searching_by_email(char *email, AddressBook *addressbook) {
    int found = 0;
    for (int i = 0; i < addressbook->contactCount; i++) {
        if (strcasecmp(email, addressbook->contacts[i].email) == 0) {
            // Contact found by email
            printf("Contact Found\n");
            printf("Name: %s\n", addressbook->contacts[i].name);
            printf("Phone: %s\n", addressbook->contacts[i].phone);
            printf("Email: %s\n", addressbook->contacts[i].email);
            found = 1;
            return i; // Return the index of the contact
        }
    }

    if (!found) {
        printf("Oops! Contact Not Found\n");
        return -1; // If not found
    }

    return -1;
}

// Function to call the appropriate search function based on user input
void searchContact(AddressBook *addressBook) 
{
    int choice;

    // Prompt user to choose search option
    printf("Enter Your Choice:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    scanf("%d", &choice);

    int valid_flag = 0;

    switch (choice) 
    {
        case 1: 
        {
            char searching_name[50];
            printf("Enter the Name to be searched: ");
            scanf("%s", searching_name);
            valid_flag = searching_by_name(searching_name, addressBook);
            break;
        }
        case 2: 
        {
            char searching_phone[20];
            printf("Enter the Phone Number to be searched: ");
            scanf("%s", searching_phone);
            valid_flag = searching_by_phone(searching_phone, addressBook);
            break;
        }
        case 3: 
        {
            char searching_email[50];
            printf("Enter the Email to be searched: ");
            scanf("%s", searching_email);
            valid_flag = searching_by_email(searching_email, addressBook);
            break;
        }
        default: 
        {
            printf("Invalid Option. Please enter a valid option.\n");
            break;
        }
    }
}

void editContact(AddressBook *addressBook) 
{
    int choice;
    int valid_flag = 0;
    
    // Ask the user what criteria they want to search by
    printf("Enter your choice to search by:\n");
    printf("1. By Name\n");
    printf("2. By Phone Number\n");
    printf("3. By Email\n");
    scanf("%d", &choice);
    
    int contactIndex = -1;  // To store the index of the contact to be edited
    
    switch(choice)
    {
        case 1: 
        {
            char searching_name[20];
            printf("Enter the Name to search and edit:\n");
            scanf(" %[^\n]", searching_name);  
            contactIndex = searching_by_name(searching_name, addressBook);
            break;
        }
        case 2: 
        {
            char searching_phone[20];
            printf("Enter the Phone Number to search and edit:\n");
            scanf(" %[^\n]", searching_phone);  
            contactIndex = searching_by_phone(searching_phone, addressBook);
            break;
        }
        case 3: 
        {
            char searching_email[50];
            printf("Enter the Email ID to search and edit:\n");
            scanf(" %[^\n]", searching_email);  
            contactIndex = searching_by_email(searching_email, addressBook);
            break;
        }
        default:
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
            return;
    }

    // If the contact is found, proceed to edit
    if (contactIndex >= 0) {
        printf("\nContact Found. You can now edit the contact details:\n");
        Contact *contactToEdit = &addressBook->contacts[contactIndex];

        // Edit Name
        char newName[50];
        printf("Current Name: %s\n", contactToEdit->name);
        printf("Enter new Name (or press Enter to keep unchanged): ");
        fgets(newName, sizeof(newName), stdin);  // Clear input buffer
        fgets(newName, sizeof(newName), stdin);  //new name
        if (strlen(newName) > 1) 
        {
            newName[strlen(newName) - 1] = '\0'; // Remove newline character
            strcpy(contactToEdit->name, newName);
        }

        // Edit Phone
        char newPhone[20];
        printf("Current Phone: %s\n", contactToEdit->phone);
        printf("Enter new Phone (or press Enter to keep unchanged): ");
        fgets(newPhone, sizeof(newPhone), stdin); 
        fgets(newPhone, sizeof(newPhone), stdin);  
        if (strlen(newPhone) > 1) 
        {
            newPhone[strlen(newPhone) - 1] = '\0'; 
            strcpy(contactToEdit->phone, newPhone);
        }

        // Edit Email
        char newEmail[50];
        printf("Current Email: %s\n", contactToEdit->email);
        printf("Enter new Email (or press Enter to keep unchanged): ");
        fgets(newEmail, sizeof(newEmail), stdin);  
        fgets(newEmail, sizeof(newEmail), stdin);  
        if (strlen(newEmail) > 1) 
        {
            newEmail[strlen(newEmail) - 1] = '\0'; 
            strcpy(contactToEdit->email, newEmail);
        }

        printf("\nContact details updated successfully.\n");
    } 
    else 
    {
        printf("Contact not found.\n");
    }
    saveContactsToFile(addressBook);

}

void deleteContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("\nNo contacts to delete.\n");
        return;
    }

    char searchKey[50]; 
    int matchPosition = -1; 

    printf("\nEnter the name, phone, or email of the contact to delete: ");
    scanf(" %[^\n]", searchKey);

    // Search for the contact by name, phone, or email
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, searchKey) == 0 ||
            strcmp(addressBook->contacts[i].phone, searchKey) == 0 ||
            strcmp(addressBook->contacts[i].email, searchKey) == 0) 
        {
            matchPosition = i;
            break;
        }
    }

    if (matchPosition != -1) 
    {
        printf("\nContact found: \n");
        printf("Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[matchPosition].name,
               addressBook->contacts[matchPosition].phone,
               addressBook->contacts[matchPosition].email);

        char confirmation;
        printf("Are you sure you want to delete this contact? (y/n): ");
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y')
        {
            // Shift all contacts after the deleted one
            for (int i = matchPosition; i < addressBook->contactCount - 1; i++) 
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;
            printf("\nContact deleted successfully.\n");
        } 
        else 
        {
            printf("\nDeletion canceled.\n");
        }
    } 
    else 
    {
        printf("\nContact not found.\n");
    }
            saveContactsToFile(addressBook);


}

