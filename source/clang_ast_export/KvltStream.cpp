#include "KvltStream.h"

#include "KvltConsumer.h"

namespace ast_export {
KvltStream::KvltStream(KvltConsumer *consumer) : consumer_(consumer) {}
KvltConsumer *KvltStream::Consumer() {
  return consumer_;
}
}
