#include "OpenCvManager.h"

Nan::Persistent<v8::Function> OpenCvManager::constructor;


OpenCvManager::OpenCvManager(){

}

OpenCvManager::~OpenCvManager() {
}


void OpenCvManager::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("OpenCvManager").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  //Nan::SetPrototypeMethod(tpl, "setPosition", SetPosition);
  //Nan::SetPrototypeMethod(tpl, "hide", Hide);
  //Nan::SetPrototypeMethod(tpl, "show", Show);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("OpenCvManager").ToLocalChecked(), tpl->GetFunction());

}

void OpenCvManager::Hide(const Nan::FunctionCallbackInfo<v8::Value>& info){
	OpenCvManager* obj = ObjectWrap::Unwrap<OpenCvManager>(info.Holder());
	//obj is used as this
}
void OpenCvManager::Show(const Nan::FunctionCallbackInfo<v8::Value>& info){
	OpenCvManager* obj = ObjectWrap::Unwrap<OpenCvManager>(info.Holder());
	//obj is used as this
}


/**
**/
void OpenCvManager::SetPosition(const Nan::FunctionCallbackInfo<v8::Value>& info){
    //Get the passed in parameters from info
	int x = info[0]->IsUndefined() ? 0 : info[0]->Uint32Value();
	int y = info[1]->IsUndefined() ? 0 : info[1]->Uint32Value();
	OpenCvManager* obj = ObjectWrap::Unwrap<OpenCvManager>(info.Holder());

}

/**
JS Constructor call for OpenCvManager
**/
void OpenCvManager::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new OpenCvManager(...)
    OpenCvManager* obj = new OpenCvManager();

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `OpenCvManager(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}
