#include "vcpkg/packages/curl_x64-windows/include/curl/curl.h"
#include "windows.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

namespace fs = std::filesystem;

// Callback function writes data to a std::ostream
size_t write_data(void *ptr, size_t size, size_t nmemb, std::ostream *stream) {
  size_t written =
      stream->write(reinterpret_cast<char *>(ptr), size * nmemb).tellp();
  return written;
}

// Function to download a file using libcurl
void download_file(const std::string &url, const std::string &outfilename) {
  CURL *curl;
  FILE *fp;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    fs::create_directories(fs::path(outfilename).parent_path());

    fp = fopen(outfilename.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);
  } else {
    std::cout << "Error: Could not initialize curl" << std::endl;
    std::cerr << "Error: Could not initialize curl" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Installer for Remove-Guns and UniMixins" << std::endl;

  fs::path outdir = fs::path(std::getenv("USERPROFILE")) /
                    "AppData\\Roaming\\minecraftedu"; // Default
  if (argc >= 2) {
    outdir = argv[1]; // Use filesystem path
  }

  // Check if outdir is a file
  if (fs::is_regular_file(outdir)) {
    outdir = outdir.parent_path(); // Use the parent directory if it's a file
  }

  std::string removeguns_url =
      "https://github.com/mayankpatibandla/Remove-Guns/releases/download/1.0.0/"
      "removeguns-1.0.0.jar";
  std::string unimixins_url =
      "https://github.com/LegacyModdingMC/UniMixins/releases/download/0.1.17/"
      "unimixins-all-1.7.10-0.1.17.jar";

  download_file(removeguns_url, outdir.string() + "\\removeguns-1.0.0.jar");
  download_file(unimixins_url,
                outdir.string() + "\\unimixins-all-1.7.10-0.1.17.jar");

  return 0;
}
