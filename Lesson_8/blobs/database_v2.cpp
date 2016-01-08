#include <string>
#include "database_v2.h"
#include "logger.h"

DatabaseV2::DatabaseV2()
  : m_db_handler(nullptr)
  , m_db_statement(nullptr)
  , m_table_name("")
  , m_next_id(0) {
  open();
}

DatabaseV2::~DatabaseV2() {
  close();
}

/* Public API */
// ----------------------------------------------------------------------------
void DatabaseV2::addPerson(const ImagePerson& person) {
  long long id = m_next_id++;

  std::string statement = "INSERT INTO '";
  statement += m_table_name;
  statement += "' VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7);";  // Quiz: compose string from values directly
  DBG("Insert statement: %s", statement.c_str());

  prepareStatement(statement);

  // check for SQLITE_OK
  sqlite3_bind_int64(m_db_statement, 1, static_cast<sqlite3_int64>(id));  // sample cast
  sqlite3_bind_text(m_db_statement, 2, person.name.c_str(), person.name.length(), SQLITE_TRANSIENT);
  sqlite3_bind_text(m_db_statement, 3, person.last_name.c_str(), person.last_name.length(), SQLITE_TRANSIENT);
  sqlite3_bind_int(m_db_statement, 4, person.age);
  sqlite3_bind_text(m_db_statement, 5, person.gender.c_str(), person.gender.length(), SQLITE_TRANSIENT);
  sqlite3_bind_int(m_db_statement, 6, person.height);
  sqlite3_bind_double(m_db_statement, 7, person.weight);
  // TODO: image

  sqlite3_step(m_db_statement);
  sqlite3_finalize(m_db_statement);
}

ImagePerson DatabaseV2::readPerson(long long id) {
  // TODO: task 1: check row(id) exists in Database

  std::string statement = "SELECT * FROM '";
  statement += m_table_name;
  statement += "' WHERE ID == '";
  statement += std::to_string(id);
  statement += "';";
  DBG("Read statement: %s", statement.c_str());

  prepareStatement(statement);
  sqlite3_step(m_db_statement);

  long long check_id = sqlite3_column_int64(m_db_statement, 0);  // check id
  std::string name(reinterpret_cast<const char*>(sqlite3_column_text(m_db_statement, 1)));
  std::string last_name(reinterpret_cast<const char*>(sqlite3_column_text(m_db_statement, 2)));
  int age = sqlite3_column_int(m_db_statement, 3);
  std::string gender(reinterpret_cast<const char*>(sqlite3_column_text(m_db_statement, 4)));
  int height = sqlite3_column_int(m_db_statement, 5);
  double weight = sqlite3_column_double(m_db_statement, 6);
  // TODO: image

  sqlite3_finalize(m_db_statement);

  ImagePerson person(name, last_name, age, gender, height, weight);
  // TODO: person.setImage();
  return person;
}

void DatabaseV2::deletePerson(long long id) {
  // TODO: task 1: check row(id) exists in Database

  std::string statement = "DELETE FROM '";
  statement += m_table_name;
  statement += "' WHERE ID == '";
  statement += std::to_string(id);
  statement += "';";
  DBG("Delete statement: %s", statement.c_str());

  // TODO: task 2: decrement m_next_id if the row with max id has just been deleted
  //               or set it to zero in case Database has become empty

  prepareStatement(statement);
  sqlite3_step(m_db_statement);
  sqlite3_finalize(m_db_statement);
}

/* Private methods */
// ----------------------------------------------------------------------------
void DatabaseV2::open() {
  int code = sqlite3_open(DATABASE_NAME, &m_db_handler);
  if (code != SQLITE_OK || m_db_handler == nullptr) {
    ERR("Failed to open database");
  }
  sqlite3_limit(m_db_handler, SQLITE_LIMIT_SQL_LENGTH, 1000000);  // statement limit in bytes
  createTable("ImagePersons");
}

void DatabaseV2::createTable(const std::string& table_name) {
  m_table_name = table_name;

  std::string statement = "CREATE TABLE IF NOT EXISTS ";
  statement += table_name;
  statement += "('ID' INTEGER PRIMARY KEY AUTOINCREMENT, "
      "'Name' TEXT, "
      "'LastName' TEXT, "
      "'Age' INTEGER, "
      "'Gender' TEXT, "
      "'Height' INTEGER, "
      "'Weight' REAL, "
      "'Image' BLOB);";

  prepareStatement(statement);
  sqlite3_step(m_db_statement);
  sqlite3_finalize(m_db_statement);
}

void DatabaseV2::prepareStatement(const std::string& statement) {
  int n_bytes = static_cast<int>(statement.length());
  int code = sqlite3_prepare_v2(m_db_handler, statement.c_str(), n_bytes, &m_db_statement, nullptr);
}

void DatabaseV2::close() {
  sqlite3_close(m_db_handler);
  sqlite3_free(nullptr);
}

