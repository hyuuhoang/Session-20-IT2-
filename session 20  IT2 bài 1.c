#include <stdio.h>
#include <string.h>

#define MAX 100

// C?u trúc Sách
typedef struct {
    char id[20];     // M? sách
    char name[100];  // Tên sách
    char author[100];// Tác gi?
    float price;     // Giá ti?n
    char genre[50];  // Th? lo?i
} Book;

// Khai báo m?ng sách và s? lý?ng sách
Book books[MAX];
int n = 0;

// Hàm nh?p thông tin m?t cu?n sách
void inputBook(Book *book) {
    getchar(); // Lo?i b? k? t? th?a
    printf("Nh?p m? sách: ");
    fgets(book->id, sizeof(book->id), stdin);
    book->id[strcspn(book->id, "\n")] = 0; // Xóa k? t? xu?ng d?ng

    printf("Nh?p tên sách: ");
    fgets(book->name, sizeof(book->name), stdin);
    book->name[strcspn(book->name, "\n")] = 0;

    printf("Nh?p tên tác gi?: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = 0;

    printf("Nh?p giá ti?n: ");
    scanf("%f", &book->price);
    getchar();

    printf("Nh?p th? lo?i: ");
    fgets(book->genre, sizeof(book->genre), stdin);
    book->genre[strcspn(book->genre, "\n")] = 0;
}

// Hàm hi?n th? thông tin m?t cu?n sách
void displayBook(Book book) {
    printf("M? sách: %s\n", book.id);
    printf("Tên sách: %s\n", book.name);
    printf("Tác gi?: %s\n", book.author);
    printf("Giá ti?n: %.2f\n", book.price);
    printf("Th? lo?i: %s\n", book.genre);
    printf("------------------------\n");
}

// Hàm hi?n th? toàn b? sách
void displayAllBooks() {
    if (n == 0) {
        printf("Danh sách sách tr?ng.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("Sách #%d:\n", i + 1);
        displayBook(books[i]);
    }
}

// Hàm thêm sách vào v? trí
void addBookAtPosition() {
    int pos;
    printf("Nh?p v? trí c?n thêm (1 - %d): ", n + 1);
    scanf("%d", &pos);
    if (pos < 1 || pos > n + 1) {
        printf("V? trí không h?p l?!\n");
        return;
    }
    for (int i = n; i >= pos; i--) {
        books[i] = books[i - 1];
    }
    printf("Nh?p thông tin sách m?i:\n");
    inputBook(&books[pos - 1]);
    n++;
}

// Hàm xóa sách theo m? sách
void deleteBookById() {
    char id[20];
    getchar();
    printf("Nh?p m? sách c?n xóa: ");
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
            printf("Ð? xóa sách v?i m? %s.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Không t?m th?y sách v?i m? %s.\n", id);
    }
}

// Hàm c?p nh?t thông tin sách theo m? sách
void updateBookById() {
    char id[20];
    getchar();
    printf("Nh?p m? sách c?n c?p nh?t: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(books[i].id, id) == 0) {
            printf("Nh?p thông tin m?i cho sách:\n");
            inputBook(&books[i]);
            printf("C?p nh?t thành công!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Không t?m th?y sách v?i m? %s.\n", id);
    }
}

// Hàm s?p x?p sách theo giá (tãng/gi?m)
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
    printf("S?p x?p thành công!\n");
}

// Hàm t?m ki?m sách theo tên
void searchBookByName() {
    char name[100];
    getchar();
    printf("Nh?p tên sách c?n t?m: ");
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
        printf("Không t?m th?y sách v?i tên \"%s\".\n", name);
    }
}

// Hàm hi?n th? menu
void showMenu() {
    printf("\nMENU\n");
    printf("1. Nh?p s? lý?ng và thông tin sách\n");
    printf("2. Hi?n th? thông tin sách\n");
    printf("3. Thêm sách vào v? trí\n");
    printf("4. Xóa sách theo m? sách\n");
    printf("5. C?p nh?t thông tin sách theo m? sách\n");
    printf("6. S?p x?p sách theo giá (1: Tãng, 0: Gi?m)\n");
    printf("7. T?m ki?m sách theo tên sách\n");
    printf("8. Thoát\n");
    printf("L?a ch?n c?a b?n: ");
}

// Hàm chính
int main() {
    int choice, ascending;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Nh?p s? lý?ng sách: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Nh?p thông tin sách #%d:\n", i + 1);
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
            printf("S?p x?p theo giá (1: Tãng, 0: Gi?m): ");
            scanf("%d", &ascending);
            sortBooksByPrice(ascending);
            break;
        case 7:
            searchBookByName();
            break;
        case 8:
            printf("Thoát chýõng tr?nh.\n");
            break;
        default:
            printf("L?a ch?n không h?p l?!\n");
        }
    } while (choice != 8);

    return 0;
}

