// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "3rdparty/rapidjson/include/rapidjson/fwd.h"

#include "../Formatter.h"

namespace threading { namespace formatter {

/**
  * A thread-safe class for converting values into a JSON representation
  * and vice versa.
  */
class JSON : public Formatter {
public:
	enum TimeFormat {
		TS_EPOCH,	// Doubles that represents seconds from the UNIX epoch.
		TS_ISO8601,	// ISO 8601 defined human readable timestamp format.
		TS_MILLIS	// Milliseconds from the UNIX epoch.  Some consumers need this (e.g., elasticsearch).
		};

	JSON(threading::MsgThread* t, TimeFormat tf);
	~JSON() override;

	bool Describe(ODesc* desc, threading::Value* val, const string& name = "") const override;
	bool Describe(ODesc* desc, int num_fields, const threading::Field* const * fields,
	                      threading::Value** vals) const override;
	threading::Value* ParseValue(const string& s, const string& name, TypeTag type, TypeTag subtype = TYPE_ERROR) const override;

private:

	rapidjson::Value BuildJSON(rapidjson::Document& doc, Value* val, const string& name = "") const;

	TimeFormat timestamps;
	bool surrounding_braces;
};

}}
