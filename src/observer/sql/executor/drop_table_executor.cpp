
#include "sql/executor/drop_table_executor.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/drop_table_stmt.h"
#include "sql/stmt/stmt.h"

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
  auto stmt    = sql_event->stmt();
  auto session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_TABLE,
      "DropTable executor can not run this command: %d",
      static_cast<int>(stmt->type)());
  DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);
  auto           table_name      = drop_table_stmt->table_name();
  auto           rc              = session->get_current_db()->drop_table(table_name);
  return rc;
}