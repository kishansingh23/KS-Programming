#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to hold book details */
typedef struct Book {
    int id;
    char title[100];
    char author[100];
}Book;

/* Function to add a book */
void addBook() {
    Book b;
    FILE *fp = fopen("library.dat", "ab"); // append in binary file
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // to consume newline

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0'; // remove newline

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Book added successfully!\n");
}


/* Function to display all books */
void displayBooks() {
    Book b;
    FILE *fp = fopen("library.dat", "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    printf("\n--- Library Books ---\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("ID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
    }
    fclose(fp);
}
/* Function to search for a book by ID */
void searchBook() {
    int id, found = 0;
    Book b; 
    FILE *fp = fopen("library.dat", "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("Book Found!\n");
            printf("ID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Book not found!\n");
    fclose(fp);
}

/* Function to delete a book by ID */
void deleteBook() {
    int id, found = 0;
    Book b;
    FILE *fp = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            found = 1;
        } else {
            fwrite(&b, sizeof(b), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}




int main() {
    int choice;

    while (1) {
        printf("\n||===== \"Library Management System\" =====||\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
