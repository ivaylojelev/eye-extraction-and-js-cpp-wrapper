#pragma once

#include <nan.h>
extern "C" {
    //Our lib`s header
    #include "../lib/libopencvjs.h"
}
class OpenCvManager : public Nan::ObjectWrap {
	private:
			explicit OpenCvManager();
    		~OpenCvManager();

    		static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    		static Nan::Persistent<v8::Function> constructor;

    		/**
    		Methods go here
    		A few examples
    		static void SetPosition(const Nan::FunctionCallbackInfo<v8::Value>& info);
    		static void Hide(const Nan::FunctionCallbackInfo<v8::Value>& info);
    		static void Show(const Nan::FunctionCallbackInfo<v8::Value>& info);
    		**/

	public:
			static void Init(v8::Local<v8::Object> exports);
};

