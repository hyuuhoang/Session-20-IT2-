#include <stdio.h>
#include <string.h>

#define MAX 100

// C?u tr�c S�ch
typedef struct {
    char id[20];     // M? s�ch
    char name[100];  // T�n s�ch
    char author[100];// T�c gi?
    float price;     // Gi� ti?n
    char genre[50];  // Th? lo?i
} Book;

// Khai b�o m?ng s�ch v� s? l�?ng s�ch
Book books[MAX];
int n = 0;

// H�m nh?p th�ng tin m?t cu?n s�ch
void inputBook(Book *book) {
    getchar(); // Lo?i b? k? t? th?a
    printf("Nh?p m? s�ch: ");
    fgets(book->id, sizeof(book->id), stdin);
    book->id[strcspn(book->id, "\n")] = 0; // X�a k? t? xu?ng d?ng

    printf("Nh?p t�n s�ch: ");
    fgets(book->name, sizeof(book->name), stdin);
    book->name[strcspn(book->name, "\n")] = 0;

    printf("Nh?p t�n t�c gi?: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = 0;

    printf("Nh?p gi� ti?n: ");
    scanf("%f", &book->price);
    getchar();

    printf("Nh?p th? lo?i: ");
    fgets(book->genre, sizeof(book->genre), stdin);
    book->genre[strcspn(book->genre, "\n")] = 0;
}

// H�m hi?n th? th�ng tin m?t cu?n s�ch
void displayBook(Book book) {
    printf("M? s�ch: %s\n", book.id);
    printf("T�n s�ch: %s\n", book.name);
    printf("T�c gi?: %s\n", book.author);
    printf("Gi� ti?n: %.2f\n", book.price);
    printf("Th? lo?i: %s\n", book.genre);
    printf("------------------------\n");
}

// H�m hi?n th? to�n b? s�ch
void displayAllBooks() {
    if (n == 0) {
        printf("Danh s�ch s�ch tr?ng.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("S�ch #%d:\n", i + 1);
        displayBook(books[i]);
    }
}

// H�m th�m s�ch v�o v? tr�
void addBookAtPosition() {
    int pos;
    printf("Nh?p v? tr� c?n th�m (1 - %d): ", n + 1);
    scanf("%d", &pos);
    if (pos < 1 || pos > n + 1) {
        printf("V? tr� kh�ng h?p l?!\n");
        return;
    }
    for (int i = n; i >= pos; i--) {
        books[i] = books[i - 1];
    }
    printf("Nh?p th�ng tin s�ch m?i:\n");
    inputBook(&books[pos - 1]);
    n++;
}

// H�m x�a s�ch theo m? s�ch
void deleteBookById() {
    char id[20];
    getchar();
    printf("Nh?p m? s�ch c?n x�a: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].id, id) == 0) {
            found = 1;
            for (int j = i; j < n - 1; j++) {
                books[j] = books[j + 1];
            }
            n--;
            printf("�? x�a s�ch v?i m? %s.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Kh�ng t?m th?y s�ch v?i m? %s.\n", id);
    }
}

// H�m c?p nh?t th�ng tin s�ch theo m? s�ch
void updateBookById() {
    char id[20];
    getchar();
    printf("Nh?p m? s�ch c?n c?p nh?t: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].id, id) == 0) {
            printf("Nh?p th�ng tin m?i cho s�ch:\n");
            inputBook(&books[i]);
            printf("C?p nh?t th�nh c�ng!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Kh�ng t?m th?y s�ch v?i m? %s.\n", id);
    }
}

// H�m s?p x?p s�ch theo gi� (t�ng/gi?m)
void sortBooksByPrice(int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((ascending && books[i].price > books[j].price) ||
                (!ascending && books[i].price < books[j].price)) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
    printf("S?p x?p th�nh c�ng!\n");
}

// H�m t?m ki?m s�ch theo t�n
void searchBookByName() {
    char name[100];
    getchar();
    printf("Nh?p t�n s�ch c?n t?m: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(books[i].name, name)) {
            displayBook(books[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Kh�ng t?m th?y s�ch v?i t�n \"%s\".\n", name);
    }
}

// H�m hi?n th? menu
void showMenu() {
    printf("\nMENU\n");
    printf("1. Nh?p s? l�?ng v� th�ng tin s�ch\n");
    printf("2. Hi?n th? th�ng tin s�ch\n");
    printf("3. Th�m s�ch v�o v? tr�\n");
    printf("4. X�a s�ch theo m? s�ch\n");
    printf("5. C?p nh?t th�ng tin s�ch theo m? s�ch\n");
    printf("6. S?p x?p s�ch theo gi� (1: T�ng, 0: Gi?m)\n");
    printf("7. T?m ki?m s�ch theo t�n s�ch\n");
    printf("8. Tho�t\n");
    printf("L?a ch?n c?a b?n: ");
}

// H�m ch�nh
int main() {
    int choice, ascending;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Nh?p s? l�?ng s�ch: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Nh?p th�ng tin s�ch #%d:\n", i + 1);
                inputBook(&books[i]);
            }
            break;
        case 2:
            displayAllBooks();
            break;
        case 3:
            addBookAtPosition();
            break;
        case 4:
            deleteBookById();
            break;
        case 5:
            updateBookById();
            break;
        case 6:
            printf("S?p x?p theo gi� (1: T�ng, 0: Gi?m): ");
            scanf("%d", &ascending);
            sortBooksByPrice(ascending);
            break;
        case 7:
            searchBookByName();
            break;
        case 8:
            printf("Tho�t ch��ng tr?nh.\n");
            break;
        default:
            printf("L?a ch?n kh�ng h?p l?!\n");
        }
    } while (choice != 8);

    return 0;
}

