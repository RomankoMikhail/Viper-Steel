#ifndef JSMETHODS_H_
#define JSMETHODS_H_

#include <duktape.h>
#include <plog/Log.h>

/*!
 * \deprecated
 */
[[deprecated]]
void JSSetupContext(duk_context* ctx, const unsigned& id);

#endif /* JSMETHODS_H_ */
