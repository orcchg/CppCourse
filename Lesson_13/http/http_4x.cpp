#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "logger.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

struct Customer {
  int customer_id;
  int store_id;
  int address_id;
  std::string first_name;
  std::string last_name;
  std::string email;
  std::string create_date;
  std::string last_update;
  bool activebool;
  int active;
};

Customer createCustomer();
std::string convertToJson(const Customer& customer);
void upload(const std::string& body);

std::ostream& operator << (std::ostream& out, const Customer& customer) {
  out << "Customer {\n\tcustomer_id=" << customer.customer_id
      << "\n\tstore_id=" << customer.store_id
      << "\n\taddress_id=" << customer.address_id
      << "\n\tfirst_name=" << customer.first_name
      << "\n\tlast_name=" << customer.last_name
      << "\n\temail=" << customer.email
      << "\n\tcreate_date=" << customer.create_date
      << "\n\tlast_update=" << customer.last_update
      << "\n\tactivebool=" << customer.activebool
      << "\n\tactive=" << customer.active
      << "\n}";
  return out;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 4x");

  // POST - create a new Customer
  Customer customer = createCustomer();
  std::string request_body = convertToJson(customer);
  upload(request_body);

  DBG("[Lesson 13]: Http 4x END");
  return 0;
}

Customer createCustomer() {
  Customer customer;
  customer.customer_id = 601;
  customer.store_id = 1;
  customer.address_id = 5;
  customer.first_name = "Maxim";
  customer.last_name="Alov";
  customer.email = "mary.smith@sakilacustomer.org";
  customer.create_date = "2006-02-14";
  customer.last_update = "2013-05-26 14:49:45.738";
  customer.activebool = true;
  customer.active = 1;
  return customer;
}

std::string convertToJson(const Customer& customer) {  // Quiz: write unit-test to check correctness
  std::ostringstream oss;
  oss << "{\n"
      << "\"customer_id\":" << customer.customer_id << ","
      << "\"store_id\":" << customer.store_id << ","
      << "\"address_id\":\"" << customer.address_id << "\","
      << "\"first_name\":\"" << customer.first_name << "\","
      << "\"last_name\":\"" << customer.last_name << "\","
      << "\"email\":\"" << customer.email << "\","
      << "\"create_date\":\"" << customer.create_date << "\","
      << "\"last_update\":\"" << customer.last_update << "\","
      << "\"activebool\":\"" << std::boolalpha << customer.activebool << std::noboolalpha << "\","
      << "\"active\":\"" << customer.active << "\""
      << "\n}";
  return oss.str();
}

void upload(const std::string& body) {
  INF("Posting: %s", body.c_str());
  curlpp::Easy request;
    
  request.setOpt(new curlpp::options::Url("http://127.0.0.1:9000/customer/add/")); 
  request.setOpt(new curlpp::options::Verbose(true)); 
    
  std::list<std::string> header; 
  header.push_back("Content-Type: application/json"); 
    
  request.setOpt(new curlpp::options::HttpHeader(header)); 
  request.setOpt(new curlpp::options::PostFields(body.c_str()));
  request.setOpt(new curlpp::options::PostFieldSize(body.size()));
    
  request.perform(); 
}

