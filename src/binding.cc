// hello.cc
#include <node.h>
#include <tensorflow/c/c_api.h>

#include "status.h"
#include "graph.h"
#include "session.h"

#define CONST_INT(n, v) \
  obj->Set(String::NewFromUtf8(isolate, n), Integer::New(isolate, v));

namespace tensorflow_node {

using v8::FunctionCallbackInfo;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Version(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, TF_Version()));
}

void FinishOperation(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, TF_Version()));
}

void InitDataType(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Object> obj = Object::New(isolate);
  CONST_INT("FLOAT", TF_FLOAT);
  CONST_INT("DOUBLE", TF_DOUBLE);
  CONST_INT("INT32", TF_INT32);  // Int32 tensors are always in 'host' memory.
  CONST_INT("UINT8", TF_UINT8);
  CONST_INT("INT16", TF_INT16);
  CONST_INT("INT8", TF_INT8);
  CONST_INT("STRING", TF_STRING);
  CONST_INT("COMPLEX64", TF_COMPLEX64); // Single-precision complex
  CONST_INT("COMPLEX", TF_COMPLEX);   // Old identifier kept for API backwards compatibility
  CONST_INT("INT64", TF_INT64);
  CONST_INT("BOOL", TF_BOOL);
  CONST_INT("QINT8", TF_QINT8);     // Quantized int8
  CONST_INT("QUINT8", TF_QUINT8);    // Quantized uint8
  CONST_INT("QINT32", TF_QINT32);    // Quantized int32
  CONST_INT("BFLOAT16", TF_BFLOAT16);  // Float32 truncated to 16 bits.  Only for cast ops.
  CONST_INT("QINT16", TF_QINT16);    // Quantized int16
  CONST_INT("QUINT16", TF_QUINT16);   // Quantized uint16
  CONST_INT("UINT16", TF_UINT16);
  CONST_INT("COMPLEX128", TF_COMPLEX128);  // Double-precision complex
  CONST_INT("HALF", TF_HALF);
  CONST_INT("RESOURCE", TF_RESOURCE);

  exports->Set(String::NewFromUtf8(isolate, "DataType"),
               obj);
}

void InitStatusCode(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Object> obj = Object::New(isolate);

  CONST_INT("OK", TF_OK);
  CONST_INT("CANCELLED", TF_CANCELLED);
  CONST_INT("UNKNOWN", TF_UNKNOWN);
  CONST_INT("INVALID_ARGUMENT", TF_INVALID_ARGUMENT);
  CONST_INT("DEADLINE_EXCEEDED", TF_DEADLINE_EXCEEDED);
  CONST_INT("NOT_FOUND", TF_NOT_FOUND);
  CONST_INT("ALREADY_EXISTS", TF_ALREADY_EXISTS);
  CONST_INT("PERMISSION_DENIED", TF_PERMISSION_DENIED);
  CONST_INT("UNAUTHENTICATED", TF_UNAUTHENTICATED);
  CONST_INT("RESOURCE_EXHAUSTED", TF_RESOURCE_EXHAUSTED);
  CONST_INT("FAILED_PRECONDITION", TF_FAILED_PRECONDITION);
  CONST_INT("ABORTED", TF_ABORTED);
  CONST_INT("OUT_OF_RANGE", TF_OUT_OF_RANGE);
  CONST_INT("UNIMPLEMENTED", TF_UNIMPLEMENTED);
  CONST_INT("INTERNAL", TF_INTERNAL);
  CONST_INT("UNAVAILABLE", TF_UNAVAILABLE);
  CONST_INT("DATA_LOSS", TF_DATA_LOSS);
  exports->Set(String::NewFromUtf8(isolate, "Code"),
               obj);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "version", Version);
  NODE_SET_METHOD(exports, "finishOperation", FinishOperation);

  InitDataType(exports);

  InitStatusCode(exports);

  Status::Init(exports);
  Graph::Init(exports);
}

NODE_MODULE(addon, init)

}  // namespace tensorflow_node
