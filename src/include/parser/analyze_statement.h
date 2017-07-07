//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// analyze_statement.h
//
// Identification: src/include/parser/analyze_statement.h
//
// Copyright (c) 2015-17, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>

#include "common/logger.h"
#include "common/sql_node_visitor.h"
#include "parser/sql_statement.h"
#include "parser/table_ref.h"

namespace peloton {
namespace parser {

class AnalyzeStatement : public SQLStatement {
 public:
  AnalyzeStatement()
      : SQLStatement(StatementType::ANALYZE),
        analyze_table(nullptr),
        analyze_columns(nullptr) {};

  virtual ~AnalyzeStatement() {}

  std::string GetTableName() const {
    if (analyze_table == nullptr) {
      return INVALID_NAME;
    }
    return analyze_table->GetTableName();
  }

  const std::vector<std::unique_ptr<char[]>>& GetColumnNames() const {
    if (analyze_columns == nullptr) {
      return NULL_COLUMN;
    }
    return (*analyze_columns);
  }

  std::string GetDatabaseName() const {
    if (analyze_table == nullptr) {
      return INVALID_NAME;
    }
    return analyze_table->GetDatabaseName();
  }

  virtual void Accept(SqlNodeVisitor* v) const override {
    v->Visit(this);
  }

  std::unique_ptr<parser::TableRef> analyze_table;
  std::unique_ptr<std::vector<std::unique_ptr<char[]>>> analyze_columns;

  const std::string INVALID_NAME = "";
  const std::vector<std::unique_ptr<char[]>> NULL_COLUMN = {};
};

}  // namespace parser
}  // namespace peloton
