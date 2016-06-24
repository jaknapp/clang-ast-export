#include "KvltConsumerJsonWriter.h"

#include <iostream>
#include <sstream>

namespace ast_export {
namespace {
std::string JsonEscape(std::string input) {
  std::ostringstream ss;
  for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
    //C++98/03:
    //for (std::string::const_iterator iter = input.begin(); iter != input.end(); iter++) {
    switch (*iter) {
      case '\\': ss << "\\\\"; break;
      case '"': ss << "\\\""; break;
      case '/': ss << "\\/"; break;
      case '\b': ss << "\\b"; break;
      case '\f': ss << "\\f"; break;
      case '\n': ss << "\\n"; break;
      case '\r': ss << "\\r"; break;
      case '\t': ss << "\\t"; break;
      default: ss << *iter; break;
    }
  }
  return ss.str();
}
}
KvltConsumerJsonWriter::KvltConsumerJsonWriter() {
  // Initialize context stack
  has_children_stack_.push(false);
  is_object_stack_.push(false);
}

void KvltConsumerJsonWriter::ConsumeKey(std::string key) {
  std::cout << MaybeSeparatorForKey() << "\"" << JsonEscape(key) << "\":";
  has_children_stack_.top() = true;
  is_object_stack_.top() = true;
}

void KvltConsumerJsonWriter::ConsumeValue(std::string value) {
  std::cout << MaybeSeparatorForValue() << "\"" << JsonEscape(value) << "\"";
  has_children_stack_.top() = true;
  is_object_stack_.top() = false;
}

void KvltConsumerJsonWriter::ConsumeListOpen() {
  std::cout << MaybeSeparatorForValue() << "[";
  has_children_stack_.top() = true;
  has_children_stack_.push(false);
  is_object_stack_.push(false);
}

void KvltConsumerJsonWriter::ConsumeListClose() {
  std::cout << "]";
  has_children_stack_.pop();
  is_object_stack_.pop();
}

void KvltConsumerJsonWriter::ConsumeKvListOpen() {
  std::cout << MaybeSeparatorForValue() << "{";
  has_children_stack_.top() = true;
  has_children_stack_.push(false);
  is_object_stack_.push(false);
}

void KvltConsumerJsonWriter::ConsumeKvListClose() {
  std::cout << "}";
  has_children_stack_.pop();
  is_object_stack_.pop();
}

const char *KvltConsumerJsonWriter::MaybeSeparatorForValue() {
  bool is_writing_value_for_object = is_object_stack_.top();
  bool is_first_value = !has_children_stack_.top();
  //std::cout << "is_first_value: " << is_first_value 
  //  //<< " is_writing_value_for_object: " << is_writing_value_for_object 
  //  << " ";
  if (is_first_value || is_writing_value_for_object) {
    return "";
  }
  return ",";
}

const char *KvltConsumerJsonWriter::MaybeSeparatorForKey() {
  bool is_first_key = !has_children_stack_.top();
  if (is_first_key) {
    return "";
  }
  return ",";
}
}
