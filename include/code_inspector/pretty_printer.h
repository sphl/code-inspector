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

#ifndef CODE_INSPECTOR_PRETTY_PRINTER_H
#define CODE_INSPECTOR_PRETTY_PRINTER_H

#include <code_inspector/func_info.h>
#include <code_inspector/io.h>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace code_inspector {

class Printer {
  public:
    /**
     * This pure virtual method is used to format the given vector of FuncInfo objects and map of BBId to BBId sets
     * (inter-procedural CFG) to a string representation.
     * @param funcInfos Vector of FuncInfo objects.
     * @param icfgInfos Map of BBId to BBId sets (iCFG).
     * @return A string representation of the formatted information.
     */
    virtual std::string format(std::vector<FuncInfo> &funcInfos,
                               std::optional<std::map<BBId, std::set<BBId>>> icfgInfos) = 0;

    /**
     * This method writes the formatted information to a file.
     * @param filepath String containing the path of the file.
     * @param funcInfos Vector of FuncInfo objects.
     * @param icfgInfos Map of BBId to BBId sets (iCFG).
     */
    void printToFile(std::string &filepath,
                     std::vector<FuncInfo> &funcInfos,
                     std::optional<std::map<BBId, std::set<BBId>>> icfgInfos =
                             std::nullopt) {  // NOLINT(google-default-arguments)
        io::writeFile(filepath, format(funcInfos, std::move(icfgInfos)));
    }
};

class JSONPrinter : public Printer {
  public:
    /**
     * This method formats the given vector of FuncInfo objects and map of BBId to BBId sets (inter-procedural CFG) to
     * a JSON string.
     * @param funcInfos Vector of FuncInfo objects.
     * @param icfgInfos Map of BBId to BBId sets (iCFG).
     * @return A JSON string representation of the formatted information.
     */
    std::string format(std::vector<FuncInfo> &funcInfos,
                       std::optional<std::map<BBId, std::set<BBId>>> icfgInfos) override;
};

}  // namespace code_inspector

#endif  // CODE_INSPECTOR_PRETTY_PRINTER_H
