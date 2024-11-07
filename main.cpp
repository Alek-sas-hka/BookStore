#include <iostream>
#include <string>
#include "BookStore.h"
#include <windows.h>


void displayMenu() {
  std::cout << "Выберите опцию:\n";
  std::cout << "1. Добавить книгу\n";
  std::cout << "2. Удалить книгу\n";
  std::cout << "3. Найти книгу по названию\n";
  std::cout << "4. Показать все книги (сортировка по названию/автору/году)\n";
  std::cout << "5. Найти книги в ценовом диапазоне\n";
  std::cout << "6. Выйти\n";
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  BookStore store;
  int choice;

  do {
    displayMenu();
    std::cout << "Введите номер опции: ";
    std::cin >> choice;

    switch (choice) {
      case 1: { // Добавить книгу
        std::string title, author;
        int year;
        double price;

        std::cout << "Введите название книги: ";
        std::cin.ignore(); // Очистка буфера перед вводом строки
        std::getline(std::cin, title);
        std::cout << "Введите автора книги: ";
        std::getline(std::cin, author);
        std::cout << "Введите год издания: ";
        std::cin >> year;
        std::cout << "Введите цену: ";
        std::cin >> price;

        store.addBook(Book(title, author, year, price));
        std::cout << "Книга успешно добавлена! \n";
        break;
      }
      case 2: { // Удалить книгу
        if (store.isEmpty()) {  // Проверка на пустоту
          std::cout << "В магазине пока нет книг";
          std::cout << std::endl;
          break;
        }

        std::string title;
        std::cout << "Введите название книги для удаления: ";
        std::cin.ignore();
        std::getline(std::cin, title);

        if (store.removeBook(title)) {
          std::cout << "Книга успешно удалена!\n";
        } else {
          std::cout << "Книга не найдена!\n";
        }
        break;
      }
      case 3: { // Найти книгу по названию
        if (store.isEmpty()) {  // Проверка на пустоту
          std::cout << "В магазине пока нет книг";
          std::cout << std::endl;
          break;
        }
        std::string title;
        std::cout << "Введите название книги для поиска: ";
        std::cin.ignore();
        std::getline(std::cin, title);

        Book* book = store.findBook(title);
        if (book) {
          std::cout << "Найдена книга:\n";
          std::cout << "Название: " << book->getTitle() << "\n";
          std::cout << "Автор: " << book->getAuthor() << "\n";
          std::cout << "Год издания: " << book->getYear() << "\n";
          std::cout << "Цена: " << book->getPrice() << " руб.\n";
        } else {
          std::cout << "Книга не найдена!\n";
        }
        break;
      }
      case 4: { // Показать все книги
        if (store.isEmpty()) {  // Проверка на пустоту
          std::cout << "В магазине пока нет книг";
          std::cout << std::endl;
          break;
        }
        int sortOption;
        std::cout << "Выберите критерий сортировки:\n";
        std::cout << "1. По названию\n";
        std::cout << "2. По автору\n";
        std::cout << "3. По году издания\n";
        std::cout << "Введите номер опции: ";
        std::cin >> sortOption;

        SortType sortType;
        if (sortOption == 1) {
          sortType = SortType::Title;
        } else if (sortOption == 2) {
          sortType = SortType::Author;
        } else if (sortOption == 3) {
          sortType = SortType::Year;
        } else {
          std::cout << "Неверный выбор.\n";
          break;
        }

        std::vector<Book> books = store.listBooks(sortType);
        for (const auto& book : books) {
          std::cout << "Название: " << book.getTitle()
                    << ", Автор: " << book.getAuthor()
                    << ", Год: " << book.getYear()
                    << ", Цена: " << book.getPrice() << " руб.\n";
        }
        break;
      }
      case 5: { // Найти книги в ценовом диапазоне
        if (store.isEmpty()) {  // Проверка на пустоту
          std::cout << "В магазине пока нет книг";
          std::cout << std::endl;
          break;
        }
        double minPrice, maxPrice;
        std::cout << "Введите минимальную цену: ";
        std::cin >> minPrice;
        std::cout << "Введите максимальную цену: ";
        std::cin >> maxPrice;

        std::vector<Book> booksInRange = store.findBooksInPriceRange(minPrice, maxPrice);
        if (booksInRange.empty()) {
          std::cout << "Нет книг в заданном диапазоне цен.\n";
        } else {
          std::cout << "Найдены книги в заданном диапазоне цен:\n";
          for (const auto& book : booksInRange) {
            std::cout << "Название: " << book.getTitle()
                      << ", Автор: " << book.getAuthor()
                      << ", Год: " << book.getYear()
                      << ", Цена: " << book.getPrice() << " руб.\n";
          }
        }
        break;
      }
      case 6: // Выйти
        std::cout << "Досвидания! Приходите ещё.\n";
        break;
      default:
        std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
    }

    std::cout << std::endl;
  } while (choice != 6);

  return 0;
}

