/*
 *	globle branch history register
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "ghr.h"


 /*
  *	Inital the global branch history table
  */
void GHR_Initial(GHR *GlobalBranchHistoryTable, uint32_t history_width)
{
	GlobalBranchHistoryTable->attributes.history_width = history_width;
	GlobalBranchHistoryTable->attributes.history_max = (uint64_t)pow_2(history_width - 1);
	GlobalBranchHistoryTable->history = 0;
}

/*
 *	Update the GlobalBranchHistoryTable
 *	input	:
 *		result	:	struct "Result", the prediction and actual result
 */
void GHR_Update(GHR *GlobalBranchHistoryTable, Result result)
{
	uint64_t old_history = GlobalBranchHistoryTable->history;
	old_history = (old_history << 1) & (GlobalBranchHistoryTable->attributes.history_max);
	if (result.actual_taken == TAKEN)
		old_history++;
	GlobalBranchHistoryTable->history = old_history;
}