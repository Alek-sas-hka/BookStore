#include <windows.h>

#include <iostream>
#include <limits>
#include <string>

#include "BookStore.h"

void displayMenu() {
  std::cout << "Выберите опцию:\n"
            << "1. Добавить книгу\n"
            << "2. Удалить книгу\n"
            << "3. Найти книгу по названию\n"
            << "4. Показать все книги (сортировка по названию/автору/году)\n"
            << "5. Найти книги в ценовом диапазоне\n"
            << "6. Выйти\n";
}

int getChoice() {
  int choice;
  std::cout << "Введите номер опции: ";
  std::cin >> choice;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                    '\n');  // Очистка буфера
    return -1;  // Возвращаем некорректное значение
  }
  return choice;
}

void addBook(BookStore& store) {
  std::string title, author;
  int year;
  double price;

  std::cout << "Введите название книги: ";
  std::cin.ignore();  // Очистка буфера перед вводом строки
  std::getline(std::cin, title);
  std::cout << "Введите автора книги: ";
  std::getline(std::cin, author);

  // Проверка на ввод года издания
  while (true) {
    std::cout << "Введите год издания: ";
    std::cin >> year;

    if (std::cin.fail() || year <= 0) {
      std::cin.clear();  // Сбрасываем состояние ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Очищаем буфер
      std::cout << "Ошибка ввода. Пожалуйста, введите корректный год.\n";
    } else {
      break;  // Ввод корректен, выходим из цикла
    }
  }

  // Проверка на ввод цены
  while (true) {
    std::cout << "Введите цену: ";
    std::cin >> price;

    if (std::cin.fail() || price < 0) {
      std::cin.clear();  // Сбрасываем состояние ошибки
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Очищаем буфер
      std::cout << "Ошибка ввода. Пожалуйста, введите корректную цену.\n";
    } else {
      break;  // Ввод корректен, выходим из цикла
    }
  }

  store.addBook(Book(title, author, year, price));
  std::cout << "Книга успешно добавлена!\n";
}

void removeBook(BookStore& store) {
  std::string title;
  std::cout << "Введите название книги для удаления: ";
  std::cin.ignore();
  std::getline(std::cin, title);

  if (store.removeBook(title)) {
    std::cout << "Книга успешно удалена!\n";
  } else {
    std::cout << "Книга не найдена!\n";
  }
}

void findBook(BookStore& store) {
  std::string title;
  std::cout << "Введите название книги для поиска: ";
  std::cin.ignore();
  std::getline(std::cin, title);

  Book* book = store.findBook(title);
  if (book) {
    std::cout << "Найдена книга:\n"
              << "Название: " << book->getTitle() << "\n"
              << "Автор: " << book->getAuthor() << "\n"
              << "Год издания: " << book->getYear() << "\n"
              << "Цена: " << book->getPrice() << " руб.\n";
  } else {
    std::cout << "Книга не найдена!\n";
  }
}

void listBooks(BookStore& store) {
  int sortOption;
  std::cout << "Выберите критерий сортировки:\n"
            << "1. По названию\n"
            << "2. По автору\n"
            << "3. По году издания\n"
            << "Введите номер опции: ";
  std::cin >> sortOption;

  SortType sortType;
  switch (sortOption) {
    case 1:
      sortType = SortType::Title;
      break;
    case 2:
      sortType = SortType::Author;
      break;
    case 3:
      sortType = SortType::Year;
      break;
    default:
      std::cout << "Неверный выбор.\n";
      return;
  }

  std::vector<Book> books = store.listBooks(sortType);
  for (const auto& book : books) {
    std::cout << "Название: " << book.getTitle()
              << ", Автор: " << book.getAuthor() << ", Год: " << book.getYear()
              << ", Цена: " << book.getPrice() << " руб.\n";
  }
}

void findBooksInPriceRange(BookStore& store) {
  double minPrice, maxPrice;
  std::cout << "Введите минимальную цену: ";
  std::cin >> minPrice;
  std::cout << "Введите максимальную цену: ";
  std::cin >> maxPrice;

  std::vector<Book> booksInRange =
      store.findBooksInPriceRange(minPrice, maxPrice);
  if (booksInRange.empty()) {
    std::cout << "Нет книг в заданном диапазоне цен.\n";
  } else {
    std::cout << "Найдены книги в заданном диапазоне цен:\n";
    for (const auto& book : booksInRange) {
      std::cout << "Название: " << book.getTitle()
                << ", Автор: " << book.getAuthor()
                << ", Год: " << book.getYear() << ", Цена: " << book.getPrice()
                << " руб.\n";
    }
  }
}

int main() {
  SetConsoleOutputCP(CP_UTF8);
  BookStore store;
  int choice;

  do {
    displayMenu();
    choice = getChoice();  // Получаем выбор пользователя

    switch (choice) {
      case 1:
        addBook(store);
        break;  // Добавить книгу
      case 2:
        removeBook(store);
        break;  // Удалить книгу
      case 3:
        findBook(store);
        break;  // Найти книгу
      case 4:
        listBooks(store);
        break;  // Показать все книги
      case 5:
        findBooksInPriceRange(store);
        break;  // Найти книги в ценовом диапазоне
      case 6:
        std::cout << "До свидания! Приходите ещё.\n";
        break;  // Выйти
      default:
        std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        break;
    }

    std::cout << std::endl;
  } while (choice != 6);

  return 0;
}
