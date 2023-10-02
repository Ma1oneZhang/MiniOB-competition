#include "event/sql_event.h"

class DropIndexExecutor
{
public:
  DropIndexExecutor()          = default;
  virtual ~DropIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};