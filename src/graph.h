#ifndef GRAPH_H
#define GRAPH_H

#include <node.h>
#include <node_object_wrap.h>
#include <tensorflow/c/c_api.h>

namespace tensorflow_node {

class Graph : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  // static void GetCode(const v8::FunctionCallbackInfo<v8::Value>& args);
  // static void GetMessage(const v8::FunctionCallbackInfo<v8::Value>& args);
  inline TF_Graph* graph() const { return graph_; }

 private:
  explicit Graph(TF_Graph* graph);
  ~Graph();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  TF_Graph* graph_;
};

}  // namespace demo

#endif
