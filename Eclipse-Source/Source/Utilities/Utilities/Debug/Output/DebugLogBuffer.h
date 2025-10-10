#pragma once

#include <streambuf>
#include <functional>

#include "DebugLogger.h"

namespace Eclipse
{
	class DebugLogBuf : public std::streambuf
	{
	protected:
		int overflow(int c) override
		{
			if (c != EOF) {
				char z = c;
				buffer.push_back(z);

				if (z == '\n') {
					FlushBuffer();
				}
			}
			return c;
		}

		int sync() override {
			FlushBuffer();
			return 0;
		}

	private:
		void FlushBuffer() {
			if (!buffer.empty()) {
				LOG(buffer);

				buffer.clear();
			}
		}

		std::string buffer;
	};
}