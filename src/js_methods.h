#ifndef JS_METHODS_H_
#define JS_METHODS_H_

#include <duktape.h>
#include <plog/Log.h>

void js_setup_context(duk_context* ctx, const unsigned& id);

#endif /* JS_METHODS_H_ */
