﻿/**
 * Copyright 2022 AntGroup CO., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#pragma once
#include <memory>
#include "lgraph/lgraph_rpc_client.h"

class LGraphPythonClient {
 public:
    LGraphPythonClient(const std::string& url, const std::string& user, const std::string& password)
        : client(std::make_shared<lgraph::RpcClient>(url, user, password)) {}

    ~LGraphPythonClient() {}

    std::pair<bool, std::string> LoadProcedure(const std::string& source_file,
                                            const std::string& procedure_type,
                                            const std::string& procedure_name,
                                            const std::string& code_type,
                                            const std::string& procedure_description,
                                            bool read_only,
                                            const std::string& graph = "default") {
        std::string result;
        bool ret = client->LoadProcedure(result, source_file, procedure_type,
                                         procedure_name, code_type, procedure_description,
                                         read_only, graph);
        return {ret, result};
    }

    std::pair<bool, std::string> CallProcedure(const std::string& procedure_type,
                                            const std::string& procedure_name,
                                            const std::string& param,
                                            double procedure_time_out = 0.0,
                                            bool in_process = false,
                                            const std::string& graph = "default",
                                            bool json_format = true) {
        std::string result;
        bool ret = client->CallProcedure(result, procedure_type, procedure_name,
                                         param, procedure_time_out, in_process, graph,
                                         json_format);
        return {ret, result};
    }

    std::pair<bool, std::string> ListProcedures(const std::string& procedure_type,
                                               const std::string& graph = "default") {
        std::string result;
        bool ret = client->ListProcedures(result, procedure_type, graph);
        return {ret, result};
    }

    std::pair<bool, std::string> DeleteProcedure(const std::string& procedure_type,
                                                  const std::string& procedure_name,
                                                  const std::string& graph = "default") {
        std::string result;
        bool ret = client->DeleteProcedure(result, procedure_type, procedure_name,
                                           graph);
        return {ret, result};
    }

    std::pair<bool, std::string> ImportSchemaFromFile(const std::string& schema_file,
                                                      const std::string& graph = "default",
                                                      bool json_format = true, double timeout = 0) {
        std::string result;
        bool ret = client->ImportSchemaFromFile(result, schema_file, graph, json_format, timeout);
        return {ret, result};
    }

    std::pair<bool, std::string> ImportDataFromFile(const std::string& conf_file,
                                                    const std::string& delimiter,
                                                    bool continue_on_error = false,
                                                    int thread_nums = 8, int skip_packages = 0,
                                                    const std::string& graph = "default",
                                                    bool json_format = true, double timeout = 0) {
        std::string result;
        bool ret =
            client->ImportDataFromFile(result, conf_file, delimiter, continue_on_error, thread_nums,
                                      skip_packages, graph, json_format, timeout);
        return {ret, result};
    }

    std::pair<bool, std::string> ImportSchemaFromContent(const std::string& schema,
                                                         const std::string& graph = "default",
                                                         bool json_format = true,
                                                         double timeout = 0) {
        std::string result;
        bool ret = client->ImportSchemaFromContent(result, schema, graph, json_format, timeout);
        return {ret, result};
    }

    std::pair<bool, std::string> ImportDataFromContent(
        const std::string& desc, const std::string& data, const std::string& delimiter,
        bool continue_on_error = false, int thread_nums = 8, const std::string& graph = "default",
        bool json_format = true, double timeout = 0) {
        std::string result;
        bool ret = client->ImportDataFromContent(result, desc, data, delimiter, continue_on_error,
                                                thread_nums, graph, json_format, timeout);
        return {ret, result};
    }

    std::pair<bool, std::string> CallCypher(const std::string& cypher,
                                            const std::string& graph = "default",
                                            bool json_format = true, double timeout = 0) {
        std::string result;
        bool ret = client->CallCypher(result, cypher, graph, json_format, timeout);
        return {ret, result};
    }

    void Logout() {
        client->Logout();
    }

    void Close() {
        client.reset();
    }

 private:
    std::shared_ptr<lgraph::RpcClient> client;
};
