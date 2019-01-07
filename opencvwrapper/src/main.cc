#include <node.h>
#include <nan.h>
#include <v8.h>

#include "OpenCvManager.h"

using v8;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

void ExtractEyes(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	// Check the number of arguments passed.
	int* imData = new int[args.length() - 2];
	for (int i = 0; i < args.length() - 2; i++) imData[i] = args[i]->NumberValue();
	int width = args.length() - 2;
	int height = args.length() - 1;
	eyeObj eyes = getEyePatches(imData, width, height);
	eye left = eyes->left;
	eye right = eyes->right;
	HandleScope handle_scope;

	// Create a new empty array.
	Handle<Array> leftPatch = Array::New(left->width*left->height*4);
	for (int i = 0; i < left->width*left->height * 4) leftPatch->Set(i, Integer::New(left->patch[i]));

	 Handle<Array> rightPatch = Array::New(right->width*right->height * 4);
	 for (int i = 0; i < right->width*right->height * 4) rightPatch->Set(i, Integer::New(right->patch[i]));

	 Handle<Object> leftEye = Object::New(isolate);
	 leftEye->Set(String::NewFromUtf8(isolate, "patch"), leftPatch);
	 leftEye->Set(String::NewFromUtf8(isolate, "imagex"), Number::New(left->imagex));
	 leftEye->Set(String::NewFromUtf8(isolate, "imagey"), Number::New(left->imagey));
	 leftEye->Set(String::NewFromUtf8(isolate, "width"), Number::New(left->width));
	 leftEye->Set(String::NewFromUtf8(isolate, "height"), Number::New(left->height));
	 
	 Handle<Object> rightEye = Object::New(isolate); 
	 rightEye->Set(String::NewFromUtf8(isolate, "patch"), rightPatch);
	 rightEye->Set(String::NewFromUtf8(isolate, "imagex"), Number::New(right->imagex));
	 rightEye->Set(String::NewFromUtf8(isolate, "imagey"), Number::New(right->imagey));
	 rightEye->Set(String::NewFromUtf8(isolate, "width"), Number::New(right->width));
	 rightEye->Set(String::NewFromUtf8(isolate, "height"), Number::New(right->height));

	 Handle<Object> eyeObj = Object::New(isolate);
	 eyeObj->Set(String::NewFromUtf8(isolate, "left"), leftEye);
	 eyeObj->Set(String::NewFromUtf8(isolate, "right"), rightEye);
	 args.GetReturnValue().Set(eyeObj);
}
void OpenCvManager::Init(v8::Local<v8::Object> exports)
{
	NODE_SET_METHOD(exports, "extractEyes", extractEyes);
}
void InitAll(v8::Local<v8::Object> exports){
    /**
    Export objects by calling ObjName::Init(export)
    **/
	OpenCvManager::Init(exports)
}

NODE_MODULE(opencvwrapper, InitAll);
