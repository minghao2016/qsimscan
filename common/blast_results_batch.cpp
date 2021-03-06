//////////////////////////////////////////////////////////////////////////////
//// This software module is developed by SciDM (Scientific Data Management) in 1998-2015
//// 
//// This program is free software; you can redistribute, reuse,
//// or modify it with no restriction, under the terms of the MIT License.
//// 
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//// 
//// For any questions please contact Denis Kaznadzey at dkaznadzey@yahoo.com
//////////////////////////////////////////////////////////////////////////////

#pragma warning (disable: 4786)
#include <platform.h>
#include "blast_results_batch.h"
#include "align.h"
#include "filters.h"

SimMergerBase  BlastResultsBatch :: null_merger_;

BlastResultsBatch :: BlastResultsBatch (int keep_per_query, int keep_per_target,  int rep_len, int rep_perc, bool triangle_only, SimMergerBase& merger)
:
MergingResultStorage (merger, keep_per_query, keep_per_target),
total_found_ (0),
passed_repeats_ (0),
rep_percent_ (rep_perc),
rep_len_ (rep_len),
rep_buf_ (NULL),
triangle_only_ (triangle_only)
{
    if (rep_len_)
    {
        try
        {
            rep_buf_ = new int [rep_len_];
        }
        catch (std::bad_alloc&)
        {
        }
        if (!rep_buf_) 
            Error (MemoryRerror);
    }
}

bool BlastResultsBatch :: match_found  (NN_SEQ& xseq, NN_SEQ& yseq, BATCH* batches, int batch_no, int matches)
{
    // for precluster - type searches:
    // We use the fact that fragment ids are fed in order, as they were obtained from set, where they are kept in order.
    // While searching, the Ids will come in strictly increasing order, which gives the possibility to cut out
    // those similarities that belong to orphan (last) triangles in striped search.
    if (triangle_only_)
        if (xseq.uid >= yseq.uid)
            return false;

    total_found_ ++;

    // By stupid but established convention, X IS QUERY while processing the results
    // so we'll swap batch here
    int tot_blen = swap_batches (batches, batch_no); // now x is query

    // recalculate the score
    float nscore = nu_score_b (yseq.seq, xseq.seq, batches, batch_no, &matches);
    float chi2score = nu_all_chi2_b (yseq.seq, xseq.seq, batches, batch_no);

    // filter results by repeats
    if (rep_len_)
    {
        int max_idx = nu_offs_score_b (yseq.seq, xseq.seq, batches, batch_no, rep_len_, rep_buf_);
        if ((rep_buf_ [max_idx] * 100) / matches > rep_percent_)
            return false;
    }
    passed_repeats_ ++;

    // save the result
    return add_result (yseq.uid, xseq.uid, yseq.rev?true:false, (int) matches - (int) (tot_blen - matches), matches, chi2score, 0, nscore, tot_blen, tot_blen, batch_no, batches, xseq.seq, xseq.uid, xseq.len);
}
