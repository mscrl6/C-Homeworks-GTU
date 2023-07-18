#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// book structure
typedef struct Book Book;
typedef struct Book {
	char ISBN[20];
	char title[50];
	char author[50];
	int publication_year;
	int reserved_status;
	Book* next;
	Book* prev;

}Book;

// student structure 
typedef struct Student Student;
typedef struct Student {
    char name[20];
    int ID;
    char borrowed_book_ISBN[3][20]; // student can borrow maximum 3 books
    Student* next;
    Student* prev;
} Student;

//Define of the functions
void borrowed_books(Student* student_root,Book* book_root,int ID);
Book* createBook(char* ISBN, char* title, char* author, int publicationYear, int reserved);
void addBook(char* isbn, char* title, char* author, int publicationYear, int method, Book** head);
void deleteBook(Book** head, char* isbn);
void updateBook(Book* head, char* isbn, char* feature, char* value); 
Book* filterBooks(Book* head, int filterChoice, char* filter);
void bubbleSortPublicationYear(Book* start);
void bubbleSortAuthor(Book* start);
void bubbleSortTitle(Book* start);
void swap(Book* a, Book* b);
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice,Book* head);
void reverseBookList(Book** head_ref);
void searchBooks(int searchChoice, char* searchValue,Book* head);
void returnBook(char* isbn, Book* book_head, Student* student_head, int student_id);
void borrowBook(char* isbn, Book* book_head, Student* student_head, int student_id);
void writeBookToFile(Book* book);
void writeAllBooks(Book* head);
void writeStudentToFile(Student* student);
void updateStudentsFile(Student* student_head);
Student* createStudent(Student** student_head, char* name, int ID);
void displayBooks(Book* head); 
Book* getBooksFromFile();
/******************************************************************************************************/

/*-------------------------------------------------------------------------------------*/

// Function to get books from file
Book* getBooksFromFile() {
    FILE* file = fopen("books.txt", "r");
    Book* head = NULL;
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    Book* current_book = NULL;
    char ISBN[20], title[20], author[20], reserved_status[20], publication_year[20];

    while(fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", ISBN, title, author, publication_year, reserved_status) == 5) {
        Book* book = (Book*)malloc(sizeof(Book));
        strcpy(book->ISBN, ISBN);
        strcpy(book->title, title);
        strcpy(book->author, author);
        book->publication_year = atoi(publication_year);
        book->reserved_status = atoi(reserved_status);
        book->next = NULL;
        book->prev = current_book;
        if (current_book) {
            current_book->next = book;
        } else {
            head = book; // Set head if this is the first book
        }
        current_book = book;
    }
    fclose(file);
    return head;
}

// Function to get students from file
Student* getStudentsFromFile() {
    FILE* file = fopen("students.txt", "r");
    Student* head = NULL;
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    Student* current_student = NULL;
    char name[20], ID[20], borrowed_book_ISBN[3][20];

    while(fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", name, ID, borrowed_book_ISBN[0], borrowed_book_ISBN[1], borrowed_book_ISBN[2]) == 5) {
        Student* student = (Student*)malloc(sizeof(Student));
        strcpy(student->name, name);
        student->ID = atoi(ID);
        strcpy(student->borrowed_book_ISBN[0], borrowed_book_ISBN[0]);
        strcpy(student->borrowed_book_ISBN[1], borrowed_book_ISBN[1]);
        strcpy(student->borrowed_book_ISBN[2], borrowed_book_ISBN[2]);
        student->next = NULL;
        student->prev = current_student;

        if (current_student) {
            current_student->next = student;
        } else {
            head = student; // Set head if this is the first student
        }
        current_student = student;
    }
    fclose(file);
    return head;
}

/*-------------------------------------------------------------------------------------*/
void borrowed_books(Student* student_root, Book* book_root, int ID) {
    Student* tempStudent = student_root;
    int i, flag;

    //Find student with ID
    while(tempStudent != NULL && tempStudent->ID != ID) {
        tempStudent = tempStudent->next;
    }

    if(tempStudent != NULL) {
        flag = 0;
        for(i = 0; i < 3; i++) {
            if(strcmp(tempStudent->borrowed_book_ISBN[i], "0") != 0) {
                // Find the book with the borrowed_book_ISBN
                Book* tempBook = book_root;
                while(tempBook != NULL && strcmp(tempBook->ISBN, tempStudent->borrowed_book_ISBN[i]) != 0) {
                    tempBook = tempBook->next;
                }
                if(tempBook != NULL) {
                    printf("Book: %s, Author: %s\n", tempBook->title, tempBook->author);
                    flag = 1;
                } else {
                    printf("Book with ISBN: %s not found\n", tempStudent->borrowed_book_ISBN[i]);
                }
            }
        }
        // If student already has 3 books
        if(flag == 0) {
            printf("Student with ID: %d has not borrowed any books.\n", ID);
        }
    } else {
        printf("Student ID not found\n");
    }
}
void borrowBook(char* isbn, Book* book_head, Student* student_head, int student_id) {
    Book* temp_book = book_head;
    Student* temp_student = student_head;
    int i;

    // Search for the book with the given ISBN
    while(temp_book != NULL && strcmp(temp_book->ISBN, isbn) != 0) {
        temp_book = temp_book->next;
    }

    // Search for the student with the given ID
    while(temp_student != NULL && temp_student->ID != student_id) {
        temp_student = temp_student->next;
    }

    // If the book and the student are found and the book is not borrowed
    if(temp_book != NULL && temp_student != NULL && temp_book->reserved_status == 0) {
        temp_book->reserved_status = 1;
        for(i = 0; i < 3; i++) {
            if(strcmp(temp_student->borrowed_book_ISBN[i], "0") == 0) {
                strcpy(temp_student->borrowed_book_ISBN[i], temp_book->ISBN);
                break;
            }
        }
        if(i == 3) {
            printf("Student %d already has 3 books.\n", temp_student->ID);
            temp_book->reserved_status = 0; // Set back book status if student can't borrow
        }
        else {
            printf("Student %d has borrowed the book %s.\n", temp_student->ID, temp_book->title);
            updateStudentsFile(student_head); // Update all students' data in the file
            writeAllBooks(book_head); // Update all books' data in the file
        }
    } else {
        printf("The book is not available for borrowing or the student does not exist.\n");
    }
}


void returnBook(char* isbn, Book* book_head, Student* student_head, int student_id) {
    Book* temp_book = book_head;
    Student* temp_student = student_head;
    int i;

    // Search for the book with the given ISBN
    while(temp_book != NULL && strcmp(temp_book->ISBN, isbn) != 0) {
        temp_book = temp_book->next;
    }

    // Search for the student with the given ID
    while(temp_student != NULL && temp_student->ID != student_id) {
        temp_student = temp_student->next;
    }

    // If the book and the student are found and the student borrowed the book
    if(temp_book != NULL && temp_student != NULL && temp_book->reserved_status == 1) {
        for(i = 0; i < 3; i++) {
            if(strcmp(temp_student->borrowed_book_ISBN[i], isbn) == 0) {
                strcpy(temp_student->borrowed_book_ISBN[i], "0");
                break;
            }
        }
        if(i == 3) {
            printf("The book is not borrowed by this student.\n");
        }
        else {
            temp_book->reserved_status = 0;
            printf("Student %d has returned the book %s.\n", temp_student->ID, temp_book->title);
            updateStudentsFile(student_head); // Update all students' data in the file
            writeAllBooks(book_head); // Update all books' data in the file
        }
    } else {
        printf("The book is not borrowed or the student does not exist.\n");
    }
}

/*-------------------------------------------------------------------------------------*/

/*Create a book*/
Book* createBook(char* ISBN, char* title, char* author, int publicationYear, int reserved) {
    Book* newBook = (Book*) malloc(sizeof(Book));
    strcpy(newBook->ISBN, ISBN);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->publication_year = publicationYear;
    newBook->reserved_status = reserved;
    newBook->next = NULL;
    return newBook;
}

void addBook(char* isbn, char* title, char* author, int publicationYear, int method, Book** head) {
    // Create new book
    Book* newBook = createBook(isbn, title, author, publicationYear, 0);
    writeBookToFile(newBook);
    if(method == 0) { // FIFO
        if(*head == NULL) {
            *head = newBook;
        } 
        else {
            Book* temp = *head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
    } 
    else if(method == 1) { // LIFO
        newBook->next = *head;
        *head = newBook;
    } 
    else {
        printf("Invalid method. Choose 0 for FIFO or 1 for LIFO.\n");
    }
}


/*-------------------------------------------------------------------------------------*/
/*Write a book to file*/
void writeBookToFile(Book* book) {
    FILE* file = fopen("books.txt", "a");
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    fprintf(file, "%s,%s,%s,%d,%d\n", book->ISBN, book->title, book->author, book->publication_year, book->reserved_status);
    fclose(file);
}

/*Write all books to file*/
void writeAllBooks(Book* head){
    FILE* file = fopen("books.txt", "w"); // Open in write mode to overwrite existing content
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    Book* temp = head;
    while(temp != NULL) {
        fprintf(file, "%s,%s,%s,%d,%d\n", temp->ISBN, temp->title, temp->author, temp->publication_year, temp->reserved_status);
        temp = temp->next;
    }
    fclose(file);
}

/*-------------------------------------------------------------------------------------*/
/*Delete a book*/
void deleteBook(Book** head, char* isbn) {
    if (*head == NULL) {
        printf("The book list is empty.\n");
        return;
    }

    Book* temp = *head;
    Book* prev = NULL;

    // If head holds the book to be deleted
    if (strcmp(temp->ISBN, isbn) == 0) {
        *head = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    // Search for the book to be deleted
    while (temp != NULL && strcmp(temp->ISBN, isbn) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // If book was not present in the list
    if (temp == NULL) {
        printf("Book not found.\n");
        return;
    }

    // Unlink the node from linked list
    prev->next = temp->next;
    writeAllBooks(*head);
    free(temp);  // Free memory
}

/*-------------------------------------------------------------------------------------*/
/* Update a book*/
void updateBook(Book* head, char* isbn, char* feature, char* value) {
        Book* temp = head;

    // Search for the book with the given ISBN
    while(temp != NULL && strcmp(temp->ISBN, isbn) != 0) {
        temp = temp->next;
    }

    // If the book is not found
    if(temp == NULL) {
        printf("Book not found.\n");
        return;
    }

    // Update the book's information
    if(strcmp(feature, "title") == 0) {
        strcpy(temp->title, value);
    } else if(strcmp(feature, "author") == 0) {
        strcpy(temp->author, value);
    } else if(strcmp(feature, "publicationYear") == 0) {
        temp->publication_year = atoi(value);
    } else {
        printf("Invalid feature. Please enter either 'title', 'author', or 'publicationYear'.\n");
        return;
    }
    // Update the file
    writeAllBooks(head);
}

/*-------------------------------------------------------------------------------------*/
/*Function to print filtered books to a file*/
void printBooksToFile(Book* head) {
    FILE* file = fopen("filtered_sorted_books.txt", "w");

    Book* temp = head;
    while(temp != NULL) {
        fprintf(file, "ISBN: %s\n", temp->ISBN);
        fprintf(file, "Title: %s\n", temp->title);
        fprintf(file, "Author: %s\n", temp->author);
        fprintf(file, "Publication Year: %d\n", temp->publication_year);
        fprintf(file, "Reservation Status: %d\n\n", temp->reserved_status);

        temp = temp->next;
    }

    fclose(file);
}
/*Function to swap book information*/
void swap(Book* a, Book* b) {
    char tempIsbn[20];
    char tempTitle[50];
    char tempAuthor[50];
    int tempPublicationYear;
    int tempReservedStatus;

    strcpy(tempIsbn, a->ISBN);
    strcpy(tempTitle, a->title);
    strcpy(tempAuthor, a->author);
    tempPublicationYear = a->publication_year;
    tempReservedStatus = a->reserved_status;

    strcpy(a->ISBN, b->ISBN);
    strcpy(a->title, b->title);
    strcpy(a->author, b->author);
    a->publication_year = b->publication_year;
    a->reserved_status = b->reserved_status;

    strcpy(b->ISBN, tempIsbn);
    strcpy(b->title, tempTitle);
    strcpy(b->author, tempAuthor);
    b->publication_year = tempPublicationYear;
    b->reserved_status = tempReservedStatus;
}
/*Function to filter books based on given criteria*/
Book* filterBooks(Book* head, int filterChoice, char* filter) {
    Book* temp = head;
    Book* filtered_head = NULL;
    Book* filtered_tail = NULL;

    while(temp != NULL) {
        if((filterChoice == 0 && strcmp(temp->author, filter) == 0) || 
           (filterChoice == 1 && temp->publication_year == atoi(filter))) {
            Book* new_book = malloc(sizeof(Book));
            strcpy(new_book->ISBN, temp->ISBN);
            strcpy(new_book->title, temp->title);
            strcpy(new_book->author, temp->author);
            new_book->publication_year = temp->publication_year;
            new_book->reserved_status = temp->reserved_status;
            new_book->next = NULL;
            if(filtered_head == NULL) {
                filtered_head = new_book;
                filtered_tail = new_book;
            } else {
                filtered_tail->next = new_book;
                filtered_tail = new_book;
            }
        }
        temp = temp->next;
    }

    return filtered_head;
}
/*Function to filter and sort books based on given criteria*/
void filterAndSortBooks(int filterChoice, char* filter, int sortChoice,Book* head) {
    Book* filtered_books = filterBooks(head, filterChoice, filter);
    if(sortChoice == 0) {
        bubbleSortTitle(filtered_books);
    } else if(sortChoice == 1) {
        bubbleSortAuthor(filtered_books);
    } else if(sortChoice == 2) {
        bubbleSortPublicationYear(filtered_books);
    } else {
        printf("Invalid sort choice.\n");
        return;
    }
    printBooksToFile(filtered_books);
}
/*Bubble sort function to sort books by title*/
void bubbleSortTitle(Book* start) {
    int swapped;
    Book* ptr1;
    Book* lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->title, ptr1->next->title) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while (swapped);
}
/*Bubble sort function to sort books by author*/
void bubbleSortAuthor(Book* start) {
    int swapped;
    Book* ptr1;
    Book* lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->author, ptr1->next->author) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
/*Bubble sort function to sort books by publication year*/
void bubbleSortPublicationYear(Book* start) {
    int swapped;
    Book* ptr1;
    Book* lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->publication_year > ptr1->next->publication_year) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/*-------------------------------------------------------------------------------------*/
/*Function to reserve the list*/
void reverseBookList(Book** head_ref) {
    Book* prev   = NULL;
    Book* current = *head_ref;
    Book* next = NULL;
    while (current != NULL) {
        next  = current->next;  
        // Reverse current node's pointer
        current->next = prev;   
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
    displayBooks(*head_ref);
}

/*-------------------------------------------------------------------------------------*/
/*Search books*/
void searchBooks(int searchChoice, char* searchValue,Book* head) {
    Book* temp = head;
    int found = 0;

    while(temp != NULL) {
        if((searchChoice == 0 && strcmp(temp->ISBN, searchValue) == 0) || 
           (searchChoice == 1 && strcmp(temp->author, searchValue) == 0) ||
           (searchChoice == 2 && strcmp(temp->title, searchValue) == 0)) {
            printf("ISBN: %s, Title: %s, Author: %s, Publication Year: %d\n", 
                    temp->ISBN, temp->title, temp->author, temp->publication_year);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found) {
        printf("No book matches the given search criteria.\n");
    }
}

/*-------------------------------------------------------------------------------------*/
/*Display books*/
void displayBooks(Book* head) {
    Book* temp = head;
    while(temp != NULL) {
        printf("ISBN: %s, Title: %s, Author: %s, Publication Year: %d\n", 
                temp->ISBN, temp->title, temp->author, temp->publication_year);
        temp = temp->next;
    }
}

/***************************************************************************************************************************/
/*Write a student to file*/
void writeStudentToFile(Student* student) {

    FILE* file = fopen("students.txt", "a");
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    fprintf(file, "%s,%d,%s,%s,%s\n", student->name, student->ID, student->borrowed_book_ISBN[0], student->borrowed_book_ISBN[1], student->borrowed_book_ISBN[2]);
    fclose(file);
}

/*Update students.txt */
void updateStudentsFile(Student* student_head) {
    FILE* file = fopen("students.txt", "w");
    if(file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    Student* current_student = student_head;
    while(current_student != NULL) {
        fprintf(file, "%s,%d,%s,%s,%s\n", current_student->name, current_student->ID, current_student->borrowed_book_ISBN[0], current_student->borrowed_book_ISBN[1], current_student->borrowed_book_ISBN[2]);
        current_student = current_student->next;
    }

    fclose(file);
}

/*Create a new student*/
Student* createStudent(Student** student_head, char* name, int ID) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->name, name);
    newStudent->ID = ID;
    strcpy(newStudent->borrowed_book_ISBN[0], "0");
    strcpy(newStudent->borrowed_book_ISBN[1], "0");
    strcpy(newStudent->borrowed_book_ISBN[2], "0");
    newStudent->next = NULL;
    writeStudentToFile(newStudent); //write student to the file

    if (*student_head == NULL) {
        *student_head = newStudent;
    } else {
        Student* current = *student_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }

    return newStudent;
}

/*---------------------------------------------------------*/

int main() {
    int choice;
    char isbn[20], title[50], author[50], feature[20], value[20], filter[20], searchValue[20],name[25];
    int publicationYear, method, filterChoice, sortChoice, searchChoice, ID;
    Student* student_head = NULL;
    Book* book_head = NULL;
    student_head=getStudentsFromFile(student_head);
    book_head=getBooksFromFile(book_head);
    while(1) {
        printf("\n****************\n");
        printf("0. Display all books\n");
        printf("1. Add book\n");
        printf("2. Add student\n");
        printf("3. List borrowed book\n");
        printf("4. Delete a book\n");
        printf("5. Update a book\n");
        printf("6. Filter and sort books\n");
        printf("7. Reverse book list\n");
        printf("8. Search books\n");
        printf("9. Borrow or return a book\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                printf("All Books\n");
                displayBooks(book_head);
                break;
            case 1:
                printf("ISBN: ");
                scanf(" %[^\n]", isbn);

                printf("Title: ");
                scanf(" %[^\n]", title); 

                printf("Author: ");
                scanf(" %[^\n]", author); 

                printf("Publication Year: ");
                scanf("%d", &publicationYear);

                printf("Method (FIFO: 0, LIFO: 1): ");
                scanf("%d", &method);
                addBook(isbn, title, author, publicationYear, method,&book_head);
                printf("Book added succesfully!\n");
                break;
            case 2:
                printf("Enter student name: ");
                scanf(" %[^\n]", name);
                printf("Enter student ID: ");
                scanf("%d",&ID);
                createStudent(&student_head, name, ID);
                printf("Student added succesfully!\n");
                break;
            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &ID);
                borrowed_books(student_head,book_head, ID);
                break;
            case 4:
                printf("Enter ISBN: ");
                scanf(" %[^\n]", isbn);
                deleteBook(&book_head, isbn);
                printf("The book %s ISBN deleted.\n",isbn);
                break;
            case 5:
                printf("ISBN: ");
                scanf(" %[^\n]",isbn);
                printf("Feature (title, author, publicationYear): ");
                scanf(" %[^\n]",feature);
                printf("New value: ");
                scanf(" %[^\n]",value);
                updateBook(book_head, isbn, feature, value);
                printf("The book with %s ISBN updated.\n",isbn);
                break;
            case 6:
                printf("Enter filter choice (0->Author, 1->Publication year): ");
                scanf("%d", &filterChoice);
                printf("Filter value: ");
                scanf(" %[^\n]",filter);
                if(filterChoice==0){
                    printf("Enter sort choice (0->Title, 1->Publication year): ");
                    scanf("%d", &sortChoice);
                    if(sortChoice==0){
                        filterAndSortBooks(filterChoice, filter, sortChoice,book_head);
                    }
                    else if(sortChoice==1){
                        sortChoice=2;
                        filterAndSortBooks(filterChoice, filter, sortChoice,book_head);
                    }
                }
                else if(filterChoice==1){
                    printf("Enter sort choice (0->Title, 1->Author): ");
                    scanf("%d", &sortChoice);
                    filterAndSortBooks(filterChoice, filter, sortChoice,book_head);
                }
                printf("The filtered books has written to the txt file.\n");
                break;
            case 7:
                reverseBookList(&book_head);
                break;
            case 8:
                printf("Enter search choice (0->ISBN number, 1->Author, 2-> Title):");
                scanf("%d", &searchChoice);
                printf("Search value: ");
                scanf(" %[^\n]",searchValue);
                searchBooks(searchChoice, searchValue,book_head);
                break;
            case 9:
                printf(">You can borrow maximum 3 books<\n");
                printf("Do you want to borrow(1) or return(2) a book?: ");
                scanf("%d",&choice);
                printf("Enter ISBN: ");
                scanf("%s", isbn);
                printf("Enter your student ID: ");
                scanf("%d",&ID);

                if(choice==1){
                    borrowBook(isbn,book_head, student_head, ID);
                }
                else if(choice==2){
                    returnBook(isbn,book_head, student_head, ID);
                }
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 10.\n");
        }
    }
    return 0;
}