#include "Book.hpp"
#include <iomanip>
#include <utility>

//Constructor
Book::Book(std::string_view title,
     std::string_view author,
     std::string_view isbn,
     double           price) : _isbn(isbn),
                               _title(title),
                               _author(author),
                               _price(price) {}

//Insertion and Extraction
std::ostream & operator<<( std::ostream & stream, const Book & book ) {
  std::string isbn = book.isbn();
  std::string title = book.title();
  std::string author = book.author();
  double price = book.price();
  stream << std::quoted(isbn) << ", "
         << std::quoted(title) << ", "
         << std::quoted(author) << ", "
         << price << std::endl;
  return stream;
}
std::istream & operator>>( std::istream & stream,       Book & book ) {
  Book temp;
  char delimiter = ',';
  stream >> std::quoted(temp._isbn) >> delimiter
         >> std::quoted(temp._title) >> delimiter
         >> std::quoted(temp._author) >> delimiter
         >> temp._price;
  if(stream) {
    book = std::move(temp);
  }
  return stream;
}

//Comparison
bool operator==( const Book & lhs, const Book & rhs ) {
  return lhs.isbn() == rhs.isbn()
      && lhs.title() == rhs.title()
      && lhs.author() == rhs.author()
      && std::abs(lhs.price() - rhs.price()) < .0001;
  }
bool operator< ( const Book & lhs, const Book & rhs ) {
  if(auto result = lhs.isbn().compare(rhs.isbn()); result != 0 ) {
    return result < 0;
  }
  if(auto result = lhs.author().compare(rhs.author()); result != 0 ) {
    return result < 0;
  }
  if(auto result = lhs.title().compare(rhs.title()); result != 0 ) {
    return result < 0;
  }
  if(std::abs(lhs.price() - rhs.price()) > .0001) {
    return lhs.price() < rhs.price();
  }
  return false;
}

// Queries
std::string Book::isbn  () const { return _isbn; }
std::string Book::title () const { return _title; }
std::string Book::author() const { return _author; }
double      Book::price () const { return _price; }

// Mutators
void Book::isbn  ( std::string_view newIsbn   ) { _isbn = newIsbn; }
void Book::title ( std::string_view newTitle  ) {_title = newTitle; }
void Book::author( std::string_view newAuthor ) { _author = newAuthor; }
void Book::price ( double           newPrice  ) { _price = newPrice; }

// Relational Operators
bool operator!=( const Book & lhs, const Book & rhs ) { return !(lhs == rhs); }
bool operator<=( const Book & lhs, const Book & rhs ) { return !(rhs < lhs); }
bool operator> ( const Book & lhs, const Book & rhs ) { return (rhs < lhs); }
bool operator>=( const Book & lhs, const Book & rhs ) { return !(lhs < rhs); }
