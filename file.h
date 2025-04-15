/*Name: Sameeksha Suresh
1.Project Name: Address Book Management System in C
2.Date Started: 12/1/25
3.Date Ended: 21/1/25
4.About Project:
The Address Book Management System is a C-based console application developed to manage 
and organize contact information efficiently. The project allows users to add, search, 
edit, delete, and display contact details such as names, phone numbers, and email addresses. 
Designed with a menu-driven interface, it ensures ease of use and quick navigation through 
functionalities. Data is stored using file handling, enabling persistence even after the 
program is closed. This project helped strengthen understanding of structures, file operations, 
and user input handling in C programming, making it a great foundation for building more complex 
database-driven applications in the future.
*/
#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
