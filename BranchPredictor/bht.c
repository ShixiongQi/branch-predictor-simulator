/*
 *	branch history table
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "bht.h"

 /*
  *	Inital the branch history table
  */
void BHT_Initial(BHT *BranchHistoryTable, uint32_t index_width, uint32_t history_width)
{
	BranchHistoryTable->attributes.index_width = index_width;
	BranchHistoryTable->attributes.history_width = history_width;
	BranchHistoryTable->attributes.history_num = (uint32_t)pow_2(index_width);
	BranchHistoryTable->attributes.history_max = (uint64_t)pow_2(history_width - 1);
	BranchHistoryTable->history = (uint64_t *)malloc(sizeof(uint64_t) * BranchHistoryTable->attributes.history_num);
	if (BranchHistoryTable->history == NULL)
		_error_exit("malloc")
	memset(BranchHistoryTable->history, 0, sizeof(uint64_t) * BranchHistoryTable->attributes.history_num);
}

/*
 *	Search the BranchPredictionTable for PC "addr" and make prediction
 *	input	:
 *		addr	:	PC
 *	return	:
 *		the history pattern of correspounding entry (at most 64 bits, hence uint64_t)
 */
uint64_t BHT_Search(BHT *BranchHistoryTable, uint32_t addr)
{
	uint32_t index = Get_Index(addr, BranchHistoryTable->attributes.index_width);
	return BranchHistoryTable->history[index];
}


/*
 *	Update the BranchPredictionTable
 *	input	:
 *		addr	:	PC
 *		result	:	struct "Result", the prediction and actual result
 */
void BHT_Update(BHT *BranchHistoryTable, uint32_t addr, Result result)
{
	uint32_t index = Get_Index(addr, BranchHistoryTable->attributes.index_width);
	uint64_t old_history = BranchHistoryTable->history[index];
	old_history = (old_history << 1) & (BranchHistoryTable->attributes.history_max);
	if (result.actual_taken == TAKEN)
		old_history++;
	BranchHistoryTable->history[index] = old_history;
}