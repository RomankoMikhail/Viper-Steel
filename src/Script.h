#ifndef SCRIPT_H_
#define SCRIPT_H_

#include <duktape.h>
#include <plog/Log.h>

namespace Game
{

/*!
 * \brief Structure for containing flags and other variables, that should be accessed from duktape context or callback
 */
struct ScriptData
{
	//! Termination flag. If set to true - duktape callback function will report execution timeout error.
	bool terminate = false;
	ScriptData() = default;
};

/*!
 * \brief Class for loading, executing and controlling scripts.
 * \ingroup scripting
 *
 * \details Script class is intended for loading, executing and controlling ECMAScript code.
 */
class Script
{
private:

	duk_context* m_ctx;
	ScriptData m_data;

	Script(const Script&);
public:
	Script();

	/*!
	 * \brief Loads and evaluates ECMAScript from file
	 * \param path path to ECMAScript
	 *
	 * \throws std::runtime_error with evaluation error
	 */
	void loadFile(std::string path);

	/*!
	 * \brief Loads and evaluates ECMAScript from std::string
	 * \param src ECMAScript source code
	 *
	 * \throws std::runtime_error with evaluation error
	 */
	void loadSrc(std::string src);

	/*!
	 * \brief Binds C function to ES function.
	 *
	 * \param callback C function pointer
	 * \param name ES function name
	 * \param args number of arguments
	 */
	void bindFunction(duk_c_function callback, std::string name, int args);

	/*!
	 * \brief Sets ES context property variable to given value
	 *
	 * \param key property name
	 * \param value value
	 */
	void setProperty(std::string key, std::string value);

	/*!
	 * \brief Gets ES context property variable by name
	 *
	 * \param key property name
	 *
	 * \return property value
	 */
	std::string getProperty(std::string key);

	/*!
	 * \brief Sets ES context property variable to given value
	 *
	 * \param ctx duktape context pointer
	 * \param key property name
	 * \param value value
	 */
	static void setProperty(duk_context* ctx, std::string key, std::string value);

	/*!
	 * \brief Gets ES context property by name
	 *
	 * \param ctx duktape context pointer
	 * \param key property name
	 *
	 * \return property value
	 */
	static std::string getProperty(duk_context* ctx, std::string key);

	/*!
	 * \brief Calls ES function without parameters by name
	 *
	 * \param func ES function name
	 */
	void call(std::string func);

	/*!
	 * \brief Requests ES script termination
	 */
	void requestTermination();
	virtual ~Script();
};

} /* namespace Game */

#endif /* SCRIPT_H_ */
