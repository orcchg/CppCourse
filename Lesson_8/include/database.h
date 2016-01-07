#ifndef DATABASE__H__
#define DATABASE__H__

#include "sqlite3.h"
#include "person.h"

/**
 * Persons:
 *  _____________________________________________________________________
 * |  ID  |  Name  |  LastName  |  Age  |  Gender  |  Height  |  Weight  |
 * |------|--------|------------|-------|----------|----------|----------|
 * |  1   |  Alex  |   Ivanov   |  27   |   Male   |   183    |   75.5   |
 * |------|--------|------------|-------|----------|----------|----------|
 * |  2   | Masha  |  Sokolova  |  19   |  Female  |   172    |   50.1   |
 * |------|--------|------------|-------|----------|----------|----------|
 * |______|________|____________|_______|__________|__________|__________|
 *
 * For SQLite3 data types: @see https://www.sqlite.org/datatype3.html
 */

static const char* DATABASE_NAME = "lesson_8_data.db";  // Quiz: why 'static' is necessary here ?

class Database {
public:
  Database();
  virtual ~Database();

  /**
   * Inserts a line of data into Database
   * @param person - Data of person
   */
  void addPerson(const Person& person);

  /**
   * Reads a line of data by it's ID
   * @param id - Identificator of line
   */
  Person readPerson(long long id);

  /**
   * Deletes a line from Database by ID
   * @param id - Identificator of line
   */
  void deletePerson(long long id);

private:
  sqlite3* m_db_handler;
  sqlite3_stmt* m_db_statement;
  std::string m_table_name;
  long long m_next_id;

  void open();
  void createTable(const std::string& table_name);
  void prepareStatement(const std::string& statement);
  void close();
};

#endif  // DATABASE__H__

