#include <node.h>
#include "status.h"

namespace tensorflow_node {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Integer;
using v8::Value;

Persistent<Function> Status::constructor;

Status::Status(TF_Status* status) : status_(status) {
}

Status::~Status() {
  TF_DeleteStatus(status_);
}

void Status::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Status"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "getCode", GetCode);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getMessage", GetMessage);
  NODE_SET_PROTOTYPE_METHOD(tpl, "set", Set);

  constructor.Reset(isolate, tpl->GetFunction());

  exports->Set(String::NewFromUtf8(isolate, "Status"),
               tpl->GetFunction());
}

void Status::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new Status(...)`
    TF_Status* status = TF_NewStatus();
    Status* obj = new Status(status);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `Status(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> instance =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(instance);
  }
}

void Status::GetCode(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Status* status = ObjectWrap::Unwrap<Status>(args.Holder());
  TF_Code code = TF_GetCode(status->status());
  args.GetReturnValue().Set(Integer::New(isolate, code));
}

void Status::GetMessage(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Status* status = ObjectWrap::Unwrap<Status>(args.Holder());
  const char* message = TF_Message(status->status());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, message));
}

void Status::Set(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Status* status = ObjectWrap::Unwrap<Status>(args.Holder());
  int64_t _code = args[0]->IntegerValue();
  TF_Code code = static_cast<TF_Code>(_code);
  String::Utf8Value s(args[1]);
  const char* _message = *s;
  TF_SetStatus(status->status(), code, _message);
  args.GetReturnValue().Set(Undefined(isolate));
}

}  // namespace demo
