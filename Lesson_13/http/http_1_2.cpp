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

const char* URL_CATAPI = "http://thecatapi.com/api/images/get?format=xml&results_per_page=3";

const char* FILENAME_XML = "cats_response.xml";

struct Image {
  std::string url;
  std::string id;
  std::string source_url;
};

void processXmlDocument(TiXmlDocument& document, std::vector<Image>* images);
Image processImage(TiXmlElement* image);

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
  DBG("[Lesson 13]: Http 1.2");

  std::fstream fout;
  fout.open(FILENAME_XML, std::fstream::out);
  fout << curlpp::options::Url(URL_CATAPI);
  fout.close();

  std::vector<Image> images;

  TiXmlDocument document(FILENAME_XML);
  bool result = document.LoadFile();
  if (result) {
    INF("TinyXML: Result is OK");
    processXmlDocument(document, &images);
  } else {
    ERR("TinyXML: failed to load file %s", FILENAME_XML);
  }

  std::copy(images.begin(), images.end(), std::ostream_iterator<Image>(std::cout, "\n"));

  DBG("[Lesson 13]: Http 1.2 END");
  return 0;
}

/* Process XML document */
// ------------------------------------------------------------------------------------------------
void processXmlDocument(TiXmlDocument& document, std::vector<Image>* array) {
  TiXmlElement* root = document.FirstChildElement("response");
  if (root != nullptr) {
    TiXmlElement* data = root->FirstChildElement("data");
    if (data != nullptr) {
      TiXmlElement* images = data->FirstChildElement("images");
      if (images != nullptr) {
        TiXmlElement* item_1 = images->FirstChildElement("image");
        if (item_1 != nullptr) {
          Image image_1 = processImage(item_1);
          array->push_back(image_1);
          TiXmlElement* item_2 = item_1->NextSiblingElement("image");
          if (item_2 != nullptr) {
            Image image_2 = processImage(item_2);
            array->push_back(image_2);
            TiXmlElement* item_3 = item_2->NextSiblingElement("image");
            if (item_3 != nullptr) {
              Image image_3 = processImage(item_3);
              array->push_back(image_3);
              // stop
            } else {
              ERR("No sibling element: image");
            }
          } else {
            ERR("No sibling element: image");
          }
        } else {
          ERR("No sibling element: image");
        }
      } else {
        ERR("No child element: images");
      }
    } else {
      ERR("No child element: data");
    }
  } else {
    ERR("No child element: response");
  }
}

Image processImage(TiXmlElement* item) {
  Image image;
  TiXmlElement* url = item->FirstChildElement("url");
  if (url != nullptr) {
    image.url = std::string(url->GetText());
    TiXmlElement* id = url->NextSiblingElement("id");
    if (id != nullptr) {
      image.id = std::string(id->GetText());
      TiXmlElement* source_url = id->NextSiblingElement("source_url");
      if (source_url != nullptr) {
        image.source_url = std::string(source_url->GetText());
      } else {
        ERR("No sibling element: source_url");
      }
    } else {
      ERR("No sibling element: id");
    }
  } else {
    ERR("No child element: url");
  }
  return image;
}

