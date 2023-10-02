#include "drop_index_executor.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/drop_index_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"

RC DropIndexExecutor::execute(SQLStageEvent *sql_event)
{
  auto stmt    = sql_event->stmt();
  auto session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_INDEX,
      "DropTable executor can not run this command: %d",
      static_cast<int>(stmt->type)());
  DropIndexStmt *drop_index_stmt = static_cast<DropIndexStmt *>(stmt);
  auto           table_name      = drop_index_stmt->table_name();
  auto           index_name      = drop_index_stmt->index_name();
  auto           rc              = session->get_current_db()->find_table(table_name)->drop_index(index_name);
  return rc;
}