#ifndef CLANG_AST_EXPORT_KVLTSTREAM_H
#define CLANG_AST_EXPORT_KVLTSTREAM_H

namespace ast_export {
class KvltConsumer;
}

namespace ast_export {
class KvltStream {
public:
  explicit KvltStream(KvltConsumer *consumer);
  KvltConsumer *Consumer();
private:
  KvltStream();
  KvltConsumer *consumer_;
};
}

#endif // CLANG_AST_EXPORT_KVLTSTREAM_H
