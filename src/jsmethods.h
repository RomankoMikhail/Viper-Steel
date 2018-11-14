#ifndef JSMETHODS_H_
#define JSMETHODS_H_

#include <duktape.h>
#include <plog/Log.h>

void setup_js_context(duk_context* ctx, const unsigned& id);

#endif /* JSMETHODS_H_ */
