#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include "logger.h"
#include "tinyxml.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/// @see http://www.curlpp.org/
/// @documentation: https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf
/// @see http://thecatapi.com/docs.html
/// @see XML parser: http://stackoverflow.com/questions/9387610/what-xml-parser-should-i-use-in-c
/// @see TinyXML: http://www.grinninglizard.com/tinyxmldocs/index.html

const char* URL_CATAPI = "http://thecatapi.com/api/images/get?format=xml&results_per_page=5";

const char* FILENAME_XML = "cats_response.xml";

struct Image {
  std::string url;
  std::string id;
  std::string source_url;
};

void processXmlDocument(TiXmlHandle& handler, std::vector<Image>* images);
Image processImage(TiXmlHandle& image);

std::ostream& operator << (std::ostream& out, const Image& image) {
  out << "Image {\n\turl=" << image.url
      << "\n\tid=" << image.id
      << "\n\tsource_url=" << image.source_url
      << "\n}";
  return out;
}

/* Main */
// ------------------------------------------------------------------------------------------------
int main(int args, char** argv) {
  DBG("[Lesson 13]: Http 1.3");

  std::fstream fout;
  fout.open(FILENAME_XML, std::fstream::out);
  fout << curlpp::options::Url(URL_CATAPI);
  fout.close();

  std::vector<Image> images;

  TiXmlDocument document(FILENAME_XML);
  bool result = document.LoadFile();
  if (result) {
    INF("TinyXML: Result is OK");
    TiXmlHandle handler(&document);
    processXmlDocument(handler, &images);
  } else {
    ERR("TinyXML: failed to load file %s", FILENAME_XML);
  }

  std::copy(images.begin(), images.end(), std::ostream_iterator<Image>(std::cout, "\n"));

  DBG("[Lesson 13]: Http 1.3 END");
  return 0;
}

/* Process XML document */
// ------------------------------------------------------------------------------------------------
void processXmlDocument(TiXmlHandle& handler, std::vector<Image>* array) {
  TiXmlHandle images = handler.FirstChild("response").FirstChild("data").FirstChild("images");

  int index = 0;
  TiXmlHandle item = images.Child("image", index);

  while (item.ToNode() != nullptr) {
    Image image = processImage(item);
    array->push_back(image);
    item = images.Child("image", ++index);
  }
}

Image processImage(TiXmlHandle& item) {
  // Quiz: rewite with FirstChild(<name>) instead
  TiXmlElement* url = item.Child(0).ToElement();
  TiXmlElement* id = item.Child(1).ToElement();
  TiXmlElement* source_url = item.Child(2).ToElement();

  Image image;
  image.url = std::string(url->GetText());
  image.id = std::string(id->GetText());
  image.source_url = std::string(source_url->GetText());
  return image;
}

