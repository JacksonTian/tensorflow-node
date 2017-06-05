#ifndef STATUS_H
#define STATUS_H

#include <node.h>
#include <node_object_wrap.h>
#include <tensorflow/c/c_api.h>

namespace tensorflow_node {

class Status : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  static void GetCode(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetMessage(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Set(const v8::FunctionCallbackInfo<v8::Value>& args);
  inline TF_Status* status() const { return status_; }

 private:
  explicit Status(TF_Status* status);
  ~Status();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  TF_Status* status_;
};

}  // namespace demo

#endif
