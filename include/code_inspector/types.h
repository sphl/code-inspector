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

#ifndef CODE_INSPECTOR_TYPES_H
#define CODE_INSPECTOR_TYPES_H

#include <set>
#include <utility>

namespace code_inspector {

using LineNumber = unsigned long;
using Lines = std::set<LineNumber>;
using LineRange = std::pair<LineNumber, LineNumber>;

using BBId = unsigned long;

}  // namespace code_inspector

#endif  // CODE_INSPECTOR_TYPES_H
