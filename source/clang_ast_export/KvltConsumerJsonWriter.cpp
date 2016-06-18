#include "KvltConsumerJsonWriter.h"

#include <iostream>

namespace ast_export {
KvltConsumerJsonWriter::KvltConsumerJsonWriter() {
  // Initialize context stack
  has_children_stack_.push(false);
  is_object_stack_.push(false);
}

void KvltConsumerJsonWriter::ConsumeKey(std::string key) {
  std::cout << MaybeSeparatorForKey() << "\"" << key << "\":";
  has_children_stack_.top() = true;
}

void KvltConsumerJsonWriter::ConsumeValue(std::string value) {
  std::cout << MaybeSeparatorForValue() << "\"" << value << "\"";
  has_children_stack_.top() = true;
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
  is_object_stack_.push(true);
}

void KvltConsumerJsonWriter::ConsumeKvListClose() {
  std::cout << "}";
  has_children_stack_.pop();
  is_object_stack_.pop();
}

const char *KvltConsumerJsonWriter::MaybeSeparatorForValue() {
  bool is_writing_value_for_object = is_object_stack_.top();
  bool is_first_value = !has_children_stack_.top();
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
