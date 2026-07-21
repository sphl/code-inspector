/**
 * Copyright 2026 Stephan Lipp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <code_inspector/bb_info.h>

using namespace code_inspector;

BBInfo::BBInfo(BBId id, Lines lineNumbers, LineRange lineRange)
    : id(id), lineNumbers(std::move(lineNumbers)), lineRange(std::move(lineRange)) {}

BBId BBInfo::getId() const { return id; }

const Lines &BBInfo::getLineNumbers() const { return lineNumbers; }

const LineRange &BBInfo::getLineRange() const { return lineRange; }

bool BBInfo::operator==(const BBInfo &rhs) const {
    return id == rhs.id && lineNumbers == rhs.lineNumbers && lineRange == rhs.lineRange;
}

bool BBInfo::operator!=(const BBInfo &rhs) const { return !(rhs == *this); }

bool BBInfo::operator<(const BBInfo &rhs) const { return id < rhs.id; }
