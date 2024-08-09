#pragma once

#include <iostream>

std::string getFileBase64Content(const char* path, bool urlencoded = false);
std::string base64_to_url_encoded(const std::string& base64_str);