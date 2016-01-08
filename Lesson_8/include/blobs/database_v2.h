#ifndef DATABASE__H__
#define DATABASE__H__

#include "sqlite3.h"
#include "image_person.h"

/**
 * ImagePersons:
 *  _______________________________________________________________________________
 * |  ID  |  Name  |  LastName  |  Age  |  Gender  |  Height  |  Weight  |  Image  |
 * |------|--------|------------|-------|----------|----------|----------|---------|
 * |  1   |  Alex  |   Ivanov   |  27   |   Male   |   183    |   75.5   |  *****  |
 * |------|--------|------------|-------|----------|----------|----------|---------|
 * |  2   | Masha  |  Sokolova  |  19   |  Female  |   172    |   50.1   |  *****  |
 * |------|--------|------------|-------|----------|----------|----------|---------|
 * |______|________|____________|_______|__________|__________|__________|_________|
 *
 * For SQLite3 data types: @see https://www.sqlite.org/datatype3.html
 *
 * BLOB example: http://www.sqlite.org/cvstrac/wiki?p=BlobExample
 */

static const char* DATABASE_NAME = "lesson_8_data_v2.db";  // Quiz: why 'static' is necessary here ?

class DatabaseV2 {
public:
  DatabaseV2();
  virtual ~DatabaseV2();

  /**
   * Inserts a line of data into Database
   * @param person - Data of person
   */
  void addPerson(const ImagePerson& person);

  /**
   * Reads a line of data by it's ID
   * @param id - Identificator of line
   */
  ImagePerson readPerson(long long id);

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

