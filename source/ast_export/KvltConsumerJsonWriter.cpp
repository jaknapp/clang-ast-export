#include "KvltConsumerJsonWriter.h"

#include <iostream>

namespace ast_export {
void JsonWriter::ConsumeKey(std::string key) {}
void JsonWriter::ConsumeValue(std::string value) {}
void JsonWriter::ConsumeListOpen() {}
void JsonWriter::ConsumeListClose() {}
void JsonWriter::ConsumeKvListOpen() {}
void JsonWriter::ConsumeKvListClose() {}
}